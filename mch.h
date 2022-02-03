/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mch.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 19:17:20 by mehill            #+#    #+#             */
/*   Updated: 2021/12/05 20:03:21 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MCH_H
# define MCH_H

# include <stdlib.h>
# include <stdio.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
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

/** defenition ***/
# define SHELL_NAME "minishell> "
# define MAX_SIZE 1500
# define ACC 1
# define DEC 2
# define MAX_PIPE 128

/** typedefs **/

typedef struct s_io_red
{
	int		fdin;
	int		fdout;
	int		fderr;
	char	*limiter;
	int		append;
}			t_io_red;

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
	int				log;
	int				in_out[2];
}				t_cmd;

typedef enum e_builtings
{
	FT_ECHO,
	FT_CD,
	FT_EXPORT,
	FT_UNSET,
	FT_ENV,
	FT_EXIT,
	FT_SUBSHELL
}			t_builtings;

typedef struct s_stack
{
	int	arr[MAX_SIZE];
	int	head;
	int	tail;
	int	size;
}				t_stack;

/** tools ***/
char		*ft_which(char	*cmd, char **envp);
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

/** execution **/
int			ft_execute_cmd(t_cmd *cmd);

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