cmake_minimum_required(VERSION 3.25)
project(finalProject)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(${PROJECT_NAME}
        src/cgvSphere.cpp
        src/cgvSphere.h
        src/cgvCamera.cpp
        src/cgvCamera.h
        src/cgvColor.h
        src/cgvScene3D.cpp
        src/cgvScene3D.h
        src/cgvLight.cpp
        src/cgvLight.h
        src/cgvInterface.cpp
        src/cgvInterface.h
        src/cgvMaterial.cpp
        src/cgvMaterial.h
        src/cgvPoint.cpp
        src/cgvPoint.h
        src/cgvTexture.cpp
        src/cgvTexture.h
        src/lodepng.cpp
        src/lodepng.h
        src/pr4.cpp
        src/cgvButton.cpp
        src/cgvButton.h)

if (LINUX)
    find_path(OPENGL_REGISTRY_INCLUDE_DIRS "GL/glcorearb.h")
    target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_REGISTRY_INCLUDE_DIRS})

    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
    target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})

    find_package(GLUT REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE GLUT::GLUT)
endif ()

if (WIN32)
    find_package(opengl_system)
    target_link_libraries(${PROJECT_NAME} opengl::opengl)

    find_package(opengl-registry)
    target_link_libraries(${PROJECT_NAME} opengl-registry::opengl-registry)

    find_package(FreeGLUT)
    target_link_libraries(${PROJECT_NAME} FreeGLUT::freeglut_static)
endif ()
