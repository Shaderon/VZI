solution "VZi-02"

  os.mkdir("bin")
--  os.mkdir("resource")
  os.mkdir("src")

  configurations { "Debug", "Release" }

  configuration { "Debug" }
    targetdir "bin/debug"
 
  configuration { "Release" }
    targetdir "bin/release"
 
  if _ACTION == "clean" then
    os.rmdir("bin")
  end

  -- A project defines one build target
  project "LinkedList"
  
    kind "ConsoleApp"
    location "build"
    language "C"

    files { 
    	"src/**.h", 
	"src/**.c", 
	"doc/**.txt",
	"doc/**.cfg",

    }

   vpaths {
      ["Header Files"] = {"src/*.h"},

      ["Source Files"] = {"src/*.c", 
                         },
    }

    platforms { 
	"x32",
    }

    -- include dirs
    includedirs { 
	"./src/",
    }

    configuration "Debug"
       defines { "DEBUG" }
       flags { "Symbols" }

    configuration "Release"
       defines { "NDEBUG" }
       flags { "Optimize" } 

