/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:40:14 by amedenec          #+#    #+#             */
/*   Updated: 2024/11/10 17:40:14 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	len_s;
	size_t	i;
	char	*dest;
	size_t	c;

	len_s = ft_strlen(s);
	i = 0;
	c = 0;
	while (s[i] && is_in_set(s[i], set))
	{
		i++;
		c++;
	}
	while (len_s > c && is_in_set(s[len_s - 1], set))
		len_s--;
	if (c > len_s)
		return (NULL);
	dest = malloc((len_s - c + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (c < len_s)
		dest[i++] = s[c++];
	dest[i] = '\0';
	return (dest);
}

/*int	main(void)
{
	#include <stdio.h>
	char	s[] = "   xx   xxx";
	char	set[] = " x";
	printf("%s", ft_strtrim(s, set));
	return (0);
}*/
