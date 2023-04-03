cmake_minimum_required(VERSION 3.25)
project(downloadManager)

set(CMAKE_CXX_STANDARD 20)

#find and include boost library from conan toolchain
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

#find and include glfw3 library from conan toolchain
find_package(glfw3 REQUIRED)
include_directories(${glfw3_INCLUDE_DIR})

#find and include imgui library from conan toolchain
find_package(imgui REQUIRED)
include_directories(${imgui_INCLUDE_DIR})

#add manually added libraries
add_subdirectory(lib)

#create the executable
add_executable(downloadManager src/main.cpp src/core/application.cpp src/core/application.h src/ui/ui.cpp src/ui/ui.h src/model/image_container.h)

if(WIN32)
    target_link_libraries(downloadManager
            ${Boost_LIBRARIES}
            ${glfw3_LIBRARIES}
            ${imgui_LIBRARIES}
            imgui_backends
            glad
            wsock32)
else()
    target_link_libraries(downloadManager
            ${Boost_LIBRARIES}
            ${glfw3_LIBRARIES}
            ${imgui_LIBRARIES})
endif()

