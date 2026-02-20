/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tiny.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:36:10 by adkhan            #+#    #+#             */
/*   Updated: 2026/02/18 19:36:11 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	sort(t_stack **a, t_stack **b)
{
	push_init(a, b);
	sort_three(a);
	while (*b)
	{
		init_nodes(*a, *b);
		do_move(a, b);
	}
	if (!is_sorted(*a))
		min_on_top(a);
}

void	sort_three(t_stack **a)
{
	t_stack	*head;
	int		rank_1;
	int		rank_2;
	int		rank_3;

	head = *a;
	if (!head || !head->next || !head->next->next)
		return ;
	rank_1 = head->index;
	rank_2 = head->next->index;
	rank_3 = head->next->next->index;
	if (rank_1 > rank_2 && rank_1 > rank_3)
		ra(a);
	else if (rank_2 > rank_1 && rank_2 > rank_3)
		rra(a);
	if ((*a)->index > (*a)->next->index)
		sa(a);
}
