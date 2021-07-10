cmake_minimum_required(VERSION 3.21.0 FATAL_ERROR)

set(PROJECT_NAME FlappyBird)

add_executable(${PROJECT_NAME}
	Source/Main.cpp
	Source/Game/Game.h
	Source/Game/Game.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(External/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(External/glad)
target_link_libraries(${PROJECT_NAME} glad)

include_directories(External/glm)
include_directories(External/stb)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/Content $<TARGET_FILE_DIR:${PROJECT_NAME}>/Content)