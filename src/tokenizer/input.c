/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:42:23 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 16:09:57 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int input_is_valid(char* input, t_shell *shell)
{
	if (!quotes_closed(input))
	{
		custom_error("syntax error: unclosed quotes\n");
		shell->exit_code = 258;
		if (DEBUG)
			printf("exit code set to %d\n", shell->exit_code);
		// TBD: mark is_valid = 0 in shell input struct
		return 0;
	}
	if (is_empty(input))
	{
		custom_error("syntax error: empty input\n");
		shell->exit_code = 258;
		if (DEBUG)
			printf("exit code set to %d\n", shell->exit_code);
		// TBD: mark is_valid = 0 in shell input struct
		return 0;
	}
	if (!is_redirect_correct(input))
	{
		custom_error("syntax error near unexpected token `newline'\n");
		shell->exit_code = 2;
		if (DEBUG)
			printf("exit code set to %d\n", shell->exit_code);
		// TBD: mark is_valid = 0 in shell input struct
		return 0;
	}
	if (!(is_pipe_correct(input)))
	{
		custom_error("syntax error near unexpected token `|'\n");
		shell->exit_code = 2;
		if (DEBUG)
			printf("exit code set to %d\n", shell->exit_code);
		// TBD: mark is_valid = 0 in shell input struct
		return 0;
	}
	
	// TBD i = has_valid_pipes(input);
	// TBD i = has_valid_redirects(input);

	return 1;
}

int process_input(t_shell *shell, char *input, char **argv)
{
    (void) shell;
    (void) argv;

    if (*input)
        add_history(input);

    if (input_is_valid(input, shell))
    {
        tokenizer(shell, input);   // Step 1: Tokenize
        debug_print_tokens(shell->tokens); // Debug: print tokens
        
        parser(shell);              // Step 2: Parse
        debug_print_commands(shell->cmd_list); // Debug: print commands before expansion
        
        expander(shell);            // Step 3: Expand
        if (DEBUG)
            printf("=== After Expansion ===\n");
        debug_print_commands(shell->cmd_list); // Debug: print commands after expansion
        
        // executor(shell);         // Step 4: Executor part
        
        cleanup_shell_after_cmd(shell);
    }
    else
    {
        return 0; // Continue
    }
    
    if (ft_strcmp(input, "exit") == 0)
    {
        printf("exit\n");
		// TBD: proper exit
        return 1; // Signal exit to main
    }

    // FOR DEBUGGING ONLY, DELETE LATER
    if (ft_strcmp(input, "") != 0)
        printf("minishell: %s: command not found\n", input);

    return 0; // Continue
}