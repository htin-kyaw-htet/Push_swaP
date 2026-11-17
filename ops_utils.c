/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htkyaw <htkyaw@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 13:43:36 by htkyaw            #+#    #+#             */
/*   Updated: 2026/11/16 13:43:37 by htkyaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_top(t_stack **s)
{
	t_stack	*first;
	t_stack	*second;

	if (!*s || !(*s)->next)
		return ;
	first = *s;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*s = second;
}

void	push_top(t_stack **src, t_stack **dst)
{
	t_stack	*node;

	if (!*src)
		return ;
	node = *src;
	*src = node->next;
	node->next = *dst;
	*dst = node;
}

void	rotate_up(t_stack **s)
{
	t_stack	*first;
	t_stack	*last;

	if (!*s || !(*s)->next)
		return ;
	first = *s;
	last = *s;
	while (last->next)
		last = last->next;
	*s = first->next;
	first->next = NULL;
	last->next = first;
}

void	rotate_down(t_stack **s)
{
	t_stack	*prev;
	t_stack	*last;

	if (!*s || !(*s)->next)
		return ;
	prev = NULL;
	last = *s;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = *s;
	*s = last;
}
