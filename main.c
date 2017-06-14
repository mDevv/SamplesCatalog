/*
* Name: main.c
* Purpose: Main function and basic UI 
* @Author: Michał Dziewulski
* @Version: 1.0 29.06.2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "record.h"
#include "basis.h"
#include "ui.h"

//Functions declarations
void show_header();
void mp_sleep(unsigned);
int menu();
void basis_menu();
void fill_basis();
//~Functions declarations

//extern
extern basis *basis_l;
extern record *list;
//~extern

int main(void)
{
    system("clear"); //Clear console
    fill_basis();

    while(1)
    {
        system("clear");
        int option = menu();
        switch(option)
        {
            case 1:
                print();
                break;
            case 2:
                basis_menu();
                break;
            case 3:
                add_ui();
                break;
            case 4:
                del_ui();
                break;
            case 5:
                edit_ui();
                break;
            case 6:
                sort_ui();
                break;
            case 7:
                //save_ui();
                break;
            case 8:
                //load_ui();
                break;
            case 9:
                clear_ui();
                break;
            case 10:
                system("clear");
                clear_rec();
                clear_basis();
                puts("Program zakonczony.");
                return 0;   
        }
    }
}

void show_header()
{
    printf("------------------------------------------------------------------\n");
    printf("Katalog probek do eksperymentow\n");
    printf("Autor: Michal Dziewulski (1I2; sroda, godz. 10)\n");
    printf("------------------------------------------------------------------\n");
}

int menu()
{
    int option;
    
    show_header();
    printf("MENU:\n");
    printf("1. Pokaz katalog\n");
    printf("2. Zarzadzaj typami podloza\n");
    printf("3. Dodaj probke\n");
    printf("4. Usun probke\n");
    printf("5. Edytuj probke\n");
    printf("6. Sortuj katalog\n");
    printf("7. Zapisz do pliku\n");
    printf("8. Odczytaj z pliku\n");
    printf("9. Wyczysc katalog\n");
    printf("10. Zakoncz program\n\n");
    printf("Wprowadz wybrana opcje: ");
    
    while(scanf("%d", &option) != 1 || (option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 6 && option != 7 && option != 8 && option != 9 && option != 10)) //Input control
    {
        puts("Bledne dane. Sprobuj ponownie.");
        sleep(1);
        system("clear");
        
        show_header();
        printf("MENU:\n");
        printf("1. Pokaz katalog\n");
        printf("2. Pokaz typy podloza");
        printf("3. Dodaj probke\n");
        printf("4. Usun probke\n");
        printf("5. Edytuj probke\n");
        printf("6. Sortuj katalog\n");
        printf("7. Zapisz do pliku\n");
        printf("8. Odczytaj z pliku\n");
        printf("9. Wyczysc katalog\n");
        printf("10. Zakoncz program\n\n");
        printf("Wprowadz wybrana opcje: ");
        while(getchar() != '\n');
    }
    
    return option;
}

void basis_menu()
{
    while(1)
    {
        system("clear");
        int option;

        show_header();
        printf("MENU:\n");
        printf("1. Pokaz typy podloza\n");
        printf("2. Dodaj typ podloza\n");
        printf("3. Usun typ podloza\n");
        printf("4. Edytuj typ podloza\n");
        printf("5. Wroc do menu\n");    
        printf("Wprowadz wybrana opcje: ");
        
        while(scanf("%d", &option) != 1 || (option != 1 && option != 2 && option != 3 && option != 4 && option != 5)) //Input control
        {
            puts("Bledne dane. Sprobuj ponownie.");
            sleep(1);
            system("clear");
            
            show_header();
            printf("MENU:\n");
            printf("1. Pokaz typy podloza\n");
            printf("2. Dodaj typ podloza\n");
            printf("3. Usun typ podloza\n");
            printf("4. Edytuj typ podloza\n");
            printf("5. Wroc do menu\n");   
            printf("Wprowadz wybrana opcje: ");
            while(getchar() != '\n');
        }

        switch(option)
        {
        case 1:
            print_basis();
            break;
        case 2:
            //add_basis_ui();
            break;
        case 3:
            del_basis_ui();
            break;
        case 4:
            //edit_basis_ui();
            break;
        case 5:
            return;
        }
    }
}

void fill_basis()
{
    basis b;
    b.b_id = 1;
    b.name = "Typ A";
    add_basis(b);
    b.b_id = 2;
    b.name = "Typ B";
    add_basis(b);
    b.b_id = 3;
    b.name = "Typ C";
    add_basis(b);
    b.b_id = 4;
    b.name = "Typ D";
    add_basis(b);
    b.b_id = 5;
    b.name = "Typ E";
    add_basis(b);
}
