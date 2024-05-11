include "dependencies.lua"

workspace "ONScripterTK"
    architecture "x64"
    startproject "arcmake"
    configurations {"Debug", "Release"}

    group "Dependencies"
        include "3rdparty/BZLIB_Premake"
    group ""

    project "arcmake"
        location "./"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

        targetdir("bin/%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}/%{prj.name}")
        objdir("int/%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}/%{prj.name}")

        files
        {
            "%{wks.location}/include/ONScripterTK/*.h",
            "%{wks.location}/source/ONScripterTK/*.cpp",
            "%{wks.location}/source/ONScripterTK/tools/arcmake.cpp"
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
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

        targetdir("bin/%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}/%{prj.name}")
        objdir("int/%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}/%{prj.name}")

        files
        {
            "%{wks.location}/include/ONScripterTK/*.h",
            "%{wks.location}/source/ONScripterTK/*.cpp",
            "%{wks.location}/source/ONScripterTK/tools/arcdec.cpp"
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