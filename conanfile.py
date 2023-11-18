import os

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout
from conan.tools.files import copy


class ImGuiExample(ConanFile):
    description = "ConanFile for application \"downloadManager\""
    settings = "os", "compiler", "build_type", "arch"

    # generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("imgui/1.89.4")
        self.requires("glfw/3.3.8")
        self.requires("glad/0.1.36")
        # self.requires("libcurl/8.2.0")

    def generate(self):
        toolchain = CMakeToolchain(self)
        dependencies = CMakeDeps(self)
        copy(self, "*glfw*", os.path.join(self.dependencies["imgui"].package_folder, "res", "bindings"),
             os.path.join(self.source_folder, "bindings"))
        copy(self, "*opengl3*", os.path.join(self.dependencies["imgui"].package_folder, "res", "bindings"),
             os.path.join(self.source_folder, "bindings"))
        toolchain.generate()
        dependencies.generate()

    def configure(self):
        self.options["glad"].spec = "gl"
        self.options["glad"].gl_profile = "core"
        self.options["glad"].gl_version = "4.6"
        self.options["glad"].extensions = "ANY"

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
