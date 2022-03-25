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
		int count = 0; //number of lines in our csv
		char c; //current char we are reading in
		do {
            c = fgetc(fp);
			if (c == '\n') // Increment count if this character is newline
				count++;
		} while (c != EOF);

        printf("%d\n", count);
        int total = 0;
        rewind(fp); //places our file pointer back at the start of the file
        // address_book->count = total;

        //making our addressbook now that we know how many entries are in it (count)
        address_book->list = malloc(count * sizeof(ContactInfo));
		if (address_book->list == NULL) //error handling
			return e_fail;
		address_book->fp = fp;
		address_book->count = count;

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
                for (int i = 0; i < 12; i++) {
                    switch(i) {
                        case 0:
                            printf("name assigned\n");
                            strcpy(((address_book->list)+(total-1))->name[0], arr[i]);
                            break;
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                            printf("number assigned\n");
                            if (strcmp(arr[i], " ") != 0) 
                                strcpy(((address_book->list)+(total-1))->phone_numbers[i-1], arr[i]);
                            else
                                strcpy(((address_book->list)+(total-1))->phone_numbers[i-1], "\0");
                            break;
                        case 6:
                        case 7:
                        case 8:
                        case 9:
                        case 10:
                            printf("email assigned\n");
                            if (strcmp(arr[i], " ") != 0) 
                                strcpy(((address_book->list)+(total-1))->email_addresses[i-6], arr[i]);
                            else
                                strcpy(((address_book->list)+(total-1))->email_addresses[i-6], "\0");
                            break;
                        case 11:
                            printf("si_no assigned\n");
                            ((address_book->list)+(total-1))->si_no = atoi(arr[i]);
                            break;
                        default:
                            printf("default case");
                            break;
                    }
                }
             }
            total++;
            printf("\n");
        }
        fclose(fp);

    }
    else
    {
        /* Create a file for adding entries */
        printf("Building address_book.csv\n");
        FILE *fp = fopen(DEFAULT_FILE, "w");
		address_book->fp = fp;
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
    char* emptyStr = "\0";
    char *header = "name,phone_number1,phone_number2,phone_number3,phone_number4,phone_number5,email1,email2,email3,email4,email5,si_no\n";
	fprintf(address_book->fp, "%s", header);

    for (int i = 0; i < address_book->count; i++) {
        fprintf(address_book->fp, "%s,", address_book->list[i].name[0]);
        //for writing the 5 phone numbers
        for(int j = 0; j < 5; j++)
			if(strcmp(address_book->list[i].phone_numbers[j], emptyStr) != 0)
				fprintf(address_book->fp, "%s,", address_book->list[i].phone_numbers[j]);
			else if(strcmp(address_book->list[i].phone_numbers[j], emptyStr) == 0)
				fprintf(address_book->fp, " ,");
				
        //for writing the 5 emails,
		for(int k = 0; k < 5; k++)
			if(strcmp(address_book->list[i].email_addresses[k], emptyStr) != 0)
				fprintf(address_book->fp, "%s,", address_book->list[i].email_addresses[k]);
			else if(strcmp(address_book->list[i].email_addresses[k], emptyStr) == 0)
				fprintf(address_book->fp, " ,");
		fprintf(address_book->fp, "\n");
    }

    fclose(address_book->fp);

    return e_success;
}

//testing
int main() {
    AddressBook address_book;
    load_file(&address_book);
    printf("%s", address_book.list[3].name[0]);
    //save_file(&address_book);
}
