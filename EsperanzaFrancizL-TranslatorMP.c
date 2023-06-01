/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
 Franciz Emmanuelle Angelo L. Esperanza, DLSU ID# 12179922
*********************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// STRUCTS

typedef char Str20 [21];
typedef char Str150 [151];

struct pair																					// language-translation pairs and their count
{
	Str20 language [10];																	// a string containing the language of the translation word
	Str20 trans [10];																		// a string containing the translation word
	int count;																				// the number of pairs in an entry
};

struct translate												 							// struct needed for translation menu
{
	Str20 langIn;																			// a string containing the language of the source text
	Str20 langOut;																			// a string containing the language of the output text
	Str150 text;																			// a string containing the text to be translated
	Str150 tokens [150];																	// an array of strings containing individual words of text
};

// PROTOTYPES

void mainMenu (struct pair *eptr [], struct translate * trptr, int * nEntry);
void manageDataMenu (struct pair *eptr [], int * nEntry);
void translateMenu (struct pair *eptr [], struct translate * trptr, int * nEntry);

int exitManageData (struct pair *eptr [], int * nEntry);
void eraseEntries (struct pair * eptr [], int * nEntry);

void doTranslate (struct pair *eptr [], struct translate * trptr, int nEntry);
void trDelete (struct translate *trptr);
int trTokenize (struct translate *trptr);

void addEntry (struct pair *eptr [], int * nEntry);
void newEntry (char strWord1 [], char strWord2 [], struct pair *eptr []);

void checkOldEntry (char strWord1 [], char strWord2 [], struct pair *eptr []);
int nOldEntry (char strWord1 [], char strWord2 [], struct pair *eptr []);
int checkIfDuplicatePair (int idEntry, char strWord1 [], char strWord2 [], struct pair * eptr []);
void displayOldEntry (int nEntry, struct pair *eptr []);
void findSimilarEntry (char strWord1 [], char strWord2 [], int arrIndex [], struct pair *eptr []);

void addTranslation (struct pair *eptr [], int nEntry);
void newTranslation (int idEntry, struct pair *eptr []);

void deleteEntry (struct pair *eptr [], int * nEntry);
void removeEntry (struct pair * eptr [], int idEntry, int nEntry);

void deleteTranslation (struct pair *eptr [], int * nEntry);
void removeTranslation (struct pair * eptr [], int idEntry, int * nEntry);

void exportFile (struct pair * eptr [], int nEntry);
int importFile (struct pair * eptr [], int * nEntry);

void displayAllEntries (struct pair * eptr [], int nEntry);
void sortAscendingPairs (struct pair * eptr [], int idEntry);
void sortEntries (struct pair * eptr [], int nEntry);
int findEnglishPair (struct pair * eptr [], struct pair sVar);
int check4EnglishPair (struct pair * eptr [], struct pair sVar);
void stringSwap (char strWord1 [], char strWord2 []);

void searchWord (struct pair * eptr []);
void searchTranslation (struct pair * eptr []);

void capltzStr (char strWord []);
void lcaseStr (char strWord []);
void trimNewline (char strWord []);
int checkIfLetters (char strWord []);
void ifValidStrInput (char prompt [], char strWord [], int nLength);
void ifValidTxtInput (char prompt [], char strWord [], int nLength);

// MAIN

int
main (void)
{
	struct pair entry [150];
	struct pair *eptr [150];
	
	struct translate input;
	struct translate *trptr = &input;
	
	int i;
	int nEntry = 0;																		// number of entries
	
	for (i = 0; i < 150; i++)															// initializing array of pointers
		eptr [i] = &entry[i];
	
	memset (entry, '\0', sizeof(entry));
	
	mainMenu (&*eptr, &*trptr, &nEntry);
	
	return 0;
}

// FUNCTIONS

/*  mainMenu displays the main menu and calls a function based on the user's input
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
 	@param trptr - a struct pointer to struct translate input
 	@param nEntry - the number of entries in the dataset
*/
void
mainMenu (struct pair * eptr [], struct translate * trptr, int * nEntry)
{
	char menuInput = '*';
	int exit = 0;
	
	do
	{
		printf ("______________________________________\n\n");
		printf ("SIMPLE TRANSLATOR by Franciz Esperanza\n\n");
		printf ("[Main Menu]\n\n");
		printf ("> Manage Data [M]\n");
		printf ("> Translate [T]\n");
		printf ("> Exit [E]\n");
		printf ("\nEnter a key: ");
		scanf (" %c", &menuInput);
		fflush (stdin);
		
		switch (menuInput)
		{
			case 'M': 
			case 'm': manageDataMenu(&*eptr, &*nEntry);
					  break;
			case 'T':
			case 't': translateMenu(&*eptr, &*trptr, &*nEntry);
					  break;
			case 'E':
			case 'e': exit = 1;
					  break;
			default: printf ("\nInvalid input.\n");
		}
	} while (exit == 0);
}

/*  manageDataMenu displays the Manage Data menu and calls a function based on the user's input
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
 	@param nEntry - the number of entries in the dataset
 	Precondition: User pressed M/m in the Main menu
*/
void
manageDataMenu (struct pair * eptr [], int * nEntry)
{
	char menuInput = '*';
	int exit = 0;
	
	do
	{
		printf ("______________________________________\n\n");
		printf ("[Manage Data]\n\n");
		printf ("> Add Entry [1]\n");
		printf ("> Add Translation [2]\n");
		printf ("> Delete Entry [3]\n");
		printf ("> Delete Translation [4]\n");
		printf ("> Display All Entries [5]\n");
		printf ("> Search Word [6]\n");
		printf ("> Search Translation [7]\n");
		printf ("> Export [8]\n");
		printf ("> Import [9]\n");
		printf ("> Exit [E]\n");
		printf ("\nEnter a key: ");
		scanf (" %c", &menuInput);
		fflush (stdin);
		
		switch (menuInput)
		{
			case '1': printf("\nAdd Entry\n");
					  addEntry(&*eptr, &*nEntry);
					  break;
			case '2': printf("\nAdd Translation\n");
					  addTranslation (&*eptr, *nEntry);
					  break;
			case '3': printf("\nDelete Entry\n");
					  deleteEntry (&*eptr, &*nEntry);
					  break;
			case '4': printf("\nDelete Translation\n");
					  deleteTranslation (&*eptr, &*nEntry);
					  break;
			case '5': printf("\nDisplay All Entries\n");
					  displayAllEntries (&*eptr, *nEntry);
					  break;
			case '6': printf("\nSearch Word\n");
					  searchWord (&*eptr);
					  break;
			case '7': printf("\nSearch Translation\n");
					  searchTranslation (&*eptr);
					  break;
			case '8': printf("\nExport\n");
					  exportFile (&*eptr, *nEntry);
					  break;
			case '9': printf("\nImport\n");
					  importFile (&*eptr, &*nEntry);
					  break;
			case 'E':
			case 'e': exit = exitManageData (&*eptr, &*nEntry);
					  break;
			default: printf ("\nInvalid input.\n");
		}
		
	} while (exit == 0);
}

