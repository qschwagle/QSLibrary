# 2048 Clone

## Description

2048 is a simple single player sliding tile puzzle video game written by Gabriele Circulli. It was
released on March 9th, 2014. The wikipedia article on the game can be found
[here][2048-wikipedia]. The original game can be found [here](https://github.com/gabrielecirulli/2048).

[2048-wikipedia]: https://en.wikipedia.org/wiki/2048_(video_game)

## How to play

The game is played by using the WASD or arrow keys to move the squares up, left, down, or right 
respectively. The moving squares will move to the next possible squares. Two squares will merge if 
they are the same value, but will not merge with a square that was generated from merging squares in 
the same action. The merge square will be in the next free square location. Moving squares will take 
priority over merging squares and so squares will move before merging. Each merge square value adds 
to the current score of the game. The objective is to achieve the highest scores. The game will
detect if the player is out of moves. If out of moves, an end game screen is presented where the
player may start a new game by pressing the new game button. A new game can be started at any time
by pressing the new game button in the right hand corner above the game board. The scores are not
saved between application sessions.

## About This Clone

This clone is meant as a "From Scratch" application. While the original is written for the web with
html, css, and js, this application is built using C++ and personal libraries: [LinAlg](/linalg/README.md)
and [Geometry](/geometry/README.md) along with third party libraries [GLFW](https://www.glfw.org/),
[glad](https://github.com/Dav1dde/glad), and [FreeType](https://freetype.org). It is built ontop of
the [OpenGL Specification](https://www.opengl.org/), The foundation was meant to be as barebones 
as possible without making the application horrifying to create.

## How to build

This project uses [CMake](https://cmake.org/) as the primary build tool. The minimum CMake version
supported is 3.22. The C++ compiler must support C++20. OpenGL and development libraries is required
for building the project. CMake will automatically try to download and compile all GLFW and FreeType. 
Please refer to those projects for their dependencies. Ideally, CMake will complain if they are 
missing dependencies when either generating the build directory or building the project. Outside of
checking the projects for their dependencies, check the generation log or build log, the errors
should say what dependencies are missing.

This project was built on Fedora 36 and Windows 11 using Visual Studio 2022.

### Note on Font ( or probably why it crashed at launch ) 

To avoid finding fonts on the various operating systems, or packaging a font with the source code
(which would ideally be managed through an asset manager, which is in the cards but not wanted
now), the fonts paths are hard coded. 

On Linux the specific font is LiberationMono Regular located here 
```
/usr/share/fonts/liberation-mono/LiberationMono-Regular.ttf
```

On Windows the specific font is Courier New Bold located here
```
C:/Windows/Fonts/courbd.ttf
```

If the font is not installed, has a different file name, or fonts are not installed in that
directory on your linux or windows operating system ( this was developed and tested on Fedora 36 
Workstation and windows 11 ), you will need to modify the constant "FONT\_PATH\_HARD\_CODED" 
in your os specific section of the if else preprocessor clause in `game_tfe/src/text.cpp` near the 
top of the file to point to the true type font which you want. Note: The font rendering is far from 
perfect. Certain fonts will be render better than others. The two fonts selected for windows and 
linux render correctly if not the best quality fonts.

### Using Cmake ( Linux )

Run the following commands to build the application (check the errors for missing packages)

```sh
cmake -DCMAKE_BUILD_TYPE=Release -Bbuild -S .
cd build
make game_tfe
```

If it generated and built successfully, the application should be located in game\_tfe as game\_tfe.

### Using Visual Studio 2022 ( Windows )

You will need C++ and CMake dependencies installed using the Visual Studio 2022 Installer.
Open the directory from Visual Studio as a CMake project. Select game\_tfe as the application to be
built in the top bar. Build and run. Check the CMake errors for dependency related issues. 

## Design and Future improvements

If you are interested in the design and future improvements of this clone, check 
[here](/game_tfe/DESIGN.md).

## Screen Shot

![picture of 2048 clone](/game_tfe/end_screen.png)

## License of the provided code and licenses for third party libraries

This project uses FreeType 2 Font Engine under The FreeType License.

Portions of this software are copyright © 2006-2022 The FreeType
Project (www.freetype.org).  All rights reserved.

The specific version is FreeType 2.12.1 of this writing.

This project uses GLFW under the zlib/libpng license.

Portions of this software are copyright 2002-2006 Marcus Geelnard and copyright 2006-2019 Camilla 
Löwy.

The specific version is GLFW 3.3.8 of this writing.

`game_tfe/glad` was generated by [glad](https://github.com/Dav1dde/glad)

The source code provided is under the MIT License by Quinton Schwagle. The original game is under 
the MIT License by Gabriele Cirulli.
