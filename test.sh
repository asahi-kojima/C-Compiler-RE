#!/bin/bash

assert(){
    echo "========================================================"

    expected="$1"
    input="$2"

    ./compiler.out "$input" > tmp.s
    gcc -o tmp tmp.s
    ./tmp
    actual="$?"
    
    if [ "$actual" = "$expected" ]; then
        echo -e "$input => $actual"
    else
        echo -e "$input => $expected expected, but got $actual\n"
        exit 1
    fi
}


assert 0 0
assert 1 1
assert 21 "5+20-4"
assert 21 "5 + 20 - 4"

echo OK