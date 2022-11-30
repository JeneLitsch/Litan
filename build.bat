cmake . -D CMAKE_CXX_COMPILER=cl++ -D param=window-release -B build -S . -G "MinGW Makefiles"
cd build
mingw32-make
cd ..
mkdir -p ./bin
cp build/exeltn.exe bin/ltn.exe
cp build/exeltnc.exe bin/ltnc.exe
cp build/exeltnvm.exe bin/ltnvm.exe
cp build/exeltninfo.exe bin/ltninfo.exe