op_tests=( 
	"test/core_lang/op_arith_add.ltn" 
	"test/core_lang/op_arith_sub.ltn" 
	"test/core_lang/op_arith_mlt.ltn" 
	"test/core_lang/op_arith_div.ltn" 
	"test/core_lang/op_arith_mod.ltn"
	"test/core_lang/op_arith_neg.ltn" 

	"test/core_lang/op_bit_and.ltn" 
	"test/core_lang/op_bit_not.ltn" 
	"test/core_lang/op_bit_or.ltn" 
	"test/core_lang/op_bit_xor.ltn" 
	
	"test/core_lang/op_comp_eql.ltn" 
	"test/core_lang/op_comp_greater_eql.ltn" 
	"test/core_lang/op_comp_greater.ltn" 
	"test/core_lang/op_comp_less_eql.ltn" 
	"test/core_lang/op_comp_less.ltn" 
	"test/core_lang/op_comp_uneql.ltn" 
	"test/core_lang/op_comp_space_ship.ltn" 
	
	"test/core_lang/op_logic_and.ltn" 
	"test/core_lang/op_logic_not.ltn" 
	"test/core_lang/op_logic_or.ltn" 
	
	"test/core_lang/op/elvis.ltn" 
	"test/core_lang/op/index.ltn" 
	"test/core_lang/op/nullco.ltn" 
	"test/core_lang/op/nulltest.ltn" 
	"test/core_lang/op/pow.ltn" 
	"test/core_lang/op/shift_l.ltn" 
	"test/core_lang/op/shift_r.ltn" 
	"test/core_lang/op/ternary.ltn" 
)

core_tests=(
	"test/core_lang/for.ltn" 
	"test/core_lang/defines.ltn" 
	"test/core_lang/globals.ltn" 
	"test/core_lang/if_else.ltn" 
	"test/core_lang/iife.ltn" 
	"test/core_lang/lambda_captures.ltn" 
	"test/core_lang/namespace.ltn" 
	"test/core_lang/switch.ltn" 
	"test/core_lang/throw.ltn" 
	"test/core_lang/while.ltn" 
	"test/core_lang/decltype.ltn" 
	${op_tests[*]}
)


stdlib_tests=(
	"test/stdlib/algorithm.ltn" 
	"test/stdlib/arity.ltn" 
	"test/stdlib/array.ltn" 
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

bin_file="tmp/bin"
asm_file="tmp/asm"

rm $bin_file
rm $asm_file

# ./bin/ltn --src ${core_tests[*]} ${stdlib_tests[*]} ${misc[*]} --args Hello World 123

./bin/ltnc -o --asm $asm_file --exe $bin_file --src ${core_tests[*]} ${stdlib_tests[*]} ${misc[*]}
./bin/ltnvm --exe $bin_file --args Hello World 123