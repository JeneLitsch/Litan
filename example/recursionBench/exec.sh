./ltnc example/recursionBench/test.asm.ltn example/recursionBench/test.ltn
./ltna example/recursionBench/test.hex.ltn example/recursionBench/test.asm.ltn -hex
echo "Old"
./ltnvmOld -bench=100000 example/recursionBench/testOld.hex.ltn -hex
echo "New"
./ltnvm -bench=100000 example/recursionBench/test.hex.ltn -hex