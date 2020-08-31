/**
 Hashing to a file and using advanced string manipulation functions.
 
 This program allows additions to, deletions from, or displays of database records in a toy database.

 NAME: Sachin Nediyanchath
 IDE: Microsoft Visual Studios 2017
*/

#define _CRT_SECURE_NO_WARNINGS	// !!Must always use this line when using MSVS2017!!
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define FILENAME "toys.txt"
#define REJECT "rejected.txt"
#define OUTFILE "HASHTIMESFOUR.txt"

#define FILEBUCK 40		// 40 buckets for hash file
#define TABLEBUCK 10	// 10 buckets for hash table
#define BUCKETSIZE 3	// 3 structs per bucket
#define SEARCH 0		// Search flag
#define DELETE 1		// Delete flag

typedef struct toy TOY;

/*
Defines toy struct, while typedef statement above make "TOY"
an acceptable struct name in lieu of "toy"
*/
struct toy
{
	char toy_id[5];		// Unique toy ID (only digits)
	char toy_name[64];	// Name of toy up to 63 characters (letters, ' , " , : , - , and !)
	int rec_age;		// Recommended user age for toy (0-16)
	double toy_price;	// Price of the toy (1.0-550.0)
	char award;			// Award rewarded for toy: G- Gold, S- Silver, R- Recommended, A- Approved
	long key;			// Key associated with a TOY struct
};

/*****************************************
Display_toy(TOY item)
Display all attributes of the TOY object
*/
void Display_toy(TOY item){
	printf("Here is all the info:\n\tID: %s\n\tName: %s\n\tRecommended age: %d\n\tPrice: %0.1f\n\tAward: %c\n\tHash Key: %ld\n", 
			item.toy_id, item.toy_name, item.rec_age, item.toy_price, item.award, item.key);
}

/**********************************
TOY Set_toy(char[5], char[64], int, double, char)
Set all attributes of a TOY object
Includes the hashing function
*/
TOY Set_toy(char id[5], char name[64], int age, double price, char award) 
{
	long hash(char *key);
	TOY temp;
	
	strcpy(temp.toy_id, id);
	strcpy(temp.toy_name, name);
	temp.rec_age = age;
	temp.toy_price = price;
	temp.award = award;
	temp.key = hash(id);
	
	return temp;
}

void toy_maker(char id[5], char name[64], int age, double price, char award, TOY table[TABLEBUCK][BUCKETSIZE])
{
	TOY temp;
	long bucket_number;

	temp = Set_toy("1234", "Hallie", 13, 66.7, 'G');
	Display_toy(temp);
	bucket_number = temp.key % TABLEBUCK;
	table[bucket_number][0] = temp;
	return;
}

/**************************************************************************
Main function in which the database will be displayed
This should be brief since other functions will be working in background
*/
int main(void)
{
	void display(TOY table[TABLEBUCK][BUCKETSIZE]);
	//TOY temp;
	//long bucket_number;

	TOY hashtable[TABLEBUCK][BUCKETSIZE] = { " " };

	toy_maker("1234", "Hallie", 13, 66.7, 'G', hashtable);
	//temp = Set_toy("1234", "Hallie", 13, 66.7, 'G');
	//Display_toy(temp);
	//bucket_number = temp.key % TABLEBUCK;
	//hashtable[bucket_number][0] = temp;

	toy_maker("1111", "Brittney", 16, 200.5, 'S', hashtable);
	/*temp = Set_toy("1111", "Brittney", 16, 200.5, 'S');
	Display_toy(temp);
	bucket_number = temp.key % TABLEBUCK;
	hashtable[bucket_number][0] = temp;*/

	toy_maker("2222", "Sara", 19, 150, 'R', hashtable);
	/*temp = Set_toy("2222", "Sara", 19, 150, 'R');
	Display_toy(temp);
	bucket_number = temp.key%TABLEBUCK;
	hashtable[bucket_number][0] = temp;*/
	
	//FILE *create_hash_file(char *filename);
	//
	//FILE *fp;
	//	
	//fp = create_hash_table(FILENAME);

	display(hashtable);

	printf("You are close to nothing");

    return 0;
}
/***************************
menu_database()
Menu to be used in display()
Search by key or ID, Delete by key, Addition of TOYs from input file inclusion,
Addition of TOY from keyboard, Exit (quit the program)
*/
void menu_database()
{
	printf("\n\tSachin's Toy Database \t-\tWhere Magic Happens\n\n");
	printf("a) Search for Toy(by Toy ID or unique key)\n");
	printf("b) Delete Toy (by unique key)\n");
	printf("c) Input file for database entry\n");
	printf("d) Enter Toy Info via keyboard\n");
	printf("e) Exit program (QUIT)\n\n");
}

