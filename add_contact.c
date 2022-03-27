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
    char choice[255];
    char select[10];
    int num = 1; 

    ContactInfo* contactInfo = address_book -> list; 
    contactInfo = (ContactInfo*) realloc(contactInfo, ((address_book -> count + 1) * sizeof(contactInfo)));

    address_book -> list = contactInfo;
    strcpy(*((address_book -> count) + contactInfo) -> name, " "); //To save name of the new contact
    strcpy(((address_book -> count) + contactInfo) -> phone_numbers[0], " "); //To save contact's phone number
    strycpy(((address_book -> count) + contactInfo) -> email_addresses[0], " "); //To save contact's email address

    while(strcmp(choice, "0") != 0)
    {
        menu_header("Add Contact:\n ");
        strcmp(select, "select");
        printf("\n0. Back\n");
        printf("1. Name       :\n");
        printf("2. Phone No 1 :\n");
        printf("3. Email ID 1 :\n");
        prontf("Please select an option for add:\n "); 
        scanf("%c", choice); 
        
        if(strcmp(choice, "0", == 0))
        {
            break; 
        }

        //If number 1 is selected, prompt the user to enter the name of the contact.
        else if(strcmp(choice, "1" == 0))
        {
            printf("\nEnter name: ");
            scanf("%s", ((address_book -> count) + contactInfo) -> name);
            num = 0;
        }//end else if

        //If number 2 is selected, prompt the user to enter the contact's phone number.
        else if(strcmp(choice, "2" == 0))
        {
            printf("\nEnter Phone No 1: ");
            scanf("%s", ((address_book -> count) + contactInfo) -> phone_numbers[0]);
            num = 0;
        }//end else if

        //If number 3 is selected, prompt the user to enter the contact's email address.
        else if(strcmp(choice, "4" == 0))
        {
            printf("\nEnter Email ID 1: ");
            scanf("%s", ((address_book -> count) + contactInfo) -> email_addresses[0]);
            num = 0;
        }//end else if
    }//end while

    //To check if any data(name, phone number, or e-mail) was added
    if(num == 0)
    {
        ((address_book -> count) + contactInfo) -> si_no = address_book -> count + 1;
        for(int i = 1; i < 5; ++i)
        {
            strcpy(((address_book -> count) + contactInfo) -> phone_numbers[i], " ");
            strcpy(((address_book -> count) + contactInfo) -> email_addresses[i], " ");
        }
        ++address_book -> count;
    }//end if
}//end add_contacts
