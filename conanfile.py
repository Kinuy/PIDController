from conan import ConanFile

class ConanTutorialRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "PremakeDeps"

    def requirements(self):	
        self.requires("catch2/3.8.0")
        self.requires("cvplot/1.2.2")