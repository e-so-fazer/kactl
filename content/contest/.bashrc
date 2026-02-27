# Makefile: "CXXFLAGS := -std=c++20 -Wall -Wextra -Wshadow -Wconversion -fsanitize=address,undefined -g3 -DLOCAL"
teste() {
    for f in "$2"/*; do
        echo "=== $f"
        cat $f
        echo "=== Out"
        $1 < $f
    done
}
# teste ./b btests
stress() {
    for ((i=1; ; i++)) do
        echo "Test $i"
        $1 > i.txt
        $2 < i.txt > o1.txt
        $3 < i.txt > o2.txt
        diff -q o1.txt o2.txt
    done
}
# stress "python3 gen.py" ./main ./brute
