#include "minishell.h"

char	**ft_joineq(char *astr, char *cr)
{
	int		i;
	char	**pair;

	i = 2;
	pair = ft_split(astr, cr[0]);
	while (pair[i])
	{
		pair[1] = ft_strjoin(pair[1], cr);
		pair[1] = ft_strjoin(pair[1], pair[i++]);
	}
	return (pair);
}

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
}