/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:00:30 by csamakka          #+#    #+#             */
/*   Updated: 2026/05/15 14:20:11 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <stddef.h>
# include "lexing.h"

void	signal_set(t_sigdata sigdata);
void	sigint_ign(void);
void	sigint_heredoc(void);

#endif