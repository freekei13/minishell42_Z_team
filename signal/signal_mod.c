/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 21:03:59 by csamakka          #+#    #+#             */
/*   Updated: 2026/06/24 01:14:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	sigint_mod(int sig)
{
	(void)sig;
	write(1,"\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_mod_child(int sig)
{
	(void)sig;
	write(1,"\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_mod_heredoc(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	return ;
}

void	sigint_mod_heredoc_parent(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_redisplay();
}
