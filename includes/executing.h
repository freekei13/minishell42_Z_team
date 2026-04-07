/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 21:32:43 by csamakka          #+#    #+#             */
/*   Updated: 2026/04/08 00:02:23 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

#include "parsing.h"
#include <fcntl.h>
#include <errno.h>

void	executer(t_ast *ast);

#endif