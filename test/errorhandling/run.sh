run () {
	echo "Testing \"$1\""
	ltnFile="test/errorhandling/$1.ltn"
	asmFile="test/errorhandling/$1.asm.ltn"
	binFile="test/errorhandling/$1.bin.ltn"
	./bin/ltnc 	$asmFile ./stdlib $ltnFile
	./bin/ltna 	$binFile  $asmFile
	./bin/ltnvm $binFile
	echo 
}

run "exception"

run_error () {
	echo "Testing Errors"
	./bin/ltn test/errorhandling/error1.ltn test/errorhandling/error2.ltn ./stdlib
	echo
}

run_error
