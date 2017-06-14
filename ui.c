/*
* Name: ui.c
* Purpose: Implementation of functions used to handle the UI 
* @Author: Michał Dziewulski
* @Version: 1.0 29.12.2016
*/

#include "ui.h"
#include "record.h"
#include "basis.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern record *list;
extern basis *basis_l;

void print() //DONE, WORKS
{
    system("clear");
    printf("------------------------------------------------------------------\n");
    printf("Katalog\n");
    printf("------------------------------------------------------------------\n");
    printf("   ID |   PODLOZE |    MOC | CZAS | GRUBOSC | DZIEN | MSC |  ROK |\n");
    
    record *ptr = list;
    while(ptr)
    {
       printf("%5u |%10s |%7.2f |%5u |%8.2f |%6u |%4u |%5u |\n", ptr->id, ptr->basis_ptr->name, ptr->power, ptr->time, ptr->thickness, ptr->date.day, ptr->date.month, ptr->date.year);
       ptr = ptr->next;
    }
    printf("\nNacisnij ENTER aby przejsc do menu...\n");
    getchar();
    while(getchar() != '\n');
    return;
}

void add_ui() //DONE, WORKS
{
    record rec_tmp;
    system("clear");
    printf("------------------------------------------------------------------\n");
    printf("Dodawanie probki\n");
    printf("------------------------------------------------------------------\n");
    
    if(basis_l == NULL)
    {
        printf("\nBlad. Brak dodanych typow podloza.");
        printf("\nNacisnij ENTER aby przejsc do menu...\n");
        getchar();
        while(getchar() != '\n');
        return; 
    }

    printf("\nPodaj oznaczenie probki (liczba 1-99999): ");
    while(scanf("%u", &rec_tmp.id) != 1 || get_record_ptr(rec_tmp.id) != NULL || rec_tmp.id < 1 || rec_tmp.id > 99999)
    {
        printf("\nBlad. Byc moze probka o podanym oznaczeniu juz istnieje. Sprobuj ponownie.");
        printf("\nPodaj oznaczenie probki (liczba 1-99999): ");
        while(getchar() != '\n');
    }

    unsigned basis_id;
    printf("\nPodaj identyfikator typu podloza: ");
    while(scanf("%u", &basis_id) != 1 || get_basis_ptr(basis_id) == NULL)
    {
        printf("\nBlad. Byc moze nie istnieje typ podloza o podanym identyfikatorze.");
        printf("\nPodaj identyfikator typu podloza: ");
        while(getchar() != '\n');
    }

    rec_tmp.basis_ptr = get_basis_ptr(basis_id);

    printf("\nPodaj moc (cecha 0 - 9999): ");
    while(scanf("%lf", &rec_tmp.power) != 1 || rec_tmp.power < 0 || rec_tmp.power > 9999) 
    {
        printf("\nBlad. Sprobuj ponownie.");
        printf("\nPodaj moc (cecha 0 - 9999): ");    
        while(getchar() != '\n');
    }

    printf("\nPodaj czas (w sekundach, zakres 0-99999): ");
    while(scanf("%u", &rec_tmp.time) != 1 || rec_tmp.time > 99999)
    {
        printf("\nBlad. Sprobuj ponownie.");
        printf("\nPodaj czas (w sekundach, zakres 0-99999): ");
        while(getchar() != '\n');
    }
    
    printf("\nPodaj grubosc (cecha 0-99999): ");
    while(scanf("%lf", &rec_tmp.thickness) != 1 || rec_tmp.thickness < 0 || rec_tmp.thickness > 99999)
    {
        printf("\nBlad. Sprobuj ponownie.");
        printf("\nPodaj grubosc (cecha 0-99999): ");
        while(getchar() != '\n');
    }
   
    printf("\nPodaj rok (liczba 1900-3000): ");
    while(scanf("%u", &rec_tmp.date.year) != 1 || rec_tmp.date.year < 1900 || rec_tmp.date.year > 3000)
    {
        printf("\nBlad. Sprobuj ponownie.");
        printf("\nPodaj rok (liczba 1900-3000): ");
        while(getchar() != '\n');
    }
    printf("\nPodaj miesiac (liczba 1-12): ");
    while(scanf("%u", &rec_tmp.date.month) != 1 || rec_tmp.date.month < 1 || rec_tmp.date.month > 12)
    {
        printf("\nBlad. Sprobuj ponownie.");
        printf("\nPodaj miesiac (liczba 1-12): ");
        while(getchar() != '\n');
    }
    printf("\nPodaj dzien (liczba 1-31): ");
    while(scanf("%u", &rec_tmp.date.day) != 1 || rec_tmp.date.day < 1 || rec_tmp.date.day > 31)
    {
        printf("\nBlad. Sprobuj ponownie.");
        printf("\nPodaj dzien (liczba 1-31): ");
        while(getchar() != '\n');
    }

    if(add(rec_tmp))
    {
        printf("\nDodano probke.\n");
    }
    else
    {
        printf("\nBlad alokacji pamieci!\n");        
    }
    
    printf("\nNacisnij ENTER aby przejsc do menu...\n");
    getchar();
    while(getchar() != '\n');
    return;
}

