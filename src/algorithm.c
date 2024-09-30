/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:50:53 by zpiarova          #+#    #+#             */
/*   Updated: 2024/09/30 23:44:36 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

// 39 80 52 21 1 23 72 87 98 58 71 100 67 47 28 26 40 73 69 90 36 7 50 37 63 20 64 74 11 51 41 35 10 19 76 84 77 46 61 42 55 82 31 16 43 92 65 17 57 13 79 85 94 83 88 6 4 78 59 91 12 18 75 8 60 15 54 38 2 25 22 49 56 29 24 45 81 48 3 5 9 97 34 99 96 89 30 93 27 44 66 86 33 32 70 14 95 68 62 53
// o count 559
////////////////////////////////////////////////////////////////////

int calculate_rr(t_operation *op)
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

int    calculate_rrr(t_operation *op)
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

// set values of the operation struct passed as first parameter, values for operations ra, rb, rra, rrb are in parameters
// !! it sets rr and rrr to 0 !
int set_operation(t_operation *op, int ra, int rb, int rra, int rrb)
{
   op->ra = ra;
   op->rb = rb;
   op->rra = rra;
   op->rrb = rrb;
//    if (ra == 0 && rb == 0 && rra != 0 && rrb != 0)
//    {
//         op->rr = 0;
//         calculate_rrr(op);
//         return (op->rra + op->rrb + op->rrr);
//    }
//    else if (ra != 0 && rb != 0 && rra == 0 && rrb == 0)
//    {
//         op->rrr = 0;
//         calculate_rr(op);
//         return (op->ra + op->rb + op->rr);
//    }
//    else
//   {
        op->rr = 0;
        op->rrr = 0;
//   }
   return (op->ra + op->rb + op->rra + op->rrb);
}

////////////////////

// set_operation(a->c_o, temp->i, friend->i, (a->size - temp->i), (b->size - friend->i));
// --> this sets how many ra, rb, rra, rrb it takes to get element to top counted from its index
void	find_cheapest_operation(t_stack *a, t_stack *b)
{
    t_operation *c_o;
    t_operation *c_o_copy;
	t_node		*temp;
	t_node		*friend;

    c_o = malloc(sizeof(t_operation));
    c_o_copy = malloc(sizeof(t_operation));
    if (!c_o || !c_o_copy)
        return ;
    temp = a->head;
	a->cheapest_o->count = a->size + b->size;
	while (temp)
	{
		if (temp->value > b->max->value || temp->value < b->min->value)
			friend = b->max;
		else
			friend = find_predecessor(temp, b);
        set_operation(c_o, temp->i, friend->i, (a->size - temp->i), (b->size - friend->i));
        set_operation(c_o_copy, c_o->ra, c_o->rb, c_o->rra, c_o->rrb);
        set_insides(c_o, c_o_copy, a);
		temp = temp->next;
	}
    free(c_o);
    free(c_o_copy);
}





void set_insides(t_operation *c_o, t_operation *c_o_copy, t_stack *a)
{
        if (c_o->ra == 0 && c_o->rb == 0) // we know it is cheapest because it takes 0 operations to get the elements to top
		{
            a->cheapest_o->count = set_operation(a->cheapest_o, 0, 0, 0, 0);
			return ;
		}
        c_o->rrcount = calculate_rr(c_o);
        c_o->rrrcount = calculate_rrr(c_o);
		// first compare if combinations ra+rrb and rb+rra do not take less operations than the count
		if (((c_o_copy->ra + c_o_copy->rrb) < c_o->rrcount) && ((c_o_copy->ra + c_o_copy->rrb) < c_o->rrrcount) && ((c_o_copy->ra + c_o_copy->rrb) < a->cheapest_o->count))
            a->cheapest_o->count = set_operation(a->cheapest_o, c_o_copy->ra, 0, 0, c_o_copy->rrb);
		else if (((c_o_copy->rb + c_o_copy->rra) < c_o->rrcount) && ((c_o_copy->rb + c_o_copy->rra) < c_o->rrrcount) && ((c_o_copy->rb + c_o_copy->rra) < a->cheapest_o->count))
            a->cheapest_o->count = set_operation(a->cheapest_o, 0, c_o_copy->rb, c_o_copy->rra, 0);
		else if (c_o->rrcount < c_o->rrrcount && c_o->rrcount < a->cheapest_o->count)
		{
            a->cheapest_o->count = set_operation(a->cheapest_o, c_o->ra, c_o->rb, 0, 0) + c_o->rr;
			a->cheapest_o->rr = c_o->rr;
			a->cheapest_o->rrr = 0;
		}
		else if (c_o->rrrcount < c_o->rrcount && c_o->rrrcount < a->cheapest_o->count)
		{
            a->cheapest_o->count = set_operation(a->cheapest_o, 0, 0, c_o->rra, c_o->rrb) + c_o->rrr;
			a->cheapest_o->rr = 0;
			a->cheapest_o->rrr = c_o->rrr;
		}
}

////////////////////////////////////////////

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

// B is filled in separate partitions, each sorted descending
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
		pb(a, b);
	}
}

// when this function starts, a has 3 already sorted elements
// b has multiple sorted descending blocks, that may not be in order
// a. if (a->min->i - a->first->i < (a->size) / 2)
// find if first is not min or last is not max we have to traverse stack once more until it is
// if distance a->first and a->min is smaller than half of a size ra, else rra
void back_to_a(t_stack * a, t_stack *b)
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












// C_O IS NOT A POINTER - THIS FUNCTION IS STABLE
/*void	find_least_operations(t_stack *a, t_stack *b)
{
	t_operation	d_o;
	t_node		*temp;
	t_node		*friend;
	t_operation c_o; // current operation - stores how many operations ra, rb, rra, rrb, rr, rrr it takes to get two corresponding elements to top of each stack

    temp = a->head;
	a->cheapest_o->count = a->size + b->size;
	while (temp)
	{
		if (temp->value > b->max->value || temp->value < b->min->value)
			friend = b->max;
		else
			friend = find_predecessor(temp, b);
		c_o.ra = temp->i;
		c_o.rb = friend->i;
		c_o.rra = a->size - temp->i;
		c_o.rrb = b->size - friend->i;
		d_o.ra = c_o.ra;
		d_o.rb = c_o.rb;
		d_o.rra = c_o.rra;
		d_o.rrb = c_o.rrb;
		if (c_o.ra == 0 && c_o.rb == 0)
		// we know it is cheapest because it takes 0 operations to get the elements to top
		{
			a->cheapest_o->ra = 0;
			a->cheapest_o->rb = 0;
			a->cheapest_o->rr = 0;
			a->cheapest_o->rra = 0;
			a->cheapest_o->rrb = 0;
			a->cheapest_o->rrr = 0;
			a->cheapest_o->count = 0;
			return ;
		}
		// try to get rr and set ra and rb accordingly
		if ((c_o.ra > 0 && c_o.rb == 0) || (c_o.rb == 0 && c_o.ra > 0))
			c_o.rr = 0;
		else
		{
			if (c_o.ra < c_o.rb)
			{
				c_o.rr = c_o.ra;
				c_o.ra = 0;
				c_o.rb = c_o.rb - c_o.rr;
			}
			else if (c_o.ra > c_o.rb)
			{
				c_o.rr = c_o.rb;
				c_o.rb = 0;
				c_o.ra = c_o.ra - c_o.rr;
			}
			else
			{
				c_o.rr = c_o.ra;
				c_o.ra = 0;
				c_o.rb = 0;
			}
		}
        //calculate_rr(c_o);
		// try to get rrr and set rra and rrb accordingly
		if ((c_o.rra > 0 && c_o.rrb == 0) || (c_o.rrb == 0 && c_o.rra > 0))
			c_o.rrr = 0;
		else if (c_o.rra > 0 && c_o.rrb > 0)
		{
			if (c_o.rra < c_o.rrb)
			{
				c_o.rrr = c_o.rra;
				c_o.rra = 0;
				c_o.rrb = c_o.rrb - c_o.rrr;
			}
			else if (c_o.rra > c_o.rrb)
			{
				c_o.rrr = c_o.rrb;
				c_o.rrb = 0;
				c_o.rra = c_o.rra - c_o.rrr;
			}
			else
			{
				c_o.rrr = c_o.rra;
				c_o.rra = 0;
				c_o.rrb = 0;
			}
		}
        calculate_rrr(c_o);
		c_o.rrcount = c_o.ra + c_o.rb + c_o.rr;
		c_o.rrrcount = c_o.rra + c_o.rrb + c_o.rrr;
        // SET THE FINAL OPERATION TO BE PERFORMED STRUCT
		// first compare if combinations ra+rrb and rb+rra do not take less operations than the count
		if (((d_o.ra + d_o.rrb) < c_o.rrcount) && ((d_o.ra + d_o.rrb) < c_o.rrrcount) && ((d_o.ra + d_o.rrb) < a->cheapest_o->count))
		{
			//set_operation(a, d_o.ra, 0, 0, d_o.rrb);
            a->cheapest_o->ra = d_o.ra;
			a->cheapest_o->rb = 0;
			a->cheapest_o->rr = 0;
			a->cheapest_o->rra = 0;
			a->cheapest_o->rrb = d_o.rrb;
			a->cheapest_o->rrr = 0;
			a->cheapest_o->count = d_o.ra + d_o.rrb;
		}
		else if (((d_o.rb + d_o.rra) < c_o.rrcount) && ((d_o.rb + d_o.rra) < c_o.rrrcount) && ((d_o.rb + d_o.rra) < a->cheapest_o->count))
		{
			a->cheapest_o->ra = 0;
			a->cheapest_o->rb = d_o.rb;
			a->cheapest_o->rr = 0;
			a->cheapest_o->rra = d_o.rra;
			a->cheapest_o->rrb = 0;
			a->cheapest_o->rrr = 0;
			//set_operation(a, 0, d_o.rb, d_o.rra, 0);
			a->cheapest_o->count = d_o.rb + d_o.rra;
		}
		// select which combination takes least operations
		else if (c_o.rrcount < c_o.rrrcount && c_o.rrcount < a->cheapest_o->count)
		{
			a->cheapest_o->ra = c_o.ra;
			a->cheapest_o->rb = c_o.rb;
			a->cheapest_o->rr = c_o.rr;
			a->cheapest_o->rra = 0;
			a->cheapest_o->rrb = 0;
			a->cheapest_o->rrr = 0;
			a->cheapest_o->count = c_o.rrcount;
		}
		else if (c_o.rrrcount < c_o.rrcount && c_o.rrrcount < a->cheapest_o->count)
		{
			a->cheapest_o->ra = 0;
			a->cheapest_o->rb = 0;
			a->cheapest_o->rr = 0;
			a->cheapest_o->rra = c_o.rra;
			a->cheapest_o->rrb = c_o.rrb;
			a->cheapest_o->rrr = c_o.rrr;
			a->cheapest_o->count = c_o.rrrcount;
		}
		// printf("el: %d, fr: %d, ra: %d, rb: %d, rr: %d, rra: %d, rrb: %d. rrr: %d\n", temp->value, friend->value, a->cheapest_o->ra, a->cheapest_o->rb, a->cheapest_o->rr, a->cheapest_o->rra, a->cheapest_o->rrb, a->cheapest_o->rrr);
		temp = temp->next;
	}
}
*/


