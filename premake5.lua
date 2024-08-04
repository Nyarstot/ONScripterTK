include "dependencies.lua"

workspace "OpenARC"
    architecture "x64"
    startproject "arcmake"
    configurations {"Debug", "Release"}

    group "Dependencies"
        include "3rdparty/BZLIB_Premake"
    group ""

    project "arcmake"
        location "./"
        kind "SharedLib"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

        targetdir("bin/%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}/%{prj.name}")
        objdir("int/%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}/%{prj.name}")

        files
        {
            "%{wks.location}/include/OpenARC/*.h",
            "%{wks.location}/source/OpenARC/*.cpp",
            "%{wks.location}/include/OpenARC/tools/ArcHandler.h",
            "%{wks.location}/source/OpenARC/tools/ArcHandler.cpp"
        }

        links
        {
            "bzlib"
        }

        includedirs
        {
            "%{wks.location}/include",
            "%{wks.location}/3rdparty/dirent/",
            "%{ExternalDirs.bzlib}",
        }

        defines
        {
            -- "UTF8_FILESYSTEM",
            -- "BULD_DLL"
            "BUILD_PY_DLL",
            "TOOLS_BUILD",
            "NSA"
        }

        filter "system:windows"
            systemversion "latest"

            defines
            {
                "WIN32",
                "_WIN32"
            }

        filter "configurations:Debug"
            symbols "on"

        filter "configurations:Release"
            optimize "on"

    project "arcdec"
        location "./"
        kind "SharedLib"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

        targetdir("bin/%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}/%{prj.name}")
        objdir("int/%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}/%{prj.name}")

        files
        {
            "%{wks.location}/include/OpenARC/*.h",
            "%{wks.location}/source/OpenARC/*.cpp",
            "%{wks.location}/include/OpenARC/tools/ArcHandler.h",
            "%{wks.location}/source/OpenARC/tools/ArcHandler.cpp"
        }

        links
        {
            "bzlib"
        }

        includedirs
        {
            "%{wks.location}/include",
            "%{wks.location}/3rdparty/dirent/",
            "%{ExternalDirs.bzlib}",
        }

        defines
        {
            -- "UTF8_FILESYSTEM",
            -- "BUILD_DLL",
            "BUILD_PY_DLL",
            "TOOLS_BUILD",
            "NSA"
        }

        filter "system:windows"
            systemversion "latest"

            defines
            {
                "WIN32",
                "_WIN32"
            }

        filter "configurations:Debug"
            symbols "on"

        filter "configurations:Release"
            optimize "on"