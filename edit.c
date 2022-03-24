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
					if (strcmp(save, &contact.name[j][i]) == 0)
					{
                        edit(address_book, i);
						j = NAME_COUNT;
						i = address_book -> count;
						break;
					}
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
					if (strcmp(save, &contact.phone_numbers[j][i]) == 0)
					{
						j = NAME_COUNT;
						i = address_book -> count;
						break;
					}
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
					if (strcmp(save, &contact.email_addresses[j][i]) == 0)
					{
						j = NAME_COUNT;
						i = address_book -> count;
						break;
					}
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
					i = address_book -> count;
					break;
				}
			}
			break;
		}
	}
	return e_success;
}

Status edit(AddressBook *address_book, int index)
{
    ContactInfo contact;
	int option;
    char input;
	int phoneCount = 0;
	int numberOfPhones = sizeof address_book->list[index].phone_numbers / sizeof *address_book->list[index].phone_numbers;
	int emailCount = 0;
	int numberOfEmails = sizeof address_book->list[index].email_addresses / sizeof *address_book->list[index].email_addresses;
		
	printf("===========================================================================================================\n");
	printf(":S.No  :Name                            :Phone No                        :Email ID                        :\n");
	printf("===========================================================================================================\n");

	printf(":%d", address_book->list[index].si_no);
	if (address_book->list[index].si_no < 10) 
	{
		for (int i = 0; i < 5; i++)
		{
			printf(" ");
		}
	} 
	else 
	{
		for (int i = 0; i < 4; i++)
		{
			printf(" ");
		}
	}
	printf(":%s", &address_book->list[index].name[0][0]);
	for (int i = 32 - strlen(&address_book->list[index].name[0][0]); i > 0; i--) 
	{
		printf(" ");
	}
	if (numberOfPhones > 0) 
	{
		printf(":%s", &address_book->list[index].phone_numbers[0][0]);
		phoneCount++;
		for (int i = 32 - strlen(&address_book->list[index].phone_numbers[0][0]); i > 0; i--)
		{
			printf(" ");
		}
	} 
	else 
	{
		for (int i = 32 ; i > 0; i--) 
		{
			printf(" ");
		}
	}

	if (numberOfEmails > 0) 
	{
		printf(":%s", &address_book->list[index].email_addresses[0][0]);
		emailCount++;
		for (int i = 32 - strlen(&address_book->list[index].email_addresses[0][0]); i > 0; i--)
		{
			printf(" ");
		}
	} 
	else 
	{
		for (int i = 32 ; i > 0; i--)
		{
			printf(" ");
		}
	}
	printf(":\n");

	for (int k = 0; k < 4; k++)
	{
		printf(":      :                                ");

		if (phoneCount < numberOfPhones) 
		{
			printf(":%s", &address_book->list[index].phone_numbers[phoneCount][0]);
			for (int m = 32 - strlen(&address_book->list[index].phone_numbers[phoneCount][0]); m > 0; m--)
			{
				printf(" ");
			}
			phoneCount++;
		} 
		else
		{
			for (int n = 32 ; n > 0; n--)
			{
				printf(" ");
			}
		}
		if (emailCount < numberOfEmails)
		{
			printf(":%s", &address_book->list[index].email_addresses[emailCount][0]);
			for (int l = 32 - strlen(&address_book->list[index].email_addresses[emailCount][0]); l > 0; l--)
			{
				printf(" ");
			}	
			emailCount++;
		} 
		else
		{
			for (int p = 32 ; p > 0; p--)
			{
				printf(" ");
			}
		}
		printf(":\n"); //end of row
		}
		printf("===========================================================================================================\n");
        printf("Press:  [s] = Select.  [q] | Cancel :");
        scanf(" %c", &input);
        if(input == 's')
        {
            printf("a");
        }
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

	} while (option != 0);
    return e_success;
}