workspace "Llama"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["GLFW"] = "Llama/vendor/GLFW/include"

    include "Llama/vendor/GLFW"

project "Llama"
    location "Llama"
    kind "SharedLib"
	language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "llamapch.h"
    pchsource "Llama/src/llamapch.cpp"

    files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
        "%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}"
	}

    links 
	{ 
		"GLFW",
		"opengl32.lib"
	}

    filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
        systemversion "latest"

        defines
        {
            "LLAMA_PLATFORM_WINDOWS",
            "LLAMA_BUILD_DLL"
        }

        postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

   filter "configurations:Debug"
       defines "LLAMA_DEBUG"
       symbols "On"
         
   filter "configurations:Release"
        defines "LLAMA_RELEASE"
        optimize "On"

   filter "configurations:Dist"
        defines "LLAMA_DIST"
        optimize "On"
                       


project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"
    
        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

   
        includedirs
        {
            "Llama/vendor/spdlog/include",
            "Llama/src"
        }
    
        links
        {
            "Llama"
        }

        filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
        systemversion "latest"

        
		defines
		{
			"LLAMA_PLATFORM_WINDOWS"
		}

   filter "configurations:Debug"
        defines "LLAMA_DEBUG"
        symbols "On"

   filter "configurations:Release"
        defines "LLAMA_RELEASE"
        optimize "On"

   filter "configurations:Dist"
        defines "LLAMA_DIST"
        optimize "On"
                   