echo "Compile: O0"
./ltnc example/benchmark/testNoOpt.ltna -O0 -c example/benchmark/test.ltns
./ltna example/benchmark/testNoOpt.ltnx example/benchmark/testNoOpt.ltna -hex
echo ""
echo "Compile: O1"
./ltnc example/benchmark/testO1.ltna -O1 -c example/benchmark/test.ltns
./ltna example/benchmark/testO1.ltnx example/benchmark/testO1.ltna -hex
echo ""
echo "Compile: O2"
./ltnc example/benchmark/testO2.ltna -O2 -c example/benchmark/test.ltns
./ltna example/benchmark/testO2.ltnx example/benchmark/testO2.ltna -hex
echo ""
echo "Compile: O3"
./ltnc example/benchmark/testO3.ltna -O3 -c example/benchmark/test.ltns
./ltna example/benchmark/testO3.ltnx example/benchmark/testO3.ltna -hex
