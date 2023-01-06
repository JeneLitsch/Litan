run () {
	echo "Example \"$1\""
	ltnFile="examples/$1.ltn"
	asmFile="examples/$1.asm.ltn"
	binFile="examples/$1.bin.ltn"
	./bin/ltn --src $ltnFile --args Hello World 123
	echo 
}


run skytale