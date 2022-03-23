#include <string.h>
#include<stdio.h> // input/output
#include<stdlib.h>  //libraries
#include "address_book.h"
#include "address_book_menu.h"

void main() {
    extern AddressBook* address_book;
    AddressBook* addressBook = address_book;
    ContactInfo* contactInfo = address_book -> list;
    search_contact(address_book);
}

Status search_contact(AddressBook* address_book) {
    // ContactInfo *name[NAME_COUNT][NAME_LEN];
    // ContactInfo *phone_numbers[PHONE_NUMBER_COUNT][NUMBER_LEN];
    // ContactInfo *email_address[EMAIL_ID_COUNT][EMAIL_ID_LEN];
    // ContactInfo *si_no;
    char choice = 0;

    AddressBook * addressBook = address_book; 
    AddressBook * contactInfo = address_book -> list;
    ContactInfo * contactPtr = address_book -> list;
    int count = addressBook->count;

   while(strcmp(choice,'0') != 0) {
        /* Select how to search the specific contact by name, by phone number, email id, or by serial number */
        selectSearch:
        menu_header("Select Contact to search by: "); 
        printf("\n0. Back\n");
        printf("1. Name\n");
        printf("2. Phone No\n");
        printf("3. Email ID\n");
        printf("4. Serial No\n");
        printf("Please select an option number:\n "); 
        scanf("%c", choice);

        switch(choice) {
        case 1:
            char nameScan;
            char targetName;
            printf("What name would you like to search for:\n");
            scanf("%s\n", nameScan);
            targetName = nameScan;

            for(int i = 0; (i+contactInfo) < addressBook->count; i++) {
                if (strcmp(contactPtr->name, targetName) == 0) {
                    printf("Name Search: %c\n", contactPtr->name);
                    return contactPtr->name;
                }
            }
            printf("Name not found\n");
            return NULL;
        break;
        case 2:
            char phone;
            char targetPhone;
            printf("What phone number would you like to search for:\n");
            scanf("%s\n", phone);
            targetPhone = phone;

            for(int i = 0; (i+contactInfo) < addressBook->count; i++) {
                if (strcmp(contactPtr->phone_numbers, targetPhone) == 0) {
                    printf("Phone Search: %s\n", contactPtr->phone_numbers);
                    return contactPtr->phone_numbers;
                }
            }
            printf("Phone number not found\n");
            return NULL;
        break;
        case 3:
            char email;
            char targetEmail;
            printf("What phone number would you like to search for:\n");
            scanf("%s\n", email);
            targetEmail = email;
            
            for(int i = 0; (i+contactInfo) < addressBook->count; i++) {
                if (strcmp(contactPtr->email_address, targetEmail) == 0) {
                    printf("Email Address Search: %s\n", contactPtr->email_address);
                    return contactPtr->email_address;
                }
            }
            printf("Email address not found\n");
            return NULL;
        break;
        case 4:
            int serial;
            int targetSerial;
            printf("What serial number would you like to search for:\n");
            scanf("%s\n", serial);
            targetSerial = serial;
            
            for(int i = 0; (i+contactInfo) < addressBook->count; i++) {
                if (contactPtr->si_no == targetSerial) {
                    printf("Serial Number Search: %s\n", si_no);
                    return contactPtr->si_no;
                }
            }
            printf("Serial number not found\n");
        break;
        default:
        printf("Error: Please enter a valid option.\n");
        goto selectSearch;
    }
    
   }
}


// ContactInfo searchContactByName(AddressBook * addressBook, AddressBook * contactInfo, int count, ContactInfo *name[NAME_COUNT][NAME_LEN]) {
    
// }

// AddressBook searchContactByPhone(AddressBook * addressBook, ContactInfo * contactInfo, int count) {
   
// }

// AddressBook searchContactByEmailId(AddressBook * addressBook, ContactInfo * contactInfo, int count) {
    
// }

// AddressBook searchContactBySerialNum(AddressBook * addressBook, ContactInfo * contactInfo, int count) {
    
// }



// int SearchContact(pc, count, name);//Find the specified contact

// int FindContactByName(AddressBook* address_book, int count, const char* name)
// {
// 	pc->sz = 0;//No information by default
// 	memset(pc->data, 0, sizeof(pc->data));

// 	int i = 0;
// 	for (i = 0; i < pc->count; i++)
// 	{
// 		if (strcmp(pc->data[i].name, name) == 0)
// 		{
// 			return i;
// 		}
// 	}
// 	return -1;
// }

// int SearchContact(const struct AddressBook* pc, int count, ContactInfo* name)
// {
// 	char name[count];
// 	printf("Please enter the name of the person you want to find:");
// 	scanf("%s", name);
// 	int pos = FindContactByName(pc, count, name);
// 	if (pos == -1)
// 	{
// 		printf("No one was found\n");
// 	}
// 	else
// 	{
// 		printf("Contact name %s", name);
// 	}
// }