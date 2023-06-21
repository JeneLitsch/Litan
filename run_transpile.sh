./sandbox/run.sh
g++-10 --std=c++2a tmp/c/main.cxx -o tmp/a
./tmp/a
echo $?