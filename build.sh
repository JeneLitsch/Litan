cmake . -D CMAKE_CXX_COMPILER=g++-10 -D param=linux-release -B build -S . 
cd build
make -j8
cd ..
mkdir -p ./bin
cp build/exeltn bin/ltn
cp build/exeltnc bin/ltnc
cp build/exeltnvm bin/ltnvm
cp build/exeltninfo bin/ltninfo