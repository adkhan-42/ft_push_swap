/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:35:45 by adkhan            #+#    #+#             */
/*   Updated: 2026/02/18 19:35:46 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	push_swap(t_stack **a, t_stack **b)
{
	int	size;

	size = get_stack_size(*a);
	if (size == 2)
		sa(a);
	else if (size == 3)
		sort_three(a);
	else
		sort(a, b);
}

int	main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;

	a = NULL;
	b = NULL;
	if (ac < 2 || (ac == 2 && !av[1][0]))
		return (0);
	init_stack_a(&a, ac, av);
	if (!is_sorted(a))
		push_swap(&a, &b);
	free_stack(&a);
	return (0);
}
