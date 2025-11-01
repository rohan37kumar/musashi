workspace "musashi"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "musashi/external/GLFW/include"
IncludeDir["Glad"] = "musashi/external/Glad/include"
IncludeDir["Imgui"] = "musashi/external/imgui"
IncludeDir["glm"] = "musashi/external/glm"

-- this simply includes the premake5.lua file from our other external projects here in this premake file
group "Dependencies"
	include "musashi/external/GLFW"
	include "musashi/external/Glad"
	include "musashi/external/imgui"

group ""

project "musashi"
	location "musashi"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "msshi_pch.h"
	pchsource "musashi/src/msshi_pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/external/glm/glm/**.hpp",
		"%{prj.name}/external/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/external/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Imgui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"Imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"
		buildoptions { "/utf-8" }

		defines
		{
			"MSSHI_PLATFORM_WINDOWS",
			"MSSHI_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}


	filter "configurations:Debug"
		defines "MSSHI_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MSSHI_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MSSHI_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"musashi/external/spdlog/include",
		"musashi/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"musashi"
	}

	filter "system:windows"
		systemversion "latest"
		buildoptions { "/utf-8" }

		defines
		{
			"MSSHI_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MSSHI_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MSSHI_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MSSHI_DIST"
		runtime "Release"
		optimize "on"

