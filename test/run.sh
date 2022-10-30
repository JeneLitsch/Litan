files=(
	"test/main.ltn"
	"test/op_add.ltn"
	"test/op_sub.ltn"
	"test/op_mlt.ltn"
	"test/op_div.ltn"
	"test/op_mod.ltn"
	"test/op_pow.ltn"
	"test/sphinx/sphinx.ltn" 
)

bin_file="tmp/bin"
asm_file="tmp/asm"

rm $bin_file
rm $asm_file

./bin/ltnc -o --asm $asm_file --exe $bin_file --src ${files[*]}
./bin/ltnvm --exe $bin_file --args Hello World 123