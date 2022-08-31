# Design of 2048 Clone

This clone was made using a couple designed principles I wanted to try out.

- Not every aspect *needs* to be a class or associated with a class

Pure Object Orientated Design prefers associated functions with data they mutate and creating
inheritance hierarchies to handle variation of behavior. Unassociated methods or static methods are
generally reserved for rare sitatuations where the methods are not mutating its object or its a pure
function such as math functions on primitives. 

There are number of non-API, static methods in the various implementation files. However, the only
function only api is drawing text (DrawText()). The DrawText API is very simple as the only
requirement is to generate character glyph runs, place the runs in a texture atlas, and add the
generated vertices to a geometry buffer. Without cache consideration between draw calls, drawing
text does not require any state (beyond the library itself, which is held as a static variable
behind a mutex). A much more feature complete version would potentially see this being transitioned
to being a class. 

- Separation of concerns, especially across dependency barriers

Different aspects of the application are grouped and designed around each other. OpenGL is separated
into the classes GLProgram, GLShader, and GLBuffer. The GameBoard and GameSqaure comprise the game
logic. Game2048 uses GLFW, maintains current state of the game, and dispatches input events.

## Potential Considerations in the future

### Moving to Vulkan

OpenGL was chosen to the be the rendering specification of this application as it is both supported
on multiple operating systems and a rather simple API compared to its successor, Vulkan. However,
OpenGL support has been deprecated in Mac OS. In order to properly support Mac OS, a metal
version should be written. However, MoltenVK is a Vulkan Portability implementation which allows
running Vulkan applications on Metal on Mac OS. Moving to MoltenVK would potentially permit writing
one version of the game for all wanted targets, Mac OS, Windows, and Linux, with potential for ports
to iOS, iPadOS, and Android.

### Text Rendering

The current text generation is both too simplistic and incomplete. FreeType does not support
properly text shaping for my complex font rendering. For best results, a font must be check to
ensure it works before using it in the game.

Using the native Font rendering library, if present, for an operating system should be considered
for both simpler compilation and offering better integration into the look and feel of the operating
system.

### Caching

Many aspects of the game could be cached for improved rendering performance. Ideally, only work is
done if necessary. To help with performance, rendering should be potentially split between
pre-rendering and rendering.

#### Split Rendering into Multiple Stages

There should be at least two stages for rendering. First stage is a pre-rendering stage where the
position change, dimension change, content change, etc is considered and required changes cache
information without generating the end geometry if possible.

After pre-rendering, the rendering pass generates all geometry information needed for rendering.

#### Geometry Buffering

The Geometry buffer itself should be an aspect of the caching mechanism. The Geometry buffer, amoung
other items, contains an dynamic resizable indicies buffer and a dynamic resizable vertices buffer.
Currently, the geometry generator algorithms add indicies and vertices to the end of the geometry
buffer during the render pass. A future data structure and algortihm would see the Geometry buffer
adding fix sizes to itself at the request of the rendering algorhtm, returing a view to the vertices
and indicies buffer which is used by the geoemtry algorithm to place requried vertices and
indicies. The rendering algorithms then cache the view and modify it during the rendering pass as
needed. As an another prepass before rendering or integrated into the pre-rendering pass, the size
changes and new dimensions of the buffer will be gathered from all rendered objects. This data is
passed to the geometry buffer to resize itself and the various views to itself for hold the new
information (potentially doing raw memory copies in the process). The benefit of this architecture
would be the reuse of preallocated buffers when geometry does not change while allowing for resizing
the buffer without needing to query each geometry object to create to vertices and indicies.

#### Text Caching

Depending on the mechanism behind text rendering, there are different optomization choices.
Rendering full glyph runs using CoreText, HarfBuzz, or DirectWrite to Bitmaps, placed in a texture
atlas, and mapped to screen has very little opportunity of optomization beyond not regenerating the
text every draw call. 

Recording glyphs individually to a font atlas which is then mapped to quads which are layed out
appriopriately later will reduce the foot print of text. Further investigation into CoreText,
DriectWrite, and HarfBuzz is needed to see if the positioning of the glyphs can be extracted and
stored for later quad generation over immediate glyph run rendering.

Both styles of rendering will benefit from using signed distance fields instead of storing as
straight red bitmaps in the texture atlas.

