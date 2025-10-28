/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:08:26 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/24 17:00:18 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// CTRL+\ is  Process terminating with default action of signal 3 (SIGQUIT)
// I think signals would be rearrenged by a partner Andrii while running some functions. But for my part (Yurii) it's like this

void handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0); // clear buffer readline
	rl_on_new_line(); // tell rl we're on a new line
	rl_redisplay(); // show prompt again	
}

// Delete showing ^C and ^ 
void hide_ctrl_c(void)
{
	struct termios term;
	
	if (tcgetattr(STDIN_FILENO, &term) == -1) // get current terminal settings
		return;
	term.c_lflag &= ~ECHOCTL; // turn off showing ^c and ^\ //
	tcsetattr(STDIN_FILENO, TCSANOW, &term); // apply changes
}

void handle_signals(void)
{
	signal(SIGINT, handle_sigint); // ctrl + c
	signal(SIGQUIT, SIG_IGN); // ctrl +\  .. SIG_IGNore
	
	hide_ctrl_c();
}
