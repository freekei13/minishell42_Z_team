/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:00:30 by csamakka          #+#    #+#             */
/*   Updated: 2026/06/22 23:07:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <termios.h>
# include <stddef.h>
# include "lexing.h"

void	signal_set(t_data data);
void	sigint_heredoc(void);
void	sigint_after_heredoc(void);
void	sigint_after_cmd(void);

void	sigint_mod(int sig);
void	sigint_mod_child(int sig);
void	sigint_mod_heredoc(int sig);
void	sigint_mod_heredoc_parent(int sig);

#endif