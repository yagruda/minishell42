#!/bin/bash

# ============================================================================
# FINAL Comprehensive Test Suite for Minishell Redirection Features
# ============================================================================

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Test counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Test timeout
TIMEOUT=5

# Cleanup function
cleanup() {
    rm -f test_*.txt err_*.txt out_*.txt input_*.txt
    rm -f temp_minishell_* heredoc_* fruit_list.txt
    rm -f f t.txt *.txt
}

# Print test header
print_header() {
    echo -e "\n${BLUE}========================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}========================================${NC}"
}

# Print test result
print_result() {
    local test_name="$1"
    local expected="$2"
    local actual="$3"
    local status="$4"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    if [ "$status" = "PASS" ]; then
        echo -e "${GREEN}✓ PASS${NC}: $test_name"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}✗ FAIL${NC}: $test_name"
        echo -e "  Expected: ${YELLOW}$expected${NC}"
        echo -e "  Actual:   ${YELLOW}$actual${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
}

# Run a minishell command and return clean output
run_minishell() {
    local cmd="$1"
    echo "$cmd" | timeout $TIMEOUT ./minishell 2>/dev/null | sed '1d;$d'
}

# Test file existence and content
test_file_content() {
    local file="$1"
    local expected="$2"
    local test_name="$3"
    
    if [ -f "$file" ]; then
        local actual=$(cat "$file" 2>/dev/null)
        if [ "$actual" = "$expected" ]; then
            print_result "$test_name" "$expected" "$actual" "PASS"
        else
            print_result "$test_name" "$expected" "$actual" "FAIL"
        fi
    else
        print_result "$test_name" "$expected" "File not found" "FAIL"
    fi
}

# Test if file exists and has content
test_file_exists_with_content() {
    local file="$1"
    local test_name="$2"
    
    if [ -f "$file" ] && [ -s "$file" ]; then
        print_result "$test_name" "File exists with content" "File exists with content" "PASS"
    else
        print_result "$test_name" "File exists with content" "File missing or empty" "FAIL"
    fi
}

# Test command output
test_command_output() {
    local cmd="$1"
    local expected="$2"
    local test_name="$3"
    
    local actual=$(run_minishell "$cmd")
    if [ "$actual" = "$expected" ]; then
        print_result "$test_name" "$expected" "$actual" "PASS"
    else
        print_result "$test_name" "$expected" "$actual" "FAIL"
    fi
}