/* *C_O IS A POINTER - stable, c_o is pointer element of a stack
void	find_least_operations(t_stack *a, t_stack *b)
{
	t_operation	d_o;
	t_node		*temp;
	t_node		*friend;

    temp = a->head;
	a->cheapest_o->count = a->size + b->size;
	while (temp)
	{
		if (temp->value > b->max->value || temp->value < b->min->value)
			friend = b->max;
		else
			friend = find_predecessor(temp, b);
		a->c_o->ra = temp->i;
		a->c_o->rb = friend->i;
		a->c_o->rra = a->size - temp->i;
		a->c_o->rrb = b->size - friend->i;
		d_o.ra = a->c_o->ra;
		d_o.rb = a->c_o->rb;
		d_o.rra = a->c_o->rra;
		d_o.rrb = a->c_o->rrb;
		if (a->c_o->ra == 0 && a->c_o->rb == 0) // we know it is cheapest because it takes 0 operations to get the elements to top
		{
			a->cheapest_o->ra = 0;
			a->cheapest_o->rb = 0;
			a->cheapest_o->rr = 0;
			a->cheapest_o->rra = 0;
			a->cheapest_o->rrb = 0;
			a->cheapest_o->rrr = 0;
			a->cheapest_o->count = 0;
			return ;
		}
        calculate_rr(a->c_o);
        calculate_rrr(a->c_o);
		a->c_o->rrcount = a->c_o->ra + a->c_o->rb + a->c_o->rr;
		a->c_o->rrrcount = a->c_o->rra + a->c_o->rrb + a->c_o->rrr;
		// first compare if combinations ra+rrb and rb+rra do not take less operations than the count
		if (((d_o.ra + d_o.rrb) < a->c_o->rrcount) && ((d_o.ra + d_o.rrb) < a->c_o->rrrcount) && ((d_o.ra + d_o.rrb) < a->cheapest_o->count))
		{
			//set_operation(a, d_o.ra, 0, 0, d_o.rrb);
            a->cheapest_o->ra = d_o.ra;
			a->cheapest_o->rb = 0;
			a->cheapest_o->rr = 0;
			a->cheapest_o->rra = 0;
			a->cheapest_o->rrb = d_o.rrb;
			a->cheapest_o->rrr = 0;
			a->cheapest_o->count = d_o.ra + d_o.rrb;
		}
		else if (((d_o.rb + d_o.rra) < a->c_o->rrcount) && ((d_o.rb + d_o.rra) < a->c_o->rrrcount) && ((d_o.rb + d_o.rra) < a->cheapest_o->count))
		{
			a->cheapest_o->ra = 0;
			a->cheapest_o->rb = d_o.rb;
			a->cheapest_o->rr = 0;
			a->cheapest_o->rra = d_o.rra;
			a->cheapest_o->rrb = 0;
			a->cheapest_o->rrr = 0;
			a->cheapest_o->count = d_o.rb + d_o.rra;
		}
		else if (a->c_o->rrcount < a->c_o->rrrcount && a->c_o->rrcount < a->cheapest_o->count)
		{
			a->cheapest_o->ra = a->c_o->ra;
			a->cheapest_o->rb = a->c_o->rb;
			a->cheapest_o->rr = a->c_o->rr;
			a->cheapest_o->rra = 0;
			a->cheapest_o->rrb = 0;
			a->cheapest_o->rrr = 0;
			a->cheapest_o->count = a->c_o->rrcount;
		}
		else if (a->c_o->rrrcount < a->c_o->rrcount && a->c_o->rrrcount < a->cheapest_o->count)
		{
			a->cheapest_o->ra = 0;
			a->cheapest_o->rb = 0;
			a->cheapest_o->rr = 0;
			a->cheapest_o->rra = a->c_o->rra;
			a->cheapest_o->rrb = a->c_o->rrb;
			a->cheapest_o->rrr = a->c_o->rrr;
			a->cheapest_o->count = a->c_o->rrrcount;
		}
		temp = temp->next;
	}
}
*/


