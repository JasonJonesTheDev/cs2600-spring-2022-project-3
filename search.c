#include <string.h>
#include <stdio.h> // input/output
#include <stdlib.h>  //libraries
#include <ctype.h>
//#include "address_book_fops.h" 
#include "address_book_menu.h"
#include "address_book.h"

// void main(AddressBook* address_book) {
//     search_contact(address_book);
// }

Status search_contact(AddressBook* address_book) {
    AddressBook * addressBook = address_book; 
    ContactInfo * contactInfo = address_book -> list;
    ContactInfo *contactPtr = address_book ->list;
    int count = addressBook->count;
    const char targetName[255];
    const char targetPhone[255];
    const char targetEmail[255];
    int targetSerial;
    char choice = '0';
    int i = 0;
    

    /* Select how to search the specific contact by name, by phone number, email id, or by serial number */
    SELECT_SEARCH:
    printf("Select Contact to search by: \n"
    "0. Back\n"
    "1. Name\n"
    "2. Phone No\n"
    "3. Email ID\n"
    "4. Serial No\n"
    "Please select an option number:\n"); 
    scanf("%s", &choice);

    switch(choice) {
        case 0:
            printf("Back\n");
            return e_back;
            break;
        case 1:
            printf("What name would you like to search for:\n");
            scanf("%s\n", &targetName);

            for(; i < count; i++) {
                if (strcmp((i+contactPtr)->name[i], targetName) == 0) {
                    printf("Name Search: %c\n", (i+contactPtr)->name[i]);
                    return e_success;
                }
            }
            printf("Name not found\n");
            return e_fail;
        break;
        case 2:
            printf("What phone number would you like to search for:\n");
            scanf("%s\n", targetPhone);

            for(; i < count; i++) {
                if (strcmp((i+contactPtr)->phone_numbers[i], targetPhone) == 0) {
                    printf("Phone Search: %s\n", contactPtr->phone_numbers[i]);
                    return e_success;
                }
            }
            printf("Phone number not found\n");
            return e_fail;
        break;
        case 3:
            printf("What phone number would you like to search for:\n");
            scanf("%s\n", targetEmail);
            
            for(; i < count; i++) {
                if (strcmp((i+contactPtr)->email_addresses[i], targetEmail) == 0) {
                    printf("Email Address Search: %s\n", (i+contactPtr)->email_addresses[i]);
                    return e_success;
                }
            }
            printf("Email address not found\n");
            return e_fail;
        break;
        case 4:
            printf("What serial number would you like to search for:\n");
            scanf("%s\n", targetSerial);
            
            for(; i < count; i++) {
                if ((i+contactPtr)->si_no == targetSerial) {
                    printf("Serial Number Search: %s\n", (i+contactPtr)->si_no);
                    return e_success;
                }
            }
            printf("Serial number not found\n");
            return e_fail;
        break;
        default:
        printf("Error: Please enter a valid option.\n");
        goto SELECT_SEARCH;
    }
}