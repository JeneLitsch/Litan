op_tests=( 
	"test/core_lang/op/add.ltn" 
	"test/core_lang/op/bitand.ltn" 
	"test/core_lang/op/bitnot.ltn" 
	"test/core_lang/op/bitor.ltn" 
	"test/core_lang/op/bitxor.ltn" 
	"test/core_lang/op/div.ltn" 
	"test/core_lang/op/elvis.ltn" 
	"test/core_lang/op/eql.ltn" 
	"test/core_lang/op/greater_eql.ltn" 
	"test/core_lang/op/greater.ltn" 
	"test/core_lang/op/index.ltn" 
	"test/core_lang/op/less_eql.ltn" 
	"test/core_lang/op/less.ltn" 
	"test/core_lang/op/logand.ltn" 
	"test/core_lang/op/lognot.ltn" 
	"test/core_lang/op/logor.ltn" 
	"test/core_lang/op/mlt.ltn" 
	"test/core_lang/op/mod.ltn" 
	"test/core_lang/op/neg.ltn" 
	"test/core_lang/op/nullco.ltn" 
	"test/core_lang/op/nulltest.ltn" 
	"test/core_lang/op/pow.ltn" 
	"test/core_lang/op/shift_l.ltn" 
	"test/core_lang/op/shift_r.ltn" 
	"test/core_lang/op/space_ship.ltn" 
	"test/core_lang/op/sub.ltn" 
	"test/core_lang/op/ternary.ltn" 
	"test/core_lang/op/uneql.ltn" 
)

core_tests=(
	"test/core_lang/for.ltn" 
	"test/core_lang/globals.ltn" 
	"test/core_lang/if_else.ltn" 
	"test/core_lang/iife.ltn" 
	"test/core_lang/lambda_captures.ltn" 
	"test/core_lang/namespace.ltn" 
	"test/core_lang/switch.ltn" 
	"test/core_lang/throw.ltn" 
	"test/core_lang/while.ltn" 
	${op_tests[*]}
)


stdlib_tests=(
	"test/stdlib/array.ltn" 
	"test/stdlib/algorithm.ltn" 
	"test/stdlib/bits_get.ltn" 
	"test/stdlib/bits_set.ltn" 
	"test/stdlib/empty.ltn" 
	"test/stdlib/functional.ltn" 
	"test/stdlib/is_type_x.ltn" 
	"test/stdlib/is_type.ltn" 
	"test/stdlib/math.ltn" 
	"test/stdlib/random.ltn" 
	"test/stdlib/size.ltn" 
	"test/stdlib/streams.ltn" 
	"test/stdlib/typeid.ltn" 
	"test/stdlib/typename.ltn" 
)

misc=(
	"test/main.ltn"
	"test/sphinx/sphinx.ltn" 
)

# ./bin/ltn -i ${core_tests[*]} ${stdlib_tests[*]} ${misc[*]} --args Hello World 123

./bin/ltnc -o --asm tmp/bin -i ${core_tests[*]} ${stdlib_tests[*]} ${misc[*]}
./bin/ltnvm tmp/bin --args Hello World 123