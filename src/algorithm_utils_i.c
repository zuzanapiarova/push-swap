/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_utils_i.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:23:52 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/10/07 21:59:04 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	calculate_rr(t_operation *op)
{
	if ((op->ra > 0 && op->rb == 0) || (op->rb == 0 && op->ra > 0))
		op->rr = 0;
	else
	{
		if (op->ra < op->rb)
		{
			op->rr = op->ra;
			op->ra = 0;
			op->rb = op->rb - op->rr;
		}
		else if (op->ra > op->rb)
		{
			op->rr = op->rb;
			op->rb = 0;
			op->ra = op->ra - op->rr;
		}
		else
		{
			op->rr = op->ra;
			op->ra = 0;
			op->rb = 0;
		}
	}
	return (op->ra + op->rb + op->rr);
}

int	calculate_rrr(t_operation *op)
{
	if ((op->rra > 0 && op->rrb == 0) || (op->rrb == 0 && op->rra > 0))
		op->rrr = 0;
	else
	{
		if (op->rra < op->rrb)
		{
			op->rrr = op->rra;
			op->rra = 0;
			op->rrb = op->rrb - op->rrr;
		}
		else if (op->rra > op->rrb)
		{
			op->rrr = op->rrb;
			op->rrb = 0;
			op->rra = op->rra - op->rrr;
		}
		else
		{
			op->rrr = op->rra;
			op->rra = 0;
			op->rrb = 0;
		}
	}
	return (op->rra + op->rrb + op->rrr);
}

// set values of the operation passed as first parameter
// values for ra, rb, rr in parameters
// returns number of operations
int	set_rr(t_operation *op, int ra, int rb, int rr)
{
	op->ra = ra;
	op->rb = rb;
	op->rr = rr;
	return (op->ra + op->rb + op->rr);
}

// set values of the operation passed as first parameter
// values for rra, rrb, rrr in parameters
// returns number of operations
int	set_rrr(t_operation *op, int rra, int rrb, int rrr)
{
	op->rra = rra;
	op->rrb = rrb;
	op->rrr = rrr;
	return (op->rra + op->rrb + op->rrr);
}

// select cheapest element to get to top by ra/rra and performs that operation
void	do_r_or_rr(t_node *n, t_stack *s)
{
	int	operation;

	if (!s || !s->head || !n)
		return ;
	if (n->i < 0 || n->i >= s->size)
		return ;
	if (n->i <= s->size / 2)
		operation = 1;
	else
		operation = 2;
	while (s->first != n)
	{
		if (operation == 1)
		{
			ra(s);
		}
		else
		{
			rra(s);
		}
	}
}
