echo "for"
./ltnc example/loop/for.ltna example/loop/for.ltns
./ltna example/loop/for.ltnx example/loop/for.ltna -hex
./ltnvm -bench=100000 example/loop/for.ltnx -hex
echo ""

echo "for optimized"
./ltnc example/loop/forOpt.ltna -O3 example/loop/for.ltns
./ltna example/loop/forOpt.ltnx example/loop/for.ltna -hex
./ltnvm -bench=100000 example/loop/forOpt.ltnx -hex
echo ""

echo "repeat"
./ltnc example/loop/repeat.ltna example/loop/repeat.ltns
./ltna example/loop/repeat.ltnx example/loop/repeat.ltna -hex
./ltnvm -bench=100000 example/loop/repeat.ltnx -hex
echo ""

echo "repeat optimized"
./ltnc example/loop/repeatOpt.ltna -O3 example/loop/repeat.ltns
./ltna example/loop/repeatOpt.ltnx example/loop/repeatOpt.ltna -hex
./ltnvm -bench=100000 example/loop/repeatOpt.ltnx -hex
echo ""
