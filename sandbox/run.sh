run () {
	echo "Sandbox \"$1\""
	ltnFile="sandbox/$1.ltn"
	asmFile="sandbox/$1.asm.ltn"
	binFile="sandbox/$1.bin.ltn"
	./bin/ltnc  $asmFile $ltnFile
	./bin/ltna 	$binFile $asmFile
	./bin/ltnvm $binFile %Hello %%World 123
	echo 
}

run_direct () {
	echo "Sandbox \"$1\""
	ltnFile="sandbox/$1.ltn"
	asmFile="sandbox/$1.asm.ltn"
	binFile="sandbox/$1.bin.ltn"
	./bin/ltn $ltnFile %Hello %World %123
	echo 
}


run_direct array
run_direct misc
run_direct fx_qualifiers