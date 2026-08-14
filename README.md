# 8086 dissasembler
This is a project that I am working on along-side the video
series [computer enhance](https://computerenhance.com). 

## Requirements
1. An assembler - I am using [nasm](https://www.nasm.us/).
2. C++ compiler - the default is clang.
3. Make
4. CMake

This is intended to be compiled with C++ 17 or greater.

### Optional

If you want to generate `compile_commands.json` you must have bear installed.
`brew install bear`. Then run `make compile_commands`
 
A .vscode directory exists to debug the program using it, you can use any 
debugger you want though.

## Building

just running `make` should do you just fine. The available make macros are

`CC` - The c++ compiler you would like to use, default `clang++`<br>
`FLAGS` - Compiler flags, default void<br>
`BUILD_DIR` - The directory to build to, default `build`. If different from default this must be set when you run `clean`.<br>
`STD` - The C++ standard you'd like to compile to, default `17`<br>

