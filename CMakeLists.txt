cmake_minimum_required(VERSION 3.26)
project(CPPTest)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(CPPTest src/main.cpp
        src/client/simulation.cpp
        src/client/simulation.h
        src/client/math/constants.h
        src/client/math/vec2d.cpp
        src/client/math/vec2d.h
        src/client/entity/simulationobject.cpp
        src/client/entity/simulationobject.h
        src/client/entity/particle.cpp
        src/client/entity/particle.h
)

target_link_libraries(CPPTest PRIVATE OpenGL::GL glfw)
