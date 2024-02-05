/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:48:57 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/05 18:48:59 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_new_cmd(t_ms *ms, int s, int e)
{
	t_cmd	*new;
	t_cmd	*tmp;
	char	*cmd;

	cmd = ft_substr(ms->line, s, e - s);
	printf("DEBUG: Obteniendo el comando ft_new_cmd(). Comando: #%s#\n", cmd);
	new = (t_cmd *) malloc(sizeof(t_cmd));
	if (!new)
		return ;
	new->cmd = cmd;
	//free(cmd);
	printf("DEBUG: Comando: #%s#\n", new->cmd);
	new->next = NULL;
	if (!ms->cmds)
		ms->cmds = new;
	else
	{
		tmp = ms->cmds;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_getcmd(t_ms *ms)
{
	int	ini;
	int	end;

	ini = 0;
	end = ini;
	printf("DEBUG: Obteniendo el comando. La linea es: %s, posición: %d\n", ms->line, ini);
	while (ms->line[end] && ms->line[end] != ' ')
		end++;
	printf("DEBUG: Posición final: %d\n", end);
	ft_new_cmd(ms, ini, end);
	//ms->cmds->cmd = ft_substr(ms->line, (*p), index - (*p));
	printf("DEBUG: En ft_getcmd(), el comando es: %s\n", ms->cmds->cmd);
}

/*
void	ft_getargs(t_ms *ms, char *line, int *p)
{
	int		index;
	int		n_arg;
	t_list	*arg_node;

	(*p)++;
	index = *p;
	n_arg = 0;
	ft_printf("DEBUG: Dentro de getargs. Obteniendo posición: %d, contenido: #%c#\n", index, line[index]);
	while (line[index])
	{
		while (line[index] && line[index] != ' ')
			index++;
		ft_printf("DEBUG: Dentro del bucle de getargs. Obteniendo posición: %d, contenido: #%c#\n", index, line[index]);
		arg_node = ft_lstnew(ft_substr(line, (*p), index - (*p)));
		ft_lstadd_back(&ms->cmd->args, arg_node);
		while (line[index] && line[index] == ' ')
			index++;
		*p = index;
	}
	*p = index;
}
*/
void	ft_parser(t_ms *ms)
{
	ft_printf("DEBUG: Dentro del parser. La linea es: #%s#\n", ms->line);
	ft_getcmd(ms);
	//ft_printf("DEBUG: El comando es: %s\n", ms->cmds->cmd);
	//ft_getargs(ms, line, &pos);
	//ft_printf("DEBUG: El comando tiene %d argumentos\n", ft_lstsize(ms->cmd->args));
}
