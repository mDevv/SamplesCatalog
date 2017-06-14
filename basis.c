/*
* Name: basis.c
* Purpose: Implementation of functions used to manage samples 
* @Author: Michał Dziewulski
* @Version: 1.0 29.12.2016
*/

#include "basis.h"
#include <stdlib.h>
#include <string.h>

basis *basis_l = NULL;

int add_basis(basis bas_tmp) //DONE, WORKS
{
    basis *ptr = basis_l;
    basis *b = malloc(sizeof(basis));
    
    if(b == NULL)
    {
        return 0;
    }
    
    b->b_id = bas_tmp.b_id;
    b->name = malloc(sizeof(bas_tmp.name));
    b->next = NULL;
    strcpy(b->name, bas_tmp.name);

    if(basis_l)
    {
        while(ptr->next)
        {
            ptr = ptr->next;
        }
        ptr->next = b;
    }
    else
    {
        basis_l = b;
    }
    

    return 1;
}

int del_basis(basis* ptr) //DONE, WORKS
{
    if(basis_l)
    {
        if(basis_l == ptr)
        {
            if(ptr->next)
            {
                basis_l = ptr->next;
            }
            else
            {
                basis_l = NULL;
            }
            free(ptr->name);
            free(ptr);
        }
        else if (ptr->next == NULL)
        {
            basis *tmp = basis_l;
            while(tmp->next->next)
            {
                tmp = tmp->next;
            }
            free(tmp->next->name);
            free(tmp->next);
            tmp->next = NULL;
        }
        else
        {
            basis *tmp = basis_l;
            while(tmp->next != ptr)
            {
                tmp = tmp->next;
            }
            tmp->next = ptr->next;
            free(ptr->name);
            free(ptr);
        }

    }
    else
    {
        return 0;
    }
    return 1;
}

void edit_basis(basis* ptr, basis bas_tmp) //DONE, WORKS
{
    ptr->b_id = bas_tmp.b_id;
    ptr->name = realloc(ptr->name, sizeof(bas_tmp.name));
    strcpy(ptr->name, bas_tmp.name);
}

void clear_basis()
{
    while(basis_l)
    {
        del_basis(basis_l);
    }
}

basis* get_basis_ptr(unsigned basis_id) //DONE, WORKS
{
    basis *ptr = basis_l;
    while(ptr)
    {
        if(ptr->b_id == basis_id)
        {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL; //no basis with given id
}