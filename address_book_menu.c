#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
//#include "abk_log.h"
#include "address_book_menu.h"
#include "address_book.h"

int get_option(int type, const char *msg)
{
    /*
     * Mutilfuction user intractions like
     * Just an enter key detection
     * Read an number
     * Read a charcter
     */

    /* Fill the code to add above functionality */
    return 0;
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
    //check if addressbook is NULL
    if (address_book == NULL)
        return e_fail;
    if (address_book->list == NULL) 
        return e_fail;

    //reallocate contact list with 1 more on size
    address_book->count += 1;
    address_book->list = realloc(address_book->list, sizeof(ContactInfo) * address_book->count);

    //take user input for name, nums, emails
    char nameInput[NAME_LEN];
    char numberInput[PHONE_NUMBER_COUNT][NUMBER_LEN];
    char emailInput[EMAIL_ID_COUNT][EMAIL_ID_LEN];
    int nameCount = 0;
    int numberCount = 0;
    int emailCount = 0;
    int choice = -1;
    int quit = 0;
    do {
        printf("\nto go back enter 0\nto input name enter 1\nto input number #%d enter 2\nto input email #%d enter 3\n", numberCount+1, emailCount+1);
        scanf(" %d", &choice);
        switch (choice) {
            case 0:
                printf("quitting\n");
                quit = 1;
                break;
            case 1:
                if (nameCount > 0) {
                    printf("max number of names already entered\n");
                    break;
                } else {
                    printf("adding name\n");
                    scanf(" %[^\n]%*c", nameInput);
                    strcpy(((address_book->list)+(address_book->count - 1))->name[0], nameInput);
                    printf("entered name: %s\n", ((address_book->list)+(address_book->count - 1))->name[0]);
                    nameCount++;
                }
                break;
            case 2:
                if (numberCount > 4) {
                    printf("max number of phone numbers already entered\n");
                    break;
                } else {
                    printf("adding number #%d", numberCount+1);
                    scanf(" %s", numberInput[numberCount]);
                    strcpy(((address_book->list)+(address_book->count - 1))->phone_numbers[numberCount], numberInput[numberCount]);
                    printf("entered number: %s\n", ((address_book->list)+(address_book->count - 1))->phone_numbers[numberCount]);
                    numberCount++;
                }
                break;
            case 3:
                if (emailCount > 4) {
                    printf("max number of emails already entered\n");
                } else {
                    printf("adding email #%d", emailCount+1);
                    scanf(" %s", emailInput[emailCount]);
                    strcpy(((address_book->list)+(address_book->count - 1))->email_addresses[emailCount], emailInput[emailCount]);
                    printf("entered email: %s\n", ((address_book->list)+(address_book->count - 1))->email_addresses[emailCount]);
                    emailCount++;
                }
                break;
            default:
                printf("error making choice, %d", choice);
                break;

        }
        printf("\n");
    } while (quit == 0);
    //setting serial number
    ((address_book->list) + (address_book->count - 1))->si_no = address_book->count;
    
    return e_success;
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
    /* Add the functionality for adding contacts here */
    return e_success;
}

Status search_contact(AddressBook *address_book)
{
    /* Add the functionality for search contacts here */
    return e_success;
}

Status edit_contact(AddressBook *address_book)
{
    /* Add the functionality for edit contacts here */
    return e_success;
}

Status delete_contact(AddressBook *address_book)
{
    /* Add the functionality for delete contacts here */
    return e_success;
}

int main() {
    AddressBook address_book;
    load_file(&address_book);
    add_contacts(&address_book);
    save_file(&address_book);
}
