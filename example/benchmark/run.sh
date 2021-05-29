echo "Testing: O0"
./ltnvm -bench=100000 example/benchmark/testNoOpt.hex.ltn -hex
echo ""
echo "Testing: 01"
./ltnvm -bench=100000 example/benchmark/testO1.hex.ltn -hex
echo ""
echo "Testing: 02"
./ltnvm -bench=100000 example/benchmark/testO2.hex.ltn -hex
echo ""
echo "Testing: 03"
./ltnvm -bench=100000 example/benchmark/testO3.hex.ltn -hex