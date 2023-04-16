cmake_minimum_required(VERSION 3.21)
project(gl3_wp5)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(extern/glad)
add_subdirectory(extern/glfw)
add_subdirectory(extern/glm)
add_subdirectory(extern/soloud)
add_subdirectory(extern/tinygltf)
add_subdirectory(extern/imgui)

add_subdirectory(engine)
#add_subdirectory(WackLumberjack)
add_subdirectory(DocumentationExample)
#add_subdirectory(WackLumberjack/src/Scripts)