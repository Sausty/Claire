workspace "Claire"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "third_party/imgui"
group ""

project "Claire"
    location "Claire"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17" -- Forcing C++ 17, we're in 2020 bruh

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "third_party/imgui/examples/imgui_impl_dx11.h",
        "third_party/imgui/examples/imgui_impl_dx11.cpp",
        "third_party/imgui/examples/imgui_impl_win32.h",
        "third_party/imgui/examples/imgui_impl_win32.cpp"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "ext/glm",
        "third_party/DirectXTex/include",
        "third_party/imgui"
    }

    links
    {
        "d3d11",
        "d3dcompiler",
        "ole32",
        "ImGui"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
        buildoptions "/MDd"
        links { "third_party/DirectXTex/bin/DirectXTexD.lib" }

	filter "configurations:Release"
		runtime "Release"
        optimize "On"
        buildoptions "/MT"
        links { "third_party/DirectXTex/bin/DirectXTex.lib" }

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17" -- still in 2020
    staticruntime "On"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c"
    }

    includedirs
    {
        "Claire/src",
        "ext/glm",
        "third_party/imgui"
    }

    links
    {
        "Claire",
        "ImGui"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
        buildoptions "/MDd"

	filter "configurations:Release"
		runtime "Release"
        optimize "On"
        buildoptions "/MT"