/***********************************************

Display menu of Toy Database (User interactive)

*/
void display(TOY table[TABLEBUCK][BUCKETSIZE]) 
{
	void search_or_delete(TOY table[TABLEBUCK][BUCKETSIZE], int insertflag);
	void insert_record(TOY table[TABLEBUCK][BUCKETSIZE]);
	void read_file_database(TOY table[TABLEBUCK][BUCKETSIZE]);

	char choice;
	int loop = 0;
	int innerloop = 1;
	do
	{		
		while (innerloop != 0)
		{
			menu_database();
			printf("Enter choice: ");
			scanf("%c", &choice);
			while (getchar() != '\n');
			choice = tolower(choice);
			printf("You chose %c\n", choice);
			switch (choice)
			{
			case 'a': printf("Searching for toy via key or ID\n");
				search_or_delete(table, 0);
				loop = 1;
				break;
			case 'b': printf("Deleting a toy via key\n");
				search_or_delete(table, 1);
				loop = 1;
				break;
			case 'c': printf("Give an input file for database inclusion\n");
				read_file_database(table);
				loop = 1;
				break;
			case 'd': printf("Enter toy info via keyboard\n");
				insert_record(table);
				loop = 1;
				break;
			case 'e': printf("Exit the program...thanks for trying ~~~\n");
				exit(1);
				//innerloop = 0;
				//loop = 0;
				break;
			default: printf("This is invalid, please enter valid input (a,b,c,d,e)\n");
				break;
			}
		}
	} while (loop != 0);
}
/*******************************************************
Hash formula = Sum of cubes of individual number of 4 digit ID
Divided by 40
Return an address that is mod 10 to store in certain bucket (hashtable[0-9][BUCKETSIZE])
*/
long hash(char *key)
{
	long address = 0;
	for (; *key != '\0'; key++)
	{
		address += ((*key) * (*key) * (*key));
	}
	address /= 40;
	//printf("The ID %s has the key %ld before being put in Basket %ld of the hash table\n", key, address, address % TABLEBUCK);
	return address;
}

/*********************
size(char * input)
Getting the size of a string to determine qualification
*/
int size(char * input)
{
	int size = 0;

	if (input == 0) printf("There is nothing to compare"), size = 0;
	else 
	{
		for (; *input != '\0'; input++)
		{
			size++;
		}
	}
	return size;
}

