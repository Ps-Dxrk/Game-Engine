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

startproject "Sandbox"

IncludeDir = {}
IncludeDir["spdlog"] = "Dark/vendor/spdlog/include"
IncludeDir["GLFW"] = "Dark/vendor/GLFW/include"
IncludeDir["GLAD"] = "Dark/vendor/GLAD/include"
IncludeDir["ImGui"] = "Dark/vendor/ImGui"
IncludeDir["glm"] = "Dark/vendor/glm"

group "Dependencies"
    include "Dark/vendor/GLFW"
    include "Dark/vendor/GLAD"
    include "Dark/vendor/ImGui"
group ""

project "Dark" 
    location "Dark"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

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
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links {
        "GLFW",
        "GLAD",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++23"
        systemversion "latest"

        defines {
            "DARK_WINDOWS_BUILD",
            "DARK_BUILD_DLL",
            "_GLFW_WIN32",
            "GLFW_INCLUDE_NONE",
            "IMGUI_API=__declspec(dllexport)"
            
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }

    filter "configurations:Debug"
        defines "DARK_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "DARK_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "DARK_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Dark/vendor/spdlog/include",
        "Dark/src",
        "%{IncludeDir.glm}",
        "%{IncludeDir.ImGui}"
    }

    links {
        "Dark"
    }

    filter "system:windows"
        cppdialect "C++23"
        systemversion "latest"

        defines {
            "DARK_WINDOWS_BUILD",
            "DARK_PLATFORM_WINDOWS",
            "IMGUI_API=__declspec(dllimport)"
        }

    filter "configurations:Debug"
        defines "DARK_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "DARK_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "DARK_DIST"
        runtime "Release"
        optimize "On"