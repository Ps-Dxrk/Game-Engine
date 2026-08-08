workspace "Dark"
    architecture "x64"

    configurations {

        "Debug",
        "Release",
        "Dist"

    }

    filter "system:windows"
        buildoptions { "/utf-8" }
    filter {}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Dark/vendor/GLFW/include"
IncludeDir["GLAD"] = "Dark/vendor/GLAD/include"

include "Dark/vendor/GLFW"
include "Dark/vendor/GLAD"


project "Dark" 
    location "Dark"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "dpch.h"
    pchsource "%{prj.name}/src/dpch.cpp" 

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}"
    }

    links {
        "GLFW",
        "GLAD",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++23"
        staticruntime "On"
        systemversion "latest"

        defines {
            "DARK_WINDOWS_BUILD",
            "DARK_BUILD_DLL",
            "_GLFW_WIN32",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "DARK_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "DARK_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "DARK_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Dark/vendor/spdlog/include",
        "Dark/src"
    }

    links {
        "Dark"
    }

    filter "system:windows"
        cppdialect "C++23"
        staticruntime "On"
        systemversion "latest"

        defines {
            "DARK_WINDOWS_BUILD",
            "DARK_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "DARK_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "DARK_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "DARK_DIST"
        optimize "On"