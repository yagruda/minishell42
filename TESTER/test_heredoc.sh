#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== HEREDOC FUNCTIONALITY TEST ===${NC}"
echo ""

# Test 1: Basic heredoc with EOF
echo -e "${YELLOW}Test 1: Basic heredoc with EOF delimiter${NC}"
echo "Testing: cat << EOF"
echo "Expected: Should read lines until EOF is entered"
echo ""
echo 'cat << EOF
This is line 1
This is line 2
EOF' | timeout 10s ./minishell
echo ""

# Test 2: Heredoc with different delimiter
echo -e "${YELLOW}Test 2: Heredoc with custom delimiter${NC}"
echo "Testing: cat << STOP"
echo "Expected: Should read lines until STOP is entered"
echo ""
echo 'cat << STOP
Custom delimiter test
Another line
STOP' | timeout 10s ./minishell
echo ""

# Test 3: Heredoc with variable expansion
echo -e "${YELLOW}Test 3: Heredoc with variable expansion${NC}"
echo "Testing: cat << EOF with variables"
echo "Expected: Should expand variables inside heredoc"
echo ""
echo 'export TEST_VAR=hello
cat << EOF
Variable: $TEST_VAR
User: $USER
EOF' | timeout 10s ./minishell
echo ""

# Test 4: Heredoc without variable expansion (quoted delimiter)
echo -e "${YELLOW}Test 4: Heredoc without expansion (quoted delimiter)${NC}"
echo "Testing: cat << \"EOF\""
echo "Expected: Should not expand variables"
echo ""
echo 'export TEST_VAR=hello
cat << "EOF"
Literal: $TEST_VAR
User: $USER
"EOF"' | timeout 10s ./minishell
echo ""

# Test 5: Interactive test (this one you'll need to run manually)
echo -e "${YELLOW}Test 5: Interactive heredoc test${NC}"
echo "Run this manually: ./minishell"
echo "Then type: cat << EOF"
echo "Enter some lines and finish with EOF"
echo "Check if it properly handles the delimiter"
echo ""

echo -e "${GREEN}Heredoc tests completed!${NC}"
echo "If any test hangs or shows 'Bad file descriptor', the issue is confirmed."
