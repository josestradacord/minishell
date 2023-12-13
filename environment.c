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

void	ft_get_env(t_ms *ms, char **envp)
{
	int			index;
	t_list_e	*node;

	index = 0;
	ms->env = NULL;
	while (envp[index] != NULL)
	{
		node = ft_create_node(envp[index]);
		if (!node)
			return ;	// es mejor devolver algo??
		ft_lste_addback(&ms->env, node);
		index++;
	}
}
