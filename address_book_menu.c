#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book.h"
#include "address_book_fops.h"
#include "address_book_menu.h"

int get_option(int type, const char *msg)
{
    /*
     * Mutilfuction user intractions like
     * Just an enter key detection
     * Read an number
     * Read a charcter
     */

    /* Fill the code to add above functionality */
}

Status save_prompt(AddressBook *address_book)
{
    char option;

    do
    {
        main_menu();

        option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

        if (option == 'Y')
        {
            save_file(address_book);
            printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

            break;
        }
    } while (option != 'N');

    free(address_book->list);

    return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
    /*
     * Add code to list all the contacts availabe in address_book.csv file
     * Should be menu based
     * The menu provide navigation option if the entries increase the page size
     */

    return e_success;
}

void menu_header(const char *str)
{
    fflush(stdout);

    system("clear");

    printf("#######  Address Book  #######\n");
    if (str != '\0')
    {
        printf("#######  %s\n", str);
    }
}

void main_menu(void)
{
    menu_header("Features:\n");

    printf("0. Exit\n");
    printf("1. Add Contact\n");
    printf("2. Search Contact\n");
    printf("3. Edit Contact\n");
    printf("4. Delete Contact\n");
    printf("5. List Contacts\n");
    printf("6. Save\n");
    printf("\n");
    printf("Please select an option: ");
}

Status menu(AddressBook *address_book)
{
    ContactInfo backup;
    Status ret;
    int option;

    do
    {
        main_menu();

        option = get_option(NUM, "");

        if ((address_book->count == 0) && (option != e_add_contact))
        {
            get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

            continue;
        }

        switch (option)
        {
        case e_add_contact:
            /* Add your implementation to call add_contacts function here */
            break;
        case e_search_contact:
            search_contact(address_book);
            break;
        case e_edit_contact:
            edit_contact(address_book);
            break;
        case e_delete_contact:
            delete_contact(address_book);
            break;
        case e_list_contacts:
            break;
            /* Add your implementation to call list_contacts function here */
        case e_save:
            save_file(address_book);
            break;
        case e_exit:
            break;
        }
    } while (option != e_exit);

    return e_success;
}

Status add_contacts(AddressBook *address_book)
{
    char choice[255];
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

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
    /* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
    /* Add the functionality for search contacts here */
}

Status edit_contact(AddressBook *address_book)
{
    /* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{ 
   ContactInfo * contactInfo = address_book -> list; 
    char save[255];
    char searchBy[255];
    char choice[10];

    do
    {
        menu_header("Search Contact to Delete by: "); 
        printf("\n0. Back\n");
        printf("1. Name\n");
        printf("2. Phone No 1\n");
        printf("3. Email ID 1\n");
        printf("4. Serial No\n");
        printf("Please select an option for search: "); 
        scanf("%s", choice); 
        
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

        while(strcmp(choice,"q") != 0)
        {
            printf("\nPress: [s] = Select, [q] to Cancel: ");
            scanf("%s", choice);
            if(strcmp(choice,"q") != 0)
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
                            strcpy(choice,"q");
                        }//end while
                    }
                }
            }
        }
    }while(strcmp(choice,"0") != 0);
}//end delete_contact
