cmake . -D CMAKE_CXX_COMPILER=${1:-clang++} -B build -S . 
cd build
make -j8
cd ..
cp build/test/test_plugin/libtest_plugin.so bin/