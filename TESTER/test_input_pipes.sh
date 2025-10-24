#!/bin/bash

# Minishell pipe syntax tester — clear visual ✅ / ❌ output

MINISHELL=../minishell

tests=(
    "|" "ERR"
    "||" "ERR"
    "   |" "ERR"
    "|   " "ERR"
    "a || b" "ERR"
    "a | | b" "ERR"
    "| a | b" "ERR"
    "a | b |" "ERR"
    "a|" "ERR"
    "|b" "ERR"
    "a |    | b" "ERR"
    "a|   |b" "ERR"
    "a | | | b" "ERR"
    "a | < b" "OK"
    "a | > b" "OK"
    "a | << b" "OK"
    "a | >> b" "OK"
    "a|b" "OK"
    "a | b" "OK"
    "ls|wc" "OK"
    "echo hi|cat" "OK"
    "echo 123 | grep 1" "OK"
    "cat < infile | grep test" "OK"
    "cat < infile | grep test | wc -l" "OK"
    "@ | !" "OK"
    "a|b|c" "OK"
    "   a | b   " "OK"
    "a > out | b < in" "OK"
)

i=1

for ((t=0; t<${#tests[@]}; t+=2)); do
    input="${tests[t]}"
    expected="${tests[t+1]}"

    output=$(echo "$input" | $MINISHELL 2>&1 | grep -E "syntax error|command not found")

    if [[ "$expected" == "ERR" && "$output" == *"syntax error near unexpected token"* ]]; then
        result="✅ OK (ERR)"
    elif [[ "$expected" == "OK" && "$output" == *"command not found"* ]]; then
        result="✅ OK (OK)"
    else
        result="❌ FAIL ($expected)"
    fi

    printf "[%02d] %s\n%s\n\n" "$i" "$input" "$result" 
    ((i++))
done

echo "All tests finished"
