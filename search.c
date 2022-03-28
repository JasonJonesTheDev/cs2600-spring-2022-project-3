#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
//#include "abk_log.h"
#include "address_book_menu.h"
#include "address_book.h"

void main(AddressBook *address_book) {
	search_contact(address_book);
}

Status search(AddressBook *address_book, char title, int i, char save[255], int serial, Modes mode) {
	FILE *fp = fopen(DEFAULT_FILE, "r");
	ContactInfo contact = address_book -> list[i];
	ContactInfo contactPtr = address_book -> list[i];
	int Found = 0;

    while(mode == e_search) {
        if(fp == NULL){
            printf("**The file is empty** !!\n\n");
        } else {
			while(!feof(fp) && Found == 0) {
				switch(title) {
					case '0':
					printf("Back\n");
					break;
					case '1':
					if(strcmp(&address_book->list[i].name[0][0], save) == 0) {
						Found=1;
						printf("The Name is:               %s\n", contact.name);
						printf("The phone number is:       %s\n", contact.phone_numbers);
						printf("The e-mail is:             %s\n", contact.email_addresses);
						printf("The serial number is:      %f\n", contactPtr.si_no);
					} else {
						Found = 0;
						printf("**There is no such Entry**\n");
					}
					break;
					case '2':
					if(strcmp(&address_book->list[i].phone_numbers[0][0], save) == 0) {
						Found=1;
						printf("The Name is:               %s\n", contact.name);
						printf("The phone number is:       %s\n", contact.phone_numbers);
						printf("The e-mail is:             %s\n", contact.email_addresses);
						printf("The serial number is:      %f\n", contactPtr.si_no);
					} else {
						Found = 0;
						printf("**There is no such Entry**\n");
					}
					break;
					case '3':
					if(strcmp(&address_book->list[i].email_addresses[0][0], save) == 0) {
						Found=1;
						printf("The Name is:               %s\n", contact.name);
						printf("The phone number is:       %s\n", contact.phone_numbers);
						printf("The e-mail is:             %s\n", contact.email_addresses);
						printf("The serial number is:      %f\n", contactPtr.si_no);
					} else {
						Found = 0;
						printf("**There is no such Entry**\n");
					}
					break;
					case '4':
					if(contact.si_no == serial) {
						Found=1;
						printf("The Name is:               %s\n", contact.name);
						printf("The phone number is:       %s\n", contact.phone_numbers);
						printf("The e-mail is:             %s\n", contact.email_addresses);
						printf("The serial number is:      %f\n", contact.si_no);
					} else {
						Found = 0;
						printf("**There is no such Entry**\n");
					}
					break;
					default:
					printf("Error");
				}
			}
			fclose(address_book->fp);
		}
    }  
	return e_success;
}

Status search_contact(AddressBook *address_book) {
    char save[255];
    int serial = 0;
	char choice = '0';
	int i;
	Modes mode = e_search;

    printf("#######  Address Book  #######\n");
	printf("Search contact to search by: \n");
	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n");
	a: printf("Please select an option: ");
	scanf("%s", &choice);

    while(choice == '0') {
        switch(choice) {
            case '0':
            return e_back;
			break;
            case '1':
            printf("What name would you like to search for:\n");
            scanf("%s\n", &save);
			for (int i = 0; i < address_book -> count; i++)
			{
				ContactInfo contact = address_book -> list[i];
				for (int j = 0; j < NAME_COUNT; j++)
				{
					serial = 0;
                    search(address_book, choice, i, save, serial, mode);
					j = NAME_COUNT;
					i = address_book -> count;
					break;
				}
			}
			break;
            case '2':
            printf("What phone number would you like to search for:\n");
            scanf("%s\n", &save);
			for (int i = 0; i < address_book -> count; i++)
			{
				ContactInfo contact = address_book -> list[i];
				for (int j = 0; j < PHONE_NUMBER_COUNT; j++)
				{
					serial = 0;
                    search(address_book, choice, i, save, serial, mode);
					j = NAME_COUNT;
					i = address_book -> count;
					break;
				}
			}
			break;
            case '3':
            printf("What email address would you like to search for:\n");
            scanf("%s\n", &save);
			for (int i = 0; i < address_book -> count; i++)
			{
				ContactInfo contact = address_book -> list[i];
				for (int j = 0; j < EMAIL_ID_COUNT; j++)
				{
					serial = 0;
                    search(address_book, choice, i, save, serial, mode);
					j = NAME_COUNT;
					i = address_book -> count;
					break;
				}
			}
			break;
            case '4':
            printf("What serial number would you like to search for:\n");
            scanf("%f\n", &serial);
			for (int i = 0; i < address_book -> count; i++)
			{
				ContactInfo contact = address_book -> list[i];
				if (serial == contact.si_no)
				{
					serial = serial;
                    search(address_book, choice, i, save, serial, mode);
					i = address_book -> count;
					break;
				}
			}
			break;
            default:
            goto a;
        }
        return e_success;
    }
}

