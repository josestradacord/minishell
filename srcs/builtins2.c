/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:59:35 by joestrad          #+#    #+#             */
/*   Updated: 2024/03/13 17:00:43 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_dir_null(t_ms *ms, t_list_e *temp)
{
	t_list_e	*old;

	old = ms->env;
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
}

void	changepwd_aux(t_ms *ms, char *dir, t_list_e *temp, t_list_e *old)
{
	if (ft_strncmp(dir, "-", 1) == 0)
	{
		if (chdir(old->value) < 0)
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			ft_putstr_fd(old->value, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			return ;
		}
		else
		{
			ft_putstr_fd(ft_get_env_value("OLDPWD", ms), STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
	}
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
		ft_dir_null(ms, temp);
		return ;
	}
	while (old && ft_strncmp(old->name, "OLDPWD", 6) != 0)
		old = old->next;
	changepwd_aux(ms, dir, temp, old);
}

int	ft_cd(t_ms *ms, char *dir)
{
	if (dir == NULL)
		changepwd(ms, dir);
	else if (ft_strncmp(dir, "-", 1) == 0)
		changepwd(ms, dir);
	else if (chdir(dir) != 0)
	{
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
