/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:50:53 by zpiarova          #+#    #+#             */
/*   Updated: 2024/10/01 18:14:40 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	find_cheapest_operation(t_stack *a, t_stack *b)
{
	t_operation	*op;
	t_operation	*cop;
	t_node		*temp;
	t_node		*friend;

	// op = malloc(sizeof(t_operation));
	// cop = malloc(sizeof(t_operation));
	// if (!op || !cop)
	// 	return ;
	temp = a->head;
	a->cheapest_o->count = a->size + b->size;
	while (temp)
	{
		if (temp->value > b->max->value || temp->value < b->min->value)
			friend = b->max;
		else
			friend = find_predecessor(temp, b);
		op = set_op(temp->i, friend->i, (a->size - temp->i), (b->size - friend->i));
		cop = set_op(op->ra, op->rb, op->rra, op->rrb);
		set_insides(op, cop, a);
		temp = temp->next;
	}
	free(op);
	free(cop);
}

// compares all 7 options that operations can take, selects and sets cheapest o
// first checks for best case scenario if ra and rb are on top thus equal to 0
// then compares if opposite operations ra+rrb or rb+rra do not take
// less operations than combination ra+rb+rr
// then checks if combination ra+rb+rr are new cheapest
// then checks if combinations rra+rrb+rrr are the new cheapest
void	set_insides(t_operation *op, t_operation *cop, t_stack *a)
{
	if (op->ra == 0 && op->rb == 0)
	{
		a->cheapest_o = set_op(0, 0, 0, 0);
		return ;
	}
	op->rrcount = calculate_rr(op);
	op->rrrcount = calculate_rrr(op);
	if (((cop->ra + cop->rrb) < op->rrcount) && ((cop->ra + cop->rrb) < op->rrrcount) && ((cop->ra + cop->rrb) < a->cheapest_o->count))
		a->cheapest_o = set_op(cop->ra, 0, 0, cop->rrb);
	else if (((cop->rb + cop->rra) < op->rrcount) && ((cop->rb + cop->rra) < op->rrrcount) && ((cop->rb + cop->rra) < a->cheapest_o->count))
		a->cheapest_o = set_op(0, cop->rb, cop->rra, 0);
	else if (op->rrcount < op->rrrcount && op->rrcount < a->cheapest_o->count)
	{
		a->cheapest_o = set_op(op->ra, op->rb, 0, 0);
		a->cheapest_o->rr = op->rr;
		a->cheapest_o->count += op->rr;
	}
	else if (op->rrrcount < op->rrcount && op->rrrcount < a->cheapest_o->count)
	{
		a->cheapest_o = set_op(0, 0, op->rra, op->rrb);
		a->cheapest_o->rrr = op->rrr;
		a->cheapest_o->count += op->rrr;
	}
}

// B is filled in descending order, always the cheapest element is taken to top and pushed to b
// if added element is new min/max, we put it above the biggest number in b
// for other elements, we add it above its predecessor - closest smaller element
void	fill_b(t_stack *a, t_stack *b)
{
	pb(a, b);
	pb(a, b);
	while (a->size > 3)
	{
		find_cheapest_operation(a, b);
		perform_operation(a, b);
		free(a->cheapest_o);
		pb(a, b);
	}
}

// when this function starts, a has 3 already sorted elements
// b has multiple sorted descending blocks, that may not be in order
// a. if (a->min->i - a->first->i < (a->size) / 2)
// find if first is not min or last is not max we have to traverse stack once more until it is
// if distance a->first and a->min is smaller than half of a size ra, else rra
void	back_to_a(t_stack *a, t_stack *b)
{
	t_node	*successor;

	while (b->head)
	{
		successor = find_successor(b->head, a);
		if (successor && a->head->value != b->head->value + 1)
			do_r_or_rr(successor, a);
		pa(a, b);
	}
	if (a->min->i - a->first->i <= (a->size) / 2)
	{
		while (a->first != a->min)
			ra(a);
	}
	else
	{
		while (a->last != a->max)
			rra(a);
	}
}

// performs actions based on how many elements it should sort
void	algorithm(t_stack *a, t_stack *b)
{
	if (is_sorted(a))
		return ;
	if (a->size == 2)
		ra(a);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size == 4)
	{
		pb(a, b);
		sort_three(a);
	}
	else if (a->size == 5)
	{
		pb(a, b);
		pb(a, b);
		sort_three(a);
	}
	else
	{
		fill_b(a, b);
		sort_three(a);
	}
	back_to_a(a, b);
}
