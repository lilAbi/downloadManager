import os

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout
from conan.tools.files import copy


class ImGuiExample(ConanFile):
    description = "ConanFile for Tower Of God"
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires("imgui/1.91.2-docking")
        self.requires("glfw/3.4")
        self.requires("glad/0.1.36")
        self.requires("glm/1.0.1")
        self.requires("spdlog/1.13.0")

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
        if self.settings.os == "Windows":
            self.options["glad"].gl_version = "4.6"
        if self.settings.os == "Macos":
            self.options["glad"].gl_version = "4.1"
        #self.options["glad"].extensions = "ANY"

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
