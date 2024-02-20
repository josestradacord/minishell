/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:48:50 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/11 16:46:20 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h> 
# include <fcntl.h>
# include <errno.h>

# include "libft/libft.h"

// DEBUG = 0 no debug; DEBUG = 1 debug
# define DEBUG	1

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
	char		*wanted;
	char		**rout;		//added by Gabriel
	t_token		*tokens;
	int			num_pipes;
	pid_t			child_pid;
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

char		**ft_routes(char **envp);

// Functions used to manage the list of environment variables
t_list_e	*ft_lste_new(char *key, char *value);
int			ft_lste_size(t_list_e *lst);
t_list_e	*ft_create_node(char *env_var);
void		ft_lste_addback(t_list_e **lst, t_list_e *new);
void		ft_lste_delone(t_list_e *lst, void (*del)(void *));
void		ft_lste_clear(t_list_e **lst, void (*del)(void *));

// Functions used to manage the environment variables
void		ft_get_env(t_ms *ms, char **envp);
void		ft_copy_envp(t_ms *ms, char **envp);
void		ft_print_env(char **envp);
void		ft_print_env_lst(t_list_e *env);
char		*ft_get_env_value(char *name, t_ms *ms);

void		ft_lste_rm(t_list_e *env, char *tofind);
void		ft_env_rm(t_ms *ms, char *tofind);


// Parser functions
void		ft_parser(t_ms *ms);
void		ft_parse_tokens(t_ms *ms);
void		ft_print_tok_list(t_token *tok);
void		ft_simp_quote(t_ms *ms, int *start, int *end, char s_quot);
void		ft_dbl_quote(t_ms *ms, int *start, int *end, char s_quot);
void		ft_redir_pipe_node(t_ms *ms, int *start, int *end, char tok);
void		ft_new_token(t_ms *ms, int start, int end);
void		ft_normal_tok(t_ms *ms, int *start, int *index);
void		ft_token_type(t_ms *ms);

// Executor functions
void		ft_executor(t_ms *ms);
char		**ft_create_command(t_token *tok);

// Builtins functions
void		ft_echo(t_ms *ms);
void		ft_cd(t_ms *ms, char *dir);
void			ft_exit(t_ms *ms);
void		ft_pwd(t_ms *ms);
void		ft_export(t_ms *ms);

int	ft_cmd(t_ms *ms);
int	ft_pipe(t_ms *ms);
int	ft_search(t_ms *ms);
char	**ft_free2(char **str);

//Clean and free functions
void		ft_free(t_ms *ms, int exit_code);
void		ft_free_cmds(t_ms *ms);
void		ft_free_toks(t_ms *ms);
void		ft_free_tok_list(t_token *tok);
void		ft_free_command(t_ms *ms);

//Utils
char		**ft_joineq(char *astr, char *cr);
int			ft_liste_comp(t_list_e *env, char **val);

#endif