/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:02:52 by amedenec          #+#    #+#             */
/*   Updated: 2024/11/11 00:02:52 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*void	f(unsigned int i, char *s)
{
	*s += i;
}*/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
	s[i] = '\0';
}

/*int	main(void)
{
	#include <stdio.h>
	char	s[] = "0000000000";
	ft_striteri(s, f);
	printf("%s", s);
	return (0);
}*/
