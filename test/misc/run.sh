run () {
	echo "Testing \"$1\""
	ltnFile="test/misc/$1.ltn"
	asmFile="test/misc/$1.asm.ltn"
	binFile="test/misc/$1.bin.ltn"
	./bin/ltnc 	$asmFile ./stdlib $ltnFile
	./bin/ltna 	$binFile  $asmFile
	./bin/ltnvm $binFile
	echo 
}

run "vars"
run "modify"
run "math"
run "algorithm"
run "operators"
