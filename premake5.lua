
include "dependencies/conandeps.premake5.lua"

workspace "PIDController"
   configurations { "Debug", "Release" }
   architecture "x64"

    project "PIDController"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir   "build/%{cfg.buildcfg}/bin"
    objdir      "build/%{cfg.buildcfg}/obj"

    location "./src"
    files { "%{prj.location}/**.h", "%{prj.location}/**.cpp" }

    filter "system:windows"
    buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

    filter "system:windows"
    systemversion "latest"
    defines { "WINDOWS" }

    filter "toolset:msc*" --Apply settings for microsoft compilers
       buildoptions {"/utf-8"} --include utf-8 support

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"
    filter{}

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"
    filter{}

    -- conan_setup("release_x86_64") -- Release
    conan_setup() -- Debug

    -- linkoptions{"/IGNORE:4099"} -- mute linker warning