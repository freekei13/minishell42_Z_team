/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:00:09 by csamakka          #+#    #+#             */
/*   Updated: 2026/05/15 14:41:54 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	sigint_mod(int sig)
{
	g_status = 128 + sig;
	write(1,"\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_mod_child(int sig)
{
	g_status = 128 + sig;
	write(1,"\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_set(t_sigdata sigdata)
{
	struct	sigaction	sa;

	sigemptyset(&sa.sa_mask);
	if (sigdata.pid == 0)
	{
		sa.sa_handler = SIG_DFL;
		sa.sa_flags = 0;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else
	{
		sa.sa_handler = sigint_mod;
		sa.sa_flags = SA_RESTART;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sa.sa_flags = 0;
		sigaction(SIGQUIT, &sa, NULL);
	}
}

void	sigint_ign(void)
{
	struct	sigaction	sa;
	
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sigint_mod_child;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void 	sigint_heredoc(void)
{
	struct	sigaction	sa;
	
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
