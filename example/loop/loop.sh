echo "for"
./ltnc example/loop/for.asm.ltn example/loop/for.ltn
./ltna example/loop/for.hex.ltn example/loop/for.asm.ltn -hex
./ltnvm -bench=100000 example/loop/for.hex.ltn -hex
echo ""

echo "for optimized"
./ltnc example/loop/forOpt.asm.ltn -O3 example/loop/for.ltn
./ltna example/loop/forOpt.hex.ltn example/loop/for.asm.ltn -hex
./ltnvm -bench=100000 example/loop/forOpt.hex.ltn -hex
echo ""

echo "repeat"
./ltnc example/loop/repeat.asm.ltn example/loop/repeat.ltn
./ltna example/loop/repeat.hex.ltn example/loop/repeat.asm.ltn -hex
./ltnvm -bench=100000 example/loop/repeat.hex.ltn -hex
echo ""

echo "repeat optimized"
./ltnc example/loop/repeatOpt.asm.ltn -O3 example/loop/repeat.ltn
./ltna example/loop/repeatOpt.hex.ltn example/loop/repeatOpt.asm.ltn -hex
./ltnvm -bench=100000 example/loop/repeatOpt.hex.ltn -hex
echo ""
