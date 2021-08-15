./ltnc example/bench/bench.asm.ltn -p -o3 example/bench/bench2.ltn

./ltna example/bench/bench.bin.ltn example/bench/bench.asm.ltn -bin

./ltnvm -bench=100000 example/bench/bench.bin.ltn -bin
./ltnvm3 -bench=100000 example/bench/bench.bin.ltn -bin
./ltnvm2 -bench=100000 example/bench/bench.bin.ltn -bin