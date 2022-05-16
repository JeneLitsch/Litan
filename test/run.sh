# echo "Testing \"$1\""
# asmFile="test/$test.asm.ltn"
# binFile="test/$test.bin.ltn"

# ./bin/ltnc -o $asmFile ./stdlib\
# 	test/algorithm.ltn\
# 	test/arith.ltn\
# 	test/array.ltn\
# 	test/bool.ltn\
# 	test/bits.ltn\
# 	test/bitwise.ltn\
# 	test/compare.ltn\
# 	test/conditional.ltn\
# 	test/exception.ltn\
# 	test/expressions.ltn\
# 	test/functional.ltn\
# 	test/globals.ltn\
# 	test/loops.ltn\
# 	test/main.ltn\
# 	test/math.ltn\
# 	test/namespace.ltn\
# 	test/queue.ltn\
# 	test/random.ltn\
# 	test/range.ltn\
# 	test/stack.ltn\
# 	test/streams.ltn\
# 	test/struct.ltn\
# 	test/switch.ltn\
# 	test/types.ltn\
# 	test/utils.ltn\

# ./bin/ltna 	$binFile  $asmFile
# ./bin/ltnvm $binFile

./bin/ltn ./stdlib\
	test/sphinx/sphinx.ltn\
	test/operators/add.ltn\
	test/operators/bitand.ltn\
	test/operators/bitnot.ltn\
	test/operators/bitor.ltn\
	test/operators/bitxor.ltn\
	test/operators/div.ltn\
	test/operators/mlt.ltn\
	test/operators/mod.ltn\
	test/operators/neg.ltn\
	test/operators/pow.ltn\
	test/operators/shift_l.ltn\
	test/operators/shift_r.ltn\
	test/operators/sub.ltn\
	test/main.ltn