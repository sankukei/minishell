/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 00:08:11 by amedenec          #+#    #+#             */
/*   Updated: 2024/11/07 00:08:11 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	c;

	i = 0;
	j = 0;
	c = 0;
	if (*s2 == '\0')
		return ((char *)s1);
	while (s1[i] && i < len)
	{
		j = 0;
		c = i;
		while (s1[c] == s2[j] && c < len)
		{
			c++;
			j++;
			if (s2[j] == '\0')
				return ((char *)&s1[i]);
		}
		i++;
	}
	return (NULL);
}

/*int	main(void)
{
#include <string.h>
	#include <stdio.h>

	char	s1[] = "les";
	char	s2[] = "salut les gens";
	printf("%s\n", ft_strnstr(s2, s1, 12));
	return (0);
}*/