void edit_ui() //DONE, WORKS
{
    record rec_tmp;
    system("clear");
    printf("------------------------------------------------------------------\n");
    printf("Edytowanie probki\n");
    printf("------------------------------------------------------------------\n");
    
    if(list == NULL)
    {
        printf("\nLista jest pusta.\n");
        printf("\nNacisnij ENTER aby przejsc do menu...\n");
        getchar();
        while(getchar() != '\n');
        return;
    }

    unsigned rec_id;
    
    printf("\nPodaj oznaczenie edytowanej probki: ");
    while(scanf("%u", &rec_id) != 1 || get_record_ptr(rec_id) == NULL)
    {
        printf("\nBlad. Byc moze probka nie istnieje. Sprobuj ponownie.");
        printf("\nPodaj oznaczenie edytowanej probki: ");
        while(getchar() != '\n');
    }

    record *ptr = get_record_ptr(rec_id);

    printf("\nPodaj nowe oznaczenie (liczba 1-99999, stare: %u): ", ptr->id);
    while(scanf("%u", &rec_tmp.id) != 1 || (get_record_ptr(rec_tmp.id) != NULL && rec_tmp.id != ptr->id) || rec_tmp.id < 1 || rec_tmp.id > 99999)
    {
        printf("\nBlad. Byc moze probka o podanym oznaczeniu juz istnieje. Sprobuj ponownie.");
        printf("\nPodaj nowe oznaczenie (liczba 1-99999, stare: %u): ", ptr->id);
        while(getchar() != '\n');
    }

    unsigned basis_id;
    printf("\nPodaj nowy identyfikator typu podloza (stary: %u): ", ptr->basis_ptr->b_id);
    while(scanf("%u", &basis_id) != 1 || get_basis_ptr(basis_id) == NULL)
    {
        printf("\nBlad. Byc moze typ o danym identyfikatorze nie istnieje.");
        printf("\nPodaj nowy identyfikator typu podloza (stary: %u): ", ptr->basis_ptr->b_id);
        while(getchar() != '\n');
    }

    rec_tmp.basis_ptr = get_basis_ptr(basis_id);

    printf("\nPodaj nowa moc (cecha 0 - 9999, stara: %f): ", ptr->power);
    while(scanf("%lf", &rec_tmp.power) != 1 || rec_tmp.power > 9999)
    {
        printf("\nBlad. Sprobuj ponownie.");
        printf("\nPodaj nowa moc (cecha 0 - 9999, stara: %f): ", ptr->power);
        while(getchar() != '\n');
    }


    printf("\nPodaj nowy czas (w sekundach, zakres 0-99999, stary: %u): ", ptr->time);
    while(scanf("%u", &rec_tmp.time) != 1 || rec_tmp.time > 99999)
    {
        printf("\nBlad. Sprobuj ponownie.");
        printf("\nPodaj nowy czas (w sekundach, zakres 0-99999, stary: %u): ", ptr->time);
        while(getchar() != '\n');
    }


    printf("\nPodaj nowa grubosc (cecha 0-99999, stara: %f): ", ptr->thickness);
    while(scanf("%lf", &rec_tmp.thickness) != 1 || rec_tmp.thickness < 0 || rec_tmp.thickness > 99999)
    {
        printf("\nPodaj nowa grubosc (stara: %f): ", ptr->thickness);
        printf("\nPodaj nowa grubosc (cecha 0-99999, stara: %f): ", ptr->thickness);
        while(getchar() != '\n');
    }


    printf("\nPodaj nowy rok (liczba 1900-3000, stary: %u): ", ptr->date.year);
    while(scanf("%u", &rec_tmp.date.year) != 1 || rec_tmp.date.year < 1900 || rec_tmp.date.year > 3000)
    {
        printf("\nBlad. Sprobuj ponownie.");
        printf("\nPodaj nowy rok (liczba 1900-3000, stary: %u): ", ptr->date.year);
        while(getchar() != '\n');
    }


    printf("\nPodaj nowy miesiac (liczba 1-12, stary: %u): ", ptr->date.month);
    while(scanf("%u", &rec_tmp.date.month) != 1 || rec_tmp.date.month < 1 || rec_tmp.date.month > 12)
    {
        printf("\nBlad. Sprobuj ponownie.");
        printf("\nPodaj nowy miesiac (liczba 1-12, stary: %u): ", ptr->date.month);
        while(getchar() != '\n');
    }


    printf("\nPodaj dzien (liczba 1-31, stary: %u): ", ptr->date.day);
    while(scanf("%u", &rec_tmp.date.day) != 1 || rec_tmp.date.day < 1 || rec_tmp.date.day > 31)
    {
        printf("\nBlad. Sprobuj ponownie.");
        printf("\nPodaj dzien (liczba 1-31, stary: %u): ", ptr->date.day);
        while(getchar() != '\n');
    }

    edit(ptr, rec_tmp);
    printf("\nWyedytowano probke\n");
    printf("\nNacisnij ENTER aby przejsc do menu...\n");
    getchar();
    while(getchar() != '\n');
    return;
}

