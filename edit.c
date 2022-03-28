#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book.h"
#include "address_book_fops.h"
#include "address_book_menu.h"

Status edit_contact(AddressBook *address_book)
{
    char save[200];
	int choice;
	int i;

    printf("#######  Address Book  #######\n");
	printf("Search contact to edit by: \n");
	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n");
	a: printf("Please select an option: ");
	scanf("%d", &choice);

	while(choice != 0)
	{
		if(choice != 0 && choice != 1 && choice != 2 && choice != 3 && choice != 4)
		{
			goto a;
		}
		
		if(choice == 0)
		{
			return e_back;
			break;
		}

		else if(choice == 1)
		{
			printf("\nEnter the name: ");
			scanf("%s", &save);
			for (int i = 0; i < address_book -> count; i++)
			{
				ContactInfo contact = address_book -> list[i];
				for (int j = 0; j < NAME_COUNT; j++)
				{
                        edit(address_book, i, save, choice, 0);
						j = NAME_COUNT;
						i = address_book -> count;
						break;
				}
			}
			break;
		}

		else if(choice == 2)
		{
			printf("\nEnter the Phone No: ");
			scanf("%s", &save);
			for (int i = 0; i < address_book -> count; i++)
			{
				ContactInfo contact = address_book -> list[i];
				for (int j = 0; j < PHONE_NUMBER_COUNT; j++)
				{
						edit(address_book, i, save, choice, 0);
						j = NAME_COUNT;
						i = address_book -> count;
						break;
				}
			}
			break;
		}

		else if(choice == 3)
		{
			printf("\nEnter the Email ID: ");
			scanf("%s", &save);
			for (int i = 0; i < address_book -> count; i++)
			{
				ContactInfo contact = address_book -> list[i];
				for (int j = 0; j < EMAIL_ID_COUNT; j++)
				{
                        edit(address_book, i, save, choice, 0);
						j = NAME_COUNT;
						i = address_book -> count;
						break;
				}
			}
			break;
		}

		else if(choice == 4)
		{
			printf("\nEnter the Serial No: ");
			int serial;
			scanf("%d", &serial);

			for (int i = 0; i < address_book -> count; i++)
			{
				ContactInfo contact = address_book -> list[i];
				if (serial == contact.si_no)
				{
					char s[200];
					sprintf(s, "&d", serial);
                    edit(address_book, i, s, choice, serial);
					i = address_book -> count;
					break;
				}
			}
			break;
		}
	}
	return e_success;
}

