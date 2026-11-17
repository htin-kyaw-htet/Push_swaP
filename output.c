/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htkyaw <htkyaw@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 15:25:00 by htkyaw            #+#    #+#             */
/*   Updated: 2026/11/16 15:26:49 by htkyaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}

void	fill_names(char **n)
{
	n[0] = "sa";
	n[1] = "sb";
	n[2] = "ss";
	n[3] = "pa";
	n[4] = "pb";
	n[5] = "ra";
	n[6] = "rb";
	n[7] = "rr";
	n[8] = "rra";
	n[9] = "rrb";
	n[10] = "rrr";
}

void	init_stats(t_stats *s)
{
	int	i;

	i = 0;
	while (i < 11)
	{
		s->count[i] = 0;
		i++;
	}
	s->total = 0;
	s->count_only = 0;
}

void	print_total_count(int n)
{
	char	c;

	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		print_total_count(n / 10);
	c = '0' + (n % 10);
	write(1, &c, 1);
}

void	print_op(t_stats *s, int id)
{
	char	*names[11];

	fill_names(names);
	s->count[id]++;
	s->total++;
	if (s->count_only)
		return ;
	ft_putstr_fd(names[id], 1);
	ft_putstr_fd("\n", 1);
}
