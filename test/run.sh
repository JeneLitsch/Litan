files=(
	"test/main.ltn"
	"test/op_add.ltn"
	"test/op_sub.ltn"
	"test/sphinx/sphinx.ltn" 
)

bin_file="tmp/bin"
asm_file="tmp/asm"

rm $bin_file
rm $asm_file

./bin/ltnc -o --asm $asm_file --exe $bin_file --src ${files[*]}
./bin/ltnvm --exe $bin_file --args Hello World 123