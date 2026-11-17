/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htkyaw <htkyaw@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 13:42:08 by htkyaw            #+#    #+#             */
/*   Updated: 2026/11/16 13:42:08 by htkyaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_bit(t_stack **a, t_stack **b, t_stats *s, int bit)
{
	int	i;
	int	size;

	size = stack_size(*a);
	i = 0;
	while (i < size)
	{
		if ((((*a)->index >> bit) & 1) == 0)
			pb(a, b, s);
		else
			ra(a, s);
		i++;
	}
	while (*b)
		pa(a, b, s);
}

void	radix_sort(t_stack **a, t_stack **b, t_stats *s)
{
	int	size;
	int	max_bits;
	int	bit;

	size = stack_size(*a);
	if (size < 2 || is_sorted(*a))
		return ;
	assign_index(*a);
	max_bits = 0;
	while (((size - 1) >> max_bits) != 0)
		max_bits++;
	bit = 0;
	while (bit < max_bits)
	{
		sort_bit(a, b, s, bit);
		bit++;
	}
}