void del_ui() //DONE, WORKS
{
    system("clear");
    printf("------------------------------------------------------------------\n");
    printf("Usuwanie probki\n");
    printf("------------------------------------------------------------------\n");
    
    if(list == NULL)
    {
        printf("\nLista jest pusta.\n");
        printf("\nNacisnij ENTER aby przejsc do menu...\n");
        getchar();
        while(getchar() != '\n');
        return;
    }

    unsigned rec_id;
    printf("\nPodaj oznaczenie usuwanej probki: ");
    while(scanf("%u", &rec_id) != 1 || get_record_ptr(rec_id) == NULL)
    {
        printf("\nBlad. Probka o podanym oznaczeniu nie istnieje.");
        printf("\nPodaj oznaczenie usuwanej probki: ");
        while(getchar() != '\n');
    }
    
    record *ptr = get_record_ptr(rec_id);

    del(ptr);
    printf("\nUsunieto probke.\n");
    printf("\nNacisnij ENTER aby przejsc do menu...\n");
    getchar();
    while(getchar() != '\n');
    return;
}

void print_basis() //DONE, WORKS
{
    system("clear");
    printf("------------------------------------------------------------------\n");
    printf("Typy podloza\n");
    printf("------------------------------------------------------------------\n");
    printf("   ID |   PODLOZE |\n");
    
    basis *ptr = basis_l;
    while(ptr)
    {
       printf("%5u |%10s |\n", ptr->b_id, ptr->name);
       ptr = ptr->next;
    }
    printf("\nNacisnij ENTER aby przejsc do menu...\n");
    getchar();
    while(getchar() != '\n');
    return;
}

