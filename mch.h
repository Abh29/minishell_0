/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mch.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 19:17:20 by mehill            #+#    #+#             */
/*   Updated: 2022/03/04 23:28:51 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MCH_H
# define MCH_H

# include <stdlib.h>
# include <stdio.h>
# include <stdio.h>
# include <signal.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <sys/stat.h>
# include <unistd.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <signal.h>
# include <string.h>

/** defenition ***/
# define SHELL_NAME "minishell> "
# define MAX_SIZE 1500
# define ACC 1
# define DEC 2
# define MAX_PIPE 128

/** enums **/

enum e_logop
{
	AND,
	OR
};

/** typedefs **/
typedef struct s_io_red
{
	int		fdin;
	int		fdout;
	int		fderr;
	char	*limiter;
	int		append;
}			t_io_red;

typedef enum e_builtings
{
	FT_ECHO,
	FT_CD,
	FT_EXPORT,
	FT_UNSET,
	FT_ENV,
	FT_EXIT,
	FT_PWD,
	FT_SUBSHELL,
	FT_NULL
}			t_builtings;

typedef struct s_cmd
{
	char			*cmd_name;
	char			**args;
	char			**envp;
	t_io_red		*red;
	int				*exit_stat;
	t_dlist			*ors;
	t_dlist			*ands;
	t_dlist			*pipe;
	t_dlist			*ands_ors;
	enum e_logop	log;
	t_builtings		builting;
	int				in_out[2];
}				t_cmd;

typedef struct s_minishell
{
	int		argc;
	char	**argv;
	char	**envp;
	int		pid_fg;
	char	*line;
	int		*ret;
	char	buff[4097];
	int		buff_idx;
	int		envp_fd;
}				t_global;

typedef struct s_stack
{
	int	arr[MAX_SIZE];
	int	head;
	int	tail;
	int	size;
}				t_stack;

/** tools ***/
char		*ft_which(char	*cmd, t_builtings *builting);
void		ft_free_split(char ***split);
void		ft_free_args(char ***split, int n);
t_cmd		*ft_new_cmd(void);
t_io_red	*ft_new_io_red(void);
char		**ft_split_args(char *line);
int			ft_arg_count(char *line);
void		ft_get_redout(t_io_red *red, char **args);
void		ft_get_redin(t_io_red *red, char **args);
void		ft_get_redctn(t_io_red *red, char **args);
t_cmd		*ft_fill_cmd(char *line, char **argv, char **envp);
t_dlist		*ft_get_cmd_list(char *line, char **argv, char **envp);
char		*ft_get_next_dollar(char *str);
char		*ft_expand_dollar(char *arg);
char		*ft_get_last_exit_status(void *args);
char		**ft_expand_args(char **args);
t_dlist		*ft_get_pipes_list(char *line, char **argv, char **envp);
char		*ft_next_logical_op(char *line);
t_dlist		*ft_get_ands_list(char *line, char **argv, char **envp);
t_dlist		*ft_get_ors_list(char *line, char **argv, char **envp);
t_dlist		*ft_get_ands_ors_list(char *line, char **argv, char **envp);
char		*ft_next_or(char *line);
char		*ft_next_and(char *line);
char		*ft_next_pipe(char *line);
int			ft_match_astrix(char *pattern, char *str);
t_dlist		*ft_get_astrix_matches(char *line);
void		ft_expand_args_astrix(char ***args);
void		ft_fill_in_redirection(t_io_red *red, char *line);
void		ft_fill_out_redirection(t_io_red *red, char *line);
void		execute_cmd_list(t_dlist *cmds);
void		ft_trim_args(char **args);
char		*ft_get_shell_line(void);
void		ft_get_envp(void);
void		ft_set_envp(void);
char		*ft_getenv(char *key);
int			ft_dellenv(char *key);
void		ft_setenv(char *key, char *val);
int			ft_updatenv(char *key, char *val);

/** lexer **/
int			ft_check_parnth(char *line, int *pos);
int			ft_check_quts(char *line, int *pos);
void		ft_check_cmd_line(char *line, int *err, int *pos);
int			ft_check_anomal_0(char *line, int *pos);
int			ft_check_anomal_1(char *line, int *pos);
int			ft_check_anomal_2(char *line, int *pos);
char		*ft_get_cmd_line(int fd);
void		ft_routine_1(char **line, int fd);
void		*ft_routine_2(char **line, int fd, char *msg);
void		ft_reset_input_buff(void);

/** execution **/
int			ft_execute_cmd(t_cmd *cmd, int *ret);
void		ft_redirect(t_cmd *cmd);
void		ft_execute_builting(t_cmd *cmd);
void		ft_execute_simple_cmd(t_cmd *cmd);
void		ft_create_pipes(t_cmd *cmd, int pipes[][2]);
void		ft_close_pipes(int pipesfds[][2]);
void		ft_proc0(t_cmd *cmd, int pipefds[][2]);
void		ft_proci(t_cmd *cmd, int pipefds[][2], int i);
int			ft_procn(t_cmd *cmd, int pipefds[][2], int n);
void		ft_pipe_cmd(t_cmd *cmd);
int			ft_execute_defined_cmd(t_cmd *cmd, int *ret);
int			ft_execute_cmd(t_cmd *cmd, int *ret);

/** helpers **/
void		ft_exit(char *msg, int err);
int			ft_max(int a, int b);
int			ft_min(int a, int b);
int			ft_abs(int a);
char		*ft_valid_red(char *arg);
int			ft_isspace(int c);
int			ft_qts_helper(char c, int *qts);

/** stack ***/
t_stack		ft_newstack(void);
void		ft_push(t_stack *s, int elm);
int			ft_pop(t_stack *s);
int			ft_isempty(t_stack *s);
int			ft_find(t_stack *s, int elm);
int			ft_isfull(t_stack *s);
void		ft_pushbottom(t_stack *s, int elm);
int			ft_popbottom(t_stack *s);
int			ft_getindex(t_stack a, int index);

/** builtings **/
void		ft_pwd(void);
int			ft_env(void);
int			ft_cd(t_cmd *cmd);
void		ft_unset(t_cmd *cmd);
int			ft_echo(t_cmd *cmd);
void		ft_export(t_cmd *cmd);
void		ft_subshell(t_cmd *cmd);

/** builting utils **/
int			print_error(void);
char		**ft_lst_get_array(t_list *lst);
void		*memory_error(size_t size);
t_list		*ft_lstpop_find(t_list **lst, char *key);
int			ft_keylen(char *keyval);
void		remove_elem_from_envp(t_list **env, char *key, char **env_line);
int			ft_split_len(char **arr);
char		**insert_or_update_elem_from_envp(t_global *g_msh, \
			t_list **env, char *keyval, char **env_line);

/** create/free ***/
t_io_red	*ft_new_io_red(void);
t_cmd		*ft_new_cmd(void);
void		ft_free_io_red(t_io_red **red);
void		ft_free_cmd(t_cmd **cmd);
char		**ft_vectdup(char **vect);
void		ft_free_cmd_list(t_dlist **cmds);

/** prints ***/
void		ft_print_splt(char	**spt, int fd);
void		ft_print_io_red(t_io_red *red, int fd);
void		ft_print_cmd(t_cmd *cmd, int fd);
void		ft_print_cmd_list(t_dlist *cmds, int fd);
void		ft_printline(char *line, int n, int fd);

/** tests  ***/
int			ft_arg_count_2(char *line);
char		**ft_split_args_2(char *line);

#endif

//\e[H\e[2J\e[3J;