/*  translateMenu asks for a file to import, displays the Translate menu, and calls a function based on the user's input
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
 	@param trptr - a struct pointer to struct translate input
 	@param nEntry - the number of entries in the dataset
 	Precondition: User pressed T/t in the Main menu
*/
void 
translateMenu (struct pair * eptr [], struct translate * trptr, int * nEntry)
{
	char menuInput = '*';
	int exit = 0;
	int open = 0;
	
	open = importFile (&*eptr, &*nEntry);
	while (exit == 0 && open == 1)
	{
		printf ("______________________________________\n\n");
		printf ("[Translate Menu]\n\n");
		printf ("> Translate [T]\n");
		printf ("> Exit [E]\n");
		printf ("\nEnter a key: ");
		scanf (" %c", &menuInput);
		fflush (stdin);
		
		switch (menuInput)
		{
			case 'T':
			case 't': printf("\nTranslate\n");
					  doTranslate (&*eptr, &*trptr, *nEntry);
					  break;
			case 'E':
			case 'e': eraseEntries (&*eptr, &*nEntry);
					  exit = 1;
					  break;
			default: printf ("\nInvalid input.\n");
		}
	}
}

/*  exitManageData reassures the user about exiting the Manage Data menu
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
 	@param nEntry - the number of entries in the dataset
 	@return 1 if user wants to exit and 0 if not
*/
int 
exitManageData (struct pair *eptr [], int * nEntry)
{
	char input = '*';
	int valid = 0;
	int exit = 0;
	
	do
	{
		printf ("\nExiting will delete all data that was not exported into a file.");
		printf ("\nAre you sure you want to exit the Manage Data menu? [Y/N]: ");
		scanf (" %c", &input);
		fflush (stdin);
		
		switch (input)
		{
			case 'Y':
			case 'y': eraseEntries (&*eptr, &*nEntry);
					  valid = 1;
					  exit = 1;
					  break;
			case 'N': 
			case 'n': valid = 1;
					  break;
			default: printf ("\nInvalid input.\n");
		}
	} while (valid == 0);
	
	return exit;
}

/*  eraseEntries deletes all entries stored in struct pair entry
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
 	@param nEntry - the number of entries in the dataset
*/
void 
eraseEntries (struct pair * eptr [], int * nEntry)
{
	int i, j;
	
	for (i = 0; i < *nEntry; i++)
	{
		for (j = 0; j < eptr [i]->count; j++)
		{
			strcpy (eptr [i]->language [j],"");
			strcpy (eptr [i]->trans [j], "");
		}
		eptr[i]->count = 0;
	}
	
	*nEntry = 0;
}

/*  doTranslate encapsulates all functions related to translating a source text
 	@param trptr - a struct pointer to struct translate input
 	@param nEntry - the number of entries in the dataset
 	Precondition: A file has been imported
*/
void 
doTranslate (struct pair *eptr [], struct translate *trptr, int nEntry)
{
	int h, i, j, k, l, m;
	int exit = 0, valid = 0;
	int wordCount;
	
	char input = '*';
	char prompt1 [] = "\nInput LANGUAGE of text to be translated: ";
	char prompt2 [] = "\nInput LANGUAGE to translate to: ";
	char prompt3 [] = "\nInput TEXT to be translated (max 150 characters): ";
	
	ifValidStrInput (prompt1, trptr->langIn, 20);
	capltzStr (trptr->langIn);
	ifValidStrInput (prompt2, trptr->langOut, 20);
	capltzStr (trptr->langOut);
	
	
	do
	{
		ifValidTxtInput (prompt3, trptr->text, 150);
		
		trDelete (&*trptr);
		wordCount = trTokenize (&*trptr);
		
		printf ("\n\n%s:\n", trptr->langIn);
		for (h = 0; h < wordCount; h++)
			printf ("%s ", trptr->tokens [h]);
			
		for (i = 0; i < wordCount; i++)																									// search through tokens
			for (j = 0; j < nEntry; j++)																								// search through entries
				for (k = 0; k < eptr [j]->count; k++)																					// search through pairs
					if (strcmp (trptr->langIn, eptr [j]->language [k]) == 0 && strcmp (trptr->tokens [i], eptr [j]->trans [k]) == 0)	// search if the text language and word is in the entry
					{
						for (l = 0; l < eptr [j]->count; l++)
							if (strcmp (trptr->langOut, eptr [j]->language [l]) == 0)
							{
								strcpy (trptr->tokens [i], eptr [j]->trans [l]);
							}
					}
		
		
		printf ("\n%s:\n", trptr->langOut);
		for (m = 0; m < wordCount; m++)
			printf ("%s ", trptr->tokens [m]);
		
		printf ("\n\n");
		
		memset (trptr->tokens, '\0', sizeof(trptr->tokens));
		
		do
		{
			printf ("Would you like translate again with the same settings? [Y/N]: ");
			scanf (" %c", &input);
			fflush (stdin);
			
			switch (input)
			{
				case 'Y': 
				case 'y': valid = 1;
						  break;
				case 'N':
				case 'n': printf ("\nOk! Sending you back to Translate Menu...\n");
						  valid = 1;
						  exit = 1;
						  break;
				default: printf ("\nInvalid input.\n");
			}
		} while (valid == 0);
		
		valid = 0;
	} while (exit == 0);
	
	memset (trptr->tokens, '\0', sizeof(trptr->tokens));
}

/*  trDelete deletes the ! ? . , symbols from a string
 	@param trptr - a struct pointer to struct translate input
 	Precondition: A valid string is stored in trptr->text
*/
void 
trDelete (struct translate *trptr)
{
	int i, j;
	int nLength;

	nLength = strlen (trptr->text);
	
	for (i = 0; i < nLength; i++)
		while (trptr->text [i] == '!' || trptr->text [i] == '.' || trptr->text [i] == ',' || trptr->text [i] == '?')
		{
			for (j = i; j < nLength; j++)
				trptr->text [j] = trptr->text [j + 1];
		}
}

