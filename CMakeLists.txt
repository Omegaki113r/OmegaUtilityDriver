if(ESP_PLATFORM)
    set( HEADERS inc )
    set( SOURCES src/OmegaUtilityDriver.c)

    idf_component_register( SRCS            ${SOURCES}
                            INCLUDE_DIRS    ${HEADERS}
                            )
    set_property(TARGET ${COMPONENT_LIB} PROPERTY C_STANDARD 23)
    target_compile_options(${COMPONENT_LIB} PRIVATE -Wall -Werror)

    include(FetchContent)
    FetchContent_Declare(foobar
      GIT_REPOSITORY "https://github.com/opencv/opencv.git"
      GIT_TAG "origin/master"   # it's much better to use a specific Git revision or Git tag for reproducibility
      SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/../opencv"
    )
    FetchContent_MakeAvailable(foobar)
endif(ESP_PLATFORM)
