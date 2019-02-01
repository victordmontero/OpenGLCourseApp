workspace "OpenGLCourseApp"
   configurations { "Debug", "Release" }
   location("build.%{_ACTION}")

project "OpenGLCourseApp"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files {
       "**.h", "**.c",
       "**.hpp","**.cpp",
       "**.hxx", "**.cxx",
       "**.shader","*.lua"
    }

    defines{"GLEW_STATIC"}

    includedirs{
        "include",
        "../glm-stable",
        "../glfw-master/include",
        "../glew-2.1.0/include",
        "../assimp-4.1.0/include"
    }

    libdirs{
        "../glfw-master/lib/Release",
        "../glew-2.1.0/lib/Release/Win32",
        "../assimp-4.1.0/lib/Release"
    }

	links{
		"opengl32.lib",
        "glew32s.lib",
        "glfw3.lib",
        "assimp-vc140-mt.lib"
    }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"