echo "Testing \"$1\""
asmFile="unit_testing/$test.asm.ltn"
binFile="unit_testing/$test.bin.ltn"

./bin/ltnc 	$asmFile ./stdlib\
	unit_testing/utils.ltn\
	unit_testing/main.ltn\
	unit_testing/arith.ltn\
	unit_testing/comp.ltn\
	unit_testing/array.ltn\
	unit_testing/queue.ltn\
	unit_testing/math.ltn\
	unit_testing/exception.ltn\

./bin/ltna 	$binFile  $asmFile
./bin/ltnvm $binFile