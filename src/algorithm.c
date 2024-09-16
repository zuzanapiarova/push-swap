/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:21:30 by zpiarova          #+#    #+#             */
/*   Updated: 2024/09/16 18:21:40 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

//check with 2 1 3 6 5 8:
/*
	sa(a);
	pb(a, b);
	pb(a, b);
	pb(a, b);
	ra(a);
	rb(b);
	rra(a);
	rrb(b);
	sa(a);
	pa(a, b);
	pa(a, b);
	pa(a, b);
*/

void sort_two(t_stack *s)
{
	if (is_sorted(s))
		return ;
	if (s->size == 2)
		ra(s);
}

void sort_three(t_stack *s)
{
	int	first;
	int	second;
	int	third;

	if (is_sorted(s))
		return ;
	first = s->head->value;
	second = s->head->next->value;
	third = s->head->next->next->value;
	if (first < second && second > third && first < third)
	{
		rra(s);
		sa(s);
	}
	else if (first < second && second > third && first > third)
		rra(s);
	else if (first > second && second < third && first > third)
		ra(s);
	else if (first > second && second < third && first < third)
		sa(s);
	else if (first > second && second > third && first > third)
	{
		sa(s);
		rra(s);
	}
}

// TODO
// when this function starts, a is already sorted
// b is sorted descending
void back_to_a(t_stack *a, t_stack *b)
{
	// // put everything from top to bottom until finding element one bigger than top of b
	// while (a->first->next > b->first)
	// {
	// 	printf("rotating top of a to end");
	// 	ra(a);
	// }
	// // pb so now list is sorted from end
	// if (b->first < a->first)
	// {
	// 	printf("pa");
	// 	pa(a, b);
	// }
	// // then take from end to top of a
	// while (a->first > b->first)
	// {
	// 	printf("rra from end to top");
	// 	rra(a);
	// }
	// if (b->first < a->first)
	// {
	// 	printf("pa");
	// 	pa(a, b);
	// }
	// print_stack(a);
	while(b->size > 0)
		pa(a, b);
}

// B is always filled in max 2 separate partitions, both sorted in descending order
// we are adding elements form one to other partition to land in the correct spot to place pa node to correct position
void fill_b(t_stack *a, t_stack *b)
{
	pb(a, b);
	pb(a, b);
	while (a->size > 3)
	{
		// if new value will be the new max/min:
		// get the biggest value to top as the new max/min must be placed on top of current max
		if(a->first->value > b->max->value || a->first->value < b->min->value) // this condition works great
		{
			int operation = select_r_or_rr(b->max, b);
			while (b->first != b->max)
			{
				if (operation == 1)
					rb(b);
				else
					rrb(b);
			}
			pb(a, b);
		}
		// else if it is other element and will not be new max/min of the stack
		//  place it to its correct position by removing all other elements until its predecessor/succesor and pb to top
		else
		{
			t_node *neighbor = find_closest_neighbor(a->first, b);
			printf("val: %d, neighbor: %d\n", a->first->value, neighbor->value);
			// place neighbor to top of b and pb above it
			int operation = select_r_or_rr(neighbor, b);
			while (b->first != neighbor)
			{
				if (operation == 1)
					rb(b);
				else
					rrb(b);
			}
			// if its smallest neighbor is th efirst on the list, just pb
			if (find_smaller_neighbor() == b->head)
				pb(a, b);
			// but if neighbor is bigger, we pb above it and then we also swap them
			if (neighbor->value > a->first->value)
			{
				rb(b);
				pb(a, b);
				rrb(b);
			}
			// if neighbor is smaller, just pb above it
			pb(a, b);
			// // place_correct(a, b); // TODO - it will place the pb node to correct place which is right below its upper neighbor
			// while (b->first->value < a->first->value) // !!!! this condition has to be changed, find algo to place el to correct spot - meaning next to its closest upper/lower neighbor
			// 	rb(b);
			// pb(a, b);
		}
	}
}

// then implement index_from_top and index_from_bottom and depending on which is bigger, either ra, ra, ra (top) or rra, rra, rra(bottom)
// or we have to find which element is closest in value from bottom or from top and then place it above/below the closer one

void	algorithm(t_stack *a, t_stack *b)
{
	if (is_sorted(a))
	{
		ft_putstr_fd("A sorted, B empty. Finished.\n", 1);
		return ;
	}
	if (a->size == 2) // we know this case is not sorted because before we checked if the list is sorted
		sort_two(a);
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
