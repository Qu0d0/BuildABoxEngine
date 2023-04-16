cmake_minimum_required(VERSION 3.18)

set(SOURCE_FILES DocGame.h DocGame.cpp main.cpp GameSystems/ObjectRotatorSystem.h GameSystems/ObjectRotatorSystem.cpp GameComponents/InputTargetComponet.h)

set(EXE_FILE DocGame)

add_executable(${EXE_FILE} ${SOURCE_FILES})

target_compile_features(${EXE_FILE} PRIVATE cxx_std_17)

target_link_libraries(${EXE_FILE} PRIVATE Engine)

target_compile_definitions(${EXE_FILE} PRIVATE DEBUG_ASSET_ROOT=${PROJECT_SOURCE_DIR}/assets/)
