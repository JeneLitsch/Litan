echo "Compile: O0"
./ltnc example/benchmark/testNoOpt.asm.ltn -O0 -c example/benchmark/test.ltn
./ltna example/benchmark/testNoOpt.hex.ltn example/benchmark/testNoOpt.asm.ltn -hex
echo ""
echo "Compile: O1"
./ltnc example/benchmark/testO1.asm.ltn -O1 -c example/benchmark/test.ltn
./ltna example/benchmark/testO1.hex.ltn example/benchmark/testO1.asm.ltn -hex
echo ""
echo "Compile: O2"
./ltnc example/benchmark/testO2.asm.ltn -O2 -c example/benchmark/test.ltn
./ltna example/benchmark/testO2.hex.ltn example/benchmark/testO2.asm.ltn -hex
echo ""
echo "Compile: O3"
./ltnc example/benchmark/testO3.asm.ltn -O3 -c example/benchmark/test.ltn
./ltna example/benchmark/testO3.hex.ltnx example/benchmark/testO3.asm.ltn -hex
