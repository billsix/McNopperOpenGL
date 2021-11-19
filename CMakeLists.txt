cmake_minimum_required(VERSION 3.6)
project (OpenGLExamples)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

# Set Variables for include and linking depending on platform

# set GLUS variables
#set(ENV_DIR ${Processor}/${OperatingSystem}/${Compiler})
#set(EXTERNAL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/External/${ENV_DIR}/include)
#set(EXTERNAL_LIB_DIR ${CMAKE_SOURCE_DIR}/External/${ENV_DIR}/lib)


#link_directories(${EXTERNAL_LIB_DIR} ${LIBRARY_OUTPUT_PATH})

if(APPLE OR WIN32)
     set(BUILD_SHARED_LIBS OFF)
     if(WIN32)
         # no console on start
         set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
     endif(WIN32)
endif()

IF(CMAKE_BUILD_TYPE MATCHES Debug)
  message("Debug mode")
  set(RESOURCE_PATH "${CMAKE_SOURCE_DIR}/res/")
ELSE(CMAKE_BUILD_TYPE MATCHES Debug)
  message("Release mode")
  set(RESOURCE_PATH "${CMAKE_INSTALL_PREFIX}/share/res/")
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

set(PATH_SEPERATOR "/")


configure_file(config.h.in config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})


add_subdirectory(deps/GLUS)
link_libraries(GLUS)


# add include directories for compilation
if(APPLE)
    option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
    option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
    option(GLFW_INSTALL "Generate installation target" OFF)
    add_subdirectory(deps/glfw)
    include_directories(deps/glfw/include)
endif(APPLE)
if(WIN32)
    option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
    option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
    option(GLFW_INSTALL "Generate installation target" OFF)
    add_subdirectory(deps/glfw)
    include_directories(deps/glfw/include)
endif(WIN32)

include_directories(deps/gl3w/include)

# link against the fetched libraries
if(WIN32)
    link_libraries(glfw opengl32)
elseif(APPLE)
    find_package(OpenGL REQUIRED)
    link_libraries(glfw ${GLFW_LIBRARIES})
else()
    # using PkgConfig to determine how to link against
    # the system's glfw and curl
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED glfw3)

    include_directories(${GLFW_INCLUDE_DIR})
    link_libraries(dl m pthread ${GLFW_LIBRARIES})
endif()



file(GLOB EXAMPLES_LIST LIST_DIRECTORIES true RELATIVE ${CMAKE_SOURCE_DIR} "Example*")
foreach (EXAMPLE ${EXAMPLES_LIST})
	message(STATUS "Add Subdirectory: " ${EXAMPLE})
	add_subdirectory(${EXAMPLE})
endforeach()



# Install
install(TARGETS
  01-BasicWindow
  02-RenderingTriangle
  03-GreyFilter
  04-PerspectiveRendering
  05-PhongRendering
  06-Texturing
  07-NormalMapping
  08-CubeMapping
  09-GPUParticles
  10-GeometryShader
  11-ReflectionAndRefraction
  12-ShadowMapping
  13-SimpleTesselation
  14-TerrainRendering
  15-WaterRendering
  16-ModelLoadingAndRendering
  17-ClippingPlanes
  18-StencilBuffer
  19-RenderToTexture
  20-TextureMatrix
  21-ComputeShader
  22-ShadowVolumes
  23-DisplacementMapping
  24-ErodeEffectWithPerlinNoise
  25-GroupsAndMaterials
  26-FurRendering
  27-ProjectionShadowForDirectionalLight
  28-ScreenSpaceAmbientOcclusion
  29-CPURaytracing
  30-GPURayTracingUsingComputeShader
  31-ManyLightsUsingDeferredShading
  32-BRDFandIBLRendering
  33-Real-TimeBRDFandIBL
  34-SubsurfaceScattering
  35-OrderInpendentTransparencyUsingDepthPeeling
  36-OrderIndependentTransparencyLinkedList
  37-CPURayMarching
  38-ProgramPipeline
  39-SeperableProgramisAndShaderRoutines
  40-ClothSimulationUsingComputeShader
  41-OceanWaveHeightWithFFT
  42-FastApproximateAntAliasing
  43-SceneWithSeveralModelsHavingGroupsAndMaterials
  44-ConservativeRasterization
  45-GPUVoxelization
  DESTINATION bin)


install(TARGETS
  GLUS
  DESTINATION lib/)

install(DIRECTORY res/ DESTINATION share/res)
