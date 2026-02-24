dcpp() {
    g++ "$1.cpp" -o "$1" -std=c++20 -DLOCAL -Wall -Wextra -Wshadow -Wconversion -ggdb -g3 -fsanitize=address,undefined
}

fcpp() {
    g++ "$1.cpp" -o "$1" -std=c++20 -O2
}

testio() {
    dcpp "$1"
    for inf in in"$1"*; do
        local suffix="${inf#in$1}"
        local outf="out$1$suffix"
        ./"$1" < "$inf" > tmp_out
        if diff -w "$outf" tmp_out > /dev/null; then
            echo "Passed test $suffix"
        else
            echo -e "\n FAILED test $suffix"
            echo -e "--- Expected ($outf) ---"; cat "$outf"
            echo -e "\n--- Your Output ---"; cat tmp_out
            rm -f tmp_out
            return 1
        fi
    done
    rm -f tmp_out
}