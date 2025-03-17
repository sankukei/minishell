/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:30:00 by amedenec          #+#    #+#             */
/*   Updated: 2024/11/06 19:30:00 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	s = src;
	d = dest;
	if (d == s || n == 0)
		return (dest);
	if (s > d)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
	return (dest);
}

/*int	main(void)
{
#include <stdio.h>
	char dest[] = "111111111111";
	char src[] = "55555000";
	int	i = 0;
	ft_memmove(dest, src, 5);
	while (i < 10)
		printf("%d", src[i++]);
	return (0);
}*/
