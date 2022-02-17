run () {
	echo "Testing \"$1\""
	ltnFile="test/datatypes/$1.ltn"
	asmFile="test/datatypes/$1.asm.ltn"
	binFile="test/datatypes/$1.bin.ltn"
	./bin/ltnc 	$asmFile ./stdlib $ltnFile
	./bin/ltna 	$binFile  $asmFile
	./bin/ltnvm $binFile
	echo 
}

run "type"
run "struct"
run "casting"
run "array"
run "container"
run "clone"
run "string"
