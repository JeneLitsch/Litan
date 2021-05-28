echo "Testing: O0"
./ltnvm -bench example/benchmark/testNoOpt.ltn 100000
echo ""
echo "Testing: 01"
./ltnvm -bench example/benchmark/testO1.ltn 100000
echo ""
echo "Testing: 02"
./ltnvm -bench example/benchmark/testO2.ltn 100000
echo ""
echo "Testing: 03"
./ltnvm -bench example/benchmark/testO3.ltn 100000