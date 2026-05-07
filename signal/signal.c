/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:00:09 by csamakka          #+#    #+#             */
/*   Updated: 2026/05/07 19:27:17 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	signal_set(void)
{
	struct	sigaction	sa;
	
	sigemptyset(&sa.sa_mask);

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}