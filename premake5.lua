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
    IncludeDir["Glad"] = "Llama/vendor/Glad/include"

    include "Llama/vendor/GLFW"
    include "Llama/vendor/Glad"

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
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}"
	}

    links 
	{ 
		"GLFW",
        "Glad",
		"opengl32.lib"
	}

    filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
        systemversion "latest"

        defines
        {
            "LLAMA_PLATFORM_WINDOWS",
            "LLAMA_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

   filter "configurations:Debug"
       defines "LLAMA_DEBUG"
       buildoptions "/MDd"
       symbols "On"
         
   filter "configurations:Release"
        defines "LLAMA_RELEASE"
        buildoptions "/MD"
        optimize "On"

   filter "configurations:Dist"
        defines "LLAMA_DIST"
        buildoptions "/MD"
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
        buildoptions "/MDd"
        symbols "On"

   filter "configurations:Release"
        defines "LLAMA_RELEASE"
        buildoptions "/MD"
        optimize "On"

   filter "configurations:Dist"
        defines "LLAMA_DIST"
        buildoptions "/MD"
        optimize "On"
                   