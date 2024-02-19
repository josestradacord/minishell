/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestradac <jestradac@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:48:15 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/18 01:28:10 by jestradac        ###   ########.fr       */
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

t_list_e	*ft_create_node(char *env_var)
{
	char		**pair;
	t_list_e	*node;

	pair = ft_split(env_var, '=');
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

char	*ft_get_env_value(char *name, t_ms *ms)
{
	//char		*value;
	t_list_e	*node;

	node = ms->env;
	while (node)
	{
		if (!ft_strncmp(name, node->name, ft_strlen(name)))
			return (node->value);
		node = node->next;
	}
	return (NULL);
}
