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

#include "../include/minishell.h"

int	ft_nflag(char *str)
{
	int	index;

	index = 0;
	if (str[index++] != '-')
		return (FALSE);
	while (str[index])
	{
		if (str[index] != 'n')
			return (FALSE);
		index++;
	}
	return (TRUE);
}

void	ft_echo(t_ms *ms)
{
	int	index;
	int	n_flg;

	index = 1;
	n_flg = FALSE;
	if (ms->command[index])
		n_flg = ft_nflag(ms->command[index]);
	if (ms->command[index] && n_flg)
		index++;
	while (ms->command[index])
	{
		ft_putstr_fd(ms->command[index], STDOUT_FILENO);
		index++;
		if (ms->command[index])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!n_flg)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

void	ft_exit(t_ms *ms)
{
	int	index;
	int	i;

	i = 0;
	index = 0;
	while (ms->command[index])
		index++;
	if (index == 1)
	{
		ft_putstr_fd(ms->command[index - 1], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		ft_free(ms, EXIT_SUCCESS);
	}
	else if (index == 2)
	{
		while (ms->command[1][i] && ft_isdigit(ms->command[1][i]))
			i++;
		if (ms->command[1][i] == '\0')
		{
			ft_putstr_fd(ms->command[index - 2], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			ft_free(ms, ft_atoi(ms->command[1]));
		}
	}
	else
		write(2, "minishell: exit: too many arguments\n", 36);
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
	else if (chdir(dir) != 0)
	{
		write(2, "cd: no such file or directory\n", 30);
		return (1);
		//changepwd(ms, dir);
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

void	ft_export(t_ms *ms)
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
			}
			ft_free2(val);
		}
	}
}

void	ft_unset(t_list_e *env, char *tofind)
{
	t_list_e	*temp;
	t_list_e	*temp2;

	if (env == NULL || env->next == NULL)
		return ;
	temp = env;
	temp2 = temp;
	if (ft_strncmp(env->next->name, tofind, ft_strlen(tofind)) == 0)
	{
		temp = env->next;
		env->next = temp->next;
		free(temp);
	}
	else if (ft_strncmp(env->name, tofind, ft_strlen(tofind)) == 0)
	{
		temp = env;
		*env = *env->next;
	}
	else
	{
		temp = env;
		ft_unset(temp->next, tofind);
	}
}