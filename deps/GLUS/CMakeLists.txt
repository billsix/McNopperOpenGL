#
# GLUS CMake file
#
# Note: Set OpenGL=ES, OpenGL=ES31 or OpenGL=ES2 for Windows OpenGL ES 3.0, 3.1 or 2.0 simulation.
#       Raspberry Pi and i.MX6 is default OpenGL ES 2.0.
#		Set SoC=iMX6 for i.MX6.
#
# (c) Norbert Nopper
#

cmake_minimum_required(VERSION 2.6)

project(GLUS)


include_directories(${EXTERNAL_INCLUDE_DIR})
include_directories(../gl3w/include)

# Files only valid for desktop OpenGL
list(APPEND ONLY_GL_C_FILES		${GLUS_SOURCE_DIR}/src/glus_window_glfw.c
								${GLUS_SOURCE_DIR}/src/glus_programpipeline.c
								${GLUS_SOURCE_DIR}/src/glus_program.c
								${GLUS_SOURCE_DIR}/src/glus_shape_adjacency.c
)

# Files currently not used
list(APPEND NOT_USED_C_FILES	${GLUS_SOURCE_DIR}/src/glus_memory_nodm.c
)

# Source files
file(GLOB C_FILES ${GLUS_SOURCE_DIR}/src/*.c)
file(GLOB ES_C_FILES ${GLUS_SOURCE_DIR}/src/*_es.c)
file(GLOB ES2_C_FILES ${GLUS_SOURCE_DIR}/src/*_es2.c)
file(GLOB ES31_C_FILES ${GLUS_SOURCE_DIR}/src/*_es31.c)
file(GLOB VG_C_FILES ${GLUS_SOURCE_DIR}/src/*_vg.c)

# Header files
file(GLOB_RECURSE H_FILES ${GLUS_SOURCE_DIR}/src/*.h)

list(REMOVE_ITEM C_FILES ${NOT_USED_C_FILES})


list(REMOVE_ITEM C_FILES ${ES_C_FILES} ${ES2_C_FILES} ${ES31_C_FILES} ${VG_C_FILES})


add_library(GLUS ${C_FILES} ${H_FILES} ../gl3w/src/gl3w.c)
target_include_directories (GLUS PUBLIC ${GLUS_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} m GL glfw )
