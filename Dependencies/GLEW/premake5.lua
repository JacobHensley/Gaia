project "GLEW"
    kind "StaticLib"
    language "C"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/intermediates/" .. outputdir .. "/%{prj.name}")

	files
	{
        "src/glew.c",
        "include/GL/glew.h",
        "include/GL/wglew.h"
    }
    
    defines
    {
        "GLEW_STATIC"
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        staticruntime "On"
        
		defines 
		{ 
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
		}

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"