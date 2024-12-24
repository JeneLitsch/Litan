cmake . -D CMAKE_CXX_COMPILER=${1:-clang++} -B build -S . 
cmake --build build -j8
cp build/test/test_plugin/libtest_plugin.so bin/