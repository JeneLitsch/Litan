run () {
	echo "Benchmarking \"$1\""
	./bin/ltn benchmark/$1.ltn ./stdlib
	echo
}

run "string"
run "memory"