#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h" 
#include "address_book_menu.h"
#include "address_book.h"

extern AddressBook *newAddress;
extern ContactInfo *contactinfo;

Status add_contacts(AddressBook *address_book)
{
    char choice;
    char select[10];
    ContactInfo* contactInfo = address_book -> list; 
    contactInfo = (ContactInfo*) realloc(contactInfo, ((address_book -> count + 1) * sizeof(contactInfo)));

    address_book -> list = contactInfo;
    strcpy(*((address_book -> count) + contactInfo) -> name, " "); //To save name of the new contact
    strcpy(((address_book -> count) + contactInfo) -> phone_numbers[0], " "); //To save contact's phone number
    strycpy(((address_book -> count) + contactInfo) -> email_addresses[0], " "); //To save contact's email address

    while(strcmp(choice,'0') != 0)
    {
        menu_header("Add Contact:\n ");
        strcmp(select, "select");
        printf("\n0. Back\n");
        printf("1. Name       :\n");
        printf("2. Phone No 1 :\n");
        printf("3. Email ID 1 :\n");
        prontf("Please select an option:\n "); 
        scanf("%c", choice); 

        //To check if the selection is valid or not.
        while((int)choice < 0 || (int)choice > 3)
        {
            menu_header("Search Contact to delete by: "); 
            strcmp(select, "select");
            printf("\n0. Back\n");
            printf("1. Name       :\n");
            printf("2. Phone No 1 :\n");
            printf("3. Email ID 1 :\n");
            prontf("Please select an option:\n "); 
            scanf("%c", choice); 
        }//end while loop

        if(strcmp(choice, '0') == 0)
        {
            break;

        }//end if

        //If number 1 is selected, prompt the user to enter the name of the contact.
        else if(strcmp(choice, '1' == 0))
        {
            printf("\nEnter name: ");
            scanf("%s", ((address_book -> count) + contactInfo) -> name);
        }//end else if

        //If number 2 is selected, prompt the user to enter the contact's phone number.
        else if(strcmp(choice, '2' == 0))
        {
            printf("\nEnter Phone No 1: ");
            scanf("%s", ((address_book -> count) + contactInfo) -> phone_numbers[0]);
        }//end else if

        //If number 3 is selected, prompt the user to enter the contact's email address.
        else if(strcmp(choice, '3' == 0))
        {
            printf("\nEnter Email ID: ");
            scanf("%s", ((address_book -> count) + contactInfo) -> email_addresses[0]);
        }//end else if
    }//end while

}
