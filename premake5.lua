workspace "Gaia"
   architecture "x64"
   configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Dependencies/GLFW/include"
IncludeDir["GLEW"] = "Dependencies/GLEW/include"
IncludeDir["FreeType"] = "Dependencies/FreeType/include"
IncludeDir["FreeTypeGL"] = "Dependencies/FreeTypeGL"

IncludeDir["AssImp"] = "Dependencies/AssImp/build/include"
IncludeDir["AssImp"] = "Dependencies/AssImp/include"

include "Dependencies/GLFW"
include "Dependencies/GLEW"
include "Dependencies/FreeType"
include "Dependencies/FreeTypeGL/FreeTypeGL"
include "Dependencies/AssImp/build/code"

project "GaiaEngine"
	location "GaiaEngine" 
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/" .. outputdir .. "/Intermediates")

	files 
	{ 
		"%{prj.name}/src/**.h",  
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/src/vendor",
		"%{wks.location}/Dependencies/GLEW/include",
		"%{wks.location}/Dependencies/GLFW/include",
		"%{wks.location}/Dependencies/FreeTypeGL",
		"%{wks.location}/Dependencies/FreeType/include",
		"%{wks.location}/Dependencies/AssImp/build/include",
		"%{wks.location}/Dependencies/AssImp/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"	


project "Sandbox"		
	location "Sandbox" 
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/" .. outputdir .. "/Intermediates")	


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
		"%{wks.location}/Dependencies/GLEW/include",
		"%{wks.location}/Dependencies/GLFW/include",
		"%{wks.location}/Dependencies/FreeTypeGL",
		"%{wks.location}/Dependencies/FreeType/include",
		"%{wks.location}/Dependencies/AssImp/build/include",
		"%{wks.location}/Dependencies/AssImp/include"
	}

	links { "GaiaEngine" }
	links { "GLEW" }
	links { "GLFW" }
	links { "Assimp" }
	links { "FreeType" }
	links { "FreeTypeGL" }

	filter "system:windows"
	cppdialect "C++17"
	staticruntime "On"
	systemversion "latest"

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"