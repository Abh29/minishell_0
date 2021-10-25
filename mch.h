/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mch.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 19:17:20 by mehill            #+#    #+#             */
/*   Updated: 2021/10/25 19:41:35 by mehill           ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <fcntl.h>

/** defenition ***/
# define SHELL_NAME "minishell> "
# define MAX_SIZE 1500
# define ACC 1
# define DEC 2

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
}				t_cmd;

typedef enum e_builtings
{
	FT_ECHO,
	FT_CD,
	FT_PWD,
	FT_EXPORT,
	FT_UNSET,
	FT_ENV,
	FT_EXIT
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

/** helpers **/
void		ft_exit(char *msg, int err);
int			ft_max(int a, int b);
int			ft_min(int a, int b);
int			ft_abs(int a);

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

#endif

//\e[H\e[2J\e[3J;