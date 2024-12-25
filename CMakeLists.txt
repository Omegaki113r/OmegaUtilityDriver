#if(ESP_PLATFORM)
#    set( HEADERS inc )
#    set( SOURCES src/OmegaUtilityDriver.cpp)
#
#    idf_component_register( SRCS            ${SOURCES}
#                            INCLUDE_DIRS    ${HEADERS}
#                            )
#    set_property(TARGET ${COMPONENT_LIB} PROPERTY C_STANDARD 23)
#    target_compile_options(${COMPONENT_LIB} PRIVATE -Wall -Werror)
#else()
    cmake_minimum_required(VERSION 3.10)
    project(OmegaUtilityDriver)

    set(CMAKE_CXX_STANDARD 23)  # Change to 23 if you want C++23
    set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Make it required
    
    set( HEADERS inc )
    set( SOURCES src/OmegaUtilityDriver.cpp)

    add_library(OmegaUtilityDriver STATIC ${SOURCES})
    target_include_directories(OmegaUtilityDriver PUBLIC ${HEADERS})
#endif()
