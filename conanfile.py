from conan.tools.cmake import cmake_layout
import os, shutil
from conan import ConanFile
from conan.tools.files import save, load

def layout(self):
    cmake_layout(self) ###,  src_folder="mysrcfolder")

def requirements(self):
    self.requires("gtest/1.15.0")
    
class Pkg(ConanFile):
   ...
   requires = "gtest/1.15.0"
   def generate(self):
        openssl = self.dependencies["gtest"]
   ##generators = "CMakeToolchain"
   settings = "os", "compiler", "build_type", "arch"
   generators = "CMakeDeps", "CMakeToolchain"
   exports_sources = "CMakeLists.txt"

   def layout(self):
       self.folders.source = "src"
       self.folders.build = "build"

   def source(self):
       # emulate a download from web site
       save(self, "CMakeLists.txt", "MISTAKE: Very old CMakeLists to be replaced")
       # Now I fix it with one of the exported files
       # shutil.copy("../CMakeLists.txt", ".")
       shutil.copy(os.path.join(self.export_sources_folder, "CMakeLists.txt", "."))
def build(self):
    cmake = CMake(self)
    cmake.configure()
    cmake.build()
    cmake.install()
    cmake.test()

