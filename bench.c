/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htkyaw <htkyaw@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 15:19:57 by htkyaw            #+#    #+#             */
/*   Updated: 2026/11/16 15:19:58 by htkyaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	put_nbr(int n)
{
	char	c;

	if (n >= 10)
		put_nbr(n / 10);
	c = '0' + n % 10;
	write(2, &c, 1);
}

static void	put_disorder(double d)
{
	int	h;

	h = (int)(d * 10000 + 0.5);
	ft_putstr_fd("[bench] disorder: ", 2);
	put_nbr(h / 100);
	ft_putstr_fd(".", 2);
	if (h % 100 < 10)
		ft_putstr_fd("0", 2);
	put_nbr(h % 100);
	ft_putstr_fd("%\n", 2);
}

static void	put_strategy(t_config *cfg)
{
	ft_putstr_fd("[bench] strategy: ", 2);
	if (cfg->strategy == ADAPTIVE)
		ft_putstr_fd("Adaptive / ", 2);
	else if (cfg->strategy == SIMPLE)
		ft_putstr_fd("Simple / ", 2);
	else if (cfg->strategy == MEDIUM)
		ft_putstr_fd("Medium / ", 2);
	else
		ft_putstr_fd("Complex / ", 2);
	if (cfg->used == SIMPLE)
		ft_putstr_fd("O(n²)\n", 2);
	else if (cfg->used == MEDIUM)
		ft_putstr_fd("O(n√n)\n", 2);
	else
		ft_putstr_fd("O(n log n)\n", 2);
}

static void	put_counts(t_stats *s, int from, int to)
{
	char	*names[11];

	fill_names(names);
	ft_putstr_fd("[bench]", 2);
	while (from < to)
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(names[from], 2);
		ft_putstr_fd(": ", 2);
		put_nbr(s->count[from]);
		from++;
	}
	ft_putstr_fd("\n", 2);
}

void	print_bench(t_config *cfg, t_stats *s)
{
	put_disorder(cfg->disorder);
	put_strategy(cfg);
	ft_putstr_fd("[bench] total_ops: ", 2);
	put_nbr(s->total);
	ft_putstr_fd("\n", 2);
	put_counts(s, 0, 5);
	put_counts(s, 5, 11);
}
