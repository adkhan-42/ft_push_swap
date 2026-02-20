/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:34:00 by adkhan            #+#    #+#             */
/*   Updated: 2026/02/18 19:34:11 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	exit_error(t_stack **a, char **str_nums)
{
	if (a)
		free_stack(a);
	if (str_nums)
		free_array(str_nums, arr_len(str_nums));
	write(2, "Error\n", 6);
	exit(1);
}
