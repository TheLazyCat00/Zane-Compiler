cmake_minimum_required(VERSION 3.15)
project(Zane VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(antlr4-runtime CONFIG REQUIRED)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs
	core
	orcjit
	executionengine
	support
	native
)

file(GLOB ANTLR_SOURCES generated-parser/parser/*.cpp)

# Create a library for the parser
add_library(zane_parser STATIC ${ANTLR_SOURCES})
target_include_directories(zane_parser PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/generated-parser
)
target_link_libraries(zane_parser PUBLIC antlr4_static)

add_executable(${CMAKE_PROJECT_NAME}
	src/main.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
	zane_parser
	${llvm_libs}
)

add_custom_target(run
	COMMAND ${CMAKE_PROJECT_NAME} src/main.zane
	DEPENDS ${CMAKE_PROJECT_NAME}
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test
)
