/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:48:15 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/11 16:57:19 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

t_list_e	*ft_create_node(char *env_var)
{
	char		**pair;
	t_list_e	*node;
	int			index;
	int			len;

	index = 0;
	len = ft_strlen(env_var);
	pair = malloc(sizeof(char *) * 3);
	if (!pair)
		perror("malloc error");
	while (env_var[index] && env_var[index] != '=')
		index++;
	pair[0] = ft_substr(env_var, 0, index);
	pair[1] = ft_substr(env_var, index + 1, len);
	pair[2] = NULL;
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

void	ft_copy_env2lst(t_ms *ms, char **envp)
{
	int			index;
	t_list_e	*node;

	index = 0;
	ms->env = NULL;
	while (envp[index] != NULL)
	{
		node = ft_create_node(envp[index]);
		if (!node)
			perror("create node error");
		ft_lste_addback(&ms->env, node);
		index++;
	}
}

char	*ft_get_env_value(char *name, t_ms *ms)
{
	t_list_e	*node;
	char		*val;

	node = ms->env;
	val = NULL;
	while (node)
	{
		if (!ft_strncmp(name, node->name, ft_strlen(name)))
		{
			val = ft_strdup(node->value);
			return (val);
		}
		node = node->next;
	}
	return (NULL);
}
