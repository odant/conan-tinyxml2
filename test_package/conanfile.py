# Tests for tinyxml2 Conan package
# Dmitriy Vetutnev, Odant 2019


from conans import ConanFile, CMake


class PackageTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"

    def build_requiments(self):
        if self.options["tinyxml2"].ninja:
            self.build_requires("ninja_installer/1.9.0@bincrafters/stable")

    def imports(self):
        self.copy("*.pdb", dst="bin", src="bin")

    def build(self):
        gen = "Ninja" if self.options["tinyxml2"].ninja else None
        cmake = CMake(self, generator=gen, msbuild_verbosity='normal')
        cmake.verbose = True
        cmake.configure()
        cmake.build()
        self.cmake_is_multi_configuration = cmake.is_multi_configuration

    def test(self):
        if self.cmake_is_multi_configuration:
            self.run("ctest --verbose --build-config %s" % self.settings.build_type)
        else:
            self.run("ctest --verbose")
