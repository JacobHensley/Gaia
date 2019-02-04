project "FreeTypeGL"
    kind "StaticLib"
    language "C"
    
  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  files
  {
      "../distance-field.h",
      "../edtaa3func.h",
      "../freetype-gl.h",
      "../texture-atlas.h",
      "../texture-font.h",
      "../utf8-utils.h",
      "../vector.h",
      "../distance-field.c",
      "../edtaa3func.c",
      "../texture-atlas.c",
      "../texture-font.c",
      "../utf8-utils.c",
      "../vector.c"
    }
    
  filter "system:windows"
        buildoptions { "-std=c11", "-lgdi32" }
        systemversion "10.0.17134.0"
        staticruntime "On"

    defines 
    { 
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
    }
    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"