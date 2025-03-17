/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:18:32 by amedenec          #+#    #+#             */
/*   Updated: 2024/11/06 18:18:32 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t count)
{
	unsigned char	*s;

	s = ptr;
	while (count--)
		*s++ = value;
	return (ptr);
}

/*int	main(void)
{
#include <stdio.h>
	char buffer[150];
	int	i = 0;

	ft_memset(buffer, 1, 127);
	while (i < 150)
	{
		printf("%d", buffer[i]);
		i++;
	}
	return (0);
}*/
