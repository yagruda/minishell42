#!/bin/bash

echo "=== Testing Minishell ==="

# Test 1: echo
echo "Test 1: echo"
printf "echo hello world\nexit\n" | timeout 2 ./minishell | grep "hello world"

# Test 2: echo -n
echo "Test 2: echo -n"
printf "echo -n test\nexit\n" | timeout 2 ./minishell | grep -o "testminishell>"

# Test 3: pwd
echo "Test 3: pwd"
printf "pwd\nexit\n" | timeout 2 ./minishell | grep "/minishell42"

# Test 4: cd
echo "Test 4: cd"
printf "cd /tmp\npwd\nexit\n" | timeout 2 ./minishell | grep "/tmp"

# Test 5: env
echo "Test 5: env"
printf "env\nexit\n" | timeout 2 ./minishell | grep "PATH="

# Test 6: export
echo "Test 6: export (no args)"
printf "export\nexit\n" | timeout 2 ./minishell | grep "declare -x"

# Test 7: exit code
echo "Test 7: exit"
printf "exit 42\n" | timeout 2 ./minishell
echo "Exit code: $?"

# Test 8: pipes
echo "Test 8: pipes"
printf "echo test | cat\nexit\n" | timeout 2 ./minishell | grep "test"

# Test 9: redirections
echo "Test 9: redirections"
printf "echo test > /tmp/test_minishell.txt\ncat < /tmp/test_minishell.txt\nexit\n" | timeout 2 ./minishell | grep "test"
rm -f /tmp/test_minishell.txt

# Test 10: external commands
echo "Test 10: external commands"
printf "ls -la | head -1\nexit\n" | timeout 2 ./minishell | grep "total"

echo "=== All tests completed ==="
