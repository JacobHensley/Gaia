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
IncludeDir["FreeTypeGL"] = "Dependencies/FreeTypeGL"
IncludeDir["GLFW"] = "Dependencies/GLFW/include"
IncludeDir["GLEW"] = "Dependencies/GLEW/include"
IncludeDir["ImGui"] = "Dependencies/imgui"

include "Dependencies/FreeType"
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
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/src/vendor",
		"Dependencies/AssImp/include",
		"%{IncludeDir.FreeType}",
		"%{IncludeDir.FreeTypeGL}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.ImGui}"
	}


	defines 
	{
		"GLEW_STATIC"
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
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

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
		"Dependencies/AssImp/include",
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
		"FreeTypeGL",
		"FreeType",
		"ImGui",
		"GaiaEngine",
		"Dependencies/AssImp/bin/Debug/assimp-vc140-mt.lib",
		"opengl32.lib"
	}

	postbuildcommands
	{
		("{COPY} %{wks.location}Dependencies/AssImp/bin/Debug/assimp-vc140-mt.lib \"../bin/" .. outputdir .. "/Sandbox/\"")
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