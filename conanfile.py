# tinyxml2 Conan package
# Dmitriy Vetutnev, Odant 2019


from conans import ConanFile, CMake


class minizipConan(ConanFile):
    name = "tinyxml2"
    version = "7.0.1"
    license = "ZLIB http://www.zlib.net/zlib_license.html"
    description = "TinyXML-2 is a simple, small, efficient, C++ XML parser that can be easily integrated into other programs."
    url = "https://github.com/odant/conan-tinyxml2"
    settings = {
        "os": ["Windows", "Linux"],
        "compiler": ["Visual Studio", "gcc"],
        "build_type": ["Debug", "Release"],
        "arch": ["x86", "x86_64", "mips"]
    }
    options = {
        "with_unit_tests": [True, False]
    }
    default_options = "with_unit_tests=False"
    generators = "cmake"
    exports_sources = "src/*", "CMakeLists.txt", "Findtinyxml2.cmake"
    no_copy_source = True
    build_policy = "missing"

    def build(self):
        build_type = "RelWithDebInfo" if self.settings.build_type == "Release" else "Debug"
        cmake = CMake(self, build_type=build_type, msbuild_verbosity='normal')
        cmake.verbose = True
        cmake.definitions["BUILD_SHARED_LIBS:BOOL"] = "OFF"
        if self.options.with_unit_tests:
            cmake.definitions["BUILD_TESTING:BOOL"] = "ON"
        cmake.configure()
        cmake.build()
        if self.options.with_unit_tests:
            if cmake.is_multi_configuration:
                self.run("ctest --output-on-failure --build-config %s" % build_type)
            else:
                self.run("ctest --output-on-failure")

    def package(self):
        self.copy("Findtinyxml2.cmake", dst=".", src=".")
        self.copy("tinyxml2.h", dst="include", src="src")
        self.copy("tinyxml2.lib", dst="lib", src="lib")
        self.copy("tinyxml2d.lib", dst="lib", src="lib")
        self.copy("libtinyxml2.a", dst="lib", src="lib")
        self.copy("libtinyxml2d.a", dst="lib", src="lib")
        self.copy("*tinyxml2.pdb", dst="bin", src="src", keep_path=False)
        self.copy("*tinyxml2d.pdb", dst="bin", src="src", keep_path=False)

    def package_id(self):
        self.info.options.with_unit_tests = "any"

    def package_info(self):
        if self.settings.build_type == "Debug":
            self.cpp_info.libs = ["tinyxml2d"]
            self.cpp_info.defines = ["TINYXML2_DEBUG"]
        else:
            self.cpp_info.libs = ["tinyxml2"]
