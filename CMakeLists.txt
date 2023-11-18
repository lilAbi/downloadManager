cmake_minimum_required(VERSION 3.26)
project(downloadManager)

set(CMAKE_CXX_STANDARD 20)

include_directories(./bindings)
include_directories(src)

find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)
find_package(glad REQUIRED)
find_package(CURL REQUIRED)

include_directories(${glfw3_INCLUDE_DIR} ${glad_INCLUDE_DIR} ${imgui_INCLUDE_DIR} ${CURL_INCLUDE_DIR} )

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "src/*.cpp" "src/*/*.cpp" "bindings/*.cpp" "src/*.h" "src/*/*.h" "bindings/*.h")

add_executable(downloadManager ${sources} )

target_link_libraries(downloadManager ${glfw3_LIBRARIES} ${glad_LIBRARIES} ${imgui_LIBRARIES} ${CURL_LIBRARIES})
