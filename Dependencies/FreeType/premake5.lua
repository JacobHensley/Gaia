project "FreeType"
    kind "StaticLib"
    language "C"
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
        "include/ft2build.h",
        "include/freetype/freetype.h",
        "include/freetype/ftadvanc.h",
        "include/freetype/ftautoh.h",
        "include/freetype/ftbbox.h",
        "include/freetype/ftbdf.h",
        "include/freetype/ftbitmap.h",
        "include/freetype/ftbzip2.h",
        "include/freetype/ftcache.h",
        "include/freetype/ftcffdrv.h",
        "include/freetype/ftchapters.h",
        "include/freetype/ftcid.h",
        "include/freetype/fterrdef.h",
        "include/freetype/fterrors.h",
        "include/freetype/ftfntfmt.h",
        "include/freetype/ftgasp.h",
        "include/freetype/ftglyph.h",
        "include/freetype/ftgxval.h",
        "include/freetype/ftgzip.h",
        "include/freetype/ftimage.h",
        "include/freetype/ftincrem.h",
        "include/freetype/ftlcdfil.h",
        "include/freetype/ftlist.h",
        "include/freetype/ftlzw.h",
        "include/freetype/ftmac.h",
        "include/freetype/ftmm.h",
        "include/freetype/ftmodapi.h",
        "include/freetype/ftmoderr.h",
        "include/freetype/ftotval.h",
        "include/freetype/ftoutln.h",
        "include/freetype/ftpcfdrv.h",
        "include/freetype/ftpfr.h",
        "include/freetype/ftrender.h",
        "include/freetype/ftsizes.h",
        "include/freetype/ftsnames.h",
        "include/freetype/ftstroke.h",
        "include/freetype/ftsynth.h",
        "include/freetype/ftsystem.h",
        "include/freetype/fttrigon.h",
        "include/freetype/ftttdrv.h",
        "include/freetype/fttypes.h",
        "include/freetype/ftwinfnt.h",
        "include/freetype/t1tables.h",
        "include/freetype/ttnameid.h",
        "include/freetype/tttables.h",
        "include/freetype/tttags.h",
        "include/freetype/ttunpat.h",
        "include/freetype/config/ftconfig.h",
        "include/freetype/config/ftheader.h",
        "include/freetype/config/ftmodule.h",
        "include/freetype/config/ftoption.h",
        "include/freetype/config/ftstdlib.h",
        "include/freetype/internal/autohint.h",
        "include/freetype/internal/ftcalc.h",
        "include/freetype/internal/ftdebug.h",
        "include/freetype/internal/ftdriver.h",
        "include/freetype/internal/ftgloadr.h",
        "include/freetype/internal/fthash.h",
        "include/freetype/internal/ftmemory.h",
        "include/freetype/internal/ftobjs.h",
        "include/freetype/internal/ftpic.h",
        "include/freetype/internal/ftrfork.h",
        "include/freetype/internal/ftserv.h",
        "include/freetype/internal/ftstream.h",
        "include/freetype/internal/fttrace.h",
        "include/freetype/internal/ftvalid.h",
        "include/freetype/internal/internal.h",
        "include/freetype/internal/psaux.h",
        "include/freetype/internal/pshints.h",
        "include/freetype/internal/sfnt.h",
        "include/freetype/internal/t1types.h",
        "include/freetype/internal/tttypes.h",
        "src/autofit/autofit.c",
        "src/base/ftbase.c",
        "src/base/ftbbox.c",
        "src/base/ftbdf.c",
        "src/base/ftbitmap.c",
        "src/base/ftcid.c",
        "src/base/ftfntfmt.c",
        "src/base/ftfstype.c",
        "src/base/ftgasp.c",
        "src/base/ftglyph.c",
        "src/base/ftgxval.c",
        "src/base/ftinit.c",
        "src/base/ftlcdfil.c",
        "src/base/ftmm.c",
        "src/base/ftotval.c",
        "src/base/ftpatent.c",
        "src/base/ftpfr.c",
        "src/base/ftstroke.c",
        "src/base/ftsynth.c",
        "src/base/ftsystem.c",
        "src/base/fttype1.c",
        "src/base/ftwinfnt.c",
        "src/bdf/bdf.c",
        "src/bzip2/ftbzip2.c",
        "src/cache/ftcache.c",
        "src/cff/cff.c",
        "src/cid/type1cid.c",
        "src/gzip/ftgzip.c",
        "src/lzw/ftlzw.c",
        "src/pcf/pcf.c",
        "src/pfr/pfr.c",
        "src/psaux/psaux.c",
        "src/pshinter/pshinter.c",
        "src/psnames/psnames.c",
        "src/raster/raster.c",
        "src/sfnt/sfnt.c",
        "src/smooth/smooth.c",
        "src/truetype/truetype.c",
        "src/type1/type1.c",
        "src/type42/type42.c",
        "src/winfonts/winfnt.c",
        "builds/windows/ftdebug.c"
    }
    
    includedirs
    {
        "include",
    }

    defines 
    { 
        "FT2_BUILD_LIBRARY",
        "FT2BUILD_H_"
    }

	filter "system:windows"
        systemversion "10.0.17134.0"
        staticruntime "On"
        
		defines 
		{ 
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
		}