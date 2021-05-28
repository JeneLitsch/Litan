echo "Compile: O0"
./ltnc example/benchmark/testNoOpt.ltn -O0 -c example/benchmark/test.ltns
echo ""
echo "Compile: O1"
./ltnc example/benchmark/testO1.ltn -O1 -c example/benchmark/test.ltns
echo ""
echo "Compile: O2"
./ltnc example/benchmark/testO2.ltn -O2 -c example/benchmark/test.ltns
echo ""
echo "Compile: O3"
./ltnc example/benchmark/testO3.ltn -O3 -c example/benchmark/test.ltns