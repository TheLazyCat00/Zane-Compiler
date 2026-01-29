cmake_minimum_required(VERSION 3.15)
project(Zane VERSION 1.0.0)

find_package(antlr4-runtime CONFIG REQUIRED)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

file(GLOB ANTLR_SOURCES src/parser/*.cpp)

add_executable(${CMAKE_PROJECT_NAME}
	src/main.cpp
	${ANTLR_SOURCES}
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
	antlr4_static
	LLVMCore
	LLVMSupport
	LLVMTarget
)

add_custom_target(run
	COMMAND ${CMAKE_PROJECT_NAME} test.txt
	DEPENDS ${CMAKE_PROJECT_NAME}
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
