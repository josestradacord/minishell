/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestradac <jestradac@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:48:50 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/18 18:34:01 by jestradac        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft/libft.h"

// DEBUG = 0 no debug; DEBUG = 1 debug
# define DEBUG	0

# define FALSE	0
# define TRUE	1

// Token delimiters
# define TOKSTR		"><|;"
# define SEPCHAR	"><| "
# define ENVCHARS	"><| '\"$"

// Types of tokens
# define NOQUOTE	10
# define SNGQUOTE	11
# define DBLQUOTE	12
# define INPREDIR	13
# define OUTREDIR	14
# define OUTREDIR_A	15
# define PIPE		16
# define HEREDOC	17

// Struct to keep the environment variables as a list
typedef struct s_list_e
{
	char			*name;
	char			*value;
	struct s_list_e	*next;
}	t_list_e;

// Struct to 
typedef struct s_token
{
	int				type;
	char			*token;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

/*typedef struct s_string_l
{
	char				*string;
	struct s_string_l	*next;
}	t_string_l;
*/
typedef struct s_cmd
{
	char			*cmd;
	int				has_pipe;
	int				file_in;
	int				file_out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_ms
{
	char		*line;
	char		**command;
	t_token		*tokens;
	int			num_pipes;
	pid_t		child_pid;
	t_list_e	*env;
	char		**envp;
	int			status;
	t_cmd		*cmds;
}	t_ms;

// Check functions
int			ft_check_args(int n_arg);
void		ft_usage(void);
int			ft_blank_line(char *line);

// Init functions
void		ft_init_data(t_ms *ms, char **argv, char **envp);

// Functions used to manage the list of environment variables
t_list_e	*ft_lste_new(char *key, char *value);
int			ft_lste_size(t_list_e *lst);
void		ft_lste_addback(t_list_e **lst, t_list_e *new);
void		ft_lste_delone(t_list_e *lst, void (*del)(void *));
void		ft_lste_clear(t_list_e **lst, void (*del)(void *));

// Functions used to manage the environment variables
void		ft_get_env(t_ms *ms, char **envp);
void		ft_copy_envp(t_ms *ms, char **envp);
void		ft_print_env(char **envp);
void		ft_print_env_lst(t_list_e *env);
char		*ft_get_env_value(char *name, t_ms *ms);

// Parser functions
void		ft_parser(t_ms *ms);
void		ft_parse_tokens(t_ms *ms);
void		ft_print_tok_list(t_ms *ms);

// Executor functions
void		ft_executor(t_ms *ms);
void		ft_create_command(t_ms *ms);

// Builtins functions
void		ft_echo(t_ms *ms);
void		ft_exit(t_ms *ms);

//Clean and free functions
void		ft_free(t_ms *ms, int exit_code);
void		ft_free_cmds(t_ms *ms);
void		ft_free_toks(t_ms *ms);
void		ft_free_command(t_ms *ms);
#endif
