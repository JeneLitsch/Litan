run () {
	echo "Sandbox \"$1\""
	ltnFile="sandbox/$1.ltn"
	asmFile="sandbox/$1.asm.ltn"
	binFile="sandbox/$1.bin.ltn"
	./bin/ltnc -o --exe $binFile --asm $asmFile --src $ltnFile
	# ./bin/ltnvm_0 --exe $binFile --args Hello World 123
	# ./bin/ltnvm_1 --exe $binFile --args Hello World 123
	./bin/ltnvm --exe $binFile --args Hello World 123
	echo 
}

run_direct () {
	echo "Sandbox \"$1\""
	ltnFile="sandbox/$1.ltn"
	asmFile="sandbox/$1.asm.ltn"
	binFile="sandbox/$1.bin.ltn"
	./bin/ltn --src $ltnFile --args Hello World 123
	echo 
}


# run misc
run_direct misc