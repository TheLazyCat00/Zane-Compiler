if(CONFIG STREQUAL "Release")
    execute_process(COMMAND ${UPX} --best ${BINARY})
endif()
