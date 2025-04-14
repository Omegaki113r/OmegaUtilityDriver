set( PROJ_HEADER_DIRS ${UTILITY_ROOT_DIR}/inc )
set( PROJ_SOURCES ${UTILITY_ROOT_DIR}/src/OmegaUtilityDriver.cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
    
add_library(OmegaUtilityDriver STATIC ${PROJ_SOURCES})
target_include_directories(OmegaUtilityDriver PUBLIC ${PROJ_HEADER_DIRS})