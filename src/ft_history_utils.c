/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:36:01 by mehill            #+#    #+#             */
/*   Updated: 2022/03/05 20:16:08 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

void	ft_creat_history(void)
{
	extern t_global	g_msh;

	g_msh.his_fd = open("/tmp/.__history__", O_CREAT | O_RDWR | O_TRUNC, 0775);
	if (g_msh.his_fd < 0)
		ft_exit("Error : couldn't create a history file !\n", 1);
	close (g_msh.his_fd);
}

void	ft_add_history_helper(char *line, int i)
{
	extern t_global	g_msh;
	char			*p;
	char			buff[8];
	int				j;

	g_msh.his_fd = open("/tmp/.__history__", O_RDWR | O_APPEND, 0775);
	if (g_msh.his_fd < 0)
		ft_exit("Error : couldnt open history file !\n", 1);
	p = ft_itoa(i);
	i = 5 - ft_strlen(p);
	j = 0;
	while (j < i)
		buff[j++] = ' ';
	while (j < 5)
	{
		buff[j] = p[j - i];
		j++;
	}
	buff[5] = ' ';
	buff[6] = ' ';
	buff[7] = 0;
	write(g_msh.his_fd, buff, 7);
	write(g_msh.his_fd, line, ft_strlen(line));
	close(g_msh.his_fd);
	free(p);
}

void	ft_add_history(char *line)
{
	extern t_global	g_msh;
	char			*p;
	int				i;

	if (line == NULL)
		return ;
	i = 1;
	g_msh.his_fd = open("/tmp/.__history__", O_RDONLY, 0775);
	if (g_msh.his_fd < 0)
	{
		perror("Error : ");
		exit(1);
	}
	p = get_next_line(g_msh.his_fd);
	while (p && i++)
	{
		free(p);
		p = get_next_line(g_msh.his_fd);
	}
	close(g_msh.his_fd);
	ft_add_history_helper(line, i);
}

void	ft_show_history(void)
{
	extern t_global	g_msh;
	char			*p;

	g_msh.his_fd = open("/tmp/.__history__", O_RDONLY, 0775);
	if (g_msh.his_fd < 0)
	{
		perror("Error : ");
		exit(1);
	}
	p = get_next_line(g_msh.his_fd);
	while (p)
	{
		ft_putstr_fd(p, STDOUT_FILENO);
		free(p);
		p = get_next_line(g_msh.his_fd);
	}
	close(g_msh.his_fd);
}
