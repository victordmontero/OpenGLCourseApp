workspace "OpenGLCourseApp"
   configurations { "Debug", "Release" }
   location("build.%{_ACTION}")

    project "OpenGLCourseApp"
       kind "WindowedApp"
       language "C++"
       cppdialect "C++11"
       targetdir "bin/%{cfg.buildcfg}"

       files {
           "Sources/**.h*",
           "Sources/**.c*",
           "Shaders/**.shader",
           "*.lua"
        }

        defines{"GLEW_STATIC"}

        includedirs{
            "include",
            "depend/glm",
            "depend/glad/include",
            "depend/sdl/include",
            "depend/sdl/build/include",
            "glfw-master/include",
            "glew-2.1.0/include",
            "depend/assimp/include",
            "depend/assimp/build/include"
        }

    --    libdirs {
     --       "depend/glad/lib/Debug",
     --       "depend/sdl/build/Debug",
    --    }

        links{
              "opengl32.lib",
              "SDL2lib",
              "Assimp",
              "glad",
              "glad.lib"
        }

        architecture "x64"
        system "windows"

       filter "configurations:Debug"
          defines { "DEBUG" }
          symbols "On"

          includedirs {
            "depend/sdl/build/include-config-debug"
          }
      
          libdirs {
              --"../glfw-master/lib/Release",
              --"../glew-2.1.0/lib/Release/Win32",
              "depend/assimp/build/lib/Debug",
              "depend/sdl/build/Debug",
              "depend/glad/lib/Debug",
          }
      
          links{
              "opengl32.lib",
              --"glew32s.lib",
              --"glfw3.lib",
              "assimp-vc143-mtd.lib", -- TODO: infer msvc version instead,
              "SDL2maind.lib",
              "SDL2d.lib",
          }

       filter "configurations:Release"
          defines { "NDEBUG" }
          optimize "On"

          includedirs{
            "depend/sdl/build/include-config-release"
          }

          libdirs {
              "../glfw-master/lib/Release",
              "../glew-2.1.0/lib/Release/Win32",
              "depend/assimp/build/lib/Release",
              "depend/sdl/build/Release",
              "depend/glad/lib/Release",
          }

          links{
              "opengl32.lib",
              --"glew32s.lib",
              --"glfw3.lib",
              "assimp-vc143-mt.lib", -- TODO: infer msvc version instead
              "SDL2main.lib",
              "SDL2.lib",
          }

    project "glad"
       kind "StaticLib"
       language "C"
       location("depend/glad/")
       targetdir "depend/glad/lib/%{cfg.buildcfg}"

       files {
           "depend/glad/**.h*",
           "depend/glad/**.c*"
        }

        includedirs{
            "include",
            "depend/glad/include",
        }

        architecture "x64"
        system "windows"

       filter "configurations:Debug"
          defines { "DEBUG" }
          symbols "On"

       filter "configurations:Release"
          defines { "NDEBUG" }
          optimize "On"


    project "Assimp"
       kind "Makefile"
       objdir()
   
       location("depend/assimp/")
       includedirs{"./include"}
       targetname "assimp"

       cleancommands {
	       "{RMDIR} %{prj.location}/build/"
       }
   
       filter "configurations:Debug"
		    targetdir "%{prj.location}/build"
   
       buildcommands {
          "cmake %{prj.location} -B %{cfg.targetdir} -DASSIMP_WARNINGS_AS_ERRORS=OFF",
	      "cmake --build %{cfg.targetdir} --parallel 7"
       }
   
       rebuildcommands {
	       "{RMDIR} %{prj.location}/build/",
	       "cmake %{prj.location} -B %{cfg.targetdir} -DASSIMP_WARNINGS_AS_ERRORS=OFF",
	       "cmake --build %{cfg.targetdir} --parallel 7"
       }
   
       filter "configurations:Release"
		    targetdir "%{prj.location}/build"
   
       buildcommands {
	       "cmake -DCMAKE_BUILD_TYPE=Release %{prj.location} -B %{cfg.targetdir} -DASSIMP_WARNINGS_AS_ERRORS=OFF",
	       "cmake --build %{cfg.targetdir} --config Release"
       }
   
       rebuildcommands {
	       "{RMDIR} %{prj.location}/build/",
	       "cmake -DCMAKE_BUILD_TYPE=Release %{prj.location} -B %{cfg.targetdir} -DASSIMP_WARNINGS_AS_ERRORS=OFF",
	       "cmake --build %{cfg.targetdir} --config Release"
       }


   project "SDL2lib"
       kind "Makefile"
       objdir()
   
       location("depend/sdl")
       includedirs{"./include"}
       targetname "SDL2"

       cleancommands {
	       "{RMDIR} %{prj.location}/build/"
       }
   
       filter "configurations:Debug"
		    targetdir "%{prj.location}/build"
   
       buildcommands {
          "cmake %{prj.location} -B %{cfg.targetdir}",
	       "cmake --build %{cfg.targetdir}"
       }
   
       rebuildcommands {
	       "{RMDIR} %{prj.location}/build/",
	       "cmake %{prj.location} -B %{cfg.targetdir}",
	       "cmake --build %{cfg.targetdir}"
       }
   
       filter "configurations:Release"
		    targetdir "%{prj.location}/build"
   
       buildcommands {
	       "cmake -DCMAKE_BUILD_TYPE=Release %{prj.location} -B %{cfg.targetdir}",
	       "cmake --build %{cfg.targetdir} --config Release"
       }
   
       rebuildcommands {
	       "{RMDIR} %{prj.location}/build/",
	       "cmake -DCMAKE_BUILD_TYPE=Release %{prj.location} -B %{cfg.targetdir}",
	       "cmake --build %{cfg.targetdir} --config Release"
       }