/*****************************************************************
Hashing to disk: search or insert
Search by key or id
Delete record by key 
*/
void search_or_delete(TOY table[TABLEBUCK][BUCKETSIZE], int insertflag)
{
	//void insert_record(char *key, long address, FILE *fp);
	void delete_record(table);
	void search(table);
	
	printf("%s\n", insertflag ? "DELETE" : "SEARCH");
	
	// Search option...
	if (insertflag == 0) 
	{
		/*char choice;
		printf("Search by Key or ID? (K or I)");
		scanf("%c", &choice);
		choice = tolower(choice);
		switch (choice) 
		{
			case 'k': printf("Searching by the key\n");
				while (printf("Enter key: "), gets(line), strcmp(line, "quit") != 0) 
				{
					token = strtok(line, "\040\t");
					if (!token) continue;
					search_record(token, line, fp);
				}
				break;
			case 'i': printf("Searching by the unique ID\n");
				while (printf("Enter unique ID: "), gets(line), strcmp(line, "quit") != 0) 
				{
					token = strtok(line, "\040\t");
					if (!token) continue;
					address = hash(line);
					search_record(token, address, fp);
				}
				break;
			default:
		}*/
		search(table);
	}

	// Delete option
	else if (insertflag == 1) 
	{
		delete_record(table);
	}
	else {
		printf("How did you even get here?");
	}
}
/*
Searching by key or ID (hashing is done in case of ID search)
Two while loops are nested in a while loop
Asks user what searching criteria, hence the internal while loops
*/
void search(TOY table[TABLEBUCK][BUCKETSIZE])
{
	void search_record(char *key, long address, TOY table[TABLEBUCK][BUCKETSIZE]);
	void search_record_by_key(char* key, long address, TOY table[TABLEBUCK][BUCKETSIZE]);
	char choice, line[10] = "", *token;
	long address;

	int loop = 0;
	// Asks user what search option (Key or Toy ID)
	while (printf("Search by Key or ID? (q to quit) : "), scanf("%c", &choice), loop != 1)
	{
		while (getchar() != '\n'); 
		//printf("Search by Key or ID? (K or I)");
		/*scanf("%c", &choice);
		while (getchar() != '\n');*/
		choice = tolower(choice);
		char * end;

		switch (choice)
		{
		case 'k': printf("Searching by the key\n");
			printf("Enter a key which can have up to 6 digits\n");
			while (printf("Enter key (type 'quit' to exit): "),gets_s(line, sizeof(line) + 1), strcmp(line, "quit") != 0)
			{	
				loop = 0;
				token = strtok(line, "\040\t");
				printf("The size of token is %d\n", size(token));
				if (size(token) == 0)	printf("What is even happening?"), loop = 1;
				if (size(token) > 6)	printf("This is way too big!!! 6 digits only\n"), loop = 1;
				while (token != "\n" && loop != 1)
				{
					printf("The key %s is being searched\n", token);
					if (!token) continue;
					long HERE = strtol(token, &end, 10);
					address = HERE % TABLEBUCK;
					search_record_by_key(token, address, table);
					token = "\n";
					fflush(stdin);
				} 
			}
			break;
		case 'i': printf("Searching by the unique ID\n");
			printf("PS: ID will only have 4 digits!\n");
			while (printf("Enter unique ID (type 'quit' to exit) : "),gets_s(line, sizeof(line) + 1), strcmp(line, "quit") != 0)
			{
				loop = 0;

				token = strtok(line, "\040\t");

				printf("The size of token is %d\n", size(token));

				if (size(token) > 4)	printf("This is way too big!!! 4 digits only\n"), loop = 1;
				
				while (token != "\n" && loop != 1)
				{
					if (!token) continue;
					address = hash(token) % TABLEBUCK;
					search_record(token, address, table);
					token = "\n";
					fflush(stdin);
				}
			}
			break;
		case 'q': printf("Hope you found what you needed!\n");
			display(table);
			break;
		default: printf("This option is not real. Please enter valid keys/IDs or enter q/Q to quit\n");
			break;
		}
	}
}

/******************************************************
Hashing to Disk: Search via hash key
*/
void search_record_by_key(char* key, long address, TOY table[TABLEBUCK][BUCKETSIZE])
{
	TOY detect, temp;
	int i;
	char * end;
	temp = table[address][0];
	//Display_toy(temp);

	long HERE = strtol(key, &end, 10);

	// find first available slot in bucket
	for (i = 0; i < BUCKETSIZE; i++)
	{
		temp = table[address][i];
		detect = temp;
		if (detect.key == HERE) // found it!
		{
			printf("\tKey %s found \n\tat hash bucket %ld.\n", key, address);
			Display_toy(detect);
			return; // nothing left to do
		}
	}
	// not found
	printf("Key %s : not found.\n", key);
	return;
}

/******************************************************
Hashing to Disk: Search via ID
*/
void search_record(char *key, long address, TOY table[TABLEBUCK][BUCKETSIZE])
{
	TOY detect, temp;
	int i;

	temp = table[address][0];
	//Display_toy(temp);

	// find first available slot in bucket
	for (i = 0; i < BUCKETSIZE; i++)
	{
		temp = table[address][i];
		detect = temp;
		if (strcmp(detect.toy_id, key) == 0) // found it!
		{
			printf("\tID %s found \n\tat hash bucket %ld.\n", key, address);
			Display_toy(detect);		
			return; // nothing left to do
		}
	}
	// not found
	printf("ID %s : not found.\n", key);
	return;
}

/******************************************************
Hashing to Disk: Delete
*/
void delete_record(TOY table[TABLEBUCK][BUCKETSIZE])
{
	TOY detect;
	char line[50] = "", *token, *end;
	long address;
	int i;

	while (printf("Enter key: "), gets_s(line,sizeof(line)+1), strcmp(line, "quit") != 0)
	{
		token = strtok(line, "\040\t");
		if (!token) continue;
		long HERE = strtol(token, &end, 10);
		address = HERE % TABLEBUCK;

		// find first available slot in bucket
		for (i = 0; i < BUCKETSIZE; i++)
		{
			detect = table[address][i];
			if (detect.key == HERE) // found it!
			{
				printf("\t%s found \n\tat hash bucket %ld.\n", token, address);
				Display_toy(detect);
				detect = Set_toy("", "", 0, 0, ' ');
				printf("Deleted...");
				table[address][i].key = 0;
				return; // nothing left to do
			}
		}	
		// not found
	printf("Deleting toy with key %s : not found.\n", token);
	return;
	}
}

