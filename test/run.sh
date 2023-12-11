files=(
	"test/main.ltn"
	"test/sphinx/sphinx.ltn" 

	"test/var.ltn"
	"test/global.ltn"
	"test/define.ltn"
	"test/assign.ltn"
	"test/block.ltn"
	"test/structured_bindings.ltn"
	"test/literals.ltn"
	"test/if_else.ltn"
	"test/switch.ltn"
	"test/choose.ltn"
	"test/for.ltn"
	"test/while.ltn"
	"test/throw.ltn"
	"test/lambda.ltn"
	"test/map.ltn"
	"test/reflect_location.ltn"
	"test/reflect_function.ltn"
	"test/reflect_namespace.ltn"
	"test/iife.ltn"
	"test/function_pointers.ltn"
	"test/tuple.ltn"
	"test/struct.ltn"
	"test/invoke_member.ltn"
	"test/variadic.ltn"
	"test/special_members.ltn"
	"test/cofunction.ltn"
	"test/colambda.ltn"

	"test/op_arith_add.ltn"
	"test/op_arith_sub.ltn"
	"test/op_arith_mlt.ltn"
	"test/op_arith_div.ltn"
	"test/op_arith_mod.ltn"
	"test/op_arith_pow.ltn"
	"test/op_neg.ltn"
	"test/op_bit_not.ltn"
	"test/op_bit_and.ltn"
	"test/op_bit_or.ltn"
	"test/op_bit_xor.ltn"
	"test/op_bit_shift_l.ltn"
	"test/op_bit_shift_r.ltn"
	"test/op_logic_not.ltn"
	"test/op_logic_and.ltn"
	"test/op_logic_or.ltn"
	"test/op_comp_eql.ltn"
	"test/op_comp_ueql.ltn"
	"test/op_comp_less.ltn"
	"test/op_comp_less_eql.ltn"
	"test/op_comp_greater.ltn"
	"test/op_comp_greater_eql.ltn"
	"test/op_comp_spaceship.ltn"
	"test/op_elvis.ltn"
	"test/op_index.ltn"
	"test/op_nullco.ltn"
	"test/op_nulltest.ltn"
	"test/op_ternary.ltn"

	"test/std/arity.ltn"
	"test/std/bits_get.ltn"
	"test/std/bits_set.ltn"
	"test/std/is_type.ltn"
	
	"test/std/container/at.ltn"
	"test/std/container/back.ltn"
	"test/std/container/contains.ltn"
	"test/std/container/empty.ltn"
	"test/std/container/front.ltn"
	"test/std/container/insert.ltn"
	"test/std/container/peek.ltn"
	"test/std/container/pop.ltn"
	"test/std/container/push.ltn"
	"test/std/container/remove.ltn"
	"test/std/container/size.ltn"

	"test/std/algorithm/for_each.ltn"
	"test/std/algorithm/sum.ltn"
	"test/std/algorithm/sort_ascn.ltn"
	"test/std/algorithm/sort_desc.ltn"
	"test/std/algorithm/is_sorted_ascn.ltn"
	"test/std/algorithm/is_sorted_desc.ltn"
	"test/std/algorithm/find.ltn"
	"test/std/algorithm/fill.ltn"
	"test/std/algorithm/reverse.ltn"
	"test/std/algorithm/transform.ltn"
	"test/std/algorithm/zip.ltn"
	"test/std/algorithm/reduce_l.ltn"
	"test/std/algorithm/reduce_r.ltn"

	"test/std/functional/arity.ltn"
	"test/std/functional/invoke.ltn"
	"test/std/functional/chain.ltn"
	"test/std/functional/is_successful.ltn"
	"test/std/functional/is_variadic.ltn"

	"test/std/io/is_eof.ltn"
	"test/std/io/read.ltn"
	"test/std/io/readln.ltn"
	"test/std/io/read_bool.ltn"
	"test/std/io/read_char.ltn"
	"test/std/io/read_int.ltn"
	"test/std/io/read_float.ltn"
	"test/std/io/read_all.ltn"
	"test/std/io/utils.ltn"

	"test/std/json/parse.ltn"
	"test/std/json/print.ltn"

	"test/std/math/pi.ltn"
	"test/std/math/min.ltn"
	"test/std/math/max.ltn"
	"test/std/math/clamp.ltn"
	"test/std/math/round.ltn"
	"test/std/math/floor.ltn"
	"test/std/math/ceil.ltn"
	"test/std/math/abs.ltn"
	"test/std/math/sin.ltn"
	"test/std/math/cos.ltn"
	"test/std/math/tan.ltn"
	"test/std/math/sqrt.ltn"
	"test/std/math/cbrt.ltn"
	"test/std/math/hypot.ltn"
	"test/std/math/log.ltn"
	"test/std/math/ln.ltn"
	"test/std/math/ld.ltn"
	"test/std/math/lg.ltn"
	"test/std/math/pow.ltn"
	"test/std/math/lerp.ltn"
	"test/std/math/is_between.ltn"

	"test/std/iter/utils.ltn"
	"test/std/iter/array.ltn"
	"test/std/iter/tuple.ltn"
	"test/std/iter/range.ltn"
	"test/std/iter/string.ltn"
	"test/std/iter/map.ltn"
	"test/std/iter/zipped.ltn"
	"test/std/iter/reversed.ltn"

	"test/std/string/str.ltn"
	"test/std/string/split.ltn"
	"test/std/string/join.ltn"
	"test/std/string/replace.ltn"

	"test/std/type/mono.ltn"
	"test/std/type/pair.ltn"
	"test/std/type/is.ltn"
	"test/std/type/cast.ltn"
	"test/std/type/has_special_.ltn"
	"test/std/type/match_type.ltn"
)

bin_file="tmp/bin"
asm_file="tmp/asm"

rm $bin_file
rm $asm_file

./bin/ltnc -o --asm $asm_file --exe $bin_file --src ${files[*]}
./bin/ltnvm --exe $bin_file --args Hello World 123

# ./bin/ltn --src ${files[*]} --args Hello World 123