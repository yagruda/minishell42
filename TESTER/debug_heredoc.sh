#!/bin/bash

# Test to see what's happening with the pipe
echo "Testing heredoc pipe content..."

# Create a simple test
echo 'cat << EOF > test_output.txt
hello world
test line
EOF
cat test_output.txt' | timeout 10s ./minishell

echo "Contents of test_output.txt:"
cat test_output.txt 2>/dev/null || echo "File not found"

# Cleanup
rm -f test_output.txt

echo ""
echo "Now testing heredoc with cat directly:"
echo 'cat << EOF
hello world
test line  
EOF' | timeout 10s ./minishell
