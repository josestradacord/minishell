#include "minishell.h"

char	**ft_joineq(char *astr, char *cr)
{
	int		i;
	char	**pair;
	char	*temp;
	char	*temp2;

	i = 2;
	pair = ft_split(astr, cr[0]);
	//temp = ft_strdup(pair[1]);
	while (pair[i])
	{
		pair[1] = ft_strjoin(pair[1], cr);
		pair[1] = ft_strjoin(pair[1], pair[i]);
		//temp = ft_strdup(temp2);
		i++;
	}
//	free(temp);
		//pair[1] = ft_strjoin(pair[1], pair[i]);
	//ft_free2(pair);
	return (pair);
}

/* 	while (pair[i + 1])
	{
		temp = ft_strdup(pair[i]);
		temp2 = ft_strjoin(temp, cr);
		//temp = ft_strdup(temp2);
		free(temp);
		i++;
	}
	pair[1] = ft_strdup(temp2);
	free(temp2); */

int	ft_liste_comp(t_list_e *env, char **val)
{
	t_list_e	*temp;

	temp = env;
	if (temp == NULL)		//comprobar que esto vaya bien
		return (1);
	if (ft_strncmp(temp->name, val[0], ft_strlen(val[0])) == 0)
	{
		free(temp->value);
		temp->value = ft_strdup(val[1]);
		return (0);
	}
	else
		ft_liste_comp(temp->next, val);
	return (0);
}