/*  trTokenize divides the text into words
 	@param trptr - a struct pointer to struct translate input
 	@return the number of words counted
 	Precondition: Symbols have been deleted from trptr->text and a space will separate the tokens
*/
int 
trTokenize (struct translate *trptr)
{
	int f = 0, g = 0, h = 0, i, j = 0, k = 0, l;
	int nLength;
	int wordCount = 0;
	int cut = 0;
	
	nLength = strlen (trptr->text);
	
	while (f < nLength)																		// removing leading whitespaces
	{
		if(trptr->text [f] == ' ' || trptr->text [f] == '\t')
		{
			f++;
		}
		else
		{
			while (trptr->text [g] != '\0')
			{
				trptr->text [g] = trptr->text [f];
				g++;
				f++;
			}
		}
	}
	
	h = strlen (trptr->text) - 1;
	
	while (!cut)																			// removing trailing whitespaces
	{
		if (trptr->text [h] == ' ' || trptr->text [h] == '\t')
			h--;
		else
			cut = 1;
	}
	
	trptr->text [h+1] = '\0';
	
	for (i = 0; i < nLength; i++)															// separating text into words
		if (trptr->text [i] != ' ')
		{
			trptr->tokens [j][k] = trptr->text[i];
			k++;
		}
		else if (trptr->text [i + 1] != ' ')
		{
			j++;
			k = 0;
		}
	
	for (l = 0; l < 150; l++)
		if (strlen (trptr->tokens [l]) != 0)
			wordCount++;
	
	return wordCount;
}

/*  addEntry checks if the user's input language-translation pair already exists in the dataset and manages new entries
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
 	@param nEntry - the number of entries in the dataset
*/
void 
addEntry (struct pair *eptr [], int * nEntry)
{
	int exit = 0;
	char input = '*';
	Str20 strLang, strTrans;
	char prompt1 [] = "\nInput LANGUAGE of language-translation pair: ";
	char prompt2 [] = "\nInput TRANSLATION of language-translation pair: ";
	
	if (*nEntry < 150)
	{
		ifValidStrInput (prompt1, strLang, 20);
		ifValidStrInput (prompt2, strTrans, 20);
		capltzStr (strLang);
		lcaseStr (strTrans);
		
		printf ("\nChecking for existing entries.....\n");
		
		if (nOldEntry (strLang, strTrans, &*eptr) == 0)
			printf ("No existing entry.");
		else
			checkOldEntry (strLang, strTrans, &*eptr);
		
		do
		{
			printf ("\nIs this a new entry? [Y/N]: ");
			scanf ("%c", &input);
			fflush (stdin);
			
			switch (input)
			{
				case 'Y': 
				case 'y': newEntry (strLang, strTrans, &*eptr);
						  (*nEntry)++;
						  sortEntries (&*eptr, *nEntry);
						  exit = 1;
						  break;
				case 'N':
				case 'n': printf ("\nOk! Sending you back to Manage Data Menu...\n");
						  exit = 1;
						  break;
				default: printf ("\nInvalid input.\n");
			}
		} while (exit == 0);
	}
	else
		printf ("\nMax number of entries reached. Returning to Manage Data menu...\n");
}

/*  newEntry initializes the user's input language-translation pair and asks if additional pairs are to be added
	@param strWord1 - a string that contains the language of a pair
	@param strWord2 - a string that contains the translation of a pair
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
 	Precondition: The user wants to add a new entry
*/
void 
newEntry (char strWord1 [], char strWord2 [], struct pair *eptr [])
{
	int i = 0, j = 0, k = 0;
	int stop = 0, valid = 0;
	char input = '*';
	
	char prompt1 [] = "\nInput LANGUAGE of language-translation pair: ";
	char prompt2 [] = "\nInput TRANSLATION of language-translation pair: ";
	
	for (i = 0; i < 150; i++)															// looking for vacant entry slots
		if (strlen (eptr [i]->language [0]) != 0)										
			j++;
		else
			i = 150;
		
	int remain = 10 - eptr [j]->count;
	
	strcpy (eptr [j]->language [k], strWord1);											// first pair initialization									
	strcpy (eptr [j]->trans [k], strWord2);
	printf ("\nLanguage-translation pair initialized.");
	eptr [j]->count++;
	remain--;
	k++;
	
	do																					// if user wants to keep inputting pairs
	{
		if (eptr [j]->count == 10)
		{
			printf ("\nMaximum number of pairs reached.");
			printf ("\nSending you back to the Manage Data Menu...\n");
			stop = 1;
		}
		else
		{
			do
			{
				printf ("\nThe entry has %d free spaces left before maximum capacity.", remain);
				printf ("\nWould you like to input another pair? [Y/N]: ");
				scanf (" %c", &input);
				fflush (stdin);
				
				switch (input)
				{
					case 'Y':
					case 'y': ifValidStrInput (prompt1, strWord1, 20);
							  ifValidStrInput (prompt2, strWord2, 20);
							  capltzStr (strWord1);
							  lcaseStr (strWord2);
							  
							  if (checkIfDuplicatePair (j, strWord1, strWord2, &*eptr) == 0)
							  {
								  strcpy (eptr [j]->language [k], strWord1);
								  strcpy (eptr [j]->trans [k], strWord2);
								  printf ("\nLanguage-translation pair initialized.");
								  eptr [j]->count++;
								  sortAscendingPairs (&*eptr, j);
								  remain--;
								  valid = 1;
						          k++;
						          break;
							  }
							  else
							  {
							  	  printf ("\nThere is already an existing pair in the current entry. Try again.\n");
							  	  break;
							  }
					case 'N':
					case 'n': printf ("\nOk! Sending you back to Manage Data Menu...\n");
							  valid = 1;
							  stop = 1;
							  break;
					default: printf ("\nInvalid input.\n");
				}	
			} while (valid == 0);
		}
		
		valid = 0;
	} while (stop == 0);
}

