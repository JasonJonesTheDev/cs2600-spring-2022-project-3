#include <string.h>
#include<stdio.h> // input/output
#include<stdlib.h>  //libraries
#include "address_book.h"

int SearchContact(AddressBook* address_book, int count) {
    ContactInfo *name[NAME_COUNT][NAME_LEN];
    char choice;

    ContactInfo * contactInfo = address_book -> list;
    AddressBook * addressBook = address_book; 

   while(strcmp(choice,'0') != 0) {
        /* Select how to search the specific contact by name, by phone number, email id, or by serial number */
        selectSearch:
        menu_header("Select Contact to search by: "); 
        printf("\n0. Back\n");
        printf("1. Name\n");
        printf("2. Phone No\n");
        printf("3. Email ID\n");
        printf("4. Serial No\n");
        printf("Please select an option:\n "); 
        scanf("%c", choice);

        switch(choice) {
        case 1:
        searchByName(addressBook, contactInfo, count);
        break;
        case 2:
        searchByPhone(addressBook, contactInfo, count);
        break;
        case 3:
        searchByEmailId(addressBook);
        break;
        case 4:
        searchBySerialNum(addressBook);
        break;
        default:
        printf("Error: Please enter a valid option.\n");
        goto selectSearch;
    }
    
   }
}

char targetName() {
    char name;
    char targetName;
    printf("What name would you like to search for:\n");
    scanf("%s\n", name);
    targetName = name;
    return targetName;
}

char targetPhone() {
    char phone;
    char targetPhone;
    printf("What phone number would you like to search for:\n");
    scanf("%s\n", phone);
    targetPhone = phone;
    return targetPhone;
}

char targetEmail() {
    char email;
    char targetEmail;
    printf("What phone number would you like to search for:\n");
    scanf("%s\n", email);
    targetEmail = email;
    return targetEmail;
}

int targetSerial() {
    int serial;
    int targetSerial;
    printf("What serial number would you like to search for:\n");
    scanf("%s\n", serial);
    targetSerial = serial;
    return targetSerial;
}

char searchByName(AddressBook * addressBook, ContactInfo * contactInfo, int count) {
    for(; contactInfo < addressBook->count; addressBook++) {
        if (strcmp(contactInfo->name, targetName()) == 0) {
            printf("Name Search: %s\n", contactInfo->name);
            return contactInfo->name;
        }
    }
    printf("Name not found\n");
    return NULL;
}

char searchByPhone(AddressBook * addressBook, ContactInfo * contactInfo, int count) {
    for(; contactInfo < addressBook->count; contactInfo++) {
        if (strcmp(contactInfo->phone_numbers, targetPhone()) == 0) {
            printf("Phone Search: %s\n", contactInfo->phone_numbers);
            return contactInfo->phone_numbers;
        }
    }
    printf("Phone number not found\n");
    return NULL;
}

char searchByEmailId(AddressBook * addressBook, ContactInfo * contactInfo, int count) {
    for(; contactInfo < addressBook->count; contactInfo++) {
        if (strcmp(contactInfo->email_addresses, targetEmail()) == 0) {
            printf("Email Address Search: %s\n", contactInfo->email_addresses);
            return contactInfo->email_addresses;
        }
    }
    printf("Email address not found\n");
    return NULL;
}

int searchBySerialNum(AddressBook * addressBook, ContactInfo * contactInfo, int count) {
    for(; contactInfo < addressBook->count; contactInfo++) {
        if (strcmp(contactInfo->si_no, targetSerial()) == 0) {
            printf("Serial Number Search: %s\n", contactInfo->si_no);
            return contactInfo->si_no;
        }
    }
    printf("Serial number not found\n");
}

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