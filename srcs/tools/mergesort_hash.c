#include "shell.h"

static t_hash	*merge_lists(t_hash *a, t_hash *b)
{
	t_hash	*merged_list;

	merged_list = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (a->hash > b->hash)
	{
		merged_list = a;
		merged_list->next = merge_lists(a->next, b);
	}
	else
	{
		merged_list = b;
		merged_list->next = merge_lists(a, b->next);
	}
	return (merged_list);
}

static void		partition(t_hash *head, t_hash **front, t_hash **back)
{
	t_hash	*fast;
	t_hash	*slow;

	if (head == NULL || head->next == NULL)
	{
		*front = head;
		*back = NULL;
	}
	else
	{
		slow = head;
		fast = head->next;
		while (fast)
		{
			fast = fast->next;
			if (fast)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front = head;
		*back = slow->next;
		slow->next = NULL;
	}
}

void			merge_sort_hash(t_hash **source)
{
	t_hash	*head;
	t_hash	*a;
	t_hash	*b;

	head = *source;
	a = NULL;
	b = NULL;
	if (head == NULL || head->next == NULL)
		return ;
	partition(head, &a, &b);
	merge_sort_hash(&a);
	merge_sort_hash(&b);
	*source = merge_lists(a, b);
}