/*  addTranslation asks for a language-translation pair to add more pairs on the entry containing it
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
 	@param nEntry - the number of entries in the dataset
*/
void 
addTranslation (struct pair *eptr [], int nEntry)
{
	int i, valid = 0, exit = 0;
	int input;
	int arrIndex [150] = {0};
	int finalInput;
	Str20 strLang, strTrans;
	char prompt1 [] = "\nInput LANGUAGE of an EXISTING language-translation pair: ";
	char prompt2 [] = "\nInput TRANSLATION of an EXISTING language-translation pair: ";

	ifValidStrInput (prompt1, strLang, 20);
	ifValidStrInput (prompt2, strTrans, 20);
	capltzStr (strLang);
	lcaseStr (strTrans);
	
	printf ("\nChecking for existing entries.....\n");
	
	if (nOldEntry (strLang, strTrans, &*eptr) == 0)
		{
			printf ("\nNo existing entry. Please use the Add Entry function first.\n");
			printf ("Sending you back to the Manage Data Menu....\n");
		}
	else if (nOldEntry (strLang, strTrans, &*eptr) == 1)
		{
			checkOldEntry (strLang, strTrans, &*eptr);
			findSimilarEntry (strLang, strTrans, arrIndex, &*eptr);
			newTranslation (arrIndex [0], &*eptr);
			sortEntries (&*eptr, nEntry);
		}
	else
		{
			checkOldEntry (strLang, strTrans, &*eptr);
			findSimilarEntry (strLang, strTrans, arrIndex, &*eptr);
			
			printf ("\nThere are multiple entries with the same pair.\n");
			
			do
			{
				printf ("\nSelect the number of the entry you wish to edit: ");
				scanf (" %d", &input);
				fflush (stdin);
				
				for (i = 0; i < 150; i++)																		// checking if input is in arrIndex
				{
					if (arrIndex [i] == input - 1)
					{
						finalInput = arrIndex [i];
						valid = 1;
						i = 150;
					}
				}
				
				if (valid == 1)
				{
					newTranslation (finalInput, &*eptr);
					sortEntries (&*eptr, nEntry);
					exit = 1;
					printf ("\nOk! Sending you back to the Manage Data Menu....\n");
				}
				else
					printf ("\nInvalid input.\n");
			} while (exit == 0);
		}
}

/*  newTranslation adds new language-translation pairs to an entry
	@param idEntry - an integer representing the index of the entry to be edited
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
*/
void 
newTranslation (int idEntry, struct pair *eptr [])
{
	int stop = 0, valid = 0;
	int entryCount = eptr [idEntry]->count;
	int remain = 10 - eptr [idEntry]->count;
	char input = '*';
	int dupe = 1;
	
	Str20 strWord1;
	Str20 strWord2;
	
	char prompt1 [] = "\nInput LANGUAGE of language-translation pair: ";
	char prompt2 [] = "\nInput TRANSLATION of language-translation pair: ";
	
	while (eptr [idEntry]->count != 10 && dupe == 1) 
	{
		printf ("\nThe entry has %d free spaces left before maximum capacity.", remain);
		ifValidStrInput (prompt1, strWord1, 20);
		ifValidStrInput (prompt2, strWord2, 20);
		capltzStr (strWord1);
		lcaseStr (strWord2);
		
		if (checkIfDuplicatePair (idEntry, strWord1, strWord2, &*eptr) == 0)
		{
			strcpy (eptr [idEntry]->language [entryCount], strWord1);
			strcpy (eptr [idEntry]->trans [entryCount], strWord2);
			printf ("\nLanguage-translation pair initialized.");
			eptr [idEntry]->count++;
			sortAscendingPairs (&*eptr, idEntry);
			remain--;
			entryCount++;
			dupe = 0;
		}
		else
			printf ("\nThere is already an existing pair in the current entry. Try again.\n");
	}

	do																	// if user wants to keep inputting pairs
	{
		if (eptr [idEntry]->count == 10)
		{
			printf ("\n\nMaximum number of pairs reached...\n");
			printf ("Sending you back to the Manage Data Menu...\n");
			stop = 1;
		}
		else
		{			  
			do
			{
				printf ("\nThe entry has %d free spaces left before maximum capacity.", remain);
				printf ("\nWould you like to input another pair? [Y/N]: ");
				scanf (" %c", &input);
				fflush (stdin);
				
				switch (input)
				{
					case 'Y':
					case 'y': ifValidStrInput (prompt1, strWord1, 20);
							  ifValidStrInput (prompt2, strWord2, 20);
							  capltzStr (strWord1);
							  lcaseStr (strWord2);
							  if (checkIfDuplicatePair (idEntry, strWord1, strWord2, &*eptr) == 0)
							  {
								  strcpy (eptr [idEntry]->language [entryCount], strWord1);
								  strcpy (eptr [idEntry]->trans [entryCount], strWord2);
								  printf ("\nLanguage-translation pair initialized.");
								  eptr [idEntry]->count++;
								  sortAscendingPairs (&*eptr, idEntry);
								  remain--;
								  entryCount++;
								  valid = 1;
						          break;
							  }
							  else
							  {
							  	  printf ("\nThere is already an existing pair in the current entry. Try again.\n");
							  	  break;
							  }
					case 'N':
					case 'n': printf ("\nOk! Sending you back to Manage Data Menu...\n");
							  valid = 1;
							  stop = 1;
							  break;
					default: printf ("\nInvalid input.\n");
				}	
			} while (valid == 0);
		}
		
		valid = 0;
		
	} while (stop == 0);
}

/*  displayAllEntries displays all entries and their pairs one by one
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
 	@param nEntry - the number of entries in the dataset
*/
void 
displayAllEntries (struct pair *eptr [], int nEntry)
{
	int i = 0;
	int valid = 0;
	int exit = 0;
	char input = '*';
	
	if (nEntry == 0)
	{
		printf ("\nNo existing entry. Please use the Add Entry function first.\n");
		printf ("Sending you back to the Manage Data Menu...\n");
	}
	else
		printf ("\nThere are %d entry/entries\n", nEntry);
	
	while (exit == 0 && nEntry != 0)
	{
		printf ("\nEntry %d:\n", i + 1);
		displayOldEntry (i, &*eptr);
		
		do
		{
			printf ("\nNext [N] | Previous [P] | Exit [E]\n");
			printf ("\nEnter a key: ");
			scanf (" %c", &input);
			fflush (stdin);
			
			switch (input)
			{
				case 'N':
				case 'n': if (i == nEntry - 1)
						  {
							printf ("\nYou can't. This is the last entry.");
							break;
						  }
						  else
						  {
						  	i++;
						  	valid = 1;
						  	break;
						  }
				case 'P':
				case 'p': if (i == 0)
						  {
							printf ("\nYou can't. This is the first entry.");
							break;
						  }
						  else
						  {
						  	i--;
						  	valid = 1;
						  	break;
						  }
				case 'E':
				case 'e': printf ("\nOk! Sending you back to Manage Data Menu...\n");
						  exit = 1;
						  valid = 1;
						  break;
				default: printf ("\nInvalid input.\n");		
			}
		} while (valid == 0);
	
		valid = 0;
	}
}

