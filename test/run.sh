bin_file="tmp/bin"
asm_file="tmp/asm"

rm $bin_file
rm $asm_file

# ./bin/ltnc -o --asm $asm_file --exe $bin_file --src "test/main.ltn"
# ./bin/ltnvm --exe $bin_file --args Hello World 123

./bin/ltn --src "test/main.ltn" --args Hello World 123