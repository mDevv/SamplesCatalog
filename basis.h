/*
* Name: basis.h
* Purpose: Header with declarations used to manage samples 
* @Author: Michał Dziewulski
* @Version: 1.0 29.12.2016
*/

#ifndef BASIS_H
#define BASIS_H

typedef
    struct basis_t
    {
        unsigned b_id;
        char *name;
        struct basis_t *next;
    }
basis;

int add_basis(basis);
int del_basis(basis*);
void edit_basis(basis*, basis);
void clear_basis();
basis* get_basis_ptr(unsigned);

#endif