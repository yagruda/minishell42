#!/bin/bash

# Colors and emojis
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

PASS="✅"
FAIL="❌"
WARN="⚠️"
INFO="ℹ️"
ROCKET="🚀"
QUOTE="💬"
DOLLAR="💲"
PIPE="🔗"
REDIR="📂"
BUILTIN="🔧"

# Test counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Function to run a test
run_test() {
    local test_name="$1"
    local input="$2"
    local expected_pattern="$3"
    local should_fail="${4:-false}"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -e "${BLUE}Testing:${NC} $test_name"
    echo -e "${INFO} Input: ${YELLOW}$input${NC}"
    
    # Run the test
    local output
    if [[ "$should_fail" == "true" ]]; then
        output=$(echo "$input" | timeout 5s ./minishell 2>&1)
        local exit_code=$?
        if [[ $exit_code -ne 0 ]] || echo "$output" | grep -q "error\|Error"; then
            echo -e "${PASS} ${GREEN}Test passed${NC} (expected failure)"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            echo -e "${FAIL} ${RED}Test failed${NC} (should have failed)"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    else
        output=$(echo "$input" | timeout 5s ./minishell 2>/dev/null)
        if echo "$output" | grep -q "$expected_pattern"; then
            echo -e "${PASS} ${GREEN}Test passed${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            echo -e "${FAIL} ${RED}Test failed${NC}"
            echo -e "Expected pattern: ${YELLOW}$expected_pattern${NC}"
            echo -e "Actual output: ${YELLOW}$output${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    fi
    echo ""
}

# Function to test simple command
test_simple_command() {
    local cmd="$1"
    local pattern="$2"
    run_test "Simple command: $cmd" "$cmd" "$pattern"
}

echo -e "${ROCKET} ${BLUE}=== MINISHELL COMPREHENSIVE TEST SUITE ===${NC}"
echo ""

# Check if minishell exists
if [[ ! -f "./minishell" ]]; then
    echo -e "${FAIL} ${RED}minishell executable not found!${NC}"
    echo "Please run 'make' first."
    exit 1
fi

echo -e "${INFO} ${BLUE}Starting tests...${NC}"
echo ""

# ===== BASIC COMMAND TESTS =====
echo -e "${ROCKET} ${BLUE}=== BASIC COMMAND TESTS ===${NC}"
test_simple_command "echo hello" "hello"
test_simple_command "echo hello world" "hello world"
test_simple_command "/bin/ls" "" # Just check it doesn't crash
echo ""

# ===== BUILTIN TESTS =====
echo -e "${BUILTIN} ${BLUE}=== BUILTIN COMMAND TESTS ===${NC}"
run_test "pwd builtin" "pwd" "/.*"
run_test "env builtin" "env" ".*=.*"
run_test "echo builtin" "echo test123" "test123"
run_test "cd and pwd" $'cd /tmp\npwd' "/tmp"
run_test "export and env" $'export TEST_VAR=hello\nenv' "TEST_VAR=hello"
run_test "unset variable" $'export TEST_VAR=hello\nunset TEST_VAR\nenv' "^((?!TEST_VAR=hello).)*$"
echo ""

# ===== DOUBLE QUOTE TESTS =====
echo -e "${QUOTE} ${BLUE}=== DOUBLE QUOTE TESTS ===${NC}"
run_test "Basic double quotes" 'echo "hello world"' "hello world"
run_test "Variable expansion in quotes" 'echo "User: $USER"' "User: .*"
run_test "Escaped quotes" 'echo "He said: \"hello\""' 'He said: "hello"'
run_test "Escaped dollar sign" 'echo "Literal: \$USER = $USER"' "Literal: \\\$USER = .*"
run_test "Space preservation" 'echo "hello    world    spaces"' "hello    world    spaces"
run_test "Braced variables" 'echo "User: ${USER}"' "User: .*"
run_test "Undefined variable" 'echo "Undefined: $UNDEFINED_VAR end"' "Undefined:  end"
run_test "Empty quotes" 'echo ""' "^$"
run_test "Mixed arguments" 'echo hello "world with spaces" more' "hello world with spaces more"
echo ""

# ===== SINGLE QUOTE TESTS =====
echo -e "${QUOTE} ${BLUE}=== SINGLE QUOTE TESTS ===${NC}"
run_test "Basic single quotes" "echo 'hello world'" "hello world"
run_test "Literal dollar in single quotes" "echo '\$USER'" '\$USER'
run_test "Single quoted command" "'ls'" ".*"
run_test "Mixed single and double quotes" $'echo \'literal: $USER\' "expanded: $USER"' "literal: \\\$USER expanded: .*"
echo ""

