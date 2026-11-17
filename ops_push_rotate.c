/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_push_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htkyaw <htkyaw@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 13:43:44 by htkyaw            #+#    #+#             */
/*   Updated: 2026/11/16 13:43:44 by htkyaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_stack **a, t_stack **b, t_stats *s)
{
	push_top(b, a);
	print_op(s, PA);
}

void	pb(t_stack **a, t_stack **b, t_stats *s)
{
	push_top(a, b);
	print_op(s, PB);
}

void	ra(t_stack **a, t_stats *s)
{
	rotate_up(a);
	print_op(s, RA);
}

void	rb(t_stack **b, t_stats *s)
{
	rotate_up(b);
	print_op(s, RB);
}

void	rr(t_stack **a, t_stack **b, t_stats *s)
{
	rotate_up(a);
	rotate_up(b);
	print_op(s, RR);
}
