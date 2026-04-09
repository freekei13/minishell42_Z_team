#include "lexing.h"

t_dquote	spaces(t_dquote qt, char *str)
{
	while (str[qt.i] && str[qt.i] != 39 && str[qt.i] != 34)
		qt.i++;
	qt.split[qt.s++] = ft_substr(str, qt.j + 1, qt.i - qt.j - 1);
	if (str[qt.i] && (str[qt.i] == 39 || str[qt.i] == 34))
	{
		qt.q_val = 1;
		qt.quote = str[qt.i];
		qt.i++;
	}
	qt.j = qt.i - 1;
	return (qt);
}

t_dquote	parenthese(t_dquote qt, char *str)
{
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

t_dquote	dollar(t_dquote qt, char *str, char **env)
{
	if (qt.j + 1 != qt.i && qt.i != 0)
		qt.split[qt.s++] = ft_substr(str, qt.j + 1, qt.i - qt.j - 1);
	qt.j = qt.i;
	while (str[qt.i] && str[qt.i] != 34 && str[qt.i] != 32 && str[qt.i] != 39)
		qt.i++;
	if (find_env(env, ft_substr(str, qt.j + 1, qt.i - qt.j - 1)) != NULL)
		qt.split[qt.s++] = find_env(env, ft_substr(str, qt.j + 1, qt.i
				- qt.j - 1));
	if (str[qt.i] == qt.quote && str[qt.i + 1] == 39)
	{
		qt.quote = str[++qt.i];
		qt.q_val = 1;
	}
	else if (str[qt.i] == qt.quote && str[qt.i + 1] != qt.quote)
		qt.q_val = 0;
	qt.j = qt.i;
	if (str[qt.i - 1] == 39 || str[qt.i] == 32 || (str[qt.i] == 39
			&& str[qt.i - 1] != 34))
		qt.j--;
	if (str[qt.i] == qt.quote)
		qt.i++;
	return (qt);
}

char	**dequote(t_dquote qt, char *str, char **env)
{
	int	x;

	qt.q_val = 1;
	if (str[0] == '$')
		qt.q_val = 0;
	while (str[++qt.i])
	{
		x = -1;
		if (str[qt.i] == qt.quote && qt.i != 0)
		{
			qt = parenthese(qt, str);
		}
		else if (str[qt.i] == '$' && (qt.quote == 34 || qt.q_val == 0))
		{
			qt = dollar(qt, str, env);
		}
		else if (str[qt.i] && qt.q_val == 0)
		{
			qt = spaces(qt, str);
		}
	}
	qt.split[qt.s] = NULL;
	return (qt.split);
}