// Status search(AddressBook *address_book, int i, char choice,) {
//     printf("hello world inside\n");
//     AddressBook * addressBook = address_book; 
//     ContactInfo contactPtr = address_book ->list;
//     printf("world hello\n");
//     int count = addressBook->count;
//     const char targetName[255];
//     const char targetPhone[255];
//     const char targetEmail[255];
//     int targetSerial = 0;
//     char choice = '0';
//     int i = 0;

//     switch(choice) {
//         case '0':
//         printf("Back\n");
//         return e_back;
//         break;
//         case '1':
            // printf("What name would you like to search for:\n");
            // scanf("%s\n", &targetName);

//             for(; i < count; i++) {
//                 if (strcmp((i+contactPtr)->name[i], targetName) == 0) {
//                     printf("Name: %s. Phone Number: %s. Email: %s. Serial Number: %f\n", (i+contactPtr)->name[i], (i+contactPtr)->phone_numbers[i], (i+contactPtr)->email_addresses[i], (i+contactPtr)->si_no);
//                     return e_success;
//                 }
//             }
//             printf("Name not found\n");
//             return e_fail;
//         break;
//         case '2':
//             printf("What phone number would you like to search for:\n");
//             scanf("%s\n", targetPhone);

//             for(; i < count; i++) {
//                 if (strcmp((i+contactPtr)->phone_numbers[i], targetPhone) == 0) {
//                     printf("Name: %s. Phone Number: %s. Email: %s. Serial Number: %f\n", (i+contactPtr)->name[i], (i+contactPtr)->phone_numbers[i], (i+contactPtr)->email_addresses[i], (i+contactPtr)->si_no);
//                     return e_success;
//                 }
//             }
//             printf("Phone number not found\n");
//             return e_fail;
//         break;
//         case '3':
//             printf("What phone number would you like to search for:\n");
//             scanf("%s\n", targetEmail);
            
//             for(; i < count; i++) {
//                 if (strcmp((i+contactPtr)->email_addresses[i], targetEmail) == 0) {
//                     printf("Name: %s. Phone Number: %s. Email: %s. Serial Number: %f\n", (i+contactPtr)->name[i], (i+contactPtr)->phone_numbers[i], (i+contactPtr)->email_addresses[i], (i+contactPtr)->si_no);
//                     return e_success;
//                 }
//             }
//             printf("Email address not found\n");
//             return e_fail;
//         break;
//         case '4':
//             printf("What serial number would you like to search for:\n");
//             scanf("%s\n", targetSerial);
            
//             for(; i < count; i++) {
//                 if ((i+contactPtr)->si_no == targetSerial) {
//                     printf("Name: %s. Phone Number: %s. Email: %s. Serial Number: %f\n", (i+contactPtr)->name[i], (i+contactPtr)->phone_numbers[i], (i+contactPtr)->email_addresses[i], (i+contactPtr)->si_no);
//                     return e_success;
//                 }
//             }
//             printf("Serial number not found\n");
//             return e_fail;
//         break;
//         default:
//         printf("Error: Please enter a valid option.\n");
//         search_contact(address_book);
//     }
// }