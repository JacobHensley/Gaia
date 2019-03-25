workspace "Gaia"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["FreeType"] = "Dependencies/FreeType/include"
IncludeDir["AssImp"] = "Dependencies/AssImp/include"
IncludeDir["FreeTypeGL"] = "Dependencies/FreeTypeGL"
IncludeDir["GLFW"] = "Dependencies/GLFW/include"
IncludeDir["GLEW"] = "Dependencies/GLEW/include"
IncludeDir["ImGui"] = "Dependencies/imgui"

include "Dependencies/FreeType"
include "Dependencies/AssImp"
include "Dependencies/FreeTypeGL/FreeTypeGL"
include "Dependencies/GLFW"
include "Dependencies/GLEW"
include "Dependencies/imgui"

project "GaiaEngine"
	location "GaiaEngine"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/intermediates/" .. outputdir .. "/%{prj.name}")

	pchheader "GaPCH.h"
	pchsource "GaiaEngine/src/GaPCH.cpp"	

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/src/vendor",
		"%{IncludeDir.AssImp}",	
		"%{IncludeDir.FreeType}",
		"%{IncludeDir.FreeTypeGL}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.ImGui}"
	}


	defines 
	{
		"GLEW_STATIC",
		"GA_PLATFORM_WINDOWS",
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"GLFW_INCLUDE_NONE",
			"GLEW_STATIC"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/intermediates/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"GaiaEngine/src",
		"GaiaEngine/src/vendor",
		"%{IncludeDir.AssImp}",
		"%{IncludeDir.FreeTypeGL}",
		"%{IncludeDir.FreeType}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}"
	}

	links 
	{ 
		"GLFW",
		"GLEW",
		"AssImp",
		"FreeTypeGL",
		"FreeType",
		"ImGui",
		"GaiaEngine",
		"opengl32.lib"
	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"