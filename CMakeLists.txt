cmake_minimum_required(VERSION 3.15)
project(Zane VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(antlr4-runtime CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
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
	${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(zane_parser PUBLIC antlr4_static)

# Generate embedded types header at configure time
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/embedded_types.hpp
	COMMAND ${CMAKE_COMMAND}
		-DTYPES_FILE=${CMAKE_CURRENT_SOURCE_DIR}/data/types.csv
		-DBUILTINS_FILE=${CMAKE_CURRENT_SOURCE_DIR}/data/builtins.csv
		-DOUTPUT_FILE=${CMAKE_CURRENT_BINARY_DIR}/embedded_types.hpp
		-P ${CMAKE_CURRENT_SOURCE_DIR}/embed_data.cmake
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/data/types.csv ${CMAKE_CURRENT_SOURCE_DIR}/data/builtins.csv
	COMMENT "Embedding types.csv and builtins.csv into header"
)

add_custom_target(generate_embedded_types DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/embedded_types.hpp)

add_executable(${CMAKE_PROJECT_NAME}
	src/main.cpp
	${CMAKE_CURRENT_BINARY_DIR}/embedded_types.hpp
)

add_dependencies(${CMAKE_PROJECT_NAME} generate_embedded_types)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
	nlohmann_json::nlohmann_json
	zane_parser
	${llvm_libs}
)
