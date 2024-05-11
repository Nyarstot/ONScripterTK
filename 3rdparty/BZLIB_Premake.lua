project "bzlib"
    kind "StaticLib"
    language "C++"
    staticruntime "on"

    targetdir("bzip2-1.0.8/bin/%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}/%{prj.name}")
    objdir("bzip2-1.0.8/int/%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}/%{prj.name}")

    files
    {
        "bzip2-1.0.8/bzlib_private.h",
        "bzip2-1.0.8/bzlib.h",

        "bzip2-1.0.8/bzlib.c",
        "bzip2-1.0.8/compress.c",
        "bzip2-1.0.8/crctable.c",
        "bzip2-1.0.8/decompress.c",
        "bzip2-1.0.8/huffman.c",
        "bzip2-1.0.8/randtable.c",
        "bzip2-1.0.8/blocksort.c"
    }

    filter "configurations:Debug"
        symbols "on"

        defines
        {
            "BZ_DEBUG"
        }