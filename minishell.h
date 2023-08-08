/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:15:18 by bsouhar           #+#    #+#             */
/*   Updated: 2023/08/04 12:11:43 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <ctype.h>
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>

extern int			g_exit_status;

typedef enum s_ParserType
{
	CMD,
	PIPE,
	RI,
	RO,
	RA,
	RH
}					t_ParserType;

typedef struct s_split
{
	char			*data;
	struct s_split	*next;
}					t_split;

typedef struct s_parser
{
	char			*content;
	t_ParserType	type;
	struct s_parser	*next;
}					t_parser;

typedef struct s_vars
{
	char			*data;
	struct s_vars	*next;
}					t_vars;

typedef struct s_helper
{
	char			**paths;
	char			**argv;
}					t_helper;

typedef struct s_main_var
{
	char			*input;
	char			**split;
	int				i;
	int				pid;
	t_vars			*head;
	t_parser		*args;
	t_helper		*help;
	char			**env;
	char			**exprt;
	char			*pwd;
	char			**herdoc;
	int				num_command;
	pid_t			*pids;
	int				exit_status;
	int				ctrl_c_pressed;
	int				fds[2];
	char			*join4;
	char			*path;
	char			*str;
	char			*str2;
	char			**split2;
	char			*tmp;
	t_split			*splits;
	int				j;
	int				nop;
	char			*home;
	int				pipes[][2];
}					t_main_var;

char				**get_env_paths(char **env);
int					is_file_exist(char **paths, char *cmd);
char				*handle_input(char *input, int *i);
char				*handle_quotes(char *input, char quote, int *i);
int					check_quotes(char *input, int i);
char				*remove_quotes(char *input);
char				**ft_token(char *s, char *set);
char				**ft_split(char **array, char *s, char c, int idx);
char				**ft_split2(char *s, char c);
void				ft_split_v2(int *idx, char **array, int j, char *s);
int					ft_strlen(char *str);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strjoin2(char *str, char c);
char				*ft_strdup(char *str, int idx);
char				*ft_strdup2(char *str, int *idx);
char				*ft_substr(char *s, int start, int len);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_strcpy(char *str, int *start, char quote);
char				*ft_strcpy2(char *str, int *start);
char				*ft_strcpy3(char *str, int *start, char quote);

void				ft_add_list(t_vars **lst, char *data);
int					ft_strcmp(char *s1, char *s2);
int					ft_isalnum(char c);
int					check_errors(t_main_var *var);
void				check_and_pass(t_vars *head, t_parser **parser_list);
int					open_files(t_parser *head);

void				execute_one_cmd(t_main_var *var);
void				execute_multiple_cmd(t_main_var *var);

int					ft_strlen_array(char **array);
int					ft_init(t_main_var *var);
void				ft_fill_args(t_helper *help, t_parser *arg, int i,
						int num_of_arg);
void				built_ins(t_main_var *var);
void				echo(t_helper *help, char **env);
int					cd(t_helper *help, char *pwd, char *home, char **env);
int					pwd(t_helper *help, char *pwd, int fd);
char				**get_env(void);
void				expand(char *str, int *start, char **env);
void				expand2(char *argvx);
char				*get_expand(char *argv, char **env, char *join4);

int					get_pwd(char *pwd, char *path);

void				print_array(char **env);
char				**add_elements(char **env, char **array, int i);
char				**add_elements2(char **env, char **array, int i);
char				**remove_elements(char **env, char **array, int i);
int					num_of_commands(t_parser *arg);
void				create_pipes(int pipes[][2], int num_commands);
void				close_pipes(int pipes[][2], int num_commands);
int					is_env_exist(char *str, char **env);
char				*cut_str(char *str);

void				free_array(char **array);
void				free_t_vars(t_vars *vars);
void				free_t_parser(t_parser *parser);
void				free_split(t_split *vars);
void				free_helper(t_helper *help);
void				free_helper2(t_helper *help);

void				print_exit_status(void);

void				execute_one_cmd2(t_main_var *var);

void				handle_signals(void);
void				handle_sigint(int sig);
void				creat_child(t_main_var *var);
int					check_quotes_and_add_to_list(t_main_var *var);
int					check_if_pressed_ctrl_c(void);
char				*herdoc(t_parser *head, t_main_var *var);
int					check_is_empty(char *input);

void				echo2(t_helper *help, int i, int j, char **env);
void				ft_putstr(char *str);
char				*ft_itoa(int n);

void				built_ins2(t_main_var *var, char *home);
void				modify_files(t_parser *command);

void				print_exprt(char **env);
void				print_export2(char *s, int j);

void				open_herdoc(t_parser *tmp, t_main_var *var);
char				*get_home(char **env);
void				check_leaks(void);
void				print(char *s, int bit);
void				assign(int *i, int *j, char ***array, char *s);
char				**fill_env(char **env);
int					check_export(char *str);
int					ft_strchr(char *s, char c);

char				*skip_quotes(char *input);
char				*skip_quotes2(char *input, char quote, int *i, char *join);
char				*skip_quotes3(char *join, char *new);
char				*ft_strcpy4(char *str, int *start, char quote);
char				**ft_split3(char *s);

char				*get_expand2(char *argv, char **env, char *join4);
char				*get_expand_v2(char *str, char *join2, char **env);
char				*get_expand_v3(char *join4, char *join2);
char				*get_expand_v4(char *join, char *join2);
char				*part_one(char *string, int *j, char **env);
char				**add_to_arg(t_split *split, char **array);
void				add_to_parser(t_split **split, char **data);
int					is_built_ins(char *s);

t_vars				*assign1(t_vars *head, t_parser *new_node);
t_vars				*assign2(t_vars *tmp, t_parser *new_node);
t_vars				*add_pipe(t_vars *tmp, t_vars **head,
						t_parser **parser_list);
t_vars				*add_red_her(t_vars *tmp, t_parser **parser_list);
t_vars				*add_cmd(t_vars *tmp, t_parser **parser_list);
void				add_list(t_parser **parser_list, t_parser *new_node);
int					check(t_vars *head);
int					check2(t_vars *head);
char				*my_func2(int *idx, char *array, char *s, char c);

void				ft_exit(char **av);
int					ft_isspace(char c);
int					ft_atoi(const char *str);
int					is_digit(char *str);
void				init_1(t_main_var *var, int *i, int *noc);
int					num_of_pipes(t_parser *arg);
void				create_child_proc2(t_main_var *var);

void				update_pwd(char **env, char *pwd, char *oldpwd);
void				assign_elements(int *count, char *arr, int *j, char **env);
char				*expand3(char *str, int *start, char **env);
char				*part_one_v2(char *string, int *j, char **env, char *join2);
char				*herdoc2(char *her, char *input);
char				*rostring(char *str);
char				*herdoc3(char *join, t_main_var *var);
char				*expand3_v2(char *new, int i, char **env);

#endif