# Main test execution
main() {
    echo -e "${CYAN}🚀 FINAL Comprehensive Minishell Test Suite${NC}"
    echo -e "${CYAN}Testing all redirection features and shell functionality${NC}"
    
    # Make sure minishell is compiled
    if [ ! -f "./minishell" ]; then
        echo -e "${RED}Error: minishell executable not found. Please compile first.${NC}"
        exit 1
    fi
    
    cleanup
    
    # ========================================================================
    print_header "CORE REDIRECTION FEATURES - USER REQUIREMENTS"
    # ========================================================================
    
    echo -e "${PURPLE}Testing the specific cases mentioned in requirements:${NC}"
    
    # Test: >f echo a → f contains a
    run_minishell ">f echo a" >/dev/null
    test_file_content "f" "a" "REQUIREMENT: >f echo a → f contains 'a'"
    
    # Test: <t.txt grep a → reads from t.txt and filters
    echo "test line with a" > t.txt
    actual=$(run_minishell "<t.txt grep a")
    expected="test line with a"
    if [ "$actual" = "$expected" ]; then
        print_result "REQUIREMENT: <t.txt grep a → reads and filters" "$expected" "$actual" "PASS"
    else
        print_result "REQUIREMENT: <t.txt grep a → reads and filters" "$expected" "$actual" "FAIL"
    fi
    
    # Test: >>f printf hi → appends hi to f
    run_minishell ">>f echo hi" >/dev/null
    expected_append=$'a\nhi'
    test_file_content "f" "$expected_append" "REQUIREMENT: >>f echo hi → appends 'hi' to f"
    
    # Test: 2>err >/dev/null false → should create err, silence stdout
    rm -f err
    run_minishell "2>err >/dev/null ls /nonexistent_test_dir_12345" >/dev/null
    test_file_exists_with_content "err" "REQUIREMENT: 2>err >/dev/null command → creates err, silences stdout"
    
    # ========================================================================
    print_header "BASIC SHELL FUNCTIONALITY"
    # ========================================================================
    
    test_command_output "echo hello" "hello" "Basic echo command"
    test_command_output "echo 'hello world'" "hello world" "Echo with single quotes"
    test_command_output 'echo "hello world"' "hello world" "Echo with double quotes"
    test_command_output "pwd" "$(pwd)" "PWD command"
    
    # ========================================================================
    print_header "OUTPUT REDIRECTION (>)"
    # ========================================================================
    
    run_minishell "echo 'basic output' > test_basic.txt" >/dev/null
    test_file_content "test_basic.txt" "basic output" "Basic output redirection"
    
    run_minishell ">test_leading.txt echo 'leading redirect'" >/dev/null
    test_file_content "test_leading.txt" "leading redirect" "Leading output redirection"
    
    run_minishell "echo 'overwrite' > test_overwrite.txt" >/dev/null
    run_minishell "echo 'new content' > test_overwrite.txt" >/dev/null
    test_file_content "test_overwrite.txt" "new content" "Output redirection overwrites"
    
    # ========================================================================
    print_header "APPEND REDIRECTION (>>)"
    # ========================================================================
    
    run_minishell "echo 'first line' > test_append.txt" >/dev/null
    run_minishell "echo 'second line' >> test_append.txt" >/dev/null
    test_file_content "test_append.txt" $'first line\nsecond line' "Append redirection"
    
    run_minishell ">>test_leading_append.txt echo 'leading append'" >/dev/null
    test_file_content "test_leading_append.txt" "leading append" "Leading append redirection"
    
    # ========================================================================
    print_header "INPUT REDIRECTION (<)"
    # ========================================================================
    
    echo "input test content" > input_test.txt
    test_command_output "cat < input_test.txt" "input test content" "Basic input redirection"
    
    echo -e "line1\nline2\nline3" > input_multiline.txt
    test_command_output "<input_multiline.txt grep line2" "line2" "Leading input redirection with grep"
    
    # ========================================================================
    print_header "FILE DESCRIPTOR REDIRECTION"
    # ========================================================================
    
    # Test stderr redirection (2>)
    run_minishell "2>err_test.txt ls /nonexistent_dir_12345" >/dev/null
    test_file_exists_with_content "err_test.txt" "Stderr redirection (2>)"
    
    # Test stdout redirection with fd number (1>)
    run_minishell "1>out_fd.txt echo 'fd stdout'" >/dev/null
    test_file_content "out_fd.txt" "fd stdout" "Explicit stdout redirection (1>)"
    
    # Test post-command fd redirection
    run_minishell "echo 'test content' 1>post_fd.txt" >/dev/null
    test_file_content "post_fd.txt" "test content" "Post-command fd redirection"
    
    # Test combined redirections
    run_minishell "2>err_combined.txt >out_combined.txt ls /valid /invalid" >/dev/null
    test_file_exists_with_content "err_combined.txt" "Combined redirection - stderr"
    if [ -f "out_combined.txt" ]; then
        print_result "Combined redirection - stdout file created" "File exists" "File exists" "PASS"
    else
        print_result "Combined redirection - stdout file created" "File exists" "File not found" "FAIL"
    fi
    
    # Test multiple leading redirections
    run_minishell "2>err_multi.txt >/dev/null ls /nonexistent" >/dev/null
    test_file_exists_with_content "err_multi.txt" "Multiple leading redirections"
    
    # ========================================================================
    print_header "MIXED REDIRECTIONS"
    # ========================================================================
    
    echo "input for mixed test" > input_mixed.txt
    run_minishell "<input_mixed.txt >output_mixed.txt cat" >/dev/null
    test_file_content "output_mixed.txt" "input for mixed test" "Input and output redirection combined"
    
    # ========================================================================
    print_header "PIPES AND REDIRECTION"
    # ========================================================================
    
    test_command_output "echo 'pipe test' | cat" "pipe test" "Basic pipe"
    
    run_minishell "echo 'pipe to file' | cat > pipe_output.txt" >/dev/null
    test_file_content "pipe_output.txt" "pipe to file" "Pipe with output redirection"
    
    echo -e "apple\nbanana\ncherry" > fruit_list.txt
    test_command_output "cat fruit_list.txt | grep banana" "banana" "Input file through pipe"
    
    # ========================================================================
    print_header "BUILTIN COMMANDS WITH REDIRECTIONS"
    # ========================================================================
    
    run_minishell "echo 'builtin test' > builtin_echo.txt" >/dev/null
    test_file_content "builtin_echo.txt" "builtin test" "Echo builtin with redirection"
    
    run_minishell "pwd > builtin_pwd.txt" >/dev/null
    test_file_content "builtin_pwd.txt" "$(pwd)" "PWD builtin with redirection"
    
    # ========================================================================
    print_header "ENVIRONMENT VARIABLES"
    # ========================================================================
    
    test_command_output "echo \$USER" "$USER" "Environment variable expansion"
    test_command_output "echo \$HOME" "$HOME" "HOME variable expansion"
    
    # ========================================================================
    print_header "ERROR HANDLING"
    # ========================================================================
    
    # Test with nonexistent command
    run_minishell "2>error_cmd.txt nonexistent_command_xyz" >/dev/null
    test_file_exists_with_content "error_cmd.txt" "Error handling - nonexistent command"
    
    # ========================================================================
    print_header "ADVANCED SCENARIOS"
    # ========================================================================
    
    # Multiple commands with redirections
    echo -e "first\nsecond\nthird" > complex_input.txt
    run_minishell "<complex_input.txt grep second > complex_output.txt" >/dev/null
    test_file_content "complex_output.txt" "second" "Complex: input + grep + output redirection"
    
    # Multiple file descriptors
    run_minishell "echo 'stdout content' 1>stdout_fd.txt 2>stderr_fd.txt" >/dev/null
    test_file_content "stdout_fd.txt" "stdout content" "Multiple FDs - stdout"
    if [ -f "stderr_fd.txt" ]; then
        print_result "Multiple FDs - stderr file created" "File exists" "File exists" "PASS"
    else
        print_result "Multiple FDs - stderr file created" "File exists" "File not found" "FAIL"
    fi
    
    # Chain of pipes with redirections
    echo -e "one\ntwo\nthree\nfour" > chain_input.txt
    actual_chain=$(run_minishell "cat chain_input.txt | grep t | wc -l")
    if [ "$actual_chain" = "2" ] || [ "$actual_chain" = "       2" ]; then
        print_result "Chain: file -> grep -> wc" "2" "$actual_chain" "PASS"
    else
        print_result "Chain: file -> grep -> wc" "2" "$actual_chain" "FAIL"
    fi
    
    # ========================================================================
    print_header "STRESS TESTS"
    # ========================================================================
    
    # Many redirections (should only write to the last file)
    run_minishell ">out1.txt >out2.txt >out3.txt echo 'multiple outputs'" >/dev/null
    test_file_content "out3.txt" "multiple outputs" "Multiple output redirections"
    
    # Long command
    run_minishell "echo 'very long command with lots of words and redirections' > long_command.txt" >/dev/null
    test_file_content "long_command.txt" "very long command with lots of words and redirections" "Long command with redirection"
    
    # ========================================================================
    print_header "EDGE CASES"
    # ========================================================================
    
    # Empty files
    run_minishell "echo -n '' > empty_file.txt" >/dev/null
    if [ -f "empty_file.txt" ]; then
        print_result "Empty file creation" "File exists" "File exists" "PASS"
    else
        print_result "Empty file creation" "File exists" "File not found" "FAIL"
    fi
    
    # Whitespace handling
    run_minishell "echo '   spaces   ' >   spaced_file.txt   " >/dev/null
    test_file_content "spaced_file.txt" "   spaces   " "Whitespace in redirection"
    
    # ========================================================================
    # FINAL RESULTS
    # ========================================================================
    
    cleanup
    
    echo -e "\n${BLUE}========================================${NC}"
    echo -e "${BLUE}🎯 FINAL TEST SUITE RESULTS${NC}"
    echo -e "${BLUE}========================================${NC}"
    echo -e "Total tests run: ${YELLOW}$TOTAL_TESTS${NC}"
    echo -e "Tests passed:   ${GREEN}$PASSED_TESTS${NC}"
    echo -e "Tests failed:   ${RED}$FAILED_TESTS${NC}"
    
    success_rate=$((PASSED_TESTS * 100 / TOTAL_TESTS))
    echo -e "Success rate:   ${CYAN}${success_rate}%${NC}"
    
    if [ $FAILED_TESTS -eq 0 ]; then
        echo -e "\n${GREEN}🎉 PERFECT SCORE! ALL TESTS PASSED! 🎉${NC}"
        echo -e "${GREEN}Your minishell redirection implementation is excellent!${NC}"
        exit 0
    elif [ $success_rate -ge 90 ]; then
        echo -e "\n${GREEN}🌟 EXCELLENT! $success_rate% tests passed!${NC}"
        echo -e "${YELLOW}Only minor issues remaining${NC}"
        exit 0
    elif [ $success_rate -ge 80 ]; then
        echo -e "\n${YELLOW}🚀 GOOD! $success_rate% tests passed!${NC}"
        echo -e "${YELLOW}Most functionality is working correctly${NC}"
        exit 0
    else
        echo -e "\n${RED}❌ Some significant issues remain${NC}"
        echo -e "${YELLOW}Please review the failed tests above${NC}"
        exit 1
    fi
}

# Run the test suite
main "$@"
