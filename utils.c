/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:53:51 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/02/27 20:53:51 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_joineq(char *env_var)
{
	int		index;
	int		len;
	char	**pair;

	index = 0;
	len = ft_strlen(env_var);
	pair = malloc(sizeof(char *) * 3);
	while (env_var[index] && env_var[index] != '=')
		index++;
	pair[0] = ft_substr(env_var, 0, index);
	pair[1]= ft_substr(env_var, index + 1, len);
	pair[2] = NULL;
	return (pair);
}

int	ft_liste_comp(t_list_e *env, char **val)
{
	t_list_e	*temp;

	temp = env;
	if (temp == NULL)
		return (1);
	else if (ft_strncmp(temp->name, val[0], ft_strlen(val[0])) == 0)
	{
		free(temp->value);
		temp->value = ft_strdup(val[1]);
		return (0);
	}
	else
		return(ft_liste_comp(temp->next, val));
}

int	ft_shlvlupenvp(t_ms *ms)
{
	int	i;
	int			num;

	i = 0;
		puts("entra");
	while (ms->envp[i])
	{
		if (ms->envp[i] == NULL)
			return (1);
		if (ft_strncmp(ms->envp[i], "SHLVL", 5) == 0)
		{
			printf("envp antes es %s\n", ms->envp[i]);
			num = ft_atoi(&ms->envp[i][6]);
			free(ms->envp[i]);
			num = num + 1;
			printf("num es %d\n", num);
			ms->envp[i] = ft_strjoin("SHLVL=", ft_itoa(num));
			printf("envp despues es %s\n", ms->envp[i]);
			return (0);
		}
		i++;
	}
	return(0);
}

int	ft_shlvlup(t_ms *ms)
{
	t_list_e	*temp;
	int			num;

	temp = ms->env;
	while (temp)
	{
		if (temp == NULL)
			return (1);
		if (ft_strncmp(temp->name, "SHLVL", 5) == 0)
		{
			num = ft_atoi(temp->value);
			free(temp->value);
			num++;
			temp->value = ft_strdup(ft_itoa(num));
			//return (0);
		}
		temp = temp->next;
	}
	ft_shlvlupenvp(ms);
	return(0);
}
