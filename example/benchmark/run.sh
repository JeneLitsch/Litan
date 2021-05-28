echo "Testing: O0"
./ltnvm -bench example/benchmark/testNoOpt.ltnx 100000
echo ""
echo "Testing: 01"
./ltnvm -bench example/benchmark/testO1.ltnx 100000
echo ""
echo "Testing: 02"
./ltnvm -bench example/benchmark/testO2.ltnx 100000
echo ""
echo "Testing: 03"
./ltnvm -bench example/benchmark/testO3.ltnx 100000