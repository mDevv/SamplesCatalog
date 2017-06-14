/*
* Name: record.c
* Purpose: Implementation of functions used to manage records 
* @Author: Michał Dziewulski
* @Version: 1.0 29.06.2016
*/

#include "record.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

record *list = NULL;

int add(record rec_tmp) //DONE, WORKS
{
    record *ptr = list;
    record *r = malloc(sizeof(record));
    
    if(r == NULL)
    {
        return 0;
    }
    
    r->id = rec_tmp.id;
    r->basis_ptr = rec_tmp.basis_ptr;
    r->power = rec_tmp.power;
    r->time = rec_tmp.time;
    r->thickness = rec_tmp.thickness;
    r->date = rec_tmp.date;
    r->next = NULL;
    if(list)
    {
        while(ptr->next)
        {
            ptr = ptr->next;
        }
        ptr->next = r;
        r->prev = ptr;
    }
    else
    {
        r->prev = NULL;
        list = r;
    }

    return 1;
}

int del(record *ptr) //DONE, WORKS
{
    if(list)
    {
        if(ptr->prev == NULL)
        {
            if(ptr->next)
            {
                list = ptr->next;
                ptr->next->prev = NULL;
            }
            else
            {
                list = NULL;
            }
            free(ptr);
        }
        else if (ptr->next == NULL)
        {
            ptr->prev->next = NULL;
            free(ptr);
        }
        else
        {
            ptr->next->prev = ptr->prev;
            ptr->prev->next = ptr->next;
            free(ptr);
        }
    }
    else
    {
        return 0;
    }

    return 1;
}

void edit(record *ptr, record rec_tmp) //DONE, WORKS
{
    ptr->id = rec_tmp.id;
    ptr->basis_ptr = rec_tmp.basis_ptr;
    ptr->date = rec_tmp.date;
    ptr->power = rec_tmp.power;
    ptr->thickness = rec_tmp.thickness;
    ptr->time = rec_tmp.time;
    return;
}

void clear_rec() //DONE
{
    while(list)
    {
        del(list);
    }
}

void sort(unsigned mode)
{
    int n = 0;
    record *ptr = list;
    while(ptr)
    {
        n++;
        ptr = ptr->next;
    }

    for(int i = 0; i < n; i++)
    {
        ptr = list;
        
        for(int j = 0; j < n - i - 1; j++)
        {
            if(compare(ptr, ptr->next, mode))
            {
                record *ptr2 = ptr->next;
                record *prv = ptr->prev;
                record *nxt = ptr2->next;
                ptr2->prev = prv;
                if(prv) prv->next = ptr2;
                ptr->next = nxt;
                if(nxt) nxt->prev = ptr;
                ptr->prev = ptr2;
                ptr2->next = ptr;
                ptr = ptr->prev;
                if(j == 0)
                {
                    list = ptr;
                }
            }
            ptr = ptr->next;
        }
    }
}

int compare(record *ptr1, record *ptr2, unsigned mode)
{
    if(mode == 1) //id
    {
        return ptr1->id > ptr2->id;
    }
    else if (mode == 2) //basis name
    {
        int v = strcmp(ptr1->basis_ptr->name, ptr2->basis_ptr->name);
        
        if(v > 0)
            return 1;
        else
            return 0;
    }
    else if (mode == 3) //power
    {
        return ptr1->power > ptr2->power;
    }
    else if (mode == 4) //time
    {
        return ptr1->time > ptr2->time;
    }
    else if (mode == 5) // thickness
    {
        return ptr1->thickness > ptr2->thickness;
    }
    else if (mode == 6) // date
    {
        return compare_date(ptr1, ptr2);
    }
    
    return 0;
}

int compare_date(record *ptr1, record *ptr2)
{
    if (ptr1->date.year > ptr2->date.year)
        return 1;
    else if (ptr1->date.year < ptr2->date.year)
        return 0;
    else if (ptr1->date.month > ptr2->date.month)
        return 1;
    else if (ptr1->date.month < ptr2->date.month)
        return 0;
    else if (ptr1->date.day > ptr2->date.day)
        return 1;
    return 0;
}

record* get_record_ptr(unsigned record_id) //DONE, WORKS
{
    record *ptr = list;
    while(ptr)
    {
        if(ptr->id == record_id)
        {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL; //no record with given id
}