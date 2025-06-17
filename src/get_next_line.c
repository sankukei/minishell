/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:30:14 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/17 18:30:15 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*res;
	int			count;
	static char	*buf;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	count = 1;
	if (!buf)
		buf = ft_calloc(1, 1);
	res = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buf || !res)
		return (NULL);
	while (count > 0)
	{
		count = read(fd, res, BUFFER_SIZE);
		if (count == 0 && !ft_strlen(buf))
			return (free(buf), buf = 0, ft_norminette(res, 0), NULL);
		res[count] = '\0';
		buf = ft_strjoin(buf, res);
		if (ft_check_buffer(buf))
			break ;
	}
	res = ft_fils(buf, res);
	buf = ft_purge(buf);
	return (res);
}

char	*ft_purge(char *str)
{
	int		i;
	int		y;
	char	*tmp;

	i = 0;
	y = 0;
	tmp = NULL;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		str = 0;
		return (NULL);
	}
	tmp = ft_calloc(ft_strlen(str) - i + 1, 1);
	if (!tmp)
		return (free(str), NULL);
	i++;
	while (str[i])
		tmp[y++] = str[i++];
	tmp[y] = 0;
	free(str);
	str = 0;
	return (tmp);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		y;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	y = 0;
	res = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!res)
		return (NULL);
	while (s1[i])
		res[y++] = s1[i++];
	i = 0;
	while (s2[i])
		res[y++] = s2[i++];
	res[y] = '\0';
	free(s1);
	s1 = 0;
	return (res);
}

int	ft_check_buffer(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_fils(char *str, char *r)
{
	int		i;
	int		y;
	char	*res;

	i = 0;
	y = 0;
	if (!str)
		return (free(r), NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	res = malloc(i + 1);
	if (!res)
		return (free(str), str = 0, NULL);
	while (str[y] && str[y] != '\n')
	{
		res[y] = str[y];
		y++;
	}
	if (str[i - 1] == '\n')
		res[y++] = '\n';
	res[y] = '\0';
	ft_norminette(r, 0);
	return (res);
}

int	main(void)
{
	#include <stdio.h>
	int	fd;
	char	*line;
	size_t	i;

	i = 0;
	fd = open("./test", O_RDONLY);
	while((line = get_next_line(fd)))
	{
		printf("line %02zu : %s", i++, line);
		free(line);
	}
	return (0);
}
