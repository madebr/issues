from conans import ConanFile, CMake


class AllLibsTesterCoan(ConanFile):
    name = 'conan_boost_program_opts'
    version = 'master'
    license = 'GPL3'
    settings = 'os', 'compiler', 'build_type', 'arch'
    options = {
        'dynamic_libs': [True, False],
    }
    default_options = (
        'dynamic_libs=False',
    )

    generators = 'cmake',

    _dependencies = {
        'cmake': ('cmake_findboost_modular/1.66.0@bincrafters/stable', ),
        'boost': ('boost_test/1.66.0@bincrafters/stable', ),
    }

    def requirements(self):
        for deps in self._dependencies.values():
            for dep in deps:
                self.requires(dep)

    def configure(self):
        self.options['boost_test'].shared = self.options.dynamic_libs

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
        # cmake.test()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()
