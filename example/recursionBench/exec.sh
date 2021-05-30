./ltnc example/recursionBench/test.asm.ltn example/recursionBench/test.ltn
./ltna example/recursionBench/test.hex.ltn example/recursionBench/test.asm.ltn -hex

./ltnc example/recursionBench/testOpt.asm.ltn -O3 example/recursionBench/test.ltn
./ltna example/recursionBench/testOpt.hex.ltn example/recursionBench/testOpt.asm.ltn -hex

echo "Old"
./ltnvmPrev -bench=100000 example/recursionBench/testOld.hex.ltn -hex
echo "New"
./ltnvm -bench=100000 example/recursionBench/test.hex.ltn -hex
echo "New Opt"
./ltnvm -bench=100000 example/recursionBench/test.hex.ltn -hex