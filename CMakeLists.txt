cmake_minimum_required(VERSION 3.28)
project(Zane VERSION 1.0.0)
find_package(antlr4-runtime CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(cereal CONFIG REQUIRED)
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
llvm_map_components_to_libnames(llvm_libs
	core
	orcjit
	executionengine
	support
	native
)
# --- Module interface library ---
file(GLOB MODULE_SOURCES src/*.ixx)
if(MODULE_SOURCES)
	add_library(modules_obj STATIC)
	target_sources(modules_obj
	    PUBLIC
	    FILE_SET CXX_MODULES FILES
	        ${MODULE_SOURCES}
	)
	target_compile_features(modules_obj PUBLIC cxx_std_23)
	target_include_directories(modules_obj PUBLIC
	    ${LLVM_INCLUDE_DIRS}
	    ${CMAKE_CURRENT_SOURCE_DIR}/src
	    ${CMAKE_CURRENT_BINARY_DIR}
	)
	target_link_libraries(modules_obj PUBLIC
	    nlohmann_json::nlohmann_json
	    cereal::cereal
	    antlr4_static
	)
	target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE modules_obj)
endif()
# --- Parser library ---
file(GLOB ANTLR_SOURCES generated-parser/parser/*.cpp)
add_library(zane_parser STATIC ${ANTLR_SOURCES})
target_include_directories(zane_parser PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/generated-parser
	${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(zane_parser PUBLIC antlr4_static)
# --- Embedded types header ---
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/embedded_types.hpp
	COMMAND ${CMAKE_COMMAND}
	    -DTYPES_FILE=${CMAKE_CURRENT_SOURCE_DIR}/data/types.csv
	    -DBUILTINS_FILE=${CMAKE_CURRENT_SOURCE_DIR}/data/builtins.csv
	    -DOUTPUT_FILE=${CMAKE_CURRENT_BINARY_DIR}/embedded_types.hpp
	    -P ${CMAKE_CURRENT_SOURCE_DIR}/embed_data.cmake
	DEPENDS
	    ${CMAKE_CURRENT_SOURCE_DIR}/data/types.csv
	    ${CMAKE_CURRENT_SOURCE_DIR}/data/builtins.csv
	COMMENT "Embedding types.csv and builtins.csv into header"
)
add_custom_target(generate_embedded_types
	DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/embedded_types.hpp
)
# --- Executable ---
add_executable(${CMAKE_PROJECT_NAME}
	src/main.cpp
)
add_dependencies(${CMAKE_PROJECT_NAME} generate_embedded_types)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_BINARY_DIR}
	${LLVM_INCLUDE_DIRS}
)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
	${LLVM_DEFINITIONS}
)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
	nlohmann_json::nlohmann_json
	cereal::cereal
	zane_parser
	${llvm_libs}
)
