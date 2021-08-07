./ltnc example/test/test.asm.ltn -p -o3\
	example/test/test.ltn\
	example/test/test2.ltn

./ltna example/test/test.bin.ltn example/test/test.asm.ltn -bin

./ltnvm -run example/test/test.bin.ltn -bin
# ./ltnvm -bench=10000 example/test/test.bin.ltn -bin