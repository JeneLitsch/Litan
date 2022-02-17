run () {
	echo "Testing \"$1\""
	ltnFile="test/functional/$1.ltn"
	asmFile="test/functional/$1.asm.ltn"
	binFile="test/functional/$1.bin.ltn"
	./bin/ltnc 	$asmFile ./stdlib $ltnFile
	./bin/ltna 	$binFile  $asmFile
	./bin/ltnvm $binFile
	echo 
}

run "lambda"
run "fxptr"