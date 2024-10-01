/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:50:53 by zpiarova          #+#    #+#             */
/*   Updated: 2024/10/01 20:05:18 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	find_cheapest_operation(t_stack *a, t_stack *b)
{
	t_operation	*c_o;
	t_operation	*c_o_copy;
	t_node		*temp;
	t_node		*friend;

	c_o = malloc(sizeof(t_operation));
	c_o_copy = malloc(sizeof(t_operation));
	if (!c_o || !c_o_copy)
		return ;
	temp = a->head;
	while (temp)
	{
		if (temp->value > b->max->value || temp->value < b->min->value)
			friend = b->max;
		else
			friend = find_predecessor(temp, b);
		set_rr(c_o, temp->i, friend->i, 0);
		set_rrr(c_o, (a->size - temp->i), (b->size - friend->i), 0);
		set_rr(c_o_copy, c_o->ra, c_o->rb, 0);
		set_rrr(c_o_copy, c_o->rra, c_o->rrb, 0);
		set_insides(c_o, c_o_copy, a);
		temp = temp->next;
	}
	free(c_o);
	free(c_o_copy);
}

// compares all 7 options the operations can take and selects and sets the cheapest one
// first checks for best case scenario if ra and rb are on top thus equal to 0
// then compare if opposite operations ra+rrb or rb+rra do not take less operations than combination ra+rb+rr
// then checks if combination ra+rb+rr are new cheapest
// then checks if combinations rra+rrb+rrr are the new cheapest
void set_insides(t_operation *c_o, t_operation *c_o_copy, t_stack *a)
{
	if (c_o->ra == 0 && c_o->rb == 0)
	{
		a->cheapest_o->count = set_rr(a->cheapest_o, 0, 0, 0) + set_rrr(a->cheapest_o, 0, 0, 0);
		return ;
	}
	c_o->rrcount = calculate_rr(c_o);
	c_o->rrrcount = calculate_rrr(c_o);
	if (((c_o_copy->ra + c_o_copy->rrb) < c_o->rrcount) && ((c_o_copy->ra + c_o_copy->rrb) < c_o->rrrcount) && ((c_o_copy->ra + c_o_copy->rrb) < a->cheapest_o->count))
		a->cheapest_o->count = set_rr(a->cheapest_o, c_o_copy->ra, 0, 0) + set_rrr(a->cheapest_o, 0, c_o_copy->rrb, 0);
	else if (((c_o_copy->rb + c_o_copy->rra) < c_o->rrcount) && ((c_o_copy->rb + c_o_copy->rra) < c_o->rrrcount) && ((c_o_copy->rb + c_o_copy->rra) < a->cheapest_o->count))
		a->cheapest_o->count = set_rr(a->cheapest_o, 0, c_o_copy->rb, 0) + set_rrr(a->cheapest_o, c_o_copy->rra, 0, 0);
	else if (c_o->rrcount < c_o->rrrcount && c_o->rrcount < a->cheapest_o->count)
		a->cheapest_o->count = set_rr(a->cheapest_o, c_o->ra, c_o->rb, c_o->rr) + set_rrr(a->cheapest_o, 0, 0, 0);
	else if (c_o->rrrcount < c_o->rrcount && c_o->rrrcount < a->cheapest_o->count)
		a->cheapest_o->count = set_rr(a->cheapest_o, 0, 0, 0) + set_rrr(a->cheapest_o, c_o->rra, c_o->rrb, c_o->rrr);
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
		a->cheapest_o = malloc(sizeof(t_operation));
		a->cheapest_o->count = 500;
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
void	back_to_a(t_stack * a, t_stack *b)
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
