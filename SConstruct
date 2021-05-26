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

dirs = [
	".",
	"cli",
	"litan",
	"litan/program",
	"litan/utils",
	"litan/vm",
	"litan/vm/registers",
	"litan/vm/extensions",
	"litan/assembler",
]

incl = []
libs = []


files = []
for dir in dirs:
	files.append(Glob(dir + "/*.cxx"))


env = Environment(CXX = "clang++", CXXFLAGS = flags, CPPPATH = dirs + incl, CPPDEFINES = [], LIBS = libs, LIBPATH = ".", SCONS_CXX_STANDART="c++20", 
	CXXCOMSTR = "[Compiling] $TARGET",
	LINKCOMSTR = "[Linking] $TARGET")
env.Append(CPPDEFINES = [
	"SFML_STATIC"
])
env.Program('vm', files)