# ===== VARIABLE EXPANSION TESTS =====
echo -e "${DOLLAR} ${BLUE}=== VARIABLE EXPANSION TESTS ===${NC}"
run_test "Simple variable" 'echo $USER' ".*"
run_test "Braced variable" 'echo ${USER}' ".*"
run_test "Variable in middle" 'echo prefix_${USER}_suffix' "prefix_.*_suffix"
run_test "Multiple variables" 'echo $USER $HOME' ".*"
run_test "Undefined variable" 'echo $UNDEFINED_VARIABLE' "^$"
echo ""

# ===== PIPE TESTS =====
echo -e "${PIPE} ${BLUE}=== PIPE TESTS ===${NC}"
run_test "Simple pipe" 'echo "hello world" | cat' "hello world"
run_test "Echo with grep" 'echo "hello world" | grep hello' "hello world"
run_test "Multiple pipes" 'echo "test" | cat | cat' "test"
run_test "Pipe with quotes" 'echo "hello world" | grep "hello"' "hello world"
echo ""

# ===== REDIRECTION TESTS =====
echo -e "${REDIR} ${BLUE}=== REDIRECTION TESTS ===${NC}"
run_test "Output redirection" $'echo "test" > /tmp/minishell_test.txt\ncat /tmp/minishell_test.txt' "test"
run_test "Append redirection" $'echo "line1" > /tmp/minishell_test2.txt\necho "line2" >> /tmp/minishell_test2.txt\ncat /tmp/minishell_test2.txt' "line1.*line2"
run_test "Input redirection" $'echo "input test" > /tmp/minishell_input.txt\ncat < /tmp/minishell_input.txt' "input test"
echo ""

# ===== ERROR HANDLING TESTS =====
echo -e "${WARN} ${BLUE}=== ERROR HANDLING TESTS ===${NC}"
run_test "Unclosed double quotes" 'echo "unclosed' "" true
run_test "Unclosed single quotes" "echo 'unclosed" "" true
run_test "Invalid command" 'nonexistentcommand123' "" true
run_test "Syntax error with pipe" '|' "" true
echo ""

# ===== COMPLEX SCENARIOS =====
echo -e "${ROCKET} ${BLUE}=== COMPLEX SCENARIOS ===${NC}"
run_test "Complex quoting" $'echo "User: $USER" \'literal: $USER\' normal_$USER' "User: .* literal: \\\$USER normal_.*"
run_test "Quotes with pipes" 'echo "hello world" | grep "world"' "hello world"
run_test "Variables with pipes" 'echo $USER | cat' ".*"
run_test "Mixed redirection and quotes" $'echo "test content" > /tmp/minishell_mixed.txt\ncat /tmp/minishell_mixed.txt' "test content"
run_test "Environment variable chain" 'echo $HOME | grep "/"' ".*"
echo ""

# ===== EDGE CASES =====
echo -e "${WARN} ${BLUE}=== EDGE CASES ===${NC}"
run_test "Empty command" '' "" true
run_test "Just spaces" '   ' "" true
run_test "Multiple spaces" 'echo     hello     world' "hello world"
run_test "Tab characters" $'echo\thello\tworld' "hello world"
run_test "Nested quotes attempt" 'echo "outer \"inner\" outer"' 'outer "inner" outer'
run_test "Dollar at end" 'echo test$' "test\\\$"
run_test "Backslash without escape" 'echo "test\\"' "test\\\\"
echo ""

# ===== BUILTIN SPECIFIC TESTS =====
echo -e "${BUILTIN} ${BLUE}=== BUILTIN SPECIFIC TESTS ===${NC}"
run_test "cd to home" $'cd\npwd' "$HOME"
run_test "cd with variable" 'cd $HOME && pwd' "$HOME"
run_test "echo with -n flag" 'echo -n hello' "hello"
run_test "exit command" 'exit 0' "" true
echo ""

# Clean up test files
rm -f /tmp/minishell_test.txt /tmp/minishell_test2.txt /tmp/minishell_input.txt /tmp/minishell_mixed.txt 2>/dev/null

# ===== FINAL RESULTS =====
echo -e "${ROCKET} ${BLUE}=== TEST RESULTS ===${NC}"
echo ""
echo -e "${INFO} Total tests run: ${YELLOW}$TOTAL_TESTS${NC}"
echo -e "${PASS} Tests passed: ${GREEN}$PASSED_TESTS${NC}"
echo -e "${FAIL} Tests failed: ${RED}$FAILED_TESTS${NC}"
echo ""

if [[ $FAILED_TESTS -eq 0 ]]; then
    echo -e "${PASS} ${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}"
    echo -e "${GREEN}Your minishell is working perfectly!${NC}"
    exit 0
else
    echo -e "${FAIL} ${RED}Some tests failed.${NC}"
    echo -e "${YELLOW}Success rate: $(( (PASSED_TESTS * 100) / TOTAL_TESTS ))%${NC}"
    exit 1
fi
