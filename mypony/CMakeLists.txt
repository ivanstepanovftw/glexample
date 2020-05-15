project(mypony)

set(CMAKE_CXX_STANDARD 20)
find_package(LibEpoxy REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(Threads REQUIRED)

# Qt library
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
set(CMAKE_AUTOMOC ON)

# OpenGL & GLEW library
find_package(OpenGL)


add_executable(myapp exe/glfw.cpp)
qt5_use_modules(myapp Widgets OpenGL)
target_compile_options(myapp PRIVATE
        -O0
        -g3
        -ggdb3
        -Wall
        -Werror
        -Wpedantic
        -Wno-error=unused
        -Wno-error=unused-function
        -Wno-error=sign-compare
        )
target_include_directories(myapp
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                ${BOOST_INCLUDE_DIR}
                ${OPENGL_INCLUDE_DIR}
        )
target_link_libraries(myapp
        glfw
        GL
        ${OPENGL_gl_LIBRARY}
        epoxy
        glm
        Threads::Threads
        glexample
        ${QT_LIBRARIES} ${OPENGL_LIBRARIES}
        )
