/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:20:36 by joestrad          #+#    #+#             */
/*   Updated: 2024/03/09 19:21:13 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		free(temp);
	}
	else if (ft_strncmp(env->name, tofind, ft_strlen(tofind)) == 0)
	{
		temp = env;
		*env = *env->next;
	}
	else
	{
		temp = env;
		ft_unset(temp->next, tofind);
	}
}
