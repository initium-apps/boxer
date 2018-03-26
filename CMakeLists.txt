cmake_minimum_required(VERSION 3.5)
project(Boxer)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(CMAKE_CXX_STANDARD 11)

find_package(wxWidgets 3.1 REQUIRED core base gl aui adv)
find_package(OpenGL REQUIRED)
include(${wxWidgets_USE_FILE})

file(GLOB_RECURSE B2_SOURCES src/Box2D/*.cpp)
set(SOURCES
	${B2_SOURCES}
	src/b2Separator.cpp
	src/boxFrame.cpp
	src/Boxer.cpp
	src/boxToolbar.cpp
	src/boxPhys.cpp
	src/boxPhystree.cpp
	src/boxIcons.cpp
	src/boxTool.cpp
	src/boxDefaultTools.cpp
	src/boxProperties.cpp
)

file(GLOB_RECURSE B2_HEADERS include/Box2D/*.h)
set(HEADERS
	${B2_HEADERS}
	include/b2Separator.h
	include/icon_kinematic.xpm
	include/icon_kinematic_small.xpm
	include/icon_dynamic.xpm
	include/icon_dynamic_small.xpm
	include/icon_static.xpm
	include/icon_static_small.xpm
	include/icon_cursor.xpm
	include/icon_path.xpm
	include/icon_circle.xpm
	include/boxFrame.h
	include/boxToolbar.h
	include/boxPhys.h
	include/boxPhystree.h
	include/boxIcons.h
	include/boxTool.h
	include/boxDefaultTools.h
	include/boxProperties.h
)

set(STUFF ${HEADERS} ${SOURCES} rc/boxer.rc)

include_directories(${wxWidgets_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} "${PROJECT_SOURCE_DIR}/include")

add_executable(BoxerRelease ${STUFF})
target_link_libraries(BoxerRelease ${wxWidgets_LIBRARIES} ${OPENGL_LIBRARIES})

add_executable(BoxerDebug ${STUFF})
target_link_libraries(BoxerDebug ${wxWidgets_LIBRARIES} ${OPENGL_LIBRARIES})
if(MINGW)
	target_compile_options(BoxerDebug PUBLIC -gdwarf-2)
else()
	target_compile_options(BoxerDebug PUBLIC -g)
endif(MINGW)
