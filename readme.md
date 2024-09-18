Push swap visualizer: https://github.com/o-reo/push_swap_visualizer
https://medium.com/@jamierobertdawson/push-swap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a
/* analyzing turksort algorithm: http://games.hazzens.com/blog/2014/02/27/turk_sort.html */

MECHANICAL TURK ALGORITHM: main idea is counting how much "work" sorting each element costs us

pick sorting algorithm in which all comparisons (and their number) we need to make are known ahead of time

strict weak ordering is a binary predicate that compares two objects, and returns true if the first argument precedes the second

strict weak ordering: A < B and B < C implies A < C -> this is how efficient sorting algorithms work

strict weak ordering: https://tanjim131.github.io/2020-05-22-strict-weak-ordering/

WHAT I WANT TO DO

1. store the arguments in a singly linked list
2. get all the info oh the stack that we can and keep it updated (and also on its nodes)
	- min
	- max
	- first
	- last
	- index each node and keep these indexes always updated
3. check if stack is already sorted (and check if b is empty (just to make sure we did not forget anything there))
4. implement solution for the short stacks - 2/3/4/5 elements
a. if stack is 2/3 arguments, sort in little operations without using stack b
b. if stack is 4, pb once, sort the stack A - DONE
c. if stack is 5, pb twice, sort the stack A - DONE / 5 must be under 12 actions
d. for bigger stacks: implement fill_b until we have only 3 elements left in a
# ALGORITHM I. - FILL_B - b is getting filled descending
	1. count how many instructions it would take to place the element in correct location - we store node with least steps in stack info as well (if multiple, store first one) - this is the Mechanical Turk approach
	- implement index for each node and then we can easily get if it is closer to bottom or the top by running node.index <=> stack.size / 2
	- now we can move to counting:
	- for ra and rra: we know if we are going to use ra or rra from previous step, now calculate how many elements are between our element and the end of the list, for ra how many elements between our element and the start of the list
	- if we can sa:
	2. pb the least-step node and place it to correct position
	- correct position for new min/max: on top of list, below it is the current max
	- correct position for other elements: above the closest lower neighbor/below closest upper neighbor
	- ? when doing ra/rra/sa, check if the same operation cannot be done on the other side as well
-> we should have 2-3 partitions max, each sorted descending
7. sort three elements left in a
# ALGORITHM II. - FILL_BACK_A - a is filled back ascending
8. fill a back - also will be done with the elements left in b from 4 and 5 size stacks

CONSIDER
- "It's the fact that you are not only pushing the smallest number, but the smallest or biggest depending on which is 'closer' to the top that improved your algorithm performance. It's not because you separated it in chunks."

! or maybe we can push exactly half elements, sort both stacks (a asc, b desc) and then just combine them by pa to the correct spot
