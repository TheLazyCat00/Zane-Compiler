#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "antlr4_static" for configuration "Release"
set_property(TARGET antlr4_static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(antlr4_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libantlr4-runtime.a"
  )

list(APPEND _cmake_import_check_targets antlr4_static )
list(APPEND _cmake_import_check_files_for_antlr4_static "${_IMPORT_PREFIX}/lib/libantlr4-runtime.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
