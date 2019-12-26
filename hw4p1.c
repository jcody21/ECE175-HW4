#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>


/*
Author: John Cody
 Date created: 02/11/2018
 Program Description: This program takes a file titled encrypted as an input and then outputs to a file called decrypted with the decrypted message. 
The program makes use of the mod, decrypt_fun, and encrypt_fun functions to ease read-ability. Program also encrypts the file if the user wants to. 
*/

int mod(int x, int y); 
char decrypt_fun(int shift, char letter);       //Giving function declarations. 
char encrypt_fun(int shift, char letter); 

int main(void) {

	FILE*input;        // Creating the files pointers
	FILE*output;
	
	int k = 0;
	char temp = NULL;
	
	char encrypt = 'A';             // Declaring some variables
	int key = 0;

	while (k != 3) {
		printf("Enter the decryption key:");      // Getting the correct declaration key from the user
		scanf("%d", &k);

		if (k != 3) {
			printf("\nWrong key\n");
		}
	}

	input = fopen("encrypted.txt", "r");       // Assigning the file pointers. 
	output = fopen("decrypted.txt", "w");

	if (input == NULL) {
		printf("The encrypted file could not be found. (Error)");       // Checking to ensure that the pointers actually work
		return -1;
	}
	if (output == NULL) {
		printf("The decryped file could not be found. (Error)");
		return -1;
	}

	while (feof(input) < 1) {
		fscanf(input, "%c", &temp);                    // Workhorse of the program that loops through the input file transfering everything to output
		fprintf(output, "%c", decrypt_fun(k,temp));
	}

	printf("\nFile decrypted!\n");           // Alerts the user that the conversion was successful

	fclose(input);            // Closes out the files
	fclose(output); 
	
	while (encrypt != 'y' && encrypt != 'n') {
		printf("Do you want to re-encrypt the file (y/n)? \n");       // Prompts the user to decide wheather to encrypt the file or not. 
		scanf(" %c", &encrypt);
	}

	if (encrypt == 'n') {
		return 0;                  // If the user decides not the encrypt, the program is over. 
	}

	printf("Enter an encryption key:");       // Otherwise, the user is prompted to determine the new encryption key
	scanf("%d", &key);

	FILE*decrypted;          // Creates new file pointers
	FILE*encrypted;

	decrypted = fopen("decrypted.txt", "r");     // Sets the pointers to actual files
	encrypted = fopen("encrypted.txt", "w");

	if (decrypted == NULL) {
		printf("The decrypted file could not be found. (Error)");     // Checks to make sure that the pointers actually work
		return -1;
	}
	if (encrypted == NULL) {
		printf("The test file could not be found. (Error)");
		return -1;
	}

	while (feof(decrypted) < 1) {
		fscanf(decrypted, "%c", &temp);      // The other program workhorse that loops through the decrypted file to output to the encrypted file
		fprintf(encrypted, "%c", encrypt_fun(key, temp));    
	}

	printf("\nFile encrypted! \nGoodbye\n");  // Informs user that the program was successful
	
	fclose(decrypted);        // Closes out the files
	fclose(encrypted); 

	return 0;    // Fin
}

int mod(int x, int y) {
	while (x < 0) {
		x += y;
	}
	return x%y;
}

char decrypt_fun(int shift, char letter) {
	if (!((letter > 96) && (letter < 123)) && !((letter > 64) && (letter < 91))) {  // Tests to find if the letter is within the two alphabets
		return letter;      // Otherwise it must be a punctuation or whitespace character, so it just gets output. 
	}
	else if (isupper(letter) > 0) {
		letter = mod(letter - shift - 'A', 26) + 'A';        // does the devcryption for the upper case letters
		return letter;
	}
	else {
		letter = mod(letter - shift - 'a', 26) + 'a';       // does the decryption for the lower case letters
		return letter;
	}
}

char encrypt_fun(int shift, char letter) {
	if (!((letter > 96) && (letter < 123)) && !((letter > 64) && (letter < 91))) {   // Tests to find if the letter is within the two alphabets
		return letter;                        // Otherwise it must be a punctuation or whitespace character, so it just gets output.
	}
	else if (isupper(letter) > 0) {
		letter = mod(letter + shift - 'A', 26) + 'A';          // does the encryption for the upper case letters
		return letter;
	}
	else {
		letter = mod(letter + shift - 'a', 26) + 'a';         // does the encryption for the lower case letters
		return letter;
	}
}