/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:00:09 by csamakka          #+#    #+#             */
/*   Updated: 2026/05/12 13:46:11 by csamakka         ###   ########.fr       */
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

void	signal_set(t_sigdata sigdata)
{
	struct	sigaction	sa;
	
	if (sigdata.pid == 0)
		printf("Child: Hello\n");
	else
	{
		printf("Parent: Hola\n");
		sigemptyset(&sa.sa_mask);
		sa.sa_handler = sigint_mod;
		sa.sa_flags = SA_RESTART;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sa.sa_flags = 0;
		sigaction(SIGQUIT, &sa, NULL);
	}
}