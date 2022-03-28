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
    //return 0;

	/* Fill the code to add above functionality */
	char option[10];
	char *ptr;
	int result = 0;
	printf("%s", msg);
	if (type != 0)
	{
		scanf("%s", option);
	}
	if (type == 1)
	{
		result = atoi(option);
		printf("%d", result);
	}
	if (type == 2)
	{
		result = strtol(option, &ptr, 10);
		printf("%d\n", result);
		printf("%s\n", ptr);
		return *ptr;
	}
	return result;

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
	printf("\n===============================================================================================================================");
	printf("\n: S.No : Name                               : Phone No                           : Email ID                                   :");
	if (mode == e_list)
	{
		char space[20] = " ";
		for (int i = 0; i < address_book->count; i++)
		{
			ContactInfo tmp = address_book->list[i];
			printf("\n===============================================================================================================================\n");
			printf(":  %-3d : %-34s : %-34s : %-42s :", tmp.si_no, tmp.name, tmp.phone_numbers, tmp.email_addresses);
			for (int j = 1; j < 5; j++)
			{
				printf("\n:  %-3s : %-34s : %-34s : %-42s :",space, space,tmp.phone_numbers[j], tmp.email_addresses[j]);
			}
		}
		printf("\n===============================================================================================================================\n\n");
	}

	system("pause");
	printf("\n press enter to continue...\n");
	getchar();
	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	system("cls");

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
			add_contacts(address_book);
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
			list_contacts(address_book, "list_all", 0, "list", e_list);
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
    char nameInput[NAME_LEN] = "\0";
    char numberInput[PHONE_NUMBER_COUNT][NUMBER_LEN] = {"\0", "\0", "\0", "\0", "\0"};
    char emailInput[EMAIL_ID_COUNT][EMAIL_ID_LEN]= {"\0", "\0", "\0", "\0", "\0"};
    int nameCount = 0;
    int numberCount = 0;
    int emailCount = 0;
    int choice = -1;
    int quit = 0;

    do {
        printf("#######   Add Contact:\n\n0. Back\n1. Name        : %s\n2. Phone No #%d : %s %s %s %s %s\n3. Email ID #%d : %s %s %s %s %s\n\n", nameInput, numberCount+1, numberInput[0], numberInput[1], numberInput[2], numberInput[3], numberInput[4],emailCount+1, emailInput[0], emailInput[1], emailInput[2], emailInput[3], emailInput[4]);
        printf("Please select an option: ");
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
                    printf("Enter the name: ");
                    scanf(" %[^\n]%*c", nameInput);
                    strcpy(((address_book->list)+(address_book->count - 1))->name[0], nameInput);
                    //printf("entered name: %s\n", ((address_book->list)+(address_book->count - 1))->name[0]);
                    nameCount++;
                }
                break;
            case 2:
                if (numberCount > 4) {
                    printf("max number of phone numbers already entered\n");
                    break;
                } else {
                    printf("Enter phone number #%d: ", numberCount+1);
                    scanf(" %s", numberInput[numberCount]);
                    strcpy(((address_book->list)+(address_book->count - 1))->phone_numbers[numberCount], numberInput[numberCount]);
                    //printf("entered number: %s\n", ((address_book->list)+(address_book->count - 1))->phone_numbers[numberCount]);
                    numberCount++;
                }
                break;
            case 3:
                if (emailCount > 4) {
                    printf("max number of emails already entered\n");
                } else {
                    printf("Enter email ID #%d: ", emailCount+1);
                    scanf(" %s", emailInput[emailCount]);
                    strcpy(((address_book->list)+(address_book->count - 1))->email_addresses[emailCount], emailInput[emailCount]);
                    //printf("entered email: %s\n", ((address_book->list)+(address_book->count - 1))->email_addresses[emailCount]);
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

	/* Add the functionality for adding contacts here */

}

