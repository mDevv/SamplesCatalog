/*
* Name: record.h
* Purpose: Header with declarations used to manage records 
* @Author: Michał Dziewulski
* @Version: 1.0 29.12.2016
*/

#ifndef RECORD_H
#define RECORD_H
#include "basis.h"

    typedef
        struct
        {
            unsigned year; //max chars 6
            unsigned month; //max chars 4
            unsigned day; //max chars 6
        }
    date_t;

    typedef
        struct record_t
        {
            unsigned id; //max chars 5
            basis *basis_ptr; //max chars 10
            double power; //max chars 6
            unsigned time; //in seconds, max chars 5
            double thickness; //max chars 8
            date_t date;
            struct record_t *prev;
            struct record_t *next;
        }
    record;

    int add(record);
    int del(record*);
    void edit(record*, record);
    void clear_rec();
    void sort(unsigned);
    int compare(record*, record*, unsigned);
    int compare_date(record*, record*);
    record *get_record_ptr(unsigned);


#endif