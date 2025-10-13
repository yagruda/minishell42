#!/bin/bash

# ============================================================================
# Comprehensive Test Suite for Minishell Redirection Features
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
    rm -f temp_minishell_*
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

# Run a minishell command and return output
run_minishell() {
    local cmd="$1"
    echo "$cmd" | timeout $TIMEOUT ./minishell 2>/dev/null | tail -n +2 | head -n -1
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

# Test if file exists
test_file_exists() {
    local file="$1"
    local test_name="$2"
    
    if [ -f "$file" ]; then
        print_result "$test_name" "File exists" "File exists" "PASS"
    else
        print_result "$test_name" "File exists" "File not found" "FAIL"
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
    echo -e "${CYAN}Starting Comprehensive Minishell Test Suite${NC}"
    echo -e "${CYAN}Testing redirection features and general shell functionality${NC}"
    
    # Make sure minishell is compiled
    if [ ! -f "./minishell" ]; then
        echo -e "${RED}Error: minishell executable not found. Please compile first.${NC}"
        exit 1
    fi
    
    cleanup
    
    # ========================================================================
    print_header "BASIC SHELL FUNCTIONALITY"
    # ========================================================================
    
    test_command_output "echo hello" "hello" "Basic echo command"
    test_command_output "echo 'hello world'" "hello world" "Echo with single quotes"
    test_command_output 'echo "hello world"' "hello world" "Echo with double quotes"
    test_command_output "pwd" "$(pwd)" "PWD command"
    
    # ========================================================================
    print_header "BASIC OUTPUT REDIRECTION (>)"
    # ========================================================================
    
    run_minishell "echo 'basic output' > test_basic.txt"
    test_file_content "test_basic.txt" "basic output" "Basic output redirection"
    
    run_minishell ">test_leading.txt echo 'leading redirect'"
    test_file_content "test_leading.txt" "leading redirect" "Leading output redirection"
    
    run_minishell "echo 'overwrite' > test_overwrite.txt"
    run_minishell "echo 'new content' > test_overwrite.txt"
    test_file_content "test_overwrite.txt" "new content" "Output redirection overwrites"
    
    # ========================================================================
    print_header "APPEND REDIRECTION (>>)"
    # ========================================================================
    
    run_minishell "echo 'first line' > test_append.txt"
    run_minishell "echo 'second line' >> test_append.txt"
    test_file_content "test_append.txt" $'first line\nsecond line' "Append redirection"
    
    run_minishell ">>test_leading_append.txt echo 'leading append'"
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
    run_minishell "2>err_test.txt ls /nonexistent_dir_12345"
    if [ -f "err_test.txt" ] && [ -s "err_test.txt" ]; then
        print_result "Stderr redirection (2>)" "Error captured" "Error captured" "PASS"
    else
        print_result "Stderr redirection (2>)" "Error captured" "No error captured" "FAIL"
    fi
    
    # Test stdout redirection with fd number (1>)
    run_minishell "1>out_fd.txt echo 'fd stdout'"
    test_file_content "out_fd.txt" "fd stdout" "Explicit stdout redirection (1>)"
    
    # Test combined redirections
    run_minishell "2>err_combined.txt >out_combined.txt ls /valid /invalid"
    test_file_exists "err_combined.txt" "Combined redirection - stderr file created"
    test_file_exists "out_combined.txt" "Combined redirection - stdout file created"
    
    # Test multiple leading redirections
    run_minishell "2>err_multi.txt >/dev/null ls /nonexistent"
    if [ -f "err_multi.txt" ] && [ -s "err_multi.txt" ]; then
        print_result "Multiple leading redirections" "Error captured, stdout silenced" "Error captured, stdout silenced" "PASS"
    else
        print_result "Multiple leading redirections" "Error captured, stdout silenced" "Failed" "FAIL"
    fi
    
    # ========================================================================
    print_header "MIXED REDIRECTIONS"
    # ========================================================================
    
    echo "input for mixed test" > input_mixed.txt
    run_minishell "<input_mixed.txt >output_mixed.txt cat"
    test_file_content "output_mixed.txt" "input for mixed test" "Input and output redirection combined"
    
    run_minishell ">output_before.txt <input_mixed.txt >>output_before.txt cat"
    expected_mixed="input for mixed test"
    actual_mixed=$(cat output_before.txt 2>/dev/null)
    if [ "$actual_mixed" = "$expected_mixed" ]; then
        print_result "Multiple redirections with same command" "$expected_mixed" "$actual_mixed" "PASS"
    else
        print_result "Multiple redirections with same command" "$expected_mixed" "$actual_mixed" "FAIL"
    fi
    
    # ========================================================================
    print_header "PIPES WITH REDIRECTIONS"
    # ========================================================================
    
    test_command_output "echo 'pipe test' | cat" "pipe test" "Basic pipe"
    
    run_minishell "echo 'pipe to file' | cat > pipe_output.txt"
    test_file_content "pipe_output.txt" "pipe to file" "Pipe with output redirection"
    
    echo -e "apple\nbanana\ncherry" > fruit_list.txt
    test_command_output "cat fruit_list.txt | grep banana" "banana" "Input file through pipe"
    
    # ========================================================================
    print_header "HEREDOC FUNCTIONALITY"
    # ========================================================================
    
    # Basic heredoc test
    cat << 'HEREDOC_TEST' > heredoc_input.txt
cat << EOF
Hello heredoc
This is a test
EOF
HEREDOC_TEST
    
    expected_heredoc=$'Hello heredoc\nThis is a test'
    actual_heredoc=$(timeout $TIMEOUT ./minishell < heredoc_input.txt 2>/dev/null | tail -n +2 | head -n -3)
    if [ "$actual_heredoc" = "$expected_heredoc" ]; then
        print_result "Basic heredoc" "$expected_heredoc" "$actual_heredoc" "PASS"
    else
        print_result "Basic heredoc" "$expected_heredoc" "$actual_heredoc" "FAIL"
    fi
    
    # ========================================================================
    print_header "BUILTIN COMMANDS WITH REDIRECTIONS"
    # ========================================================================
    
    run_minishell "echo 'builtin test' > builtin_echo.txt"
    test_file_content "builtin_echo.txt" "builtin test" "Echo builtin with redirection"
    
    run_minishell "pwd > builtin_pwd.txt"
    test_file_content "builtin_pwd.txt" "$(pwd)" "PWD builtin with redirection"
    
    # ========================================================================
    print_header "ENVIRONMENT AND VARIABLES"
    # ========================================================================
    
    test_command_output "echo \$USER" "$USER" "Environment variable expansion"
    test_command_output "echo \$HOME" "$HOME" "HOME variable expansion"
    
    run_minishell "echo \$PATH > path_output.txt"
    if [ -f "path_output.txt" ] && [ -s "path_output.txt" ]; then
        print_result "PATH variable to file" "PATH written to file" "PATH written to file" "PASS"
    else
        print_result "PATH variable to file" "PATH written to file" "Failed to write PATH" "FAIL"
    fi
    
    # ========================================================================
    print_header "ERROR HANDLING"
    # ========================================================================
    
    # Test with nonexistent command
    run_minishell "2>error_cmd.txt nonexistent_command_xyz"
    if [ -f "error_cmd.txt" ] && [ -s "error_cmd.txt" ]; then
        print_result "Error handling - nonexistent command" "Error captured" "Error captured" "PASS"
    else
        print_result "Error handling - nonexistent command" "Error captured" "No error captured" "FAIL"
    fi
    
    # Test with invalid file for input
    output=$(run_minishell "cat < /nonexistent/file/path" 2>&1)
    if [[ $output == *"No such file"* ]] || [[ $output == *"cannot"* ]] || [ -z "$output" ]; then
        print_result "Error handling - invalid input file" "Error handled" "Error handled" "PASS"
    else
        print_result "Error handling - invalid input file" "Error handled" "Unexpected output: $output" "FAIL"
    fi
    
    # ========================================================================
    print_header "COMPLEX SCENARIOS"
    # ========================================================================
    
    # Multiple commands with redirections
    echo -e "first\nsecond\nthird" > complex_input.txt
    run_minishell "<complex_input.txt grep second > complex_output.txt"
    test_file_content "complex_output.txt" "second" "Complex: input redirection + grep + output redirection"
    
    # Multiple file descriptors
    run_minishell "echo 'stdout content' 1>stdout_fd.txt 2>stderr_fd.txt"
    test_file_content "stdout_fd.txt" "stdout content" "Multiple FDs - stdout"
    test_file_exists "stderr_fd.txt" "Multiple FDs - stderr file created"
    
    # Chain of pipes with redirections
    echo -e "one\ntwo\nthree\nfour" > chain_input.txt
    test_command_output "cat chain_input.txt | grep t | wc -l" "2" "Chain: file -> grep -> wc"
    
    # ========================================================================
    print_header "STRESS TESTS"
    # ========================================================================
    
    # Many redirections
    run_minishell ">out1.txt >out2.txt >out3.txt echo 'multiple outputs'"
    # Should only write to the last file (out3.txt)
    test_file_content "out3.txt" "multiple outputs" "Multiple output redirections"
    
    # Long command with redirections
    run_minishell "echo 'very long command with lots of words and redirections' > long_command.txt"
    test_file_content "long_command.txt" "very long command with lots of words and redirections" "Long command with redirection"
    
    # ========================================================================
    print_header "EDGE CASES"
    # ========================================================================
    
    # Empty files
    run_minishell "echo -n '' > empty_file.txt"
    test_file_exists "empty_file.txt" "Empty file creation"
    
    # Whitespace handling
    run_minishell "echo '   spaces   ' >   spaced_file.txt   "
    test_file_content "spaced_file.txt" "   spaces   " "Whitespace in redirection"
    
    # Special characters in filenames
    run_minishell "echo 'special' > 'file-with-dash.txt'"
    test_file_content "file-with-dash.txt" "special" "Special characters in filename"
    
    # ========================================================================
    # FINAL RESULTS
    # ========================================================================
    
    cleanup
    
    echo -e "\n${BLUE}========================================${NC}"
    echo -e "${BLUE}TEST SUITE SUMMARY${NC}"
    echo -e "${BLUE}========================================${NC}"
    echo -e "Total tests run: ${YELLOW}$TOTAL_TESTS${NC}"
    echo -e "Tests passed:   ${GREEN}$PASSED_TESTS${NC}"
    echo -e "Tests failed:   ${RED}$FAILED_TESTS${NC}"
    
    if [ $FAILED_TESTS -eq 0 ]; then
        echo -e "\n${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}"
        echo -e "${GREEN}Your minishell implementation is working correctly!${NC}"
        exit 0
    else
        echo -e "\n${RED}❌ Some tests failed${NC}"
        echo -e "${YELLOW}Please review the failed tests above${NC}"
        exit 1
    fi
}

# Run the test suite
main "$@"