//DO NOT TOUCH, USED IN DELETE AND POSSIBLY EDIT
int search(AddressBook *address_book, char *type)
{
    //check if addressbook is NULL
    if (address_book == NULL)
        return e_fail;
    if (address_book->list == NULL) 
        return e_fail;
    
    //take input from user to determine what theyre searching
    int choice = -1;
    int siNoIn = -1;
    char search[32] = "\0";
    ContactInfo *result;
    printf("#######   Search Contact to %s by: \n\n0. Back\n1. Name\n2. Phone No\n3. Email ID\n4. Serial No\n\n", type);
    printf("Enter choice: ");
    scanf(" %d", &choice);
    switch(choice) {
        case 0:
            printf("quitting\n");
            break;
        case 1:
            printf("Enter the Name: ");
            scanf(" %[^\n]%*c", search);
            //printf("\n%s\n", search);
            printf("\n");
            for (int i = 0; i < address_book->count; i++) {
                //printf("%s\n",(((address_book->list)+i)->name[0]));
                if (strcmp((((address_book->list)+i)->name[0]), search) == 0)
                    result = ((address_book->list)+i);
            }
            break;
        case 2:
            printf("Enter the Phone No: ");
            scanf(" %[^\n]%*c", search);
            //printf("\n%s\n", search);
            for (int i = 0; i < address_book->count; i++) {
                for (int j = 0; j < 5; j++) {
                    //printf("%s", (((address_book->list)+i)->phone_numbers[j]));
                    if (strcmp((((address_book->list)+i)->phone_numbers[j]), search) == 0)
                        result = ((address_book->list)+i);
                }
            }
            printf("\n");

            break;
        case 3:
            printf("Enter the Email ID: ");
            scanf(" %[^\n]%*c", search);
            //printf("\n%s\n", search);
            printf("\n");
            for (int i = 0; i < address_book->count; i++) {
                for (int j = 0; j < 5; j++) {
                    if (strcmp((((address_book->list)+i)->email_addresses[j]), search) == 0)
                        result = ((address_book->list)+i);
                }
            }
            break;
        case 4:
            printf("Enter the Serial No:");
            scanf(" %d", &siNoIn);
            printf("\n");
            for (int i = 0; i < address_book->count; i++) {
                if ((((address_book->list)+i)->si_no) == siNoIn)
                    result = ((address_book->list)+i);
            }
            break;
        default:
            printf("bad input %d\n", choice);
            break;

    }

    if (result == NULL) {
        printf("search not found\n");
        return e_fail;
    } else {
        return result->si_no;
    }

    /* Add the functionality for adding contacts here */
    return e_success;

	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
    //check if addressbook is NULL
    if (address_book == NULL)
        return e_fail;
    if (address_book->list == NULL) 
        return e_fail;
    
    //take input from user to determine what theyre searching
    int choice = -1;
    int siNoIn = -1;
    char search[32] = "\0";
    ContactInfo *result;
    printf("#######   Search Contact by: \n\n0. Back\n1. Name\n2. Phone No\n3. Email ID\n4. Serial No\n\n");
    printf("Enter choice: ");
    scanf(" %d", &choice);
    switch(choice) {
        case 0:
            printf("quitting\n");
            break;
        case 1:
            printf("Enter the Name: ");
            scanf(" %[^\n]%*c", search);
            //printf("\n%s\n", search);
            printf("\n");
            for (int i = 0; i < address_book->count; i++) {
                //printf("%s\n",(((address_book->list)+i)->name[0]));
                if (strcmp((((address_book->list)+i)->name[0]), search) == 0)
                    result = ((address_book->list)+i);
            }
            break;
        case 2:
            printf("Enter the Phone No: ");
            scanf(" %[^\n]%*c", search);
            //printf("\n%s\n", search);
            for (int i = 0; i < address_book->count; i++) {
                for (int j = 0; j < 5; j++) {
                    //printf("%s", (((address_book->list)+i)->phone_numbers[j]));
                    if (strcmp((((address_book->list)+i)->phone_numbers[j]), search) == 0)
                        result = ((address_book->list)+i);
                }
            }
            printf("\n");

            break;
        case 3:
            printf("Enter the Email ID: ");
            scanf(" %[^\n]%*c", search);
            //printf("\n%s\n", search);
            printf("\n");
            for (int i = 0; i < address_book->count; i++) {
                for (int j = 0; j < 5; j++) {
                    if (strcmp((((address_book->list)+i)->email_addresses[j]), search) == 0)
                        result = ((address_book->list)+i);
                }
            }
            break;
        case 4:
            printf("Enter the Serial No:");
            scanf(" %d", &siNoIn);
            printf("\n");
            for (int i = 0; i < address_book->count; i++) {
                if ((((address_book->list)+i)->si_no) == siNoIn)
                    result = ((address_book->list)+i);
            }
            break;
        default:
            printf("bad input %d\n", choice);
            break;

    }

    if (result == NULL) {
        printf("search not found\n");
        return e_fail;
    } else {      //PRINT FORMATTING HERE ONLY WORK IN THE ELSE
        printf("\n#######   Search Result: \n\n");
        printf("\n===============================================================================================================================");
	    printf("\n: S.No : Name                               : Phone No                           : Email ID                                   :");
		char space[20] = " ";
        printf("\n===============================================================================================================================\n");
        printf(":  %-3d : %-34s : %-34s : %-42s :", result->si_no, result->name, result->phone_numbers, result->email_addresses);
        for (int k = 1; k < 5; k++)
        {
            printf("\n:  %-3s : %-34s : %-34s : %-42s :",space, space,result->phone_numbers[k], result->email_addresses[k]);
        }
		printf("\n===============================================================================================================================\n\n");
    }

    /* Add the functionality for search contacts here */

    return e_success;

	/* Add the functionality for search contacts here */

}

