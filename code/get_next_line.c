/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:58:05 by aartiges          #+#    #+#             */
/*   Updated: 2021/11/10 20:03:25 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	in_array(char *buf, char to_find, ssize_t len)
{
	ssize_t	i;

	i = 0;
	while (i < len)
	{
		if (buf[i] == to_find)
			return (i);
		++i;
	}
	return (-1);
}

static char	*get_line(char *buff)
{
	size_t	i;
	size_t	pos[2];
	char	*ret;

	i = 0;
	while (i < BUFFER_SIZE + 1 && buff[i] == 0)
		++i;
	pos[0] = i;
	while (i < BUFFER_SIZE + 1 && buff[i] != '\n' && buff[i] != 0)
		++i;
	pos[1] = i + 1;
	if (pos[1] > BUFFER_SIZE + 1)
		return (NULL);
	ret = malloc((pos[1] - pos[0] + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = pos[0];
	while (i < pos[1])
	{
		ret[i - pos[0]] = buff[i];
		buff[i] = 0;
		++i;
	}
	ret[i - pos[0]] = '\0';
	return (ret);
}

static size_t	str_len(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*str_cat_lines(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	char	*ret;

	len_s1 = str_len(s1);
	len_s2 = str_len(s2);
	ret = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len_s1)
	{
		ret[i] = s1[i];
		++i;
	}
	while (i < len_s1 + len_s2)
	{
		ret[i] = s2[i - len_s1];
		++i;
	}
	ret[i] = '\0';
	free(s1);
	free(s2);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;
	char		*tmp;
	ssize_t		len_buff;
	int			eol;

	if ((fd < 3 && fd != 0) || BUFFER_SIZE < 1)
		return (NULL);
	eol = in_array(buff, '\n', BUFFER_SIZE + 1);
	line = get_line(buff);
	if (line && eol != -1)
		return (line);
	len_buff = read(fd, buff, BUFFER_SIZE);
	if (len_buff == 0)
		return (line);
	while (len_buff > 0)
	{
		eol = in_array(buff, '\n', len_buff + 1);
		tmp = get_line(buff);
		line = str_cat_lines(line, tmp);
		if (eol != -1)
			return (line);
		len_buff = read(fd, buff, BUFFER_SIZE);
	}
	return (line);
}
