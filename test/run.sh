files=(
	"test/main.ltn"
	"test/op_add.ltn"
	"test/sphinx/sphinx.ltn" 
)

bin_file="tmp/bin"
asm_file="tmp/asm"

rm $bin_file
rm $asm_file

# ./bin/ltn --src ${core_tests[*]} ${stdlib_tests[*]} ${misc[*]} --args Hello World 123

./bin/ltnc -o --asm $asm_file --exe $bin_file --src ${files[*]}
./bin/ltnvm --exe $bin_file --args Hello World 123