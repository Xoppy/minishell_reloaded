/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ituriel <ituriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:06:00 by adi-marc          #+#    #+#             */
/*   Updated: 2025/07/28 14:28:58 by ituriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

// Global used for signals
extern int			g_sig;

// Environment variable structure
typedef struct s_envp
{
	char			*key;
	char			**values;
}					t_envp;

// Doubly-linked list of environments
typedef struct s_envi
{
	t_envp			*env;
	struct s_envi	*prev;
	struct s_envi	*next;
}					t_envi;

// AST node for commands and operators
typedef struct s_tree
{
	char			*content;
	char			**argv;
	struct s_tree	*left;
	struct s_tree	*right;
	int				heredoc_fd;
	int				start;
	int				end;
}					t_tree;

// Execution context structure
typedef struct s_exec
{
	char			**argv;
	int				status;
	t_envi			*env;
	t_tree			*ast;
}					t_exec;

// global memory structure
typedef struct s_memory
{
	t_envi			*envi;
	t_tree			*tree;
	t_exec			*exec;
	char			*line;
	char			**tokens;
	int				status;
}					t_memory;

// init_env
void				env_init(t_envi **shell, char **envp);
void				shell_envi_init(t_memory **shell, char **envp);
void				env_destroy(t_envi *shell);

// memory
void				ft_free_string_array(char **arr);
void				ft_free_shell(t_memory **shell);

// prompt
char				*prompt_read_line(const char *prompt_fmt);

// tokenizer
char				**lexer_split_tokens(const char *input_line);
char				*next_token(const char **sp);
int					is_special(char c);

// parser
t_tree				*parser_build_ast(t_memory **shell);
void				parser_free_ast(t_tree *root);
t_tree				*make_empty_command(void);
t_tree				*parse_range(char **tokens, int start, int end);
int					is_pipe(char *s);
int					is_redirect(char *s);
t_tree				*new_node(const char *content);
char				**dup_argv(char **tokens, int start, int end);
t_tree				*make_command_node(char **tokens, int start, int end);

// executor
int					executor_execute_ast(t_tree *node, t_memory **shell);
int					executor_is_builtin(const char *command_name);
int					executor_run_builtin(t_exec *context, t_memory **shell);
int					exec_pipe_node(t_memory **shell, t_tree *node);
void				child_process(char **argv, t_memory **shell);
int					exec_redirect_node(t_tree *node, t_memory **shell);
int					redirect_out(t_tree *node, t_memory **shell, int flags);
int					redirect_in(t_tree *node, t_memory **shell);
int					get_heredoc_fd(char *delimiter, t_envi *env_list);
int					check_cmd(char *cmd, t_memory **shell);

// builtins
int					builtin_cd(t_exec *context);
int					builtin_echo(t_exec *context);
int					builtin_env(t_exec *context);
int					builtin_export(t_exec *context);
int					builtin_unset(t_exec *context);
int					builtin_pwd(t_exec *context);
int					builtin_exit(t_exec *context, t_memory **shell);
int					cd_add_env(t_envi **env_list, char *key, char *value);
int					error_cd(char *target);

// utils
int					is_valid_name(const char *name);
char				*ft_mini_strndup(const char *src, size_t n);
char				*ft_triple_strjoin(const char *s1, const char *s2,
						const char *s3);
int					ft_isspace(int c);
char				**env_list_to_array(t_envi *env);
char				*ft_strjoin_arr(char **arr, char sep);
char				**ft_strdup_arr(char **arr);
size_t				ft_arr_count(char **arr);

// path
char				*find_in_path(const char *cmd, t_envi *env_list);

// expansion
char				*expand_token(const char *token, t_envi *env_list,
						int last_status);
char				*handle_dollar(const char **cursor, t_envi *env_list,
						int last_status);
void				expand_tokens(t_memory **shell);
int					toggle_quotes(char c, int *in_single, int *in_double);
char				*get_env_str(char *key, t_envi *env_list);
char				*append_str(char *origin, char *to_add);

// signals
void				signal_init(void);

// prints
void				print_error(const char *msg);
void				print_message(const char *msg);
void				print_err_prefix(char *s);

#endif
