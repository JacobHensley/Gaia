project "GLEW"
    kind "StaticLib"
    language "C"
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
        "src/glew.c",
        "include/GL/glew.h",
        "include/GL/wglew.h"
    }
    
    includedirs
    {
        "include"
    }

    defines
    {
        "GLEW_STATIC"
    }

	filter "system:windows"
        systemversion "10.0.17134.0"
        staticruntime "On"
        
		defines 
		{ 
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
		}
    filter { "system:windows", "configurations:Release" }