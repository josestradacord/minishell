/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:47:38 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/09 13:07:47 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief 		Counts the number of tokens that must have the command line
 * 				it stops when it finds a PIPE
 * 
 * @param tok 
 * @return int 
 */
int	ft_count_tokens(t_token *tok)
{
	int		nbr;
	t_token	*aux;

	nbr = 0;
	aux = tok;
	while (aux && aux->type != PIPE)
	{
		if (aux->type <= DBLQUOTE && aux->type >= NOQUOTE)
			nbr++;
		aux = aux->next;
	}
	return (nbr);
}

char	**ft_create_command(t_token *toks)
{
	char	**res;
	int		index;

	res = malloc(sizeof(char *) * (ft_count_tokens(toks) + 1));
	if (!res)
		perror("malloc error");
	index = 0;
	while (toks && toks->type != PIPE && toks->type != 14 && toks->type != 15)
	{
		if (toks->type <= DBLQUOTE && toks->type >= NOQUOTE)
			res[index] = ft_strdup(toks->token);
		index++;
		toks = toks->next;
	}
	res[index] = NULL;
	return (res);
}

int	ft_builtins(t_ms *ms)
{
	int	i;

	i = 0;
	if (ft_strncmp("echo", ms->command[0], 4) == 0)
		ft_echo(ms);
	else if (ft_strncmp("exit", ms->command[0], 4) == 0)
		return (ft_exit(ms));
	else if (ft_strncmp("cd", ms->command[0], 2) == 0)
		return (ft_cd(ms, ms->command[1]));
	else if (ft_strncmp("pwd", ms->command[0], 3) == 0)
		ft_pwd(ms);
	else if (ft_strncmp("env", ms->command[0], 3) == 0)
		return (ft_print_env_lst(ms->env));
	else if (ft_strncmp("unset", ms->command[0], 5) == 0)
	{
		while (ms->command[i])
		{
			ft_unset(ms->env, ms->command[i]);
			i++;
		}
	}
	else if (ft_strncmp("export", ms->command[0], 6) == 0)
		return (ft_export(ms));
	return (0);
}

void	ft_nump(t_ms *ms)
{
	t_token	*toks;

	toks = ms->tokens;
	while (toks)
	{
		if (toks->type == PIPE)
			ms->num_pipes++;
		toks = toks->next;
	}
}
