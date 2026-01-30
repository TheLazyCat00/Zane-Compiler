cmake_minimum_required(VERSION 3.15)
project(Zane VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(antlr4-runtime CONFIG REQUIRED)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Link the essential JIT and hardware components
llvm_map_components_to_libnames(llvm_libs
	core
	orcjit
	executionengine
	support
	native
)

file(GLOB ANTLR_SOURCES src/parser/*.cpp)

add_executable(${CMAKE_PROJECT_NAME}
	src/main.cpp
	${ANTLR_SOURCES}
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
	antlr4_static
	${llvm_libs}
)

add_custom_target(run
	COMMAND ${CMAKE_PROJECT_NAME} test.txt
	DEPENDS ${CMAKE_PROJECT_NAME}
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
