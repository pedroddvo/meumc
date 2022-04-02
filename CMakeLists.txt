cmake_minimum_required(VERSION 3.21.0)
project(meumc VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_subdirectory(src)

target_link_libraries(meumc PRIVATE glfw)
target_link_libraries(meumc PRIVATE glad::glad)
target_link_libraries(meumc PRIVATE cglm_headers)

add_subdirectory(dependencies/cglm/ EXCLUDE_FROM_ALL)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