/*  searchWord displays the entries that contain the search word
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
*/
void 
searchWord (struct pair *eptr [])
{
	int i, j, k = 0, l = 0;
	int nFound = 0;
	int valid = 0;
	int exit = 0;
	int arrIndex [150] = {0};
	char input = '*';
	char prompt1 [] = "\nInput WORD to search for: ";
	
	Str20 word;
	
	ifValidStrInput (prompt1, word, 20);
	lcaseStr (word);
	
	for (i = 0; i < 150; i++)													// finding the no of found word in entries and storing index no of entries containing the word
		for (j = 0; j < 10; j++)
			if (strcmp(word, eptr [i]->trans [j]) == 0)
			{
				arrIndex [k] = i;
				k++;
				nFound++;
				j = 10;
			}
	
	if (nFound == 0)
	{
		printf ("\nWord not found in all entries. Please use the Add Entry or Add Translation function first.\n");
		printf ("Sending you back to the Manage Data Menu...\n");
	}
	else
		printf ("\nThe system found %d entry/entries\n", nFound);
		
	while (exit == 0 && nFound != 0)
	{
		printf ("\nEntry %d:\n", arrIndex [l] + 1);
		
		displayOldEntry (arrIndex [l], &*eptr);
		
		do
		{
			printf ("\nNext [N] | Previous [P] | Exit [E]\n");
			printf ("\nEnter a key: ");
			scanf (" %c", &input);
			fflush (stdin);
			
			switch (input)
			{
				case 'N':
				case 'n': if (l == nFound - 1)
						  {
							printf ("\nYou can't. This is the last entry.");
							break;
						  }
						  else
						  {
						  	l++;
						  	valid = 1;
						  	break;
						  }
				case 'P':
				case 'p': if (l == 0)
						  {
							printf ("\nYou can't. This is the first entry.");
							break;
						  }
						  else
						  {
						  	l--;
						  	valid = 1;
						  	break;
						  }
				case 'E':
				case 'e': printf ("\nOk! Sending you back to Manage Data Menu...\n");
						  exit = 1;
						  valid = 1;
						  break;
				default: printf ("\nInvalid input.\n");		
			}
		} while (valid == 0);
		
		valid = 0;
	}
}

/*  searchTranslation displays the entries that contain the user's input language-translation pair
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
*/
void 
searchTranslation (struct pair *eptr [])
{
	int i, j, k = 0, l = 0;
	int nFound = 0;
	int valid = 0;
	int exit = 0;
	int arrIndex [150] = {0};
	char input = '*';
	char prompt1 [] = "\nInput LANGUAGE to search for: ";
	char prompt2 [] = "\nInput TRANSLATION to search for: ";
	
	Str20 strWord1;
	Str20 strWord2;
	
	ifValidStrInput (prompt1, strWord1, 20);
	ifValidStrInput (prompt2, strWord2, 20);
	
	capltzStr (strWord1);
	lcaseStr (strWord2);
	
	for (i = 0; i < 150; i++)													// finding the no of found word in entries and storing index no of entries containing the word
		for (j = 0; j < 10; j++)
			if (strcmp(strWord1, eptr [i]->language [j]) == 0  && strcmp(strWord2, eptr [i]->trans [j]) == 0)
			{
				arrIndex [k] = i;
				k++;
				nFound++;
				j = 10;
			}
	
	if (nFound == 0)
	{
		printf ("\nThe pair is not found in all entries. Please use the Add Entry or Add Translation function first.\n");
		printf ("Sending you back to the Manage Data Menu...\n");
	}
	else
		printf ("\nThe system found %d entry/entries\n", nFound);
	
		
	while (exit == 0 && nFound != 0)
	{
		printf ("\nEntry %d:\n", arrIndex [l] + 1);
		
		displayOldEntry (arrIndex [l], &*eptr);
		
		do
		{
			printf ("\nNext [N] | Previous [P] | Exit [E]\n");
			printf ("\nEnter a key: ");
			scanf (" %c", &input);
			fflush (stdin);
			
			switch (input)
			{
				case 'N':
				case 'n': if (l == nFound - 1)
						  {
							printf ("\nYou can't. This is the last entry.");
							break;
						  }
						  else
						  {
						  	l++;
						  	valid = 1;
						  	break;
						  }
				case 'P':
				case 'p': if (l == 0)
						  {
							printf ("\nYou can't. This is the first entry.");
							break;
						  }
						  else
						  {
						  	l--;
						  	valid = 1;
						  	break;
						  }
				case 'E':
				case 'e': printf ("\nOk! Sending you back to Manage Data Menu...\n");
						  exit = 1;
						  valid = 1;
						  break;
				default: printf ("\nInvalid input.\n");		
			}
		} while (valid == 0);
		
		valid = 0;
	}
}

/*  deleteEntry manages the deletion process of entries
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
 	@param nEntry - the number of entries in the dataset
*/
void 
deleteEntry (struct pair *eptr [], int * nEntry)
{
	int i = 0;
	int valid = 0;
	int exit = 0;
	char input1 = '*';
	int input2;
	
	if (*nEntry == 0)
	{
		printf ("\nNo existing entry. Please use the Add Entry function first.\n");
		printf ("Sending you back to the Manage Data Menu...\n");
	}
	else
	{
		while (exit == 0 && *nEntry != 0)
		{
			printf ("\nEntry %d:\n", i + 1);
			displayOldEntry (i, &*eptr);
			
			do
			{
				printf ("\nNext [N] | Previous [P] | Proceed to Deleting [D]\n");
				printf ("\nEnter a key: ");
				scanf (" %c", &input1);
				fflush (stdin);
				
				switch (input1)
				{
					case 'N':
					case 'n': if (i == (*nEntry) - 1)
							  {
								printf ("\nYou can't. This is the last entry.");
								break;
							  }
							  else
							  {
							  	i++;
							  	valid = 1;
							  	break;
							  }
					case 'P':
					case 'p': if (i == 0)
							  {
								printf ("\nYou can't. This is the first entry.");
								break;
							  }
							  else
							  {
							  	i--;
							  	valid = 1;
							  	break;
							  }
					case 'D':
					case 'd': exit = 1;
							  valid = 1;
							  break;
					default: printf ("\nInvalid input.\n");		
				}
			} while (valid == 0);
			
			valid = 0;
		}
	
		printf ("\nWhich entry should I delete?: ");
		scanf ("%d", &input2);
		
		if (input2 < 1 || input2 > *nEntry)
			printf ("\nInvalid input. Returning to Manage Data Menu...\n");
		else
		{
			removeEntry (&*eptr, input2, *nEntry);
			(*nEntry)--;
		}
	}
}

