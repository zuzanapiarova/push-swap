/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:40:11 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/09/16 23:28:54 by zuzanapiaro      ###   ########.fr       */
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
   int first;
   int second;
   int third;

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
    // TODO NOW:
    // CANNOT DO PB-RRA   PB-RRA AS IT WILL ROTATE OUR STACK THE OTHER WAY
    //a. a is sorted block with no gaps - smaller than b block - we pb entire b block and then rra
    //b. a is sorted block with no gaps - bigger than b block - we just pb
    //c. a is sorted block, b is two blocks top smaller and bottom bigger than a - we just pb until we find element bigger than biggest a
    //d. a is sorted block, b is two blocks bottom smaller and top bigger than a - we pb until find element smaller than smallest a block node

    // we have to pb until our new a->first is not smaller than
   // // put everything from top to bottom until finding element one bigger than top of b
   // while (a->first->next > b->first)
   // {
   //  printf("rotating top of a to end");
   //  ra(a);
   // }
   // // pb so now list is sorted from end
   // if (b->first < a->first)
   // {
   //  printf("pa");
   //  pa(a, b);
   // }
   // // then take from end to top of a
   // while (a->first > b->first)
   // {
   //  printf("rra from end to top");
   //  rra(a);
   // }
   // if (b->first < a->first)
   // {
   //  printf("pa");
   //  pa(a, b);
   // }
   // print_stack(a);
   while(b->size > 0)
       pa(a, b);
}

// find the closestc predecessor to node n in stack s
t_node *find_predecessor(t_node *n, t_stack *s)
{
           // finding predecessor(closest smaller element) to our a head --> getting it to top --> then pb - so new element is on top of its predecessor
           t_node *temp = s->head;
           int delta;
           t_node *predecessor;

           // find first smaller value
           while (temp->value > n->value)
               temp = temp->next;
           if (temp->value < n->value)
           {
               delta = n->value - temp->value;
               predecessor = temp;
           }
           temp = temp->next;
           while (temp)
           {
               if (n->value - temp->value < delta && temp->value < n->value)
               {
                   predecessor = temp;
                   delta = n->value - temp->value;
               }
               temp = temp->next;
           }
           printf("el: %d, predecessor: %d\n", n->value, predecessor->value);
           return predecessor;
}

// B is always filled in max 2 separate partitions, both sorted in descending order
// we are adding elements form one to other partition to land in the correct spot to place pa node to correct position
void fill_b(t_stack *a, t_stack *b)
{
   pb(a, b);
   pb(a, b);
   while (a->size > 3)
   {
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
       //else place the element into its correct position by removing all other elements until its predecessor/successor and pb to top
       else
       {
           t_node *predecessor = find_predecessor(a->head, b);
           int operation = select_r_or_rr(predecessor, b);
           while (b->first != predecessor)
           {
               if (operation == 1)
                   rb(b);
               else
                   rrb(b);
           }
           pb(a, b);
       }
   }
}
// then implement index_from_top and index_from_bottom and depending on which is bigger, either ra, ra, ra (top) or rra, rra, rra(bottom)
// or we have to find which element is closest in value from bottom or from top and then place it above/below the closer one


void    algorithm(t_stack *a, t_stack *b)
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

