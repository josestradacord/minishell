/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:20:36 by joestrad          #+#    #+#             */
/*   Updated: 2024/03/11 19:04:57 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_env(t_list_e *enval)
{
	free(enval->name);
	free(enval->value);
	free(enval);
}

void	ft_unset(t_list_e *env, char *tofind)
{
	t_list_e	*temp;

	if (env == NULL || env->next == NULL)
		return ;
	temp = env;
	if (ft_strncmp(env->next->name, tofind, ft_strlen(tofind)) == 0)
	{
		temp = env->next;
		env->next = temp->next;
		ft_free_env(temp);
	}
	else if (ft_strncmp(env->name, tofind, ft_strlen(tofind)) == 0)
	{
		temp = env;
		env = env->next;
		ft_free_env(temp);
	}
	else
	{
		temp = env;
		ft_unset(temp->next, tofind);
	}
}

int	ft_export(t_ms *ms)
{
	t_list_e	*temp;
	t_list_e	*new;
	char		**val;
	int			i;

	i = 0;
	temp = ms->env;
	if (!ms->command[1])
	{
		while (temp)
		{
			ft_printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
			temp = temp->next;
		}
	}
	else
	{
		while (ms->command[++i] != NULL)
		{
			val = ft_joineq(ms->command[i]);
			if (ft_isalpha(val[0][0]) == 1)
			{
				if (ft_liste_comp(ms->env, val) != 0)
				{
					new = ft_lste_new(val[0], val[1]);
					ft_lste_addback(&temp, new);
				}
				ft_free_matrix(val);
			}
			else
			{
				write(2, "export: not a valid identifier\n", 31);
				ft_free_matrix(val);
				return (1);
			}
		}
	}
	return (0);
}
