solution "VZi-03"

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
  project "Stack"
  
    kind "ConsoleApp"
    location "build"
    language "C++"

    files { 
    	"src/**.h", 
    	"src/**.hpp", 
	"src/**.c", 
	"src/**.cc", 
	"src/**.cpp", 
	"doc/**.txt",
	"doc/**.cfg",

    }

   vpaths {
      ["Header Files"] = {"src/*.h", "src/*.hpp"},
      ["Source Files"] = {"src/*.cpp", "src/*.cc"},
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

