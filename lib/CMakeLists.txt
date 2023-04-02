#this cmake file builds manually added 3rd party libaries

#---------------------------------------------------------------------


#add missing backend files from imgui
file(GLOB IMGUI_BACKENDS_SRC CONFIGURE_DEPENDS imgui/include/backends/*.cpp)
add_library(imgui_backends SHARED ${IMGUI_BACKENDS_SRC})
target_include_directories(imgui_backends PUBLIC imgui/include)

#find and include imgui library from conan toolchain
find_package(imgui REQUIRED)
include_directories(${imgui_INCLUDE_DIR})

#this depends on imgui library
target_link_libraries(imgui_backends PUBLIC ${imgui_LIBRARIES} ${glfw3_LIBRARIES})


#---------------------------------------------------------------------


#add glad library
add_library(glad SHARED glad/src/gl.c)
target_include_directories(glad PUBLIC glad/include)


#---------------------------------------------------------------------