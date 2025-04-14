cmake_minimum_required(VERSION 3.5)

set(UTILITY_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
if(ESP_PLATFORM)
  include(${CMAKE_CURRENT_LIST_DIR}/cmake/ESP32xx.cmake)
elseif(WIN32)
  include(${CMAKE_CURRENT_LIST_DIR}/cmake/Windows.cmake)
endif()
