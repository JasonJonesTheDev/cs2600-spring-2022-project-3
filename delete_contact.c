#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// #include "abk_fileops.h"
// #include "abk_log.h"
// #include "abk_menus.h"
// #include "abk.h"

#include "address_book_fops.h" //fileops
#include "address_book_menu.h"
#include "address_book.h"

Status delete_contact(AddressBook *address_book)
{ 
    ContactInfo * contactInfo = address_book -> list; 
    char save[255];
    char searchBy[255];
    char select[10];
    char choice[10];

    do
    {
        menu_header("Search Contact to Delete by: "); 
        strcpy(select, "select");
        printf("\n0. Back\n");
        printf("1. Name\n");
        printf("2. Phone No 1\n");
        printf("3. Email ID 1\n");
        printf("4. Serial No\n");
        printf("Please select an option for search: "); 
        scanf("%s", choice); 

        //Sanitizing User Inputs to check if the selection is valid or not.
        while(strcmp(choice, "0") != 0 && strcmp(choice, "1") != 0 && strcmp(choice, "2") != 0
                     && strcmp(choice, "3") != 0 && strcmp(choice, "4") != 0)
        {
            menu_header("Search Contact to Delete by: "); 
            printf("\n0. Back\n");
            printf("1. Name\n");
            printf("2. Phone No 1\n");
            printf("3. Email ID 1\n");
            printf("4. Serial No\n");
            printf("Please select an option for search: "); 
            scanf("%s", choice); 
        }
        
        if(strcmp(choice, "0") ==0)
        {
            break; 
        }//end if 

        //Search the contact by name
        else if(strcmp(choice, "1") ==0)
        {
            printf("\nEnter the name: ");
            scanf("%s", save);
            strcpy(searchBy, "Name"); 
        }//end else if

        //Search the contact by phone number  
        else if(strcmp(choice, "2") ==0)
        {
            printf("\nEnter Phone No 1: ");
            scanf("%s", save);
            strcpy(searchBy, "Phone"); 
        }//end else if

        //Search the contact by e-mail address 
        else if(strcmp(choice, "3") ==0)
        {
            printf("\nEnter Email ID 1: ");
            scanf("%s", save);
            strcpy(searchBy, "Email"); 
        }//end else if

        //Search the contact by serial number
        else if(strcmp(choice, "4") ==0)
        {
            printf("\nEnter Serial No: ");
            scanf("%s", save);
            strcpy(searchBy, "Serial"); 
        }//end else if

        while(strcmp(select,"q") != 0)
        {
            printf("\nPress: [s] = Select, [q] to Cancel: ");
            scanf("%s", select);
            if(strcmp(select,"q") != 0)
            {
                printf("\nSelect a Serial Number (S.No) to Delete: ");
                scanf("%s", save); 
                menu_header("Delete Contact: "); 
                for(int i = 0; i < address_book -> count; ++i)
                {
                    if(search(save, address_book, address_book -> count, 4 ,"Serial", e_search) == e_success)
                    {
                        while(strcmp(choice,"0") != 0)
                        {
                            menu_header("Delete Contact: ");
                            printf("\n0. Back");
                            printf("\n1. Name       : %s", ((i) + contactInfo) -> name);
                            printf("\n2. Phone No 1 : %s", ((i) + contactInfo) -> phone_numbers[0]);
                            int numberOfEmails = 1; 
                            int numberOfPhones = 1;
                            int count = 3; 

                            for(int j = 0; j <= 4; ++j)
                            {
                                if(strcmp((i+contactInfo) -> phone_numbers[j], " ") != 0)
                                {
                                    printf("\n Phone No %d: %s", j+1, (i + contactInfo) -> phone_numbers[1]);
                                    numberOfPhones = numberOfPhones + 1;
                                    count = count + 1;
                                }
                            }//end for

                            printf("\n3. Email ID 1 : %s", ((i)+contactInfo)->email_addresses[0]);
                            for(int j=1; j<5;++j)
                            {
                                if(strcmp((i+contactInfo)->email_addresses[j], " ") !=0)
                                {
                                    printf("\n  Email No %d  :  %s", j+1,(i+contactInfo) -> email_addresses[j]);
                                    numberOfEmails = numberOfEmails + 1;
                                    count = count + 1;
                                }
                            }//end for

                            printf("\n\nPress Y to delete. [Press any key to ignore] :\n ");
                            scanf("%s", choice);
                            if(strcmp(choice, "Y") == 0)
                            {
                                int number = 0;
                                ContactInfo info; 

                                for(int i = 0; i < address_book -> count; ++i)
                                {
                                    if(address_book -> list[i].si_no == atoi(save))
                                    {
                                        info = address_book -> list[i];
                                        number = i;
                                    }
                                }
                                for(int i = number; i < address_book -> count - 1; ++i)
                                {
                                    address_book -> list[i] = address_book -> list[i + 1];
                                }
                                --address_book -> count;
                            }
                            strcpy(choice,"0");
                            strcpy(select,"q");
                        }//end while
                    }
                }
            }
        }
    }while(strcmp(choice,"0") != 0);
}//end delete_contact
