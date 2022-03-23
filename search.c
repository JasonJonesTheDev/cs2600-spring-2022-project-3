#include <string.h>
#include<stdio.h> // input/output
#include<stdlib.h>  //libraries
#include "address_book.h"

int SearchContact(AddressBook* address_book, int count) {
    char choice;

    ContactInfo * contactInfo = address_book -> list; 

   while(strcmp(choice,'0') != 0) {
        /* Select how to search the specific contact by name, by phone number, email id, or by serial number */
        selectSearch:
        menu_header("Select Contact to search by: "); 
        printf("\n0. Back\n");
        printf("1. Name\n");
        printf("2. Phone No\n");
        printf("3. Email ID\n");
        printf("4. Serial No\n");
        prontf("Please select an option:\n "); 
        scanf("%c", choice); 

        switch(choice) {
        case 1:
        searchByName(contactInfo);
        break;
        case 2:
        searchByPhone(contactInfo);
        break;
        case 3:
        searchByEmailId(contactInfo);
        break;
        case 4:
        searchBySerialNum(contactInfo);
        break;
        default:
        printf("Error: Please enter a valid option.");
        goto selectSearch;
    }
   }
}

char searchByName(ContactInfo * contactInfo) {

}

char searchByPhone(ContactInfo * contactInfo) {

}

int searchByEmailId(ContactInfo * contactInfo) {

}

int searchBySerialNum(ContactInfo * contactInfo) {

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