echo "for"
./ltnc example/loop/for.ltn -S example/loop/for.ltns
./ltnvm -bench example/loop/for.ltn 100000
echo ""

echo "for optimized"
./ltnc example/loop/forOpt.ltn -O3 -S example/loop/for.ltns
./ltnvm -bench example/loop/forOpt.ltn 100000
echo ""

echo "repeat"
./ltnc example/loop/repeat.ltn -S example/loop/repeat.ltns
./ltnvm -bench example/loop/repeat.ltn 100000
echo ""

echo "repeat optimized"
./ltnc example/loop/repeatOpt.ltn -O3 -S example/loop/repeat.ltns
./ltnvm -bench example/loop/repeatOpt.ltn 100000
echo ""