// WORKS  -short, a->cheapest is pointer, c_o is pointer
/*
void	find_least_operations(t_stack *a, t_stack *b)
{
	t_operation	d_o;
	t_node		*temp;
	t_node		*friend;

    temp = a->head;
	a->cheapest_o->count = a->size + b->size;
	while (temp)
	{
		if (temp->value > b->max->value || temp->value < b->min->value)
			friend = b->max;
		else
			friend = find_predecessor(temp, b);
        set_operation(a->c_o, temp->i, friend->i, (a->size - temp->i), (b->size - friend->i));
		d_o.ra = a->c_o->ra;
		d_o.rb = a->c_o->rb;
		d_o.rra = a->c_o->rra;
		d_o.rrb = a->c_o->rrb;
		if (a->c_o->ra == 0 && a->c_o->rb == 0) // we know it is cheapest because it takes 0 operations to get the elements to top
		{
            set_operation(a->cheapest_o, 0, 0, 0, 0);
			a->cheapest_o->rr = 0;
			a->cheapest_o->rrr = 0;
			a->cheapest_o->count = 0;
			return ;
		}
        calculate_rr(a->c_o);
        calculate_rrr(a->c_o);
		a->c_o->rrcount = a->c_o->ra + a->c_o->rb + a->c_o->rr;
		a->c_o->rrrcount = a->c_o->rra + a->c_o->rrb + a->c_o->rrr;
		// first compare if combinations ra+rrb and rb+rra do not take less operations than the count
		if (((d_o.ra + d_o.rrb) < a->c_o->rrcount) && ((d_o.ra + d_o.rrb) < a->c_o->rrrcount) && ((d_o.ra + d_o.rrb) < a->cheapest_o->count))
		{
            set_operation(a->cheapest_o, d_o.ra, 0, 0, d_o.rrb);
			a->cheapest_o->rr = 0;
			a->cheapest_o->rrr = 0;
			a->cheapest_o->count = d_o.ra + d_o.rrb;
		}
		else if (((d_o.rb + d_o.rra) < a->c_o->rrcount) && ((d_o.rb + d_o.rra) < a->c_o->rrrcount) && ((d_o.rb + d_o.rra) < a->cheapest_o->count))
		{
            set_operation(a->cheapest_o, 0, d_o.rb, d_o.rra, 0);
			a->cheapest_o->rr = 0;
			a->cheapest_o->rrr = 0;
			a->cheapest_o->count = d_o.rb + d_o.rra;
		}
		else if (a->c_o->rrcount < a->c_o->rrrcount && a->c_o->rrcount < a->cheapest_o->count)
		{
            set_operation(a->cheapest_o, a->c_o->ra, a->c_o->rb, 0, 0);
			a->cheapest_o->rr = a->c_o->rr;
			a->cheapest_o->rrr = 0;
			a->cheapest_o->count = a->c_o->rrcount;
		}
		else if (a->c_o->rrrcount < a->c_o->rrcount && a->c_o->rrrcount < a->cheapest_o->count)
		{
            set_operation(a->cheapest_o, 0, 0, a->c_o->rra, a->c_o->rrb);
			a->cheapest_o->rr = 0;
			a->cheapest_o->rrr = a->c_o->rrr;
			a->cheapest_o->count = a->c_o->rrrcount;
		}
		temp = temp->next;
	}
}*/
