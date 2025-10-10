workspace "musashi"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "musashi"
	location "musashi"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "msshi_pch.h"
	pchsource "musashi/src/msshi_pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/external/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		buildoptions { "/utf-8" }

		defines
		{
			"MSSHI_PLATFORM_WINDOWS",
			"MSSHI_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "MSSHI_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MSSHI_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MSSHI_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	
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
		"musashi/src"
	}

	links
	{
		"musashi"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		buildoptions { "/utf-8" }

		defines
		{
			"MSSHI_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MSSHI_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MSSHI_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MSSHI_DIST"
		optimize "On"

