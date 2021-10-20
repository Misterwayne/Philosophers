/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:01:31 by mwane             #+#    #+#             */
/*   Updated: 2019/10/18 11:36:27 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int		get_str_len(long nbr)
{
	int i;

	i = 0;
	if (nbr <= 0)
	{
		i++;
		nbr *= -1;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	long	nbr;
	char	*result;
	int		nega;
	int		i;
	int		j;

	nbr = n;
	j = -1;
	i = get_str_len(nbr);
	if (!(result = malloc(sizeof(char) * (i + 1))))
		return (0);
	if (nbr < 0)
	{
		nbr *= -1;
		result[0] = '-';
		j += 1;
	}
	result[i] = '\0';
	nega = i--;
	while (++j < nega && result[i] != '-')
	{
		result[i--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (result);
}
