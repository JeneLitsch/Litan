run () {
	ltnFile="test/$1.ltn"
	asmFile="test/$1.asm.ltn"
	binFile="test/$1.bin.ltn"
	./bin/ltnc 	$asmFile ./stdlib $ltnFile
	./bin/ltna 	$binFile  $asmFile
	./bin/ltnvm $binFile
}

run "vars"