/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:20:36 by joestrad          #+#    #+#             */
/*   Updated: 2024/03/11 18:39:49 by joestrad         ###   ########.fr       */
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
