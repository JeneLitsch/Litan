./sandbox/run.sh
g++-10 --std=c++2a tmp/c/main.cxx -O3 -o tmp/a
./tmp/a
echo $?