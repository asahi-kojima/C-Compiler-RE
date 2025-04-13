#!/bin/bash

assert(){
    echo "========================================================"

    expected="$1"
    input="$2"

    ./compiler.out "$input" > tmp.s
    cp tmp.s tmp_debug.s
    gcc -z noexecstack -o tmp tmp.s
    ./tmp
    actual="$?"
    
    if [ "$actual" = "$expected" ]; then
        echo -e "OK : $input => $actual"
    else
        echo -e "$input => $expected expected, but got $actual\n"
        exit 1
    fi
}


#四則演算関係
assert 0 0
assert 1 1
assert 21 "5+20-4"
assert 21 "5 + 20 - 4"
assert 10 "1 + 3 * 3"
assert 1 "4 / 4"
assert 12 "(1 + 3) * (4 - 1)"
assert 2 "((1 + 3) * (2 + 3)) / 10"
assert 1 "-1 + 2"
assert 6 "(-3 + 1) * -3"

#等価演算子関係
assert 1 "1 == 1"
assert 1 "0 == 0"
assert 1 "-1 == -1"
assert 0 "1 != 1"
assert 0 "0 != 0"
assert 0 "-1 != -1"
assert 1 "123 != 1"
assert 1 "-234 != 123"
assert 1 "-1 != -123"

#比較演算子
assert 1 "1 < 2"
assert 1 "-1 < 1"
assert 1 "-2 < -1"
assert 1 "1 <= 2"
assert 1 "2 <= 2"
assert 1 "-1 <= 1"
assert 1 "-2 <= -1"

assert 0 "1 > 2"
assert 0 "-1 > 1"
assert 0 "-2 > -1"
assert 0 "1 >= 2"
assert 0 "-1 >= 1"
assert 0 "-2 >= -1"

assert 0 "2 < 1"
assert 0 "1 < -1"
assert 0 "-1 < -2"
assert 0 "2 <= 1"
assert 0 "1 <= -1"
assert 0 "-1 <= -2"

echo "========================================================"