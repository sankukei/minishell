/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 05:11:51 by amedenec          #+#    #+#             */
/*   Updated: 2024/11/08 05:11:51 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t		y;
	size_t		str_len;
	char		*tmp;

	y = 0;
	str_len = ft_strlen(str);
	if (start >= str_len)
		len = 0;
	else if (len > str_len - start)
		len = str_len - start;
	tmp = malloc(len + 1);
	if (!tmp)
		return (NULL);
	while (y < len)
	{
		tmp[y] = str[start + y];
		y++;
	}
	tmp[y] = '\0';
	return (tmp);
}

/*int main()
{	
	char* test = ft_substr("salut la team", 6, 2);
	printf("%s", test);
	return (0);
}*/
