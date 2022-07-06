run () {
	echo "Sandbox \"$1\""
	ltnFile="sandbox/$1.ltn"
	asmFile="sandbox/$1.asm.ltn"
	binFile="sandbox/$1.bin.ltn"
	./bin/ltnc -o $binFile $ltnFile
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


run misc