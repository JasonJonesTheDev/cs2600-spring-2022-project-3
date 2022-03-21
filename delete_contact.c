#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h" 
#include "address_book_menu.h"
#include "address_book.h"

extern AddressBook *newAddress;
extern ContactInfo *contactinfo;
Status delete_contact(AddressBook *address_book)
{
    //A variable to save name, phone number, serial number, and email id every time we do search
    char* save[255]; 
    char searchBy[255];
    char select[10];
    char choice;

    ContactInfo * contactInfo = address_book -> list; 
    
    //To find the contact that has to be deleted
    while(strcmp(choice,'0') != 0)
    {
        /* Select how to search the specific contact that has to be deleted
            by name, by phone number, email id, or by serial number */
        menu_header("Search Contact to delete by: "); 
        strcmp(select, "select");
        printf("\n0. Back\n");
        printf("1. Name\n");
        printf("2. Phone No\n");
        printf("3. Email ID\n");
        printf("4. Serial No\n");
        prontf("Please select an option:\n "); 
        scanf("%c", choice); 

        //To check if the selection is valid or not.
        while((int)choice < 0 || (int)choice > 4)
        {
            menu_header("Search Contact to delete by: "); 
            strcmp(select, "select");
            printf("\n0. Back\n");
            printf("1. Name\n");
            printf("2. Phone No\n");
            printf("3. Email ID\n");
            printf("4. Serial No\n");
            prontf("Please select an option:\n "); 
            scanf("%c", choice); 
        }//end while loop
        
        if(strcmp(choice, '0') == 0)
        {
            break; //stop 
        }//end if

        //Search the contact by name
        else if(strcmp(choice, '1') == 0)
        {
            printf("\nEnter the name: ");
            scanf("%s", save);
            strcpy(searchBy, "Name"); 
        }//end else if

        //Search the contact by phone number
        else if(strcmp(choice, '2') == 0)
        {
            printf("\nEnter the Phone No: ");
            scanf("%s", save);
            strcpy(searchBy, "Phone"); 
        }//end else if

        //Search the contact by Email ID 
        else if(strcmp(choice, '3') == 0)
        {
            printf("\nEnter the Email ID: ");
            scanf("%s", save);
            strcpy(searchBy, "Email"); 
        }//end else if

        //Search the contact by serial number 
        else if(strcmp(choice, '4') == 0)
        {
            printf("\nEnter the Serial No: ");
            scanf("%s", save);
            strcpy(searchBy, "Serial"); 
        }//end else if

        menu_header("Search Result:\n");
        printf("===================================================================================================");
        printf("\n: S.No : Name                              : Phone No                          : Email ID                                  :");

        for(int i=0; i < newAddress ->count; ++i)
        {
            if(search(save, address_book, i, 0, searchBy, e_search) == e_success)
            {
                char format[20] = " ";
                ContactInfo *contactPtr = newAddress ->list;

                //Showing the result in the output 
                printf("==================================================================================================\n");
                printf("%-4.4d : %-33.32s : %-33.32s : %-33.32s :", 
                       (i + contactPtr) -> si_no, (i + contactPtr) -> name, (i + contactPtr) -> phone_numbers[0], (i + contactPtr) -> email_addresses);
            }

        }//end for loop

        while(strcmp(choice,'q')!=0)
        {
            printf("\nPress: [s] = Select, [q] to Cancel:\n ");
            scanf("%s", choice);
            if(strcmp(choice,'q') != 0)
            {
                printf("\nSelect a Serial Number (S.No) to Delete: ");
                scanf("%s", save); 
                menu_header("Delete Contact: "); 
                for(int i = 0; i < address_book -> count; ++i)
                {
                    if(search(save, address_book ,i , 0, "Serial", e_search) == e_success)
                    {
                        while(strcmp(choice,'0') != 0)
                        {
                            menu_header("Edit Contact: ");
                            printf("\n0. Back");
                            printf("\n1. Name       : %s", ((i)+contactinfo)->name);
                            printf("\n2. Phone No 1 : %s", ((i)+contactinfo)->phone_numbers[0]);
                            printf("\n3. Email ID 1: %s", ((i)+contactinfo)-> email_addresses);

                            int numberOfEmails = 1; 
                            int numberOfPhones = 1;
                            int count = 3; 

                            for(int j=1; j<5; ++j)
                            {
                                if(strcmp((i+contactinfo) -> phone_numbers[j], " ") != 0)
                                {
                                    printf("\nPhone No %d: %s", j+1, (i + contactinfo) -> phone_numbers[1]);
                                    ++count;
                                    ++numberOfPhones;
                                }
                            }//end for

                            printf("\n3. Email ID 1 : %s", ((i)+contactinfo) -> email_addresses[0]);
                            for(int j = 1; j < 5; ++j)
                            {
                                if(strcmp((i+contactinfo)->email_addresses[j], " ") != 0)
                                {
                                    printf("\nEmail No %d  :  %s", j+1,(i+contactinfo) -> email_addresses[j]);
                                    ++numberOfEmails;
                                    ++count;
                                }
                            }//end for

                            printf("\n\nEnter 'Y' to delete. [Press any key to ignore] : \n");
                            scanf("%s", choice);

                            if(strcmp(choice, 'Y') == 0)
                            {
                                ContactInfo *contactPtr = newAddress -> list;
                                printf("\nSerial: %d", (i+contactPtr) -> si_no);
                                strcpy(*(i+contactPtr) -> name, *((address_book -> count-1) + contactPtr) -> name);
                                for(int j=0; j < 5; ++j)
                                {
                                    strcpy((i+contactPtr) -> phone_numbers[j], ((address_book -> count-1) + contactPtr) -> phone_numbers[j]);
                                }
                                for(int j = 0; j < 5; ++j)
                                {
                                    strcpy((i+contactPtr) -> email_addresses, ((address_book -> count-1) + contactPtr) -> email_addresses[j]);
                                }
                                contactinfo = (ContactInfo*) realloc(contactinfo, ((address_book->count - 1) * sizeof(ContactInfo)));
                                address_book -> list = contactinfo;
                                address_book -> count--; 
                            }
                            strcpy(choice,'0');
                            strcpy(choice,'q');
                        }//end while
                    }
                }
            }
        }
    }
}//end delete_contact