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


void	ft_echo(t_ms *ms)
{
	int		index;

	index = 1;
	while (ms->command[index])
	{
		ft_putstr_fd(ms->command[index], STDOUT_FILENO);
		index++;
		if (ms->command[index])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

/* void	ft_echo(char **str)
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
} */

/* int	ft_exit(t_ms *ms)
{
	exit(0);
} */

void	ft_exit(t_ms *ms)
{
	int	index;

	index = 0;
	while (ms->command[index])
		index++;
	if (index == 1)
	{
		ft_putstr_fd(ms->command[index - 1], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		ft_free(ms, EXIT_SUCCESS);
	}
}

void	changepwd(t_ms *ms, char *dir)
{
	t_list_e	*temp;
	t_list_e	*old;

	temp = ms->env;
	old = ms->env;
	while (temp && ft_strncmp(temp->name, "PWD", 3) != 0)
		temp = temp->next;
	if (dir == NULL)
	{
		while (old && ft_strncmp(old->name, "HOME", 4) != 0)
			old = old->next;
		chdir(old->value);
		free(temp->value);
		temp->value =malloc(100 * sizeof(char));
		getcwd(temp->value, 100);
		return ;
	}
	while (old && ft_strncmp(old->name, "OLDPWD", 6) != 0)
		old = old->next;
	if (ft_strncmp(dir, "-", 1) == 0)
		chdir(old->value);
 	free(old->value);
	old->value = ft_strdup(temp->value);
	free(temp->value);
	temp->value =malloc(100 * sizeof(char));
	getcwd(temp->value, 100);
	if (ft_strncmp(dir, "/", 1) == 0)
		chdir("/");
}

void	ft_cd(t_ms *ms, char *dir)		//aumentar el SHLVL
{
	if (dir == NULL)
		changepwd(ms, dir);
	else if (chdir(dir) != 0)
	{
		dup2(STDERR_FILENO, STDIN_FILENO);
		//changepwd(ms, dir);
		ft_printf("No existe el archivo o el directorio: %s\n", dir); //cambiar mensaje de error
	}
	else
	{
		printf("existe el dir %s", dir);
			changepwd(ms, dir);}
}

//Tener en cuenta que al ejecutarse una shell dentro de la shell el SHLVL aumenta en 1

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
	//char		**args;
	t_list_e	*temp;
	t_list_e	*new;
	char		**val;
	int			i;

	i = 0;
	temp = ms->env;
	//args = ft_split(ms->cmds->cmd, ' ');
	if (!ms->command[1])
		while (temp)
		{
			ft_printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
			temp = temp->next;
		}
	else
		while(ms->command[++i] != NULL)
		{
			val = ft_joineq(ms->command[i], "=");
			if (ft_isalpha(val[0][0]) == 1)
				if (ft_liste_comp(ms->env, val) != 0)
				{	
					new = ft_lste_new(val[0], val[1]);
					ft_lste_addback(&temp, new);
				}
			ft_free2(val);
		}
	//ft_free2(args);
}

void	ft_lste_rm(t_list_e *env, char *tofind)		//unset
{
	t_list_e	*temp;				//Si no existe la variable a borrar no hace nada
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
	else if (ft_strncmp(env->name, tofind, ft_strlen(tofind)) == 0)
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