/*  removeEntry deletes a whole entry based on the user's input
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
 	@param idEntry - an integer that represents the index of the entry to be edited
 	@param nEntry - the number of entries in the dataset
*/
void 
removeEntry (struct pair * eptr [], int idEntry, int nEntry)
{
	int i;
	int index = idEntry - 1;
	
	for (i = index; i < nEntry-1; i++)
		*eptr [i] = *eptr [i + 1];
	
	for (i = 0; i < 10; i++)
	{
		strcpy (eptr [nEntry - 1]->language[i], "");
		strcpy (eptr [nEntry - 1]->trans[i], "");
	}
	
	eptr [nEntry-1]->count = 0;
	sortEntries (&*eptr, nEntry);
	printf ("\nDelete successful. Returning to Manage Data Menu...\n");
}

/*  deleteTranslation manages the deletion process of a language-translation pair in an entry
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
 	@param nEntry - the number of entries in the dataset
*/
void 
deleteTranslation (struct pair *eptr [], int * nEntry)
{
	int i = 0;
	int valid = 0;
	int exit = 0;
	char input1 = '*';
	int input2;
	
	
	if (*nEntry == 0)
	{
		printf ("\nNo existing entry. Please use the Add Entry function first.\n");
		printf ("Sending you back to the Manage Data Menu...\n");
	}
	else
	{
		while (exit == 0 && *nEntry != 0)
		{
			printf ("\nEntry %d:\n", i + 1);
			displayOldEntry (i, &*eptr);
			
			do
			{
				printf ("\nNext [N] | Previous [P] | Proceed to Deleting [D]\n");
				printf ("\nEnter a key: ");
				scanf (" %c", &input1);
				fflush (stdin);
				
				switch (input1)
				{
					case 'N':
					case 'n': if (i == (*nEntry) - 1)
							  {
								printf ("\nYou can't. This is the last entry.");
								break;
							  }
							  else
							  {
							  	i++;
							  	valid = 1;
							  	break;
							  }
					case 'P':
					case 'p': if (i == 0)
							  {
								printf ("\nYou can't. This is the first entry.");
								break;
							  }
							  else
							  {
							  	i--;
							  	valid = 1;
							  	break;
							  }
					case 'D':
					case 'd': exit = 1;
							  valid = 1;
							  break;
					default: printf ("\nInvalid input.\n");		
				}
			} while (valid == 0);
			
			valid = 0;
		}
	
		printf ("\nWhich entry should I delete from?: ");
		scanf ("%d", &input2);
		
		if (input2 < 1 || input2 > *nEntry)
			printf ("\nInvalid input. Returning to Manage Data Menu...\n");
		else
			removeTranslation (&*eptr, input2, &*nEntry);
	}
}

/*  removeTranslation deletes a whole entry based on the user's input
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
 	@param idEntry - an integer that represents the index of the entry to be edited
 	@param nEntry - the number of entries in the dataset
*/
void 
removeTranslation (struct pair * eptr [], int idEntry, int * nEntry)
{
	int i, j;
	int input1;
	char input2 = '*';
	int exit = 0;
	int valid = 0;
	int index = idEntry - 1;
	
	do
	{
		displayOldEntry (index, &*eptr);
		
		printf ("\nWhich pair should I delete?: ");
		scanf ("%d", &input1);
		
		if (input1 < 1 || input1 > eptr [index]->count)
		{
			printf ("\nInvalid input. Returning to Manage Data Menu...\n");
			exit = 1;
		}
		else
		{
			for (i = input1 - 1; i < eptr [index]->count - 1; i++)
			{
				strcpy (eptr [index]->language [i], eptr [index]->language [i + 1]);
				strcpy (eptr [index]->trans [i], eptr [index]->trans [i + 1]);
			}
			strcpy (eptr [index]->language[eptr [index]->count - 1], "");
			strcpy (eptr [index]->trans[eptr [index]->count - 1], "");
			eptr [index]->count--;
			printf ("\nDelete successful.");
			
			while (valid == 0 && eptr [index]->count != 0)
			{
				printf ("\nWould you like to continue deleting pairs? [Y/N]: ");
				scanf (" %c", &input2);
				fflush (stdin);
				
				switch (input2)
				{
					case 'Y':
					case 'y': valid = 1;
							  break;
					case 'N':
					case 'n': printf ("\nOk! Returning to Managa Data menu...\n");	
							  valid = 1;
							  exit = 1;
							  break;
					default: printf ("\nInvalid input.\n");	
				}
			}
			
			valid = 0;
		}
		
		if (eptr [index]->count == 0)															// delete entry once all pairs are deleted
		{
			for (j = index; j < *nEntry - 1; j++)
			{
				*eptr [j] = *eptr [j + 1];
			}
			
			for (j = 0; j < 10; j++)
			{
				strcpy (eptr [*nEntry - 1]->language[j], "");
				strcpy (eptr [*nEntry - 1]->trans[j], "");
			}
			eptr [*nEntry-1]->count = 0;
			(*nEntry)--;
			printf ("\nAll translation pairs in the entry has been deleted. Returning to Manage Data Menu...\n");
			exit = 1;
		}
	} while (exit == 0);
	
	sortEntries (&*eptr, *nEntry);
}

/*  exportFile exports the content of struct pair entry into a file
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
 	@param nEntry - the number of entries in the dataset
*/
void 
exportFile (struct pair * eptr [], int nEntry)
{
	FILE * fptr;
	int i, j;
	char filename [31];
	char prompt [] = "\nEnter file name to EXPORT (max. 30 characters w/ extension): ";
	
	ifValidTxtInput (prompt, filename, 30);
	printf ("\nExporting file....");
	fptr = fopen (filename, "w");
	
	for (i = 0; i < nEntry; i++)
	{
		for (j = 0; j < eptr [i]->count; j++)
		{
			fprintf (fptr, "%s: %s\n", eptr [i]->language [j], eptr [i]->trans [j]);
		}
		
		fprintf (fptr, "\n");
	}
	
	printf ("\nSuccessfully exported file! Returning to Manage Data Menu...\n");
	
	fclose (fptr);
}

