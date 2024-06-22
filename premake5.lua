workspace "OpenGLCourseApp"
   configurations { "Debug", "Release" }
   platforms { "Linux", "Win64" }
   location("proj_%{_ACTION}")

    project "OpenGLCourseApp"
       kind "WindowedApp"
       language "C++"
       cppdialect "C++14"
       targetdir "bin/%{cfg.buildcfg}"

       files {
           "Sources/**.h*",
           "Sources/**.c*",
           "Shaders/**.shader",
           "*.lua"
        }

        includedirs{
            "include",
            "depend/glm",
            "depend/glad/include",
            "depend/sdl/include",
            --"depend/sdl/build/include",
            "depend/assimp/include",
            "depend/assimp/build/include"
        }

        libdirs {
              "depend/glad/lib",
        }

        links{
            "SDL2lib",
            "assimplib",
            "gladlib"
        }

       filter "platforms:Win64"
           defines{"WIN32", "WIN64"}
           architecture "x64"

       filter "platforms:Win*"
          system "windows"
          links{
              "opengl32.lib",
              "glad.lib"
          }

       filter  "platforms:Linux"
           defines{"LINUX"}
           system "linux"

           libdirs {
              "depend/assimp/build/lib",
		          "depend/assimp/build/contrib/zlib",
              "depend/sdl/build",
              --"depend/glad/lib",
           }

           links{
              "zlibstaticd",
              "z",
              "SDL2",
              "assimpd",
              "glad",
            }

       filter "configurations:Debug"
          defines { "DEBUG" }
          symbols "On"

          includedirs {
            "depend/sdl/build/include-config-debug"
          }
      

       filter "configurations:Release"
          defines { "NDEBUG" }
          optimize "On"

          includedirs{
            "depend/sdl/build/include-config-release"
          }


       filter {"configurations:Debug", "platforms:Win*"}

           libdirs {
              "depend/assimp/build/lib/Debug",
              "depend/sdl/build/Debug",
          }

          links{
              "assimp-vc143-mtd.lib",
              "SDL2maind.lib",
              "SDL2d.lib"
          }

       filter {"configurations:Release", "platforms:Win*"}

           libdirs {
              "depend/assimp/build/lib/Release",
              "depend/sdl/build/Release",
           }

           links{
              "assimp-vc143-mt.lib",
              "SDL2main.lib",
              "SDL2.lib"
          }

    project "gladlib"
       kind "StaticLib"
       language "C"
       location("depend/glad/")
       targetdir "depend/glad/lib"
       targetname "glad"

       files {
           "depend/glad/**.h*",
           "depend/glad/**.c*"
        }

        includedirs{
            "include",
            "depend/glad/include",
        }

       filter  "platforms:Win64"
           defines{"WIN32", "WIN64"}
           architecture "x64"
           system "windows"

       filter  "platforms:Linux"
           defines{"LINUX"}
           system "linux"

       filter "configurations:Debug"
          defines { "DEBUG" }
          symbols "On"

       filter "configurations:Release"
          defines { "NDEBUG" }
          optimize "On"

    project "assimplib"
       kind "Makefile"
       objdir()
   
       location("depend/assimp/")
       includedirs{"./include"}
       targetname "assimp"


	     cmake_opt = " -DASSIMP_BUILD_ZLIB=ON -DBUILD_SHARED_LIBS=OFF -DASSIMP_BUILD_TESTS=OFF "

       cleancommands {
	       "{RMDIR} %{prj.location}/build/"
       }
   
--       filter "configurations:Debug"
--		    targetdir "%{prj.location}/build"
--   
--       buildcommands {
--          "cmake %{prj.location} -B %{cfg.targetdir} -DASSIMP_WARNINGS_AS_ERRORS=OFF -DASSIMP_INSTALL=OFF -DBUILD_SHARED_LIBS=OFF",
--	      "cmake --build %{cfg.targetdir} "
--       }
--   
--       rebuildcommands {
--	       "{RMDIR} %{prj.location}/build/",
--	       "cmake %{prj.location} -B %{cfg.targetdir} -DASSIMP_WARNINGS_AS_ERRORS=OFF -DBUILD_SHARED_LIBS=OFF",
--	       "cmake --build %{cfg.targetdir} "
--       }
--   
--       filter "configurations:Release"
--		    targetdir "%{prj.location}/build"
--   
--       buildcommands {
--	       "cmake -DCMAKE_BUILD_TYPE=Release %{prj.location} -B %{cfg.targetdir} -DASSIMP_WARNINGS_AS_ERRORS=OFF -DASSIMP_BUILD_TESTS=OFF -DASSIMP_INSTALL=OFF -DBUILD_SHARED_LIBS=OFF",
--	       "cmake --build %{cfg.targetdir}  --config Release"
--       }
--   
--       rebuildcommands {
--	       "{RMDIR} %{prj.location}/build/",
--	       "cmake -DCMAKE_BUILD_TYPE=Release %{prj.location} -B %{cfg.targetdir} -DASSIMP_WARNINGS_AS_ERRORS=OFF -DASSIMP_BUILD_TESTS=OFF -DASSIMP_INSTALL=OFF -DBUILD_SHARED_LIBS=OFF",
--	       "cmake --build %{cfg.targetdir}  --config Release"
--       }


      	buildcommands {
      	  "cmake -DCMAKE_BUILD_TYPE=%{cfg.buildcfg}" .. cmake_opt .. "%{prj.location} -B %{cfg.targetdir}",
      		"cmake --build %{cfg.targetdir} --config %{cfg.buildcfg}"
      	}
      	
      	rebuildcommands {
      		"{RMDIR} %{prj.location}/out/",
      	  "cmake -DCMAKE_BUILD_TYPE=%{cfg.buildcfg}" .. cmake_opt .. "%{prj.location} -B %{cfg.targetdir}",
      		"cmake --build %{cfg.targetdir} --config %{cfg.buildcfg}"
      	}


       filter "configurations:Debug"
		    targetdir "%{prj.location}/build"
       filter "configurations:Release"
		    targetdir "%{prj.location}/build"


   project "SDL2lib"
       kind "Makefile"
       objdir()
   
       location("depend/sdl")
       includedirs{"./include"}
       targetname "SDL2"

       cmake_opt = " -DBUILD_SHARED_LIBS=OFF -DSDL_SHARED=OFF -DSDL_STATIC=ON -DSDL_TEST=OFF -DSDL_WAYLAND=OFF "

       cleancommands {
         "{RMDIR} %{prj.location}/build/"
       }
 
       buildcommands {
         "cmake -DCMAKE_BUILD_TYPE=%{cfg.buildcfg}" .. cmake_opt .. "%{prj.location} -B %{cfg.targetdir}",
      	 "cmake --build %{cfg.targetdir} --config %{cfg.buildcfg}"
       }
       
       rebuildcommands {
         "{RMDIR} %{prj.location}/build/",
         "cmake -DCMAKE_BUILD_TYPE=%{cfg.buildcfg}" .. cmake_opt .. "%{prj.location} -B %{cfg.targetdir}",
      	 "cmake --build %{cfg.targetdir} --config %{cfg.buildcfg}"
       }
      
      filter "configurations:Debug"
          targetdir "%{prj.location}/build"
      filter "configurations:Release"
          targetdir "%{prj.location}/build"
      	
