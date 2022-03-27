#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
//#include "abk_log.h"
#include "address_book_menu.h"
#include "address_book.h"

void main(AddressBook* address_book) {
    printf("hello world\n");
    search_contact(address_book);
}

Status search_contact(AddressBook* address_book) {
    printf("hello world inside\n");
    AddressBook * addressBook = address_book; 
    ContactInfo *contactPtr = address_book ->list;
    printf("world hello\n");
    int count = addressBook->count;
    const char targetName[255];
    const char targetPhone[255];
    const char targetEmail[255];
    int targetSerial = 0;
    char choice = '0';
    int i = 0;
    

    /* Select how to search the specific contact by name, by phone number, email id, or by serial number */
    /*// printf("Select Contact to search by: \n");
    // printf("0. Back\n");
    // printf("1. Name\n");
    // printf("2. Phone No\n");
    // printf("3. Email ID\n");
    // printf("4. Serial No\n");
    // printf("Please select an option number:\n"); 
    // scanf("%s", &choice);*/

    printf("hollow world\n");

    switch(choice) {
        case '0':
        printf("Back\n");
        return e_back;
        break;
        case '1':
            printf("What name would you like to search for:\n");
            scanf("%s\n", &targetName);

            for(; i < count; i++) {
                if (strcmp((i+contactPtr)->name[i], targetName) == 0) {
                    printf("Name: %s. Phone Number: %s. Email: %s. Serial Number: %f\n", (i+contactPtr)->name[i], (i+contactPtr)->phone_numbers[i], (i+contactPtr)->email_addresses[i], (i+contactPtr)->si_no);
                    return e_success;
                }
            }
            printf("Name not found\n");
            return e_fail;
        break;
        case '2':
            printf("What phone number would you like to search for:\n");
            scanf("%s\n", targetPhone);

            for(; i < count; i++) {
                if (strcmp((i+contactPtr)->phone_numbers[i], targetPhone) == 0) {
                    printf("Name: %s. Phone Number: %s. Email: %s. Serial Number: %f\n", (i+contactPtr)->name[i], (i+contactPtr)->phone_numbers[i], (i+contactPtr)->email_addresses[i], (i+contactPtr)->si_no);
                    return e_success;
                }
            }
            printf("Phone number not found\n");
            return e_fail;
        break;
        case '3':
            printf("What phone number would you like to search for:\n");
            scanf("%s\n", targetEmail);
            
            for(; i < count; i++) {
                if (strcmp((i+contactPtr)->email_addresses[i], targetEmail) == 0) {
                    printf("Name: %s. Phone Number: %s. Email: %s. Serial Number: %f\n", (i+contactPtr)->name[i], (i+contactPtr)->phone_numbers[i], (i+contactPtr)->email_addresses[i], (i+contactPtr)->si_no);
                    return e_success;
                }
            }
            printf("Email address not found\n");
            return e_fail;
        break;
        case '4':
            printf("What serial number would you like to search for:\n");
            scanf("%s\n", targetSerial);
            
            for(; i < count; i++) {
                if ((i+contactPtr)->si_no == targetSerial) {
                    printf("Name: %s. Phone Number: %s. Email: %s. Serial Number: %f\n", (i+contactPtr)->name[i], (i+contactPtr)->phone_numbers[i], (i+contactPtr)->email_addresses[i], (i+contactPtr)->si_no);
                    return e_success;
                }
            }
            printf("Serial number not found\n");
            return e_fail;
        break;
        default:
        printf("Error: Please enter a valid option.\n");
        search_contact(address_book);
    }
}