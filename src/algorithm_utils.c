/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:23:52 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/10/01 15:25:05 by zuzanapiaro      ###   ########.fr       */
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

// after we set the cheapest operation for number from stack a, we perform all its actions
void	perform_operation(t_stack *a, t_stack *b)
{
	while (a->cheapest_o->ra-- > 0)
		ra(a);
	while (a->cheapest_o->rb-- > 0)
		rb(b);
	while (a->cheapest_o->rr-- > 0)
		rr(a, b);
	while (a->cheapest_o->rra-- > 0)
		rra(a);
	while (a->cheapest_o->rrb-- > 0)
		rrb(b);
	while (a->cheapest_o->rrr-- > 0)
		rrr(a, b);
}

// set values of the operation struct passed as first parameter, values for operations ra, rb, rra, rrb are in parameters
// sets rr and rrr to 0, so it must be changed afterwards if needed and added to operation count
int	set_operation(t_operation *op, int ra, int rb, int rra, int rrb)
{
	op->ra = ra;
	op->rb = rb;
	op->rra = rra;
	op->rrb = rrb;
	op->rr = 0;
	op->rrr = 0;
	return (op->ra + op->rb + op->rra + op->rrb);
}
