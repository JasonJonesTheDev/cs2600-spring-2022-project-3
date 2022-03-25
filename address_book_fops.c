#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

Status load_file(AddressBook *address_book)
{
    int ret;
    FILE *fp;
    
    /*
     * Check for file existance
     */
    if( access( DEFAULT_FILE, F_OK ) == 0 ) {
        printf("the file exists\n");
        ret = 0;
    } else {
        printf("the file does not exist\n");
        ret = 1;
    }

    fp = fopen(DEFAULT_FILE, "r");
    char line[500];

    if (ret == 0)
    {
        
        //this loop is used to set count for our address book
        address_book->list = malloc(sizeof(ContactInfo)*50);
         int total = 0;
         

        printf("%d", total);
         address_book->count = total;
         while (fgets(line, sizeof(line), fp)) {
             char *token;
             token = strtok(line,",");
             int count = 0;
             char arr[12][32];
             while (token != NULL) {
                 strcpy(arr[count], token);
                 count++;
                 token = strtok(NULL, ",");
             }
             printf("assignment loop %d\n", total);
             if (total > 0) {
                for (int i = 0; i < 11; i++) {
                    switch(i) {
                        case 0:
                            strcpy(address_book->list[total].name[0], arr[i]);
                            break;
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                            if (strcmp(arr[i], " ") != 0) 
                                strcpy(address_book->list[total].phone_numbers[i-1], arr[i]);
                            else
                                strcpy(address_book->list[total].phone_numbers[i-1], "\0");
                            break;
                        case 6:
                        case 7:
                        case 8:
                        case 9:
                        case 10:
                            if (strcmp(arr[i], " ") != 0) 
                                strcpy(address_book->list[total].email_addresses[i-6], arr[i]);
                            else
                                strcpy(address_book->list[total].email_addresses[i-6], "\0");
                            break;
                        case 11:
                            address_book->list[total].si_no = atoi(arr[i]);
                            break;
                        default:
                            printf("default case");
                            break;
                    }
                }
             }
             total++;
             printf("#11 %s", arr[11]);
             printf("\n");
         }

    }
    else
    {
        /* Create a file for adding entries */
        printf("Building address_book.csv\n");
		address_book->fp = fopen(DEFAULT_FILE, "w");
		address_book->count = 0;
		fclose(address_book->fp);
    }

    return e_success;
}

Status save_file(AddressBook *address_book)
{
    /*
     * Write contacts back to file.
     * Re write the complete file currently
     */
    address_book->fp = fopen(DEFAULT_FILE, "w");

    if (address_book->fp == NULL)
    {
        return e_fail;
    }

    /*
     * Add the logic to save the file
     * Make sure to do error handling
     */
    char* target = "\0";
    char *header = "name,phone_number1,phone_number2,phone_number3,phone_number4,phone_number5,email1,email2,email3,email4,email5,si_no\n";
	fprintf(address_book->fp, "%s", header);

    for (int i = 0; i < address_book->count; i++) {
        fprintf(address_book->fp, "%s,", address_book->list[i].name[0]);
        //for writing the 5 phone numbers
        for(int j = 0; j < 5; j++)
			if(strcmp(address_book->list[i].phone_numbers[j],target) != 0)
				fprintf(address_book->fp, "%s,", address_book->list[i].phone_numbers[j]);
			else if(strcmp(address_book->list[i].phone_numbers[j],target) == 0)
				fprintf(address_book->fp, " ,");
				
        //for writing the 5 emails,
		for(int k = 0; k < 5; k++)
			if(strcmp(address_book->list[i].email_addresses[k],target) != 0)
				fprintf(address_book->fp, "%s,", address_book->list[i].email_addresses[k]);
			else if(strcmp(address_book->list[i].email_addresses[k],target) == 0)
				fprintf(address_book->fp, " ,");
		fprintf(address_book->fp, "\n");
    }

    fclose(address_book->fp);

    return e_success;
}

int main() {
    AddressBook *address_book;
    load_file(address_book);
    printf("%s", address_book->list[1].name[0]);
}
