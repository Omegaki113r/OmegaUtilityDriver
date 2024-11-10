if(ESP_PLATFORM)
    set( HEADERS inc )
    set( SOURCES src/OmegaUtilityDriver.c)

    idf_component_register( SRCS            ${SOURCES}
                            INCLUDE_DIRS    ${HEADERS}
                            )
    set_property(TARGET ${COMPONENT_LIB} PROPERTY C_STANDARD 23)
    target_compile_options(${COMPONENT_LIB} PRIVATE -Wall -Werror)

    include(FetchContent)
    add_compile_definitions(BUILD_TESTING=0)
    FetchContent_Declare(foobar
      GIT_REPOSITORY "https://github.com/stclib/STC.git"
      GIT_TAG "origin/master"   # it's much better to use a specific Git revision or Git tag for reproducibility
      SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/submodules/third-party/STC"
    )
    FetchContent_MakeAvailable(foobar)
endif(ESP_PLATFORM)
