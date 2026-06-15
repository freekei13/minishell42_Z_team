/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 21:03:59 by csamakka          #+#    #+#             */
/*   Updated: 2026/05/20 16:36:29 by csamakka         ###   ########.fr       */
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
	g_status = sig;
	write(1, "\n", 1);
	return ;
}

void	sigint_mod_heredoc_parent(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_redisplay();
}