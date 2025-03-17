/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:37:16 by amedenec          #+#    #+#             */
/*   Updated: 2024/11/10 16:37:16 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	int		i;
	int		d;
	char	*dest;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dest = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	d = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
		d++;
	}
	i = -1;
	while (s2[++i])
		dest[i + d] = s2[i];
	dest[i + d] = '\0';
	return (dest);
}

/*int	main(void)
{
	#include <stdio.h>
	char	*s1;
	char	*s2;

	s1 = "Salut la team";
	s2 = " comment ca va";
	printf("%s", ft_strjoin(s1, s2));
	return (0);
}*/
