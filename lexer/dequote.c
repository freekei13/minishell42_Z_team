/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csamakka <csamakka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 11:59:33 by lalamino          #+#    #+#             */
/*   Updated: 2026/08/03 12:30:16 by csamakka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

t_dquote	spaces(t_dquote qt, char *str)
{
	while (str[qt.i] && str[qt.i] != 39 && str[qt.i] != 34 && str[qt.i] != 36)
		qt.i++;
	qt.split[qt.s++] = ft_substr(str, qt.j + 1, qt.i - qt.j - 1);
	if (str[qt.i] && (str[qt.i] == 39 || str[qt.i] == 34))
	{
		qt.q_val = 0;
		qt.quote = str[qt.i];
		qt.i--;
	}
	if (str[qt.i] == '$')
		qt.i--;
	qt.j = qt.i;
	return (qt);
}

// Responsabilité : ouvrir une region quotee. Appelee uniquement depuis
// parenthese() quand on etait hors quotes (q_val == 0), donc la quote sous
// qt.i est forcement une OUVRANTE. On pousse le segment non quote en attente
// [qt.j + 1 .. qt.i - 1] (souvent vide), on enregistre le delimiteur, et
// qt.j = qt.i pour que le prochain flush couvre le contenu de la region.

t_dquote	open_quote(t_dquote qt, char *str)
{
	qt.split[qt.s++] = ft_substr(str, qt.j + 1, qt.i - qt.j - 1);
	qt.q_val = 1;
	qt.quote = str[qt.i];
	qt.j = qt.i;
	return (qt);
}

// Responsabilité : traiter un caractere de quote. C'est q_val — et non le
// caractere lui-meme ni son voisin — qui decide du sens :
//   - q_val == 0 : rien n'est ouvert, donc cette quote OUVRE -> open_quote().
//   - q_val == 1 : cette quote FERME la region ouverte en qt.j. On pousse son
//     contenu [qt.j + 1 .. qt.i - 1], puis si le caractere suivant est lui
//     aussi une quote, c'est l'ouvrante d'une nouvelle region collee
//     ("abc"'def') : on avance sur elle et on repart a q_val == 1.
// Ne jamais deduire l'etat d'une paire de caracteres : dans "'$USER'" le '\''
// qui suit la '"' ouvrante n'est pas un delimiteur, c'est du texte. Le
// quoting POSIX n'est pas symetrique — dans "..." seuls $, `, " et \ gardent
// un sens ; dans '...' tout est litteral.

t_dquote	parenthese(t_dquote qt, char *str)
{
	if (qt.q_val == 0)
		return (open_quote(qt, str));
	qt.split[qt.s++] = ft_substr(str, qt.j + 1, qt.i - qt.j - 1);
	qt.q_val = 0;
	if (str[qt.i + 1] && (str[qt.i + 1] == 34 || str[qt.i + 1] == 39))
	{
		qt.quote = str[++qt.i];
		qt.q_val = 1;
	}
	qt.j = qt.i;
	return (qt);
}

// Responsabilité : orchestrer l'expansion d'un $ puis remettre l'état de
// quoting dans l'invariant attendu par la boucle de dequote().
// Apres scan/resolve, qt.i pointe sur le caractere qui a arrete le scan du
// nom de variable ('"', '\'', ' ', '$' ou '\0') : ce caractere n'est PAS
// consomme, il doit etre redispatche par la boucle.
//   - hors quotes (q_val == 0) et on tombe sur une quote : c'est forcement
//     une OUVRANTE (rien n'etait ouvert), on enregistre le delimiteur et on
//     laisse qt.i dessus.
//   - sinon on recule qt.i d'un cran, car la boucle fait while (str[++qt.i])
//     et chaque handler doit laisser qt.i sur le dernier caractere consomme.
//   - exception $? : dollar_resolve a deja repositionne qt.i sur le '?',
//     reculer une seconde fois ferait relire le '$'.
// qt.quote et q_val ne sont jamais touches en dehors du 1er cas : une
// expansion ne change pas l'etat de quoting ("$USER'" reste dans des
// doubles quotes, le '\'' qui suit est litteral).

t_dquote	dollar(t_dquote qt, char *str, char **env, int ext_status)
{
	qt = dollar_scan(qt, str);
	qt = dollar_resolve(qt, str, env, ext_status);
	if (qt.q_val == 0 && (str[qt.i] == '\"' || str[qt.i] == '\''))
	{
		qt.quote = str[qt.i];
		qt.q_val = 1;
	}
	else if (str[qt.j] != '$' || str[qt.j + 1] != '?')
		qt.i--;
	qt.j = qt.i;
	qt.expand = 0;
	return (qt);
}

char	**dequote(t_dquote qt, char *str, char **env, int ext_status)
{
	qt.q_val = 1;
	if (qt.i != -1)
	{
		qt.i -= 1;
		qt.j -= 1;
		qt.q_val = 0;
	}
	if (qt.i != -1 && str[qt.i] == '\0')
		return (qt.split);
	if (str[qt.i + 1] == '$')
		qt.q_val = 0;
	qt.expand = 0;
	while (str[++qt.i])
	{
		if (str[qt.i] == qt.quote && qt.i != 0 && qt.quote != '$')
			qt = parenthese(qt, str);
		else if (str[qt.i] == '$' && (qt.quote == 34 || qt.q_val == 0))
			qt = dollar(qt, str, env, ext_status);
		else if ((str[qt.i] && qt.q_val == 0))
			qt = spaces(qt, str);
		if (str[qt.i] == '\0')
			break ;
	}
	qt.split[qt.s] = NULL;
	return (qt.split);
}
