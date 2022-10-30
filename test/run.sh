files=(
	"test/main.ltn"
	"test/sphinx/sphinx.ltn" 
	
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
	"test/op_index.ltn"

	"test/if_else.ltn"
	"test/switch.ltn"
	"test/choose.ltn"
	"test/for.ltn"
	"test/while.ltn"
	"test/throw.ltn"
)

bin_file="tmp/bin"
asm_file="tmp/asm"

rm $bin_file
rm $asm_file

./bin/ltnc -o --asm $asm_file --exe $bin_file --src ${files[*]}
./bin/ltnvm --exe $bin_file --args Hello World 123