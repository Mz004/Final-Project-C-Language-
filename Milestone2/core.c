/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 2
Full Name  : Manav ALpeshbhai Zadafiya
Student ID#: 144095221
Email      : mazadafiya@myseneca.ca
Section    : ZEE

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "core.h"

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

//Function guarantee an integer value is entered and returned.
int inputInt(void) {
    char ch = ' ';
    int value;

    scanf("%d%c", &value, &ch);
    while (ch != '\n') {
        clearInputBuffer();
        printf("Error! Input a whole number: ");
        scanf("%d%c", &value, &ch);
    }

    return value; //If character == '\n', then  appropriate value was entered
}

//Function guarantees a positive integer value is entered and returned.
int inputIntPositive(void) {
    char ch = ' ';
    int value;


    scanf("%d%c", &value, &ch);
    while (value <= 0) {
        printf("ERROR! Value must be > 0: ");
        if (ch != '\n') {
            clearInputBuffer();
            printf("Error! Input a number: ");
        }
        scanf("%d%c", &value, &ch);
    }

    return value;
}

//Function guarantees that an integer value is entered within the range (inclusive) and returned.
int inputIntRange(int lowerBound, int upperBound) {
    char ch = ' ';
    int value;

    scanf("%d%c", &value, &ch);
    while (!(value <= upperBound && value >= lowerBound)) {
        if (ch != '\n') {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
        else if (!(value <= upperBound && value >= lowerBound)) {
            printf("ERROR! Value must be between -3 and 11 inclusive: ");
        }
        scanf("%d%c", &value, &ch);
    }

    return value;
}

//Function guarantees a single character value is entered within the list of valid characters and returned.
char inputCharOption(const char str[]) {
    int count = 0;
    char input;

    scanf(" %c", &input);
    while (count == 0) {
        if (strchr(str, input) == NULL) {
            printf("ERROR: Character must be one of [%s]: ", str);
            scanf(" %c", &input);
        }
        else {
            count++;
        }
    }

    clearInputBuffer();
    return input;
}

//Function guarantees a C string value is entered containing the number of characters within the range specified by the 2nd and 3rd arguments.
void inputCString(char str[], int minChar, int maxChar)
{
    char string[100] = { 0 };
    int len = 0, flag = 0;

    do {
        len = 0;
        scanf("%99[^\n]", string);
        clearInputBuffer();
        len = strlen(string);
        if (minChar == maxChar && len != minChar) {
            printf("ERROR: String length must be exactly %d chars: ",
                minChar);
        }

        else if (len > maxChar) {
            printf("ERROR: String length must be no more than %d chars: ",
                maxChar);
        }
        else if (len < minChar) {
            printf("ERROR: String length must be between %d and %d chars: ",
                minChar, maxChar);
        }
        else {
            flag = 1;
        }

    } while (!flag);

    strcpy(str, string);
}

//Function display an array of 10-character digits as a formatted phone number.
void displayFormattedPhone(const char* str) {
    int len = 0, i;

    len = strlen(str);

    if (len == 10) {
        i = 0;
        printf("(");
        while (i < 3) {
            printf("%c", str[i]);
            i++;
        }
        printf(")");
        while (i < 6) {
            printf("%c", str[i]);
            i++;
        }
        printf("-");
        while (i < 10) {
            printf("%c", str[i]);
            i++;
        }
    }
    else {
        printf("(___)___-____");
    }
    if (str != 0) {
        for (i = 0; str[i] != '\0'; i++)
            len++;
    }
}
//
// Copy your work done from Milestone #1 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
// - Also copy the commented "sections" to help with finding functions quickly!
//
