if(ESP_PLATFORM)
    set( HEADERS inc )
    set( SOURCES src/OmegaUtilityDriver.c)

    idf_component_register( SRCS            ${SOURCES}
                            INCLUDE_DIRS    ${HEADERS}
                            )
    set_property(TARGET ${COMPONENT_LIB} PROPERTY C_STANDARD 23)
    target_compile_options(${COMPONENT_LIB} PRIVATE -Wall -Werror)

    #include(ExternalProject)
    #ExternalProject_Add(STC
        #GIT_REPOSITORY    https://github.com/stclib/STC.git
        #GIT_TAG           origin/master
        #SOURCE_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/submodules/third-party/STC
        #BINARY_DIR        ${CMAKE_BINARY_DIR}/STC
        #CONFIGURE_COMMAND ""
        #BUILD_COMMAND     ""
        #INSTALL_COMMAND   ""
        #TEST_COMMAND      ""
    #)
    #target_include_directories(${COMPONENT_LIB} PRIVATE 
        #submodules/third-party/STC/include/c11
        #submodules/third-party/STC/include/stc/algo
        #submodules/third-party/STC/include/stc/priv
        #submodules/third-party/STC/include/stc
        #)
else()
    cmake_minimum_required(VERSION 3.8)
    project(OmegaUtilityDriver)
    set( HEADERS inc )
    set( SOURCES src/OmegaUtilityDriver.c)
    set(SOURCE_FILES ${SOURCES} ${HEADERS})
    add_library(OmegaUtilityDriver STATIC ${SOURCE_FILES})
endif(ESP_PLATFORM)
