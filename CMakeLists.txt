

cmake_minimum_required (VERSION 2.6)
project(C++)

add_executable(C++ main.cpp)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

   # Mac OS X specific code
   SET(OperatingSystem "Mac OS X")

   # Use the homebrew installation location to make it behave well.
   include_directories("/usr/local/Cellar/glfw/3.2.1/include/")
   include_directories("/usr/local/Cellar/glew/2.0.0/include/GL/")

   find_package(OpenGL)

   IF (OPENGL_FOUND)

   		include_directories(${OPENGL_INCLUDE_DIR})
   		target_link_libraries(C++ ${OPENGL_LIBRARIES})

   ENDIF (OPENGL_FOUND)

   target_link_libraries(C++ "/usr/local/Cellar/glew/2.0.0/lib/libGLEW.2.0.0.dylib")
   target_link_libraries(C++ "/usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.2.dylib")

ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF(WIN32)
	


ENDIF(WIN32)

