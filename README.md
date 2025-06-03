# Credits
- Physics, collisions, gameplay and level design by me
- Sound and art assets by Sofea Allysa Leong
- Game framework and input by Terence New Zi Yang

# Setup
1. Install Microsoft DirectX June 2010 Software Development Kit, [here](https://www.microsoft.com/en-us/download/details.aspx?id=6812)
   - If you encounter error code *S1023*, please follow the link [here](https://stackoverflow.com/questions/4102259/directx-sdk-june-2010-installation-problems-error-code-s1023)
3. Go to your *Project Properties* -> *Configuration Properties* -> *VC++ Directories*.
- The directs your project to refer to the DirectX include directory path for the header files.
3. Add `“$(DXSDK_DIR)lib\x86”` and `$(ProjectDir)\inc` to Library Directories and Include Directories.
- This directs your projects to refer to the DirectX library directory path for the static library files. x86 means we are using the 32 bit version of Direct3D 9 static library.
4. Inside the project properties, Go to *Linker* > *Input* > *Additional Directories* > *edit* > *d3d9.lib*
5. Run the game in *x86*
