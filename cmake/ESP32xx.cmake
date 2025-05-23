# if(ESP_PLATFORM)
    set( HEADERS ${UTILITY_ROOT_DIR}/inc )
    set( SOURCES ${UTILITY_ROOT_DIR}/src/OmegaUtilityDriver.cpp)

    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
    
    idf_component_register( 
                            INCLUDE_DIRS    ${HEADERS}
                            SRCS            ${SOURCES}
    )
    set_property(TARGET ${COMPONENT_LIB} PROPERTY C_STANDARD 23)
# else()
#     cmake_minimum_required(VERSION 3.10)
#     project(OmegaUtilityDriver)

#     set(CMAKE_CXX_STANDARD 23)  # Change to 23 if you want C++23
#     set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Make it required
#     set(CMAKE_CXX_EXTENSIONS OFF)
#     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    
#     set( HEADERS inc )
#     set( SOURCES src/OmegaUtilityDriver.cpp)

#     add_library(OmegaUtilityDriver STATIC ${SOURCES})
#     target_include_directories(OmegaUtilityDriver PUBLIC ${HEADERS})
#     target_link_options(OmegaUtilityDriver PRIVATE -static-libgcc -static-libstdc++)
# endif()