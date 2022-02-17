run () {
	echo "Testing \"$1\""
	ltnFile="test/io/$1.ltn"
	asmFile="test/io/$1.asm.ltn"
	binFile="test/io/$1.bin.ltn"
	./bin/ltnc 	$asmFile ./stdlib $ltnFile
	./bin/ltna 	$binFile  $asmFile
	./bin/ltnvm $binFile
	echo 
}

run "files"
