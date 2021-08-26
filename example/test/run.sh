./ltnc example/test/test.asm.ltn -p -o3\
	example/test/test.ltn

./ltna example/test/test.bin.ltn example/test/test.asm.ltn -bin

./ltnvm -run example/test/test.bin.ltn -bin