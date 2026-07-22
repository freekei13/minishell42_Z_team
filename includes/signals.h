/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:00:30 by csamakka          #+#    #+#             */
/*   Updated: 2026/07/22 23:45:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <termios.h>
# include <stddef.h>
# include "lexing.h"

extern int g_signal;

void	signal_set(t_data data);
void	sigint_heredoc(void);
void	sigint_after_heredoc(void);
void	sigint_after_cmd(void);
void    sigint_silent_child(void);

void	sigint_mod(int sig);
void	sigint_mod_exec(int sig);
void	sigint_mod_heredoc_parent(int sig);
void    sigint_mod_silent(int sig);

#endif