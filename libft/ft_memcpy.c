/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:44:43 by amedenec          #+#    #+#             */
/*   Updated: 2024/11/06 18:44:43 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	unsigned char		*back;

	s = src;
	d = dest;
	back = dest;
	if (!dest && !src)
		return ((void *)back);
	while (n--)
		*d++ = *s++;
	return ((void *)back);
}

/*int	main(void)
{
	#include <stdio.h>
	unsigned char	buffer[150];
	const unsigned char	fugger[] = "aaaaaaaaaaaaaaaa";

	ft_memcpy(buffer, fugger, 13);
	int	i = 0;
	while (i < 20)
		printf("%d", buffer[i++]);
	return (0);
}*/
