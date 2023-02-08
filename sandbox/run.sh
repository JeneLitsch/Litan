run () {
	echo "Sandbox \"$1\""
	ltnFile="sandbox/$1.ltn"
	asmFile="sandbox/$1.asm.ltn"
	binFile="sandbox/$1.bin.ltn"
	./bin/ltnc -o --exe $binFile --asm $asmFile -- $ltnFile
	./bin/ltnvm --exe $binFile --args Hello World 123
	echo 
}

run_direct () {
	echo "Sandbox \"$1\""
	ltnFile="sandbox/$1.ltn"
	asmFile="sandbox/$1.asm.ltn"
	binFile="sandbox/$1.bin.ltn"
	./bin/ltn --args Hello World 123 -- $ltnFile
	echo 
}


# run misc
run_direct misc