void add_basis_ui() //DONE, WORKS
{
    basis bas_tmp;
    system("clear");
    printf("------------------------------------------------------------------\n");
    printf("Dodawanie typu podloza\n");
    printf("------------------------------------------------------------------\n");

    printf("\nPodaj identyfikator typu podloza (liczba 1-99999): ");
    while(scanf("%u", &bas_tmp.b_id) != 1 || get_basis_ptr(bas_tmp.b_id) != NULL || bas_tmp.b_id < 1 || bas_tmp.b_id > 99999)
    {
        printf("\nBlad. Byc moze juz istnieje typ podloza o podanym identyfikatorze.");
        printf("\nPodaj identyfikator typu podloza (liczba 1-99999): ");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');

    const int str_l = 11;
    bas_tmp.name = malloc(sizeof(char) * str_l);
    printf("\nPodaj nazwe (max 10 znakow): ");
    fgets(bas_tmp.name, str_l, stdin);
    bas_tmp.name[strcspn(bas_tmp.name, "\n")] = 0;
    while(getchar() != '\n');

    
    if(add_basis(bas_tmp))
    {
        printf("\nDodano typ podloza.\n");
    }
    else
    {
        printf("\nBlad alokacji pamieci!\n");        
    }
    
    free(bas_tmp.name);
    printf("\nNacisnij ENTER aby przejsc do menu...\n");
    getchar();
    return;
}

void del_basis_ui() //DONE, WORKS
{
    system("clear");
    printf("------------------------------------------------------------------\n");
    printf("Usuwanie typu podloza\n");
    printf("------------------------------------------------------------------\n");
    
    if(basis_l == NULL)
    {
        printf("\nLista jest pusta.\n");
        printf("\nNacisnij ENTER aby przejsc do menu...\n");
        getchar();
        while(getchar() != '\n');
        return;
    }

    unsigned bas_id;
    printf("\nPodaj oznaczenie usuwanego typu: ");
    while(scanf("%u", &bas_id) != 1 || get_basis_ptr(bas_id) == NULL)
    {
        printf("\nBlad. Probka o podanym oznaczeniu nie istnieje.");
        printf("\nPodaj oznaczenie usuwanego typu: ");
        while(getchar() != '\n');
    }
    
    basis *ptr = get_basis_ptr(bas_id);
    
    record *tmp_ptr = list;
    
    while(tmp_ptr)
    {
        if(tmp_ptr->basis_ptr == ptr)
        {
            printf("\nBlad. Istnieje przynajmniej jedna probka z przypisanym typem podloza.\n");
            printf("\nNacisnij ENTER aby przejsc do menu...\n");
            getchar();
            getchar();
            return;
        }
        tmp_ptr = tmp_ptr->next;
    }

    del_basis(ptr);
    printf("\nUsunieto typ podloza.\n");
    printf("\nNacisnij ENTER aby przejsc do menu...\n");
    getchar();
    while(getchar() != '\n');
    return;
}

void edit_basis_ui() //DONE, WORKS
{
    basis bas_tmp;
    system("clear");
    printf("------------------------------------------------------------------\n");
    printf("Edytowanie typu podloza\n");
    printf("------------------------------------------------------------------\n");
    
    if(basis_l == NULL)
    {
        printf("\nLista jest pusta.\n");
        printf("\nNacisnij ENTER aby przejsc do menu...\n");
        getchar();
        while(getchar() != '\n');
        return;
    }

    unsigned bas_id;
    
    printf("\nPodaj identyfikator edytowanego typu podloza: ");
    while(scanf("%u", &bas_id) != 1 || get_basis_ptr(bas_id) == NULL)
    {
        printf("\nBlad. Byc moze typ podloza o podanym identyfikatorze nie istnieje.");
        printf("\nPodaj identyfikator edytowanego typu podloza: ");
        while(getchar() != '\n');
    }

    basis *ptr = get_basis_ptr(bas_id);

    printf("\nPodaj nowy identyfikator (liczba 1-99999, stare: %u): ", ptr->b_id);
    while(scanf("%u", &bas_tmp.b_id) != 1 || (get_basis_ptr(bas_tmp.b_id) != NULL && bas_tmp.b_id != ptr->b_id) || bas_tmp.b_id < 1 || bas_tmp.b_id > 99999)
    {
        printf("\nBlad. Byc moze typ podloza o podanym identyfikatorze juz istnieje. Sprobuj ponownie.");
        printf("\nPodaj nowy identyfikator (liczba 1-99999, stare: %u): ", ptr->b_id);
        while(getchar() != '\n');
    }
    while(getchar() != '\n');

    const int str_l = 11;
    bas_tmp.name = malloc(sizeof(char) * str_l);
    printf("\nPodaj nazwe (max 10 znakow, stara: %s): ", ptr->name);
    fgets(bas_tmp.name, str_l, stdin);
    bas_tmp.name[strcspn(bas_tmp.name, "\n")] = 0;
    while(getchar() != '\n');

    edit_basis(ptr, bas_tmp);
    free(bas_tmp.name);
    printf("\nWyedytowano typ podloza\n");
    printf("\nNacisnij ENTER aby przejsc do menu...\n");
    getchar();
    return;
}

void clear_ui()
{
    system("clear");
    printf("------------------------------------------------------------------\n");
    printf("Czyszczenie bazy\n");
    printf("------------------------------------------------------------------\n");
    
    if(list == NULL)
    {
        printf("\nLista jest pusta.\n");
        printf("\nNacisnij ENTER aby przejsc do menu...\n");
        getchar();
        while(getchar() != '\n');
        return;
    }

    printf("\nCzy na pewno chcesz wyczyscic baze? (1 = nie, 0 = tak) ");
    int c;
    while(scanf("%d", &c) != 1 || (c != 1 && c != 0))
    {
        printf("\nBlad. Sprobuj ponownie");
        printf("\nCzy na pewno chcesz wyczyscic baze? (1 = nie, 0 = tak) ");
        while(getchar() != '\n');
    }

    if(c == 0)
    {
        clear_rec();
        printf("\nWyczyszczono baze\n");
    }
    else
    {
        printf("\nAnulowano\n");
    }

    printf("\nNacisnij ENTER aby przejsc do menu...\n");
    getchar();
    while(getchar() != '\n');
    return;
}

void sort_ui()
{
    int option;
    system("clear");
    printf("------------------------------------------------------------------\n");
    printf("Sortowanie\n");
    printf("------------------------------------------------------------------\n");
    
    if(list == NULL)
    {
        printf("\nLista jest pusta.\n");
        printf("\nNacisnij ENTER aby przejsc do menu...\n");
        getchar();
        while(getchar() != '\n');
        return;
    }
    
    printf("KRYTERIUM:\n");
    printf("1. Oznaczenie\n");
    printf("2. Typ podloza\n");
    printf("3. Moc\n");
    printf("4. Czas\n");
    printf("5. Grubosc\n");
    printf("6. Data\n");
    printf("7. Wroc do menu\n\n");
    printf("Wprowadz wybrana opcje: ");
    
    while(scanf("%d", &option) != 1 || (option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 6 && option != 7)) //Input control
    {
        puts("Bledne dane. Sprobuj ponownie.");
        sleep(1);
        system("clear");
        
        system("clear");
        printf("------------------------------------------------------------------\n");
        printf("Sortowanie\n");
        printf("------------------------------------------------------------------\n");
        printf("KRYTERIUM:\n");
        printf("1. Oznaczenie\n");
        printf("2. Typ podloza\n");
        printf("3. Moc\n");
        printf("4. Czas\n");
        printf("5. Grubosc\n");
        printf("6. Data\n");
        printf("7. Wroc do menu\n\n");
        printf("Wprowadz wybrana opcje: ");
        while(getchar() != '\n');
    }

    sort(option);
    printf("\nKatalog posortowany\n");
    printf("\nNacisnij ENTER aby przejsc do menu...\n");
    getchar();
    while(getchar() != '\n');
    return;
}