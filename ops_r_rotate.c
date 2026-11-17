/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_r_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htkyaw <htkyaw@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 13:43:47 by htkyaw            #+#    #+#             */
/*   Updated: 2026/11/16 13:43:47 by htkyaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_stack **a, t_stats *s)
{
	rotate_down(a);
	print_op(s, RRA);
}

void	rrb(t_stack **b, t_stats *s)
{
	rotate_down(b);
	print_op(s, RRB);
}

void	rrr(t_stack **a, t_stack **b, t_stats *s)
{
	rotate_down(a);
	rotate_down(b);
	print_op(s, RRR);
}
