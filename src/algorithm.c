/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:50:53 by zpiarova          #+#    #+#             */
/*   Updated: 2024/10/07 22:15:49 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	find_cheapest_operation(t_stack *a, t_stack *b)
{
	t_operation	*co;
	t_operation	*cop;
	t_node		*temp;
	t_node		*friend;

	co = malloc(sizeof(t_operation));
	cop = malloc(sizeof(t_operation));
	if (!co || !cop)
		return ;
	temp = a->head;
	while (temp)
	{
		if (temp->value > b->max->value || temp->value < b->min->value)
			friend = b->max;
		else
			friend = find_predecessor(temp, b);
		set_rr(co, temp->i, friend->i, 0);
		set_rrr(co, (a->size - temp->i), (b->size - friend->i), 0);
		set_rr(cop, co->ra, co->rb, 0);
		set_rrr(cop, co->rra, co->rrb, 0);
		set_insides(co, cop, a);
		temp = temp->next;
	}
	free(co);
	free(cop);
}

// compares all operation combinations and selects and sets cheapest one
// first checks for best case scenario if ra and rb are on top thus equal to 0
// then compare if opposite operations ra+rrb/rb+rra dont take less operations
// then checks if combination ra+rb+rr are new cheapest
// then checks if combinations rra+rrb+rrr are the new cheapest
void	set_insides(t_operation *co, t_operation *cop, t_stack *a)
{
	if (co->ra == 0 && co->rb == 0)
	{
		a->ch->count = set_rr(a->ch, 0, 0, 0) + set_rrr(a->ch, 0, 0, 0);
		return ;
	}
	co->rrcount = calculate_rr(co);
	co->rrrcount = calculate_rrr(co);
	if (((cop->ra + cop->rrb) < co->rrcount)
		&& ((cop->ra + cop->rrb) < co->rrrcount)
		&& ((cop->ra + cop->rrb) < a->ch->count))
		a->ch->count = set_rr(a->ch, cop->ra, 0, 0)
			+ set_rrr(a->ch, 0, cop->rrb, 0);
	else if (((cop->rb + cop->rra) < co->rrcount)
		&& ((cop->rb + cop->rra) < co->rrrcount)
		&& ((cop->rb + cop->rra) < a->ch->count))
		a->ch->count = set_rr(a->ch, 0, cop->rb, 0)
			+ set_rrr(a->ch, cop->rra, 0, 0);
	else if (co->rrcount < co->rrrcount && co->rrcount < a->ch->count)
		a->ch->count = set_rr(a->ch, co->ra, co->rb, co->rr)
			+ set_rrr(a->ch, 0, 0, 0);
	else if (co->rrrcount < co->rrcount && co->rrrcount < a->ch->count)
		a->ch->count = set_rr(a->ch, 0, 0, 0)
			+ set_rrr(a->ch, co->rra, co->rrb, co->rrr);
}

// B is filled descending, always finding cheapest element in each iteration
// cheapest element is always taken to top and pushed to b
// if added element is new min/max, we put it above the biggest number in b
// for other elements, we add it above its predecessor - closest smaller element
void	fill_b(t_stack *a, t_stack *b)
{
	pb(a, b);
	pb(a, b);
	while (a->size > 3)
	{
		a->ch = malloc(sizeof(t_operation));
		a->ch->count = 500;
		find_cheapest_operation(a, b);
		perform_operation(a, b);
		free(a->ch);
		pb(a, b);
	}
}

// when this function starts, a has 3 already sorted elements
// b has multiple sorted descending blocks, that may not be in order
// a. if (a->min->i - a->first->i < (a->size) / 2)
// if first is not min or last is not max we have to rotate stack until it is
// if distance a->first and a->min is smaller than half of a size ra, else rra
void	back_to_a(t_stack *a, t_stack *b)
{
	t_node	*successor;

	while (b->head)
	{
		successor = find_successor(b->head, a);
		if (successor && a->head->value != b->head->value + 1)
			do_r_or_rr(successor, a);
		if (!successor && a->min->i != 0)
			do_r_or_rr(a->min, a);
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

void	back_to_a(t_stack *a, t_stack *b)
{
	t_node	*successor;

	while (b->head)
	{
		successor = find_successor(b->head, a);
		if (successor && a->head->value != b->head->value + 1)
			do_r_or_rr(successor, a);
		if (!successor && a->min != a->first)
			do_r_or_rr(a->min, a);
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