Status edit_contact(AddressBook *address_book)
{

    /* Add the functionality for edit contacts here */
    //return e_success;

	char save[200];
	int choice;
	int i;

	// AddressBook *address_book;

	printf("#######  Address Book  #######\n");
	printf("Search contact to edit by: \n");
	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n");
a:
	printf("Please select an option: ");
	scanf("%d", &choice);

	while (choice != 0)
	{
		if (choice != 0 && choice != 1 && choice != 2 && choice != 3 && choice != 4)
		{
			goto a;
		}

		if (choice == 0)
		{
			return e_back;
			break;
		}

		else if (choice == 1)
		{
			printf("\nEnter the name: ");
			scanf("%s", &save);
			for (int i = 0; i < address_book->count; i++)
			{
				ContactInfo contact = address_book->list[i];
				for (int j = 0; j < NAME_COUNT; j++)
				{
					if (strcmp(save, &contact.name[j][i]) == 0)
					{
						edit(address_book, i);
						j = NAME_COUNT;
						i = address_book->count;
						break;
					}
				}
			}
			break;
		}

		else if (choice == 2)
		{
			printf("\nEnter the Phone No: ");
			scanf("%s", &save);
			for (int i = 0; i < address_book->count; i++)
			{
				ContactInfo contact = address_book->list[i];
				for (int j = 0; j < PHONE_NUMBER_COUNT; j++)
				{
					if (strcmp(save, &contact.phone_numbers[j][i]) == 0)
					{
						j = NAME_COUNT;
						i = address_book->count;
						break;
					}
				}
			}
			break;
		}

		else if (choice == 3)
		{
			printf("\nEnter the Email ID: ");
			scanf("%s", &save);
			for (int i = 0; i < address_book->count; i++)
			{
				ContactInfo contact = address_book->list[i];
				for (int j = 0; j < EMAIL_ID_COUNT; j++)
				{
					if (strcmp(save, &contact.email_addresses[j][i]) == 0)
					{
						j = NAME_COUNT;
						i = address_book->count;
						break;
					}
				}
			}
			break;
		}

		else if (choice == 4)
		{
			printf("\nEnter the Serial No: ");
			int serial;
			scanf("%d", &serial);
			for (int i = 0; i < address_book->count; i++)
			{
				ContactInfo contact = address_book->list[i];
				if (serial == contact.si_no)
				{
					i = address_book->count;
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

	printf("==\n");
	printf(":S.No  :Name                            :Phone No                        :Email ID                        :\n");
	printf("==\n");

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
		for (int i = 32; i > 0; i--)
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
		for (int i = 32; i > 0; i--)
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
			for (int n = 32; n > 0; n--)
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
			for (int p = 32; p > 0; p--)
			{
				printf(" ");
			}
		}
		printf(":\n"); // end of row
	}
	printf("==\n");
	printf("Press:  [s] = Select.  [q] | Cancel :");
	scanf(" %c", &input);
	if (input == 's')
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
				if (strcmp(address_book->list[index].phone_numbers[i], "") == 0)
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
				if (strcmp(address_book->list[index].email_addresses[i], "") == 0)
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

Status delete_contact(AddressBook *address_book)
{
    //allocate mem in a temp addressbook with size count - 1
    ContactInfo *temp = malloc(sizeof(ContactInfo) * address_book->count - 1);
    //search to find contact to be deleted (return pointer to )
    char *type = "delete";
    int delitem = search(address_book, type);
    ContactInfo deleted = *((address_book->list) + delitem - 1);

    for (int i = 0; i < delitem-1; i++) {
        temp[i] = *((address_book->list) + i);
        //printf("ab: %s\n",((address_book->list) + i)->name[0]);
        //printf("temp: %s\n",temp[i].name[0]);
    }
    for (int j = delitem; j < (address_book->count); j++) {
        ((address_book->list) + j)->si_no -= 1;
        temp[j-1] = *((address_book->list) + j);
        //printf("ab: %s\n",((address_book->list) + j)->name[0]);
        //printf("temp: %s\n",temp[j-1].name[0]);
    }

    address_book->count -= 1;
    address_book->list = realloc(address_book->list, sizeof(ContactInfo) * address_book->count);
    address_book->list = temp;
    free(temp);

    //DO TEXT FORMATTING DOWN HERE
    printf("\n#######   Search Result: \n\n");
    printf("\n===============================================================================================================================");
	printf("\n: S.No : Name                               : Phone No                           : Email ID                                   :");
		char space[20] = " ";
        printf("\n===============================================================================================================================\n");
        printf(":  %-3d : %-34s : %-34s : %-42s :", deleted.si_no, deleted.name, deleted.phone_numbers, deleted.email_addresses);
        for (int k = 1; k < 5; k++)
        {
            printf("\n:  %-3s : %-34s : %-34s : %-42s :",space, space,deleted.phone_numbers[k], deleted.email_addresses[k]);
        }
		printf("\n===============================================================================================================================\n\n");

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
    return e_success;
}

//testing compile with both address_book_fops_.c and address_book_menu.c
// int main() {
//     AddressBook address_book;
//     load_file(&address_book);
//     //add_contacts(&address_book);
//     search_contact(&address_book);
//     //delete_contact(&address_book);
//     save_file(&address_book);
// }

// int main() {
//     AddressBook address_book;
//     load_file(&address_book);
//     add_contacts(&address_book);
//     save_file(&address_book);
// }

	/* Add the functionality for delete contacts here */
// }

