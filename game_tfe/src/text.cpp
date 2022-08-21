#include "game_tfe/text.h"

#include <mutex>
#include <iostream>

#include "freetype2/ft2build.h"
#include "freetype2/freetype/freetype.h"
#include "freetype2/freetype/ftglyph.h"
#include "freetype2/freetype/ftoutln.h"

inline size_t Coords(size_t column, size_t row, size_t width) {
    return row * width + column;
}


static void WriteToBuffer(unsigned char* buffer, size_t buffer_width, FT_Bitmap& bitmap, long long x, long long y)
{
    for(int row = 0; row < bitmap.rows; ++row) {
        for(int col = 0; col < bitmap.width; ++col) {
            buffer[Coords(col+x, row+y, buffer_width)] =  bitmap.buffer[Coords(col,row,bitmap.width)];
        }
    }
}

void compute_string_bbox(FT_BBox *abbox, std::vector<FT_Glyph>& glyphs, std::vector<FT_Vector>& position)
{
    FT_BBox bbox;
    FT_BBox glyph_bbox;

    bbox.xMin = bbox.yMin = 32000;
    bbox.xMax = bbox.yMax = -32000;

    for(int n = 0; n < glyphs.size(); ++n) {
        FT_Glyph_Get_CBox(glyphs[n], ft_glyph_bbox_pixels, &glyph_bbox);
        glyph_bbox.xMin += position[n].x;
        glyph_bbox.xMax += position[n].x;
        glyph_bbox.yMin += position[n].y;
        glyph_bbox.yMax += position[n].y;

        if(glyph_bbox.xMin < bbox.xMin) {
            bbox.xMin = glyph_bbox.xMin;
        }

        if(glyph_bbox.yMin < bbox.yMin) {
            bbox.yMin = glyph_bbox.yMin;
        }

        if(glyph_bbox.xMax > bbox.xMax) {
            bbox.xMax = glyph_bbox.xMax;
        }

        if(glyph_bbox.yMax > bbox.yMax) {
            bbox.yMax = glyph_bbox.yMax;
        }
    }

    if(bbox.xMin > bbox.xMax) {
        bbox.xMin = 0;
        bbox.xMax = 0;
        bbox.yMin = 0;
        bbox.yMax = 0;
    }

    *abbox = bbox;
}

static FT_Library library;

static std::mutex freetype_lock;
 
static bool freetype_initialized{false};

void DrawText(
        Geometry<9>& out, 
        RVector<2>* dim_out,
        RVector<3> coordinate, 
        RVector<4> color, 
        std::string& text,
        unsigned int pt,
        unsigned int screen_width,
        unsigned int screen_height
        )
{
    DrawText(out, dim_out, coordinate, color, text, pt, screen_width, screen_height,  TextAlignment::LEFT);
}

void DrawText(
        Geometry<9>& out, 
        RVector<2>* dim_out,
        RVector<3> coordinate, 
        RVector<4> color, 
        std::string& text,
        unsigned int pt,
        unsigned int screen_width,
        unsigned int screen_height,
        TextAlignment alignment
        )
{
    freetype_lock.lock();
    FT_Error error;
    if(!freetype_initialized) {
        FT_Error error = FT_Init_FreeType(&library);
        if(error) {
            std::cerr << "DrawText:Error initailizing FreeType Library. Exiting" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        freetype_initialized = true;
    }

    FT_Face face;

    error = FT_New_Face( library, "/usr/share/fonts/liberation-mono/LiberationMono-Regular.ttf", 0, &face);
    if(error) {
        std::cerr << "DrawText:Error Creating new Face. Exiting" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    error = FT_Set_Char_Size(face, 0, pt * 64, screen_width, screen_height);
    if(error) {
        std::cerr << "DrawText:Error Setting Char Size. Exiting" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    FT_GlyphSlot slot = face->glyph;

    std::vector<FT_Glyph> glyphs;
    std::vector<FT_Vector> pos;

    int pen_x = 0;
    int pen_y = 0;

    FT_Bool use_kerning = FT_HAS_KERNING(face);
    FT_UInt previous = 0;

    for(int n = 0; n < text.size(); ++n) {
        FT_UInt glyph_index = FT_Get_Char_Index(face, text[n]);

        if(use_kerning && previous && glyph_index) {
            FT_Vector delta;
            FT_Get_Kerning(face, previous, glyph_index, FT_KERNING_DEFAULT, &delta);
            pen_x += delta.x >> 6;
        }

        pos.push_back(FT_Vector { .x = pen_x, .y = pen_y });
        error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
        if(error)
            continue;

        glyphs.emplace_back();
        error = FT_Get_Glyph(face->glyph, &(glyphs.back()));

        if(error)
            continue;

        pen_x += slot->advance.x >> 6;
        previous = glyph_index;
    }

    FT_BBox string_bbox;
    compute_string_bbox(&string_bbox, glyphs, pos);

    long long string_width = string_bbox.xMax - string_bbox.xMin;
    long long string_height = string_bbox.yMax - string_bbox.yMin;

    std::array<RVector<2>, 4> tex_coords;

    std::array<size_t, 2> offset;

    unsigned char* block = out.GetAtlas()->GetNextFit(string_width, string_height, sizeof(unsigned char), tex_coords, offset);

    for(int n = 0; n < glyphs.size(); ++n) {
        FT_Glyph image;
        FT_Vector pen { .x = pos[n].x, .y = pos[n].y };
        image = glyphs[n];

        unsigned int x = offset[0] + pos[n].x;

        error = FT_Glyph_To_Bitmap(&image, FT_RENDER_MODE_NORMAL, &pen, 0);
        if(!error) {
            FT_BitmapGlyph bit = (FT_BitmapGlyph) image;

            WriteToBuffer(block, out.GetAtlas()->GetWidth(), bit->bitmap, x, 0);

            // write glyph
        }
        FT_Done_Glyph(image);
        glyphs[n] = nullptr;

    }

    switch(alignment) {
        case TextAlignment::CENTER:
            coordinate[0] -= string_width / 2.0f;
            coordinate[1] -= string_height / 2.0f;
            break;
        case TextAlignment::LEFT:
            break;
    }

    CreateRectangle3D(out, coordinate, color, string_width, string_height, tex_coords[1], tex_coords[0], tex_coords[3], tex_coords[2]);

    if(dim_out != nullptr){
        (*dim_out)[0] = string_width;
        (*dim_out)[1] = string_height;
    }
    FT_Done_Face(face);

    freetype_lock.unlock();
}
