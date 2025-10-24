#!/bin/bash

# Path to your minishell executable
MINISHELL=../minishell

OUTDIR=./validator_tests
mkdir -p $OUTDIR

# Each test: "input | expected"
# expected can be "OK" (should be valid syntax) or "ERR" (should be invalid)
TESTS=(
  "echo hello > out.txt@OK"
  "echo hello >> out.txt@OK"
  "cat < infile > outfile@OK"
  "echo a | b@OK"
  ">@ERR"
  "| echo test@ERR"
  "echo test ||@ERR"
  "echo >@ERR"
  "echo <@ERR"
  ">@ERR"
  ">< file@ERR"
  ">>@ERR"
  "<<@ERR"
  ">>> file@ERR"
  "<<< file@ERR"
  "echo > file@OK"
  "echo >> file@OK"
  "echo < file@OK"
  "echo < file > file2@OK"
  "echo > file < file2@OK"
  "echo hello@OK"
  ">@ERR"
  "echo > > file@ERR"
  "echo < < infile@ERR"
  "echo < > file@ERR"
  "echo << limiter >> out@OK"
  "echo << limiter < infile@OK"
  "echo << limiter | cat@OK"
)

i=1
for t in "${TESTS[@]}"; do
    CMD="${t%%@*}"
    EXPECT="${t##*@}"

    printf "\n\033[1;36m[%02d] %s\033[0m\n" "$i" "$CMD"

    printf "%s\nexit\n" "$CMD" | timeout 3s $MINISHELL >$OUTDIR/$i.out 2>&1
    grep -qi "syntax error" $OUTDIR/$i.out && FOUND="ERR" || FOUND="OK"

    if [ "$FOUND" == "$EXPECT" ]; then
        echo "✅ OK ($EXPECT)"
    else
        echo "❌ FAIL (expected $EXPECT, got $FOUND)"
        echo "--- minishell output ---"
        cat $OUTDIR/$i.out
    fi
    ((i++))
done
