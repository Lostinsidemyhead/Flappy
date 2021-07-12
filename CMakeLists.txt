cmake_minimum_required(VERSION 3.21.0 FATAL_ERROR)

set(PROJECT_NAME Flappy)

add_executable(${PROJECT_NAME}
	Source/Main.cpp
	Source/Utils/Shader.h
	Source/Utils/Shader.cpp
	Source/Utils/Texture.h
	Source/Utils/Texture.cpp
	Source/Utils/ResourceManager.h
	Source/Utils/ResourceManager.cpp
	Source/Utils/SpriteRenderer.h
	Source/Utils/SpriteRenderer.cpp
	Source/Game/Game.h
	Source/Game/Game.cpp
	Source/Game/Actor.h
	Source/Game/Actor.cpp
	Source/Game/ObstaclesGenerator.h
	Source/Game/ObstaclesGenerator.cpp)

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
					${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources)