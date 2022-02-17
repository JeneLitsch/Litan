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
run "io"
run "modify"
run "type"
run "misc"
run "struct"
run "casting"
run "math"
run "algorithm"
run "array"
run "container"
run "clone"
run "exception"
run "string"

run_error () {
	echo "Testing Errors"
	./bin/ltn test/error1.ltn test/error2.ltn ./stdlib
	echo
}

run_error
