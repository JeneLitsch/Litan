echo "Testing \"$1\""
asmFile="test/$test.asm.ltn"
binFile="test/$test.bin.ltn"

./bin/ltnc 	$asmFile ./stdlib\
	test/algorithm.ltn\
	test/arith.ltn\
	test/array.ltn\
	test/bool.ltn\
	test/compare.ltn\
	test/captures.ltn\
	test/exception.ltn\
	test/loops.ltn\
	test/main.ltn\
	test/math.ltn\
	test/namespace.ltn\
	test/queue.ltn\
	test/range.ltn\
	test/stack.ltn\
	test/struct.ltn\
	test/types.ltn\
	test/utils.ltn\

./bin/ltna 	$binFile  $asmFile
./bin/ltnvm $binFile