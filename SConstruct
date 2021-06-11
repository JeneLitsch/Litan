class Builder:
	__libs = []
	__libInclude = []
	__flags = []
	__compiler = ""

	def __init__(self, compiler, flags):
		self.__compiler = compiler
		self.__flags = flags

	def __makeEnvironment(self, includeDirs):
		env = Environment(
			CXX = self.__compiler,
			CXXFLAGS = self.__flags,
			CPPPATH = includeDirs + self.__libInclude,
			CPPDEFINES = [],
			LIBS = self.__libs,
			LIBPATH = ".",
			CXXCOMSTR = "[Compiling] $TARGET",
			LINKCOMSTR = "[Linking] $TARGET")
		return env

	def __getFiles(self, dirs):
		files = []
		for dir in dirs:
			files.append(Glob(dir + "/*.cxx"))
		return files

	def buildLib(self, dirs, target):
		env = self.__makeEnvironment(dirs)
		env.Library(target, self.__getFiles(dirs))
		self.__libs = target
		self.__libInclude += dirs

	def build(self, dirs, target):
		env = self.__makeEnvironment(dirs)
		env.Program(target, self.__getFiles(dirs))

flags = [
	"-std=c++2a",
	]

flags += [
	"-O3",
	"-W",
	"-Wall",
	"-Wextra",
	"-pedantic",
	"-Wpedantic",
	"-pedantic-errors",
	"-Wunused",
	"-Wwrite-strings",
	"-Wzero-length-array",
	"-Wconversion",
	"-Wunreachable-code",
	"-Wuninitialized",
	"-Wold-style-cast",
	"-Walloca",
	"-Wparentheses",
	"-Wunreachable-code-aggressive"
]

print(flags)



dirsLtnC = [
	".",
	"litan/compiler",
	"litan/compiler/utils",
	"litan/compiler/lexer",
	"litan/compiler/parser",
	"litan/compiler/parser/nodes",
	"litan/compiler/parser/nodes/expr",
	"litan/compiler/parser/nodes/stmt",
	"litan/compiler/parser/nodes/decl",
	"litan/compiler/compiler",
	"litan/compiler/compiler/evaluation",
	"litan/compiler/compiler/components",
	"litan/compiler/compiler/scoping",
	"litan/compiler/compiler/utils",
]

dirsLtnA = [
	"litan/assembler",
]

dirsLtnVm = [
	".",
	"litan/vm",
	"litan/vm/memory",
	"litan/vm/extensions",
]


dirsShared = [
	"litan/shared",
	"litan/shared/program",
]



builder = Builder("clang++", flags)

builder.buildLib(dirsShared, "ltnShared") 
builder.build(dirsLtnC, "ltnc")
builder.build(dirsLtnA, "ltna")
builder.build(dirsLtnVm, "ltnvm")