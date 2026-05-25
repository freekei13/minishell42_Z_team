/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:00:30 by csamakka          #+#    #+#             */
/*   Updated: 2026/05/19 21:36:52 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <termios.h>
# include <stddef.h>
# include "lexing.h"

void	signal_set(t_sigdata sigdata);
void	sigint_heredoc(void);
void	sigint_after_heredoc(void);
void	sigint_after_cmd(void);

void	sigint_mod(int sig);
void	sigint_mod_child(int sig);
void	sigint_mod_heredoc(int sig);
void	sigint_mod_heredoc_parent(int sig);

#endif