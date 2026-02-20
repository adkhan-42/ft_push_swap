/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:15:40 by adkhan            #+#    #+#             */
/*   Updated: 2025/11/05 13:28:32 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_result(char *res, int n, int size)
{
	res[size] = '\0';
	while (n != 0)
	{
		size--;
		res[size] = (n % 10) + '0';
		n = n / 10;
	}
}

static int	get_len(int n)
{
	int	size;

	size = 0;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*res;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	sign = 0;
	if (n < 0)
	{
		n = -n;
		sign = 1;
	}
	size = get_len(n);
	if (sign == 1)
		size++;
	res = (char *)malloc((size + 1) * sizeof(char));
	if (!res)
		return (NULL);
	fill_result(res, n, size);
	if (sign == 1)
		res[0] = '-';
	return (res);
}
