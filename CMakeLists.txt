if(ESP_PLATFORM)
    set( HEADERS inc )
    set( SOURCES src/OmegaUtilityDriver.c)

    idf_component_register( SRCS            ${SOURCES}
                            INCLUDE_DIRS    ${HEADERS}
                            )
    set_property(TARGET ${COMPONENT_LIB} PROPERTY C_STANDARD 23)
    target_compile_options(${COMPONENT_LIB} PRIVATE -Wall -Werror)
else()
    cmake_minimum_required(VERSION 3.8)
    project(OmegaUtilityDriver)
    set( HEADERS inc )
    set( SOURCES src/OmegaUtilityDriver.cpp)

    add_library(OmegaUtilityDriver STATIC ${SOURCES})
    target_include_directories(OmegaUtilityDriver PUBLIC ${HEADERS})
endif()