/*  importFile deletes a whole entry based on the user's input
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
 	@param nEntry - the number of entries in the dataset
 	@return 1 if a file has been imported and 0 if not
*/
int 
importFile (struct pair * eptr [], int * nEntry)
{
	FILE * fptr;
	int i = 0, j, k, l;
	int valid = 0;
	int open = 0;
	int start_nEntry = *nEntry;
	char input = '*';
	char filename [31];
	char prompt [] = "\nEnter file name to IMPORT (max. 30 characters w/ extension): ";
	
	struct pair temp;
	char spaces [1][43];																				
	
	ifValidTxtInput (prompt, filename, 30);
	printf ("\nImporting file....");
	fptr = fopen (filename, "r");
	
	if (fptr != NULL)
	{
		open = 1;
		
		while (feof (fptr) == 0)
		{
			fgets (spaces [0], 44, fptr);																// store a line to detect newlines
			
			if (spaces [0][0] != '\n')																	// show entry when newline is the first character
			{
				sscanf (spaces [0], "%[^:] : %[^\n]\n", temp.language [i], temp.trans [i]);
				i++;
				temp.count++;
			}
			else if (start_nEntry == 0)
			{
				for (j = 0; j < temp.count; j++)
				{
					strcpy (eptr [*nEntry]->language [j], temp.language [j]);
					strcpy (eptr [*nEntry]->trans [j], temp.trans [j]);
				}
				eptr [*nEntry]->count = temp.count;
				(*nEntry)++;
				sortEntries (&*eptr, *nEntry);
				i = 0;
				temp.count = 0;
			}
			else if (*nEntry != 150)
			{
				printf ("\nCount: %d", temp.count);
				printf ("\n%-20s|%s\n", "Language", "Translation");
				for (k = 0; k < temp.count; k++)
					printf ("\n%-20s|%s", temp.language [k], temp.trans [k]);
				printf ("\n------------------------------------------------------------------\n");
				
				do
				{
					printf ("\nWould you like to add this entry? [Y/N]: ");
					scanf (" %c", &input);
					fflush (stdin);
					
					switch (input)
					{
						case 'Y':
						case 'y': for (l = 0; l < temp.count; l++)
								  {
										strcpy (eptr [*nEntry]->language [l], temp.language [l]);
										strcpy (eptr [*nEntry]->trans [l], temp.trans [l]);
								  }
								  eptr [*nEntry]->count = temp.count;
								  (*nEntry)++;
								  sortEntries (&*eptr, *nEntry);
								  i = 0;
								  temp.count = 0;
								  valid = 1;
								  break;
						case 'N':
						case 'n': i = 0;
								  temp.count = 0;
								  valid = 1;
								  break;
						default: printf ("\nInvalid input.\n");
					}
				} while (valid == 0);
				valid = 0;
			}
		}
		printf ("\nSuccessfully imported file!\n");
	}
	else
		printf ("\nFile does not exist. Returning to the previous menu...\n");
	
	fclose (fptr);
	return open;
}

/*  sortEntries sort the entries that have an English translation pair and all language-translation pairs in entries alphabetically
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
 	@param nEntry - the number of entries in the dataset
 	Precondition: There are entries to sort
*/
void 
sortEntries (struct pair * eptr [], int nEntry)
{
	int i, j, k, l, m;
	int nEnglish = 0;
	int iEng1, iEng2;
	struct pair temp;
	struct pair key;
	
	for (i = 1; i < nEntry; i++)
	{
		key = *eptr [i];
		j = i - 1;
		
		while (j >= 0 && check4EnglishPair (&*eptr, *eptr [j]) < check4EnglishPair (&*eptr, key))					// when key's left neighbor do not contain an English pair, key moves
		{																											// to the left (insertion sort)
			*eptr [j + 1] = *eptr [j];
			j = j - 1;
		}
		*eptr [j + 1] = key;
	}
	
	for (k = 0; k < nEntry; k++)																					// getting the number of entries with English as a language
		if (check4EnglishPair (&*eptr, *eptr [k]) == 1)
			nEnglish++;
	
	for (l = 0; l < nEnglish; l++)
		for (m = 0; m < nEnglish-1; m++)
		{
			iEng1 = findEnglishPair (&*eptr, *eptr [m]);															// gets index where English pair is initialized
			iEng2 = findEnglishPair (&*eptr, *eptr [m + 1]);															
			
			if (strcmp (eptr [m + 1]->trans [iEng2], eptr [m]->trans [iEng1]) < 0)
			{
				temp = *eptr [m];
				*eptr [m] = *eptr [m + 1];
				*eptr [m + 1] = temp;
			}
		}
}

/*  findEnglishPair returns the index of the English translation pair in an entry
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
 	@param sVar - a struct var that contains the language-translation pairs and its count
 	@return the index of the English translation pair in an entry
 	Precondition: sVar has an English pair and pairs are sorted alphabetically based on language
*/
int 
findEnglishPair (struct pair *eptr [], struct pair sVar)
{
	int i;
	int index;
	
	for (i = 0; i < sVar.count; i++)
		if (strcmp (sVar.language [i], "English") == 0)
		{
			index = i;
			i = sVar.count;
		}
	
	return index;
}

/*  check4EnglishPair checks for an English translation pair in a particular entry
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
 	@param sVar - a struct var that contains the language-translation pairs and its count
*/
int 
check4EnglishPair (struct pair *eptr [], struct pair sVar)
{
	int i, found = 0;
	
	for (i = 0; i < sVar.count; i++)
		if (strcmp (sVar.language [i], "English") == 0)
		{
			found = 1;
			i = sVar.count;
		}
	
	return found;
}

/*  sortAscendingPairs sorts the language-translation pairs in an entry
 	@param eptr - an array containing struct pointers to array of structures struct pair entry
 	@param idEntry - an integer that represents the index of the entry to be edited
*/
void 
sortAscendingPairs (struct pair *eptr [], int idEntry)
{
	int i, j;
	
	for (i = 0; i < eptr [idEntry]->count; i++)
		for (j = 0; j < eptr [idEntry]->count-1; j++)
		{
			if (strcmp (eptr [idEntry]->language [j + 1], eptr [idEntry]->language [j]) < 0)
			{
				stringSwap (eptr [idEntry]->language [j], eptr [idEntry]->language [j + 1]);
				stringSwap (eptr [idEntry]->trans [j], eptr [idEntry]->trans [j + 1]);
			}
			else if (strcmp (eptr [idEntry]->language [j + 1], eptr [idEntry]->language [j]) == 0
					&& strcmp (eptr [idEntry]->trans [j + 1], eptr [idEntry]->trans [j]) < 0)
			{
				stringSwap (eptr [idEntry]->language [j], eptr [idEntry]->language [j + 1]);
				stringSwap (eptr [idEntry]->trans [j], eptr [idEntry]->trans [j + 1]);
			}
		}
}

/*  stringSwap swaps the content of two strings
 	@param strWord1 - a string that contains the language or translation of a pair
	@param strWord2 - a string that contains the language or translation of a pair
*/
void 
stringSwap (char strWord1 [], char strWord2 [])
{
	Str20 temp;
	
	strcpy (temp, strWord1);
	strcpy (strWord1, strWord2);
	strcpy (strWord2, temp);
}

/*  capltzStr capitalizes the first letter of aa string
 	@param strWord - a string that contains the language or translation of a pair
 	Precondition: strWord only contains letters
*/
void 
capltzStr (char strWord [])
{	
	if (strWord [0] < 'A' || strWord [0] > 'Z')
		strWord [0] -= 32;
	
	lcaseStr (strWord + 1);
}

