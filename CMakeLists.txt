if(ESP_PLATFORM)
    set( HEADERS inc )
    set( SOURCES src/OmegaUtilityDriver.c)

    idf_component_register( SRCS            ${SOURCES}
                            INCLUDE_DIRS    ${HEADERS}
                            REQUIRES OmegaBaseLoggingController
                            )
    set_property(TARGET ${COMPONENT_LIB} PROPERTY C_STANDARD 23)
    target_compile_options(${COMPONENT_LIB} PRIVATE -Wall -Werror)
endif(ESP_PLATFORM)
