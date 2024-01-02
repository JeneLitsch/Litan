cmake . -D CMAKE_CXX_COMPILER=${1:-clang++} -B build -S . 
cd build
make -j8
cd ..
mkdir -p ./bin
cp build/exeltn bin/ltn
cp build/exeltnc bin/ltnc
cp build/exeltnvm bin/ltnvm
cp build/exeltninfo bin/ltninfo