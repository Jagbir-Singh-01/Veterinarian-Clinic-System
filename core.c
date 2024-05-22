/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Jagbir Singh
Student ID#: 144019221
Email      : jagbir-singh1@myseneca.ca
Section    : NBB

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////
// Checking user is inputting an integer value

int inputInt(void) {
    int value;
    char newLine;

    do {
        scanf("%d%c", &value, &newLine);
        if (newLine != '\n') {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (newLine != '\n');

    return value;
}

// Checking user is inputting a positive integer
int inputIntPositive(void) {
    int value;

    do {
        value = inputInt();
        if (value <= 0) {
            printf("ERROR! Value must be > 0: ");
        }
    } while (value <= 0);

    return value;
}

// Checking inputted variable is within limits
int inputIntRange(int lowerLimit, int upperLimit) {
    int value;

    do {
        value = inputInt();
        if (value < lowerLimit || value > upperLimit) {
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerLimit, upperLimit);
        }
    } while (value < lowerLimit || value > upperLimit);

    return value;
}

//Cheching a character in a string
char inputCharOption(const char string[]) {
    char character, newLine;
    int i, flag = 0;

    do {
        scanf("%c%c", &character, &newLine);
        if (newLine == '\n') {
            for (i = 0; string[i] != '\0' && flag == 0; i++) {
                if (character == string[i]) {
                    flag = 1;
                }
            }
            if (flag == 0) {
                printf("ERROR: Character must be one of [%s]: ", string);
            }
        }
    } while (flag == 0);

    return character;
}

// Checking the string length is within the limit
void inputCString(char* cstringValue, int minCharacter, int maxCharacter) {
    int length;
    char string[31] = { '\0' };

    do {
        scanf("%[^\n]", string);
        clearInputBuffer();

        length = strlen(string);

        if (length < minCharacter || length > maxCharacter) {
            if (minCharacter == maxCharacter) {
                printf("Invalid 10-digit number! Number: ");
            }
            else if (length > maxCharacter) {
                printf("ERROR: String length must be no more than %d chars: ", maxCharacter);
            }
            else {
                printf("ERROR: String length must be between %d and %d chars: ", minCharacter, maxCharacter);
            }
        }
    } while (length < minCharacter || length > maxCharacter);

    strcpy(cstringValue, string);
}

// Displaying formatted phone number
void displayFormattedPhone(const char string[]) {
    int i, length, flag = 0;

    if (string == NULL) {
        printf("(___)___-____");
    }
    else {
        for (i = 0; string[i] != '\0'; i++) {
            if (string[i] < 48 || string[i] > 57) {
                flag = 1;
            }
        }
        length = strlen(string);

        if (length == 10 && flag == 0) {
            printf("(%c%c%c)%c%c%c-%c%c%c%c",
                string[0], string[1], string[2],
                string[3], string[4], string[5],
                string[6], string[7], string[8], string[9]);
        }
        else {
            printf("(___)___-____");
        }
    }
}

