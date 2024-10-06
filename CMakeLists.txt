cmake_minimum_required(VERSION 3.28)
project(downloadManager)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(src)
include_directories(bindings)

find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)
find_package(spdlog REQUIRED)

include_directories(
        ${glfw3_INCLUDE_DIR}
        ${glad_INCLUDE_DIR}
        ${imgui_INCLUDE_DIR}
        ${glm_INCLUDE_DIR}
        ${spdlog_INCLUDE_DIR}
)

file(GLOB sources CONFIGURE_DEPENDS
        "src/main.cpp"
        "src/core/*.cpp"
        "src/ui/*.cpp"
        "src/window/*.cpp"
        "src/download/*.cpp"
        "bindings/*.cpp"
)

add_executable(downloadManager ${sources})

target_link_libraries(downloadManager PUBLIC
        imgui::imgui
        glfw
        glad::glad
        glm::glm
        spdlog::spdlog
)
