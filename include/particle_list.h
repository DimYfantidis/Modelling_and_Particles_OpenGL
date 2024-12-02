#pragma once

#include <stdio.h>
#include <stdbool.h>

#include "particle.h"

// Doubly linked list node object -- dynamically allocated content
struct list_node
{
	struct particle* data;
	struct list_node* next;
	struct list_node* prev;
};
typedef struct list_node list_node;

// Doubly linked list implementation
struct list
{
	size_t size;
	list_node* head;
	list_node* tail;
};
typedef struct list list;

// List constructor
void initList(struct list* list)
{
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}

// Append (dynamically allocated) particle to list
struct particle* appendToList(struct list* list, struct particle* entry)
{
	// Stores the current tail node
	list_node* old_tail = list->tail;

	// The tail becomes a new node with the given process's data.
	list->tail = (struct list_node*)malloc(sizeof(struct list_node));
	if (list->tail == NULL)
	{
		list->tail = old_tail;
		return NULL;
	}
	list->tail->data = entry;
	list->tail->next = NULL;

	list->size++;

	if (old_tail != NULL) 
	{
		// The new tail becomes the old tail's next node.
		old_tail->next = list->tail;
		list->tail->prev = old_tail;
	}
	else 
	{
		// Special case: The list was empty before the insertion.
		list->head = list->tail;
		list->head->prev = NULL;
		list->tail->prev = list->head;
	}
	return list->tail->data;
}

// WARNING: Dangerous method - user must be sure that the provided node exists inside the given list
void removeFromList(struct list* list, struct list_node* entry)
{
	if (entry == list->head)
	{
		list->head = entry->next;
		list->head->prev = NULL;
	}
	else if (entry == list->tail)
	{
		list->tail = entry->prev;
		list->tail->next = NULL;
	}
	else
	{
		entry->prev->next = entry->next;
		entry->next->prev = entry->prev;
	}

	free(entry->data);
	free(entry);

	list->size--;
}

// List destructor
void destroyList(struct list* list, bool logFlag)
{
	list_node* temp;

	if (logFlag)
	{
		printf("\t> Deallocating list of %zu particles\n", list->size);
	}
	for (list_node* iterator = list->head; iterator != NULL; iterator = temp)
	{
		// Deallocate all dynamically allocated nodes and their dynamically allocated particles objects
		temp = iterator->next;
		free(iterator->data);
		free(iterator);
	}
}