Status edit(AddressBook *address_book, int index, char save[200], int choice, int serialNo)
{
    ContactInfo contact;
	int option;
    char input;
	int serialInput;
	int result = 0;

	if(choice == 1)
	{
		for (int i = 0; i < address_book->count; i++)
		{
			contact = address_book->list[i];
			for (int j = 0; j < NAME_COUNT; j++)
			{
				if (strcmp(save, &contact.name[j][0]) == 0)
				{
					result = 1;
					j = NAME_COUNT; // to exit inner loop
					i = address_book->count; //to exit outer loop
					break;
				}
			}
		}
	}

	else if(choice == 2)
	{
		for (int i = 0; i < address_book->count; i++)
		{
			contact = address_book->list[i];
			for (int j = 0; j < PHONE_NUMBER_COUNT; j++)
			{
				if (strcmp(save, &contact.phone_numbers[j][0]) == 0)
				{
					result = 1;
					j = NAME_COUNT; // to exit inner loop
					i = address_book->count; //to exit outer loop
					break;
				}
			}
		}
	}

	else if(choice == 3)
	{
		for (int i = 0; i < address_book->count; i++)
		{
			contact = address_book->list[i];
			for (int j = 0; j < PHONE_NUMBER_COUNT; j++)
			{
				if (strcmp(save, &contact.email_addresses[j][0]) == 0)
				{
					result = 1;
					j = NAME_COUNT; // to exit inner loop
					i = address_book->count; //to exit outer loop
					break;
				}
			}
		}
	}
	else if(choice == 4)
	{
		char *ptr;
		int s = strtol(save, &ptr, 10);
		for (int i = 0; i < address_book->count; i++)
		{
			contact = address_book->list[i];
			if (serialNo == contact.si_no)
			{
				result = 1;
				i = address_book->count; //to exit outer loop
				break;
			}
		}
	}

	printf("===========================================================================================================\n");
	printf(":S.No  :Name                            :Phone No                        :Email ID                        :\n");
	printf("===========================================================================================================\n");
	printf(":%d", contact.si_no);
	if (contact.si_no < 10)
	{
		for (int i = 0; i < 5; i++)
			printf(" ");
	}
		else
		{
			for (int i = 0; i < 4; i++)
			printf(" ");
		}
		printf(":%s", &contact.name[0][0]);
		for (int i = 32 - strlen(&contact.name[0][0]); i > 0; i--)
		{
			printf(" ");
		}
		int numberOfPhones = sizeof contact.phone_numbers / sizeof *contact.phone_numbers;
		int numberOfEmails = sizeof contact.email_addresses / sizeof *contact.email_addresses;
		int phoneCount = 0;
		int emailCount = 0;

		if (numberOfPhones > 0)
		{
			printf(":%s", &contact.phone_numbers[0][0]);
			phoneCount++;
			for (int i = 32 - strlen(&contact.phone_numbers[0][0]); i > 0; i--)
			{
				printf(" ");
			}
		}
			else
			for (int i = 32 ; i > 0; i--)
			{
				printf(" ");
			}

			if (numberOfEmails > 0)
			{
				printf(":%s", &contact.email_addresses[0][0]);
				emailCount++;
				for (int i = 32 - strlen(&contact.email_addresses[0][0]); i > 0; i--)
					printf(" ");
			}
			else
				for (int i = 32 ; i > 0; i--)
					printf(" ");
			printf(":\n"); 

			for (int k = 0; k < 4; k++)
			{
				printf(":      :                                ");

				if (phoneCount < numberOfPhones)
				{
					printf(":%s", &contact.phone_numbers[phoneCount][0]);
					for (int i = 32 - strlen(&contact.phone_numbers[phoneCount][0]); i > 0; i--)
						printf(" ");
					phoneCount++;
				}
				else
					for (int i = 32 ; i > 0; i--)
						printf(" ");

				if (emailCount < numberOfEmails)
				{
					printf(":%s", &contact.email_addresses[emailCount][0]);
					for (int i = 32 - strlen(&contact.email_addresses[emailCount][0]); i > 0; i--)
						printf(" ");
					emailCount++;
				}
				else
					for (int i = 32 ; i > 0; i--)
						printf(" ");
				printf(":\n");
			}

			printf("===========================================================================================================\n");

		if (index < (address_book->count-1)) 
		{
			index++;
		}	
		printf("Press:  [s] = Select.  [q] | Cancel: ");
        scanf(" %c", &input);
        if(input == 's')
        {
            printf("Select a Serial Number (S.No) to edit: ");
        }
		else if(input == 'q')
		{
			return e_success;
		}
		scanf("%d", &serialInput);
		serialInput --;
		index = serialInput;
        do
        {
			printf("Edit Contact:\n");
			printf("0. Back\n");
			printf("1. Name\t\t: %s\n", address_book->list[index].name[0]);
			printf("2. Phone No 1\t: %s\n", address_book->list[index].phone_numbers[0]);
			
        	if (numberOfPhones > 1)
        	{
            	for (int i = 1; i < numberOfPhones; i++)
            	{
					if(strcmp (address_book->list[index].phone_numbers[i], "") == 0)
					{
						continue;
					}
					else
					{
						printf("\t    %d\t: %s\n", i + 1, address_book->list[index].phone_numbers[i]);
					}
            	}
        	}

		printf("3. Email ID 1\t: %s\n", address_book->list[index].email_addresses[0]);
        if (numberOfEmails > 1)
        {
            for (int i = 1; i < numberOfEmails; i++)
            {
				if(strcmp (address_book->list[index].email_addresses[i], "") == 0)
				{
					continue;
				}
				else
				{
					printf("\t    %d\t: %s\n", i + 1, address_book->list[index].email_addresses[i]);
				}
            }
        }
		printf("\nPlease select an option: ");
		scanf("%d", &option);

		if(option == 0)
		{
			break;
		}
		if(option == 1)
		{
			printf("Enter the name: ");
			scanf("%s", &address_book->list[index].name[0][0]);
			if (strlen(*address_book->list[index].name) > NAME_LEN)
			{
				printf("ERROR. Invalid Length of Name. Please enter a key to continue: ");
				getchar();
			}
		}

		if(option == 2)
		{
			if (phoneCount < PHONE_NUMBER_COUNT)
			{
				printf("Enter Phone Number %d: ", phoneCount + 1);
				scanf("%s", &address_book->list[index].phone_numbers[phoneCount][0]);
				if (strlen(address_book->list[index].phone_numbers[phoneCount]) > NUMBER_LEN)
				{
					printf("ERROR. Invalid Length of Phone Number. Please enter a key to continue: ");
					getchar();
				}
				else
					phoneCount++;
			}
			else
			{
				printf("ERROR. You have reached maximum number of Phone Numbers. Please enter a key to continue: ");
				getchar();
			}
		}
		if(option == 3)
		{
			if (emailCount < EMAIL_ID_COUNT)
			{
				printf("Enter Email ID %d: ", emailCount + 1);
				scanf("%s", &address_book->list[index].email_addresses[emailCount][0]);
				if (strlen(&address_book->list[index].email_addresses[emailCount][0]) > EMAIL_ID_LEN)
				{
					printf("ERROR. Invalid Length of Email. Please enter a key to continue: ");
					getchar();
				}
				else
					emailCount++;
			}
			else
			{
				printf("ERROR. You have reached maximum number of Emails. Please enter a key to continue: ");
				getchar();
			}
		}
		getchar();
	} while (option != 0);
    return e_success;
}