/******************************************************
Hashing to Disk: Insert
*/
void insert_record(TOY table[TABLEBUCK][BUCKETSIZE])
{
	char line_insert[100] = "";
	char * token, *end;
	TOY detect, temp;
	int i;

	printf("Please insert info (\"ID Name; Age Price Medal\") : ");
	gets_s(line_insert, sizeof(line_insert));
	token = strtok(line_insert, "\040\t");
	// Inserting Toy ID into temp object
	strcpy(temp.toy_id, token);
	token = strtok(NULL, ";");
	// Inserting Toy name into temp object
	strcpy(temp.toy_name, token);
	token = strtok(NULL, "\040\t");
	char * sam = token;
	// Inserting recc age into temp object
	int rage = atoi(sam);
	temp.rec_age = rage;
	token = strtok(NULL,"\040\t");
	sam = token;
	double dage = strtold(sam, &end);
	// Inserting price into temp object
	temp.toy_price = dage;
	token = strtok(NULL, "\040\t\n");
	temp.award = token[0];
	temp.key = hash(temp.toy_id);
	Display_toy(temp);

	long address = temp.key % TABLEBUCK;

	// find first available slot in the bucket.
	for (i = 0; i < BUCKETSIZE; i++)
	{
		detect = table[address][i];
		if (detect.key == '\0') // available slot
		{
			detect = temp;
			printf("Record: %ld :added to bucket %ld.\n", temp.key, address);
			table[address][i] = detect;
			return; // nothing left to do
		}
		else printf("This is just funny to me\n");
	}
	if(table[address][2].key != '\0')
	{
		FILE *fp;
		printf("This bucket is full, so let us put you into rejected.txt");
		fp = fopen(REJECT, "w");
		fwrite(&temp, sizeof(TOY), 1, fp);
	}

}

/******
read_file_database(char * FILENAME, table[10][3])
This function will read the file and insert TOYs line by line
*/
void read_file_database(TOY table[TABLEBUCK][BUCKETSIZE])
{
	FILE *fp;
	TOY temp;
	char filename [18];
	int loop = 0;

	while (printf("Enter filename: "), scanf(" %[0-9A-Za-z:?+ ]", filename), loop != 1)
	{
		if((fp = fopen(filename, "a+")) == NULL)
		{
			printf("Could not open %s.\n", filename);
			exit(2);
		}
		fread(&temp, sizeof(TOY), 1, fp);
		loop = 1;
	}
}

///********************************************************
//Empty hash file - 40 3-struct (TOY) buckets
//This has to be initiated first, so that hash table can be written into this
//No arg necessary since this will be a new file...
//Might or might not use at end...
//*/
//FILE *create_hash_file(/*char *filename*/)
//{
//	FILE *fp;
//	TOY hashfile[FILEBUCK][BUCKETSIZE] = { "" };
//
//	//if ((fp = fopen(filename, "w+b")) == NULL)
//	//{
//	//	printf("Could not open %s.\n", filename);
//	//	exit(1);
//	//}
//	// check for write errors just to be safe.
//	if (fwrite(&hashfile[0][0], sizeof(TOY), FILEBUCK * BUCKETSIZE, fp) < FILEBUCK)
//	{
//		printf("Hash file could not be created. Abort!\n");
//		exit(1);
//	}
//	rewind(fp);
//	return fp;
//}
//
///********************************************************
//Empty hash table - 10 3-struct (TOY) buckets 
//This is created from toys.txt, so including additional files
//is dealt in different function...
//*/
//FILE *create_hash_table(char *filename)
//{
//	FILE *fp;
//	//TOY hashtable[TABLEBUCK][BUCKETSIZE] = {{"", "", "", ""}};
//	TOY hashtable[TABLEBUCK][BUCKETSIZE] = { "" };
//	
//	if ((fp = fopen(filename, "w+b")) == NULL)
//	{
//		printf("Could not open %s.\n", filename);
//		exit(1);
//	}
//	// check for write errors just to be safe.
//	if (fwrite(&hashtable[0][0], sizeof(TOY), TABLEBUCK * BUCKETSIZE, fp) < TABLEBUCK)
//	{
//		printf("Hash table could not be created. Abort!\n");
//		exit(2);
//	}
//	rewind(fp);
//	return fp;
//}
//
