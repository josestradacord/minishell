/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:59:35 by joestrad          #+#    #+#             */
/*   Updated: 2024/03/09 18:07:51 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	changepwd(t_ms *ms, char *dir)
{
	t_list_e	*temp;
	t_list_e	*old;

	temp = ms->env;
	old = ms->env;
	while (temp && ft_strncmp(temp->name, "PWD", 3) != 0)
		temp = temp->next;
	if (temp == NULL)
		return ;
	if (dir == NULL)
	{
		while (old && ft_strncmp(old->name, "HOME", 4) != 0)
			old = old->next;
		if (old->value)
			chdir(old->value);
		else
			return ;
		free(temp->value);
		temp->value = malloc(100 * sizeof(char));
		if (!temp->value)
			perror("malloc error");
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
	temp->value = malloc(100 * sizeof(char));
	if (!temp->value)
		perror("malloc error");
	getcwd(temp->value, 100);
	if (ft_strncmp(dir, "/", 1) == 0)
		chdir("/");
}

int	ft_cd(t_ms *ms, char *dir)
{
	if (dir == NULL)
		changepwd(ms, dir);
	else if (ft_strncmp(dir, "-", 1) == 0)
		changepwd(ms, dir);
	else if (chdir(dir) != 0)
	{
		//write(2, "cd: no such file or directory\n", 30);
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(dir, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		ms->status = 1;
		return (1);
	}
	else
		changepwd(ms, dir);
	return (0);
}

void	ft_pwd(t_ms *ms)
{
	char	pwd[100];

	if (ms->command[1] == NULL)
	{
		getcwd(pwd, 100);
		printf("%s\n", pwd);
	}
	else
		write(2, "pwd: too many arguments\n", 24);
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

int	ft_export(t_ms *ms)
{
	t_list_e	*temp;
	t_list_e	*new;
	char		**val;
	int			i;

	i = 0;
	temp = ms->env;
	if (!ms->command[1])
	{
		while (temp)
		{
			ft_printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
			temp = temp->next;
		}
	}
	else
	{
		while (ms->command[++i] != NULL)
		{
			val = ft_joineq(ms->command[i]);
			if (ft_isalpha(val[0][0]) == 1)
			{
				if (ft_liste_comp(ms->env, val) != 0)
				{
					new = ft_lste_new(val[0], val[1]);
					ft_lste_addback(&temp, new);
				}
				ft_free2(val);
			}
			else
			{
				write(2, "export: not a valid identifier\n", 31);
				ft_free2(val);
				return (1);
			}
		}
	}
	return (0);
}
