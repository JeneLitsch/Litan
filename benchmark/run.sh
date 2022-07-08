# run () {
# 	echo "Benchmarking \"$1\""
# 	./bin/ltn benchmark/$1.ltn ./stdlib
# 	echo
# }

run () {
	echo "Benchmarking \"$1\""
	ltnFile="benchmark/$1.ltn"
	asmFile="benchmark/$1.asm.ltn"
	binFile="benchmark/$1.bin.ltn"
	./bin/ltnc 	$binFile -i $ltnFile
	./bin/ltnvm $binFile
	echo 
}

run "array"
run "string"
run "memory"
run "fx"
run "member"
run "range"