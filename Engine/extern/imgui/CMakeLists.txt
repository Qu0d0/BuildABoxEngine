cmake_minimum_required(VERSION 3.18)

project(imgui)

# set glad header files variable
set(HEADER_FILES imconfig.h imgui.h imgui_internal.h imstb_rectpack.h imstb_textedit.h imstb_truetype.h backends/imgui_impl_opengl3.h backends/imgui_impl_opengl3_loader.h backends/imgui_impl_glfw.h)

# set glad source files variable
set(SOURCE_FILES backends/imgui_impl_opengl3.cpp imgui.cpp imgui_demo.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp backends/imgui_impl_glfw.cpp)

# add glad as a static library
add_library(imgui STATIC ${HEADER_FILES} ${SOURCE_FILES})

# require C++ 17 compiler
target_compile_features(imgui PRIVATE cxx_std_17)

# specify the include directory for this static libray
target_include_directories(imgui PUBLIC ../imgui)