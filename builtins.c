/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:47:59 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/11 16:58:31 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_echo(char **str)
{
	int	i;
	int	k;

	if (ft_strncmp(str[1], "-n", 2) == 0 && str[1][2] == '\0')
	{
		i = 2;
		k = 0;
	}
	else
	{
		i = 1;
		k = 1;
	}
	while (str[i + 1])
		ft_printf("%s ", str[i++]);
	if (k == 1)
		ft_printf("%s\n", str[i]);
	else
		ft_printf("%s", str[i]);
}

int	ft_exit(t_ms *ms)
{
	exit(0);
}


void	ft_cd(char *dir)
{
	if (chdir(dir) != 0)
	{
		dup2(STDERR_FILENO, STDIN_FILENO);
		ft_printf("No existe el archivo o el directorio: %s\n", dir); //cambiar mensaje de error
	}
}

//Tener en cuenta que al ejecutarssssssssse una shell dentro de la shell el SHLVL aumenta en 1

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

	i = 0;
	temp = ms->env;
	args = ft_split(ms->cmds->cmd, ' ');
	if (!args[1])
		while (temp)
		{
			ft_printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
			temp = temp->next;
		}
	else
		while(args[++i] != NULL)
		{
			val = ft_joineq(args[i], "=");
			if (ft_isalpha(val[0][0]) == 1)
				if (ft_liste_comp(ms->env, val) != 0)
				{	
					new = ft_lste_new(val[0], val[1]);
					ft_lste_addback(&temp, new);
				}
			ft_free2(val);
		}
	ft_free2(args);
}
