# OpenARC
This repository contains program to decode and encode **.arc** archieves used by ONScripter visual novel game engine and may be used as basis for ONScripter based game translation toolkit and so on. Whatever, i'm do it just for fun and some translation projects. Original archive codebase has been taken from ONScripter-EN repository (https://github.com/Galladite27/ONScripter-EN)

# Build
To build project simply run *GenerateProject.bat* script in the root of repository and then build DLL via Visual Studio.

# Usage
After setting up library in your project, just include ArcHandler.h header.

```C++
#include <OpenARC/tools/ArcHandler.h>

...

// By default handler will use ArchiveType::ARCHIVE_TYPE_NSA
ArcHandler handler();
// If given directory is not exists, ArcHandler will create it
handler.decodeArc("path/to/arc.nsa", "path/to/outdir");
```
