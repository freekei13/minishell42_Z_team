
#include "lexing.h"

char	**make_env(char **env)
{
	int		i;
	char	**res;
	int		j;

	j = 0;
	while (env[j])
		j++;
	i = -1;
	res = malloc(sizeof(char **) * j);
	while (env[++i])
		res[i] = ft_strdup(env[i]);
	res[i] = NULL;
	return (res);
}

char	*find_env(char **env, char *cherche)
{
	int	i;
	int	j;

	j = -1;
	while (env[++j])
	{
		i = 0;
		while (cherche[i] == env[j][i])
			i++;
		if (env[j][i] == '=')
			return (env[j] + i + 1);
	}
	return (NULL);
}
