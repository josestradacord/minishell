/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:48:15 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/10 16:21:11 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_env(char **envp)
{
	int	index;

	index = 0;
	while (envp[index] != NULL)
	{
		printf("%s\n", envp[index]);
		index++;
	}
}

void	ft_print_env_lst(t_list_e *env)
{
	t_list_e	*node;

	node = env;
	while (node)
	{
		printf("%s=%s\n", node->name, node->value);
		node = node->next;
	}
}

t_list_e	*ft_create_node(char *env_var)		//modified by Gabriel 09/02/2024
{
	char		**pair;
	t_list_e	*node;
	int			i;

	i = 2;
	pair = ft_split(env_var, '=');			//de esta forma se añaden los '=' que forman parte de los valores de las variables (vease LS_COLORS)
	while (pair[i])
	{
		pair[1] = ft_strjoin(pair[1], "=");
		pair[1] = ft_strjoin(pair[1], pair[i++]);
	}
	node = ft_lste_new(pair[0], pair[1]);
	free(pair[0]);
	free(pair[1]);
	free(pair);
	return (node);
}

void	ft_copy_envp(t_ms *ms, char **envp)
{
	int	index;

	index = 0;
	while (envp[index])
		index++;
	ms->envp = malloc(sizeof(char *) * (index + 1));
	if (!ms->envp)
		perror("malloc error");
	index = 0;
	while (envp[index])
	{
		ms->envp[index] = ft_strdup(envp[index]);
		index++;
	}
	ms->envp[index] = NULL;
}

void	ft_get_env(t_ms *ms, char **envp)
{
	int			index;
	t_list_e	*node;

	index = 0;
	ms->env = NULL;
	//ft_copy_envp(ms, envp);
	while (envp[index] != NULL)
	{
		node = ft_create_node(envp[index]);
		if (!node)
			perror("create node error");
			// es mejor devolver algo?? return ;	
		ft_lste_addback(&ms->env, node);
		index++;
	}
}

		//added by Gabriel 09/02/2024

void	ft_lste_rm(t_list_e *env, char *tofind)
{
	t_list_e	*temp;
	t_list_e	*temp2;

	if (env == NULL || env->next == NULL)
		return ;
	temp = env;
	temp2 = temp;
	if (ft_strncmp(env->next->name, tofind, ft_strlen(tofind)) == 0)
	{
		temp = env->next;
		env->next = temp->next;
		free(temp); //liberar nodo y enlazar el siguiente con el anterior
	}
	if (ft_strncmp(env->name, tofind, ft_strlen(tofind)) == 0)
	{
		temp = env;
		*env = *env->next;
		//free(temp);
	}
	else
	{
		temp = env;
		ft_lste_rm(temp->next, tofind);
	}
}

		//end add
