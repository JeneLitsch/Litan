echo "Testing \"$1\""
asmFile="test/$test.asm.ltn"
binFile="test/$test.bin.ltn"

./bin/ltnc 	$asmFile ./stdlib\
	test/bool.ltn\
	test/utils.ltn\
	test/main.ltn\
	test/arith.ltn\
	test/comp.ltn\
	test/array.ltn\
	test/queue.ltn\
	test/math.ltn\
	test/exception.ltn\
	test/range.ltn\

./bin/ltna 	$binFile  $asmFile
./bin/ltnvm $binFile