/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:25:22 by adkhan            #+#    #+#             */
/*   Updated: 2025/11/05 14:11:34 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_match;

	last_match = NULL;
	while (1)
	{
		if (*s == (char)c)
			last_match = (char *)s;
		if (*s == '\0')
			break ;
		s++;
	}
	return (last_match);
}
