/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:25:03 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/27 06:57:32 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	len(int size, char **str)
{
	int	i;
	int	y;
	int	res;

	i = 0;
	y = 0;
	res = 0;
	while (i < size)
	{
		while (str[i][y])
			y++;
		res += y;
		y = 0;
		i++;
	}
	return (res);
}

char	*ft_strcat(char *dest, char *src)
{
	char	*ptr;

	ptr = dest + ft_strlen(dest);
	while (*src)
		*ptr++ = *src++;
	return (dest);
}

char	*ft_join(int size, char **strs, char *sep)
{
	char	*res;
	int		i;
	int		flen;
	int		lsep;

	if (size == 0)
		return (0);
	lsep = (ft_strlen(sep) * size - 1);
	flen = len(size, strs) + lsep;
	i = 0;
	res = malloc((flen * sizeof(char)) + 2);
	if (!res)
		return (0);
	bzero(res, (flen * sizeof(char)) + 1);
	while (i < size)
	{
		if (ft_strlen(strs[i]) != 0)
			ft_strcat(res, strs[i]);
		if (i != size - 1 && ft_strlen(strs[i]) != 0)
			ft_strcat(res, sep);
		i++;
	}
	res[flen + 1] = 0;
	return (res);
}
