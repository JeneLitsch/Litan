run () {
	echo "Testing \"$1\""
	ltnFile="test/logic/$1.ltn"
	asmFile="test/logic/$1.asm.ltn"
	binFile="test/logic/$1.bin.ltn"
	./bin/ltnc 	$asmFile ./stdlib $ltnFile
	./bin/ltna 	$binFile  $asmFile
	./bin/ltnvm $binFile
	echo 
}

run "compare"
run "short_circuit"