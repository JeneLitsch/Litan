run () {
	echo "Testing \"$1\""
	ltnFile="test/$1.ltn"
	asmFile="test/$1.asm.ltn"
	binFile="test/$1.bin.ltn"
	./bin/ltnc 	$asmFile ./stdlib $ltnFile
	./bin/ltna 	$binFile  $asmFile
	./bin/ltnvm $binFile
	echo 
}

run "vars"
run "fx"
run "io"
run "modify"
run "andOr"
run "type"
run "misc"
run "struct"
run "casting"