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

dirsLtnVm = [
	".",
	"cli",
	"litan/shared",
	"litan/shared/program",
	"litan/vm",
	"litan/vm/registers",
	"litan/vm/extensions",
	"litan/assembler",
]

dirsLtnC = [
	".",
	"litan/shared",
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
]

def run(dirs, target):
	files = []
	for dir in dirs:
		files.append(Glob(dir + "/*.cxx"))


	env = Environment(CXX = "clang++", CXXFLAGS = flags, CPPPATH = dirs, CPPDEFINES = [], LIBS = [], LIBPATH = ".", SCONS_CXX_STANDART="c++20", 
		CXXCOMSTR = "[Compiling] $TARGET",
		LINKCOMSTR = "[Linking] $TARGET")
	env.Append(CPPDEFINES = [
		"SFML_STATIC"
	])
	env.Program(target, files)

run(dirsLtnVm, "ltnvm")
run(dirsLtnC, "ltnc")