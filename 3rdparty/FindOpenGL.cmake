if (WIN32)
    set(OGL opengl32)
    set(OGLLIB ${OGL})
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
elseif (UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
    find_package(OpenGL REQUIRED)
    add_definitions(${OPENGL_DEFINITIONS})
    find_package(X11 REQUIRED)

    # note that the order is important for setting the libs
    # use pkg-config --libs $(pkg-config --print-requires --print-requires-private glfw3) in a terminal to confirm
    set(OGL GL)
    set(OGLLIB X11 Xrandr Xinerama Xi Xxf86vm Xcursor ${OGL} dl Threads::Threads)
elseif (APPLE)
    find_package(OpenGL REQUIRED)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    MARK_AS_ADVANCED(COCOA_LIBRARY OpenGL_LIBRARY)
    SET(APPLE_LIBS ${COCOA_LIBRARY} ${IOKit_LIBRARY} ${CoreVideo_LIBRARY})
    set(OGL OpenGL::GL)
    set(OGLLIB ${OGL} ${APPLE_LIBS})
else ()
    set(OGLLIB)
endif (WIN32)

set(GLAD_DIR ${PROJECT_SOURCE_DIR}/3rdparty/glad)
FILE(GLOB_RECURSE glad_headers CONFIGURE_DEPENDS ${GLAD_DIR}/include/*.h)
FILE(GLOB glad_sources ${GLAD_DIR}/src/*.c)
add_library(glad STATIC ${glad_headers} ${glad_sources})
target_include_directories(glad
        PUBLIC
        $<BUILD_INTERFACE:${GLAD_DIR}/include>
        )