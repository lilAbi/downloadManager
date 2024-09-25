# downloadManager

Build/Run Instructions:

1. grab libraries using conan:

conan install . --output-folder=<cmake/build/directory>/build --build=missing

2. link the cmake toolchain that conan just created to your cmake build
   -DCMAKE_TOOLCHAIN_FILE=<cmake/build/directory>/build/Release/generators/conan_toolchain.cmake

3. run cmake and build app