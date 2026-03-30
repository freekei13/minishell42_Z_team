/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:29:27 by csamakka          #+#    #+#             */
/*   Updated: 2026/03/30 19:30:27 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// Algorithme du parser
// - cherche token pipe. si trouve cree un noeud pipe.
// 	- gauche et droite
// - si pas de pipe.
// 	- cree un noeud cmd
// test test