/*  lcaseStr sets the letters of a string to lowercase letter
 	@param strWord - a string that contains the language or translation of a pair
 	Precondition: strWord only contains letters
*/
void 
lcaseStr (char strWord [])
{
	int i;
	
	for (i = 0; i < strlen (strWord); i++)
		if (strWord [i] < 'a' || strWord [i] > 'z')
			strWord [i] += 32;
}

/*  checkOldEntry checks and displays the entries that contains the language-translation pair
 	@param strWord1 - a string that contains the language or translation of a pair
	@param strWord2 - a string that contains the language or translation of a pair
	@param eptr - an array containing struct pointers to array of structures struct pair entry
*/
void 
checkOldEntry (char strWord1 [], char strWord2 [], struct pair * eptr [])
{
	int i, j;
	
	for (i = 0; i < 150; i++)
		for (j = 0; j < 10; j++)
			if (strcmp(strWord1, eptr [i]->language [j]) == 0 && strcmp(strWord2, eptr [i]->trans [j]) == 0)
			{
				printf ("\nEntry %d:\n", i+1);
				displayOldEntry (i, &*eptr);
				j = 10;
			}
}

/*  nOldEntry returns the number of entries that contains the language-translation pair
 	@param strWord1 - a string that contains the language or translation of a pair
	@param strWord2 - a string that contains the language or translation of a pair
	@param eptr - an array containing struct pointers to array of structures struct pair entry
	@return the number of entries that contains the language-translation pair
*/
int 
nOldEntry (char strWord1 [], char strWord2 [], struct pair * eptr [])
{
	int i, j;
	int found = 0;
	
	for (i = 0; i < 150; i++)
		for (j = 0; j < 10; j++)
			if (strcmp(strWord1, eptr [i]->language [j]) == 0 && strcmp(strWord2, eptr [i]->trans [j]) == 0)
			{
				found++;
				j = 10;
			}
	
	return found;
}

/*  checkIfDuplicatePair checks if a language-translation pair is already in the same entry
	@param idEntry - an integer that represents the index of a particular entry
 	@param strWord1 - a string that contains the language or translation of a pair
	@param strWord2 - a string that contains the language or translation of a pair
	@param eptr - an array containing struct pointers to array of structures struct pair entry
	@return 1 if a duplicate has been found and 0 if not
*/
int 
checkIfDuplicatePair (int idEntry, char strWord1 [], char strWord2 [], struct pair * eptr [])
{
	int i;
	int dupe = 0;
	
	for (i = 0; i < 10; i++)
		if (strcmp(strWord1, eptr [idEntry]->language [i]) == 0 && strcmp(strWord2, eptr [idEntry]->trans [i]) == 0)
		{
			dupe = 1;
			i = 10;
		}
	
	return dupe;
}

/*  findSimilarEntry checks if an entry contains a certain language-translation pair and gets its index number
 	@param strWord1 - a string that contains the language or translation of a pair
	@param strWord2 - a string that contains the language or translation of a pair
	@param arrIndex - an array containing indices of entries with similar language-translation pairs
	@param eptr - an array containing struct pointers to array of structures struct pair entry
*/
void 
findSimilarEntry (char strWord1 [], char strWord2 [], int arrIndex [], struct pair * eptr [])
{
	int i, j, k = 0;
	
	for (i = 0; i < 150; i++)
		for (j = 0; j < 10; j++)
			if (strcmp(strWord1, eptr [i]->language [j]) == 0 && strcmp(strWord2, eptr [i]->trans [j]) == 0)
			{
				arrIndex [k] = i;
				k++;
				j = 10;
			}
}

/*  displayOldEntry displays an entry given the entry's index
	@param idEntry - an integer that represents the index of a particular entry
	@param eptr - an array containing struct pointers to array of structures struct pair entry
*/
void 
displayOldEntry (int idEntry, struct pair * eptr [])
{
	int i, x;
	
	x =  eptr [idEntry]->count;
	printf ("\nCount: %d", x);
	printf ("\n%-20s|%s\n", "Language", "Translation");
	
	for (i = 0; i < x; i++)
		printf ("\n%-20s|%s", eptr [idEntry]->language [i], eptr [idEntry]->trans [i]);
	
	printf ("\n------------------------------------------------------------------\n");
}

/*  trimNewline trims the newline character on a string
	@param strWord - a string that contains the language or translation of a pair
	Precondition: strWord only contains letters and the fgets function was used prior to function call
*/
void 
trimNewline (char strWord [])
{
	int i;
	
	for (i = 0; i < strlen (strWord); i++)												// trimming excess newline in string
		if (strWord [i] == '\n')
			strWord [i] = '\0';
}

/*  checkIfLetters checks if a string only contains letters
	@param strWord - a string that contains the language or translation of a pair
	@return 1 if strWord only contains letters and 0 if not
*/
int 
checkIfLetters (char strWord [])
{
	int i;
	int valid = 1;
	
	for (i = 0; i < strlen (strWord); i++)
		if (isalpha (strWord [i]) == 0)
			valid = 0;
	
	return valid;
}

/*  ifValidStrInput checks if a string input is of appropriate length and only containing letters
	@param prompt - a string that prompts the user what to input
	@param strWord - a string that contains the language or translation of a pair
	@param nLength - the maximum length of an input string
*/
void 
ifValidStrInput (char prompt [], char strWord [], int nLength)
{
	int valid = 0;
	
	do
	{
		printf ("%s", prompt);
		fgets (strWord, nLength + 2, stdin);
		
		trimNewline (strWord);
		fflush (stdin);
		
		if (strlen (strWord) > nLength || strlen (strWord) < 1)
			printf ("\nInvalid input length.");
		else if (checkIfLetters (strWord) == 0)
			printf ("\nPlease only input letters.");
		else
			valid = 1;
	} while (valid == 0);
}

/*  ifValidTxtInput checks if a string input is of appropriate length
	@param prompt - a string that prompts the user what to input
	@param strWord - a string that contains the language or translation of a pair
	@param nLength - the maximum length of an input string
*/
void 
ifValidTxtInput (char prompt [], char strWord [], int nLength)
{
	int valid = 0;
	
	do
	{
		printf ("%s", prompt);
		fgets (strWord, nLength + 2, stdin);
		
		trimNewline (strWord);
		fflush (stdin);
		
		if (strlen (strWord) > nLength || strlen (strWord) < 1)
			printf ("\nInvalid input length.");
		else
			valid = 1;
	} while (valid == 0);
}

