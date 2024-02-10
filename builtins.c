/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:47:59 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/10 17:54:10 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	ft_echo(t_ms *ms)
{
	int		index;
	t_list	*node;

	node = ms->cmd->args;
	index = ft_lstsize(node);
	while (index > 0)
	{
		printf("%s ", node->content);
		node = node->next;
		index--;
	}
	printf("\n");
	return (TRUE);
}

int	ft_exit(t_ms *ms)
{
	(void)	*ms;
	return (FALSE);
}
*/

void	ft_pwd(t_ms *ms)
{
	t_ms *temp;

	temp = ms;
	while(strncmp(temp->env->name,"PWD", 3) != 0)
	{
		if (temp == NULL  || temp->env->next == NULL) // COMPROBAR QUE AL BORRAR PWD  y usar este comando no pete
			return ;
		temp->env = temp->env->next;
	}
	ft_printf("%s\n", temp->env->value);
	}

		//export a secas muestra las variables(ver en detalle),
		//puedes declarar varias variables con y sin valor en la misma linea de comando
		//(ej:export a=1 b=2 ext ; export a b c)
		//si tiene un pipe parece que no hace nada

char	**ft_free2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free (str);
	return (NULL);
}

void	ft_export(t_ms *ms)		//faltan comprobantes de que la variable exista y que el nombre de la variable exista(ej. b= 23(mal); 23(mal))
{
	char		**args;
	t_list_e	*temp;
	t_list_e	*new;
	char		**val;
	int			i;
	char		*borrar;

	i = 0;
	temp = ms->env;
	args = ft_split(ms->cmds->cmd, ' ');
	if (!args[1])
		while (temp)
		{
			ft_printf("declare -x %s=\34%s\34\n", temp->name, temp->value);
			temp = temp->next;
		}
	else
		while(args[++i] != NULL)
		{
			val = ft_split(args[i], '=');
			new = ft_lste_new(val[0], val[1]);
			ft_lste_addback(&temp, new);
			ft_free2(val);
		}
	ft_free2(args);
}
