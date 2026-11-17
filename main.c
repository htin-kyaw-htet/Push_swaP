/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmyat <mmyat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 16:38:46 by mmyat             #+#    #+#             */
/*   Updated: 2026/11/17 07:18:32 by mmyat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	run(t_strategy st, t_stack **a, t_stack **b, t_stats *s)
{
	if (st == SIMPLE)
		selection_sort(a, b, s);
	else if (st == MEDIUM)
		medium_sort(a, b, s);
	else
		radix_sort(a, b, s);
}

static void	solve(t_config *cfg, t_stack **a, t_stack **b)
{
	t_stats	st;

	init_stats(&st);
	st.count_only = cfg->count_only;
	cfg->disorder = compute_disorder(*a);
	cfg->used = pick_strategy(cfg->strategy, cfg->disorder, stack_size(*a));
	run(cfg->used, a, b, &st);
	if (cfg->count_only)
		print_total_count(st.total);
	else if (cfg->bench && *a)
		print_bench(cfg, &st);
}

int	main(int ac, char **av)
{
	t_config	cfg;
	t_stack		*a;
	t_stack		*b;

	if (ac < 2)
		return (0);
	a = NULL;
	b = NULL;
	cfg.strategy = ADAPTIVE;
	cfg.bench = 0;
	cfg.count_only = 0;
	if (!load_stack(ac, av, &a, &cfg))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	solve(&cfg, &a, &b);
	free_stack(&a);
	free_stack(&b);
	return (0);
}
