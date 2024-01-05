/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 1
Full Name  : Manav Alpeshbhai countadafiya
Student ID#: 144095221
Email      : macountadafiya@myseneca.ca
Section    : countEE

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
    int i, count = 0;
    char input;

    scanf(" %c", &input);
    while (count == 0) {
        for (i = 0; str[i] != '\0'; i++) {
            if (input == str[i]) {
                count++;
            }
        }

        if (count == 0) {
            printf("ERROR: Character must be one of [%s]: ", str);
            scanf(" %c", &input);
        }
    }

    clearInputBuffer();
    return input;
}

//Function guarantees a C string value is entered containing the number of characters within the range specified by the 2nd and 3rd arguments.
void inputCString(char* str, int minChar, int maxChar) {
    int i;
    int count = 0;
    char inputValue[100] = { 0 };

    do
    {
        count = 0;
        scanf(" %99[^\n]", inputValue);

        for (i = 0; inputValue[i] != '\0'; i++)
        {
            count++;
        }
        if (!(count <= maxChar && count >= minChar))
        {
            if (minChar == maxChar)
            {
                printf("ERROR: String length must be exactly %d chars: ", maxChar);
            }
            else if (minChar != maxChar)
            {
                if (count > maxChar)
                {
                    printf("ERROR: String length must be no more than %d chars: ", maxChar);
                }
                else if (count < minChar)
                {
                    printf("ERROR: String length must be between %d and %d chars: ", minChar, maxChar);
                }
            }
        }
    } while (!(count <= maxChar && count >= minChar));

    for (i = 0; inputValue[i] != '\0'; i++)
    {
        str[i] = inputValue[i];
    }
}



//Function display an array of 10-character digits as a formatted phone number.
void displayFormattedPhone(const char* str) {
    int flag = 1;
    int i = 0;

    if (str != NULL)
    {
        for (i = 0; str[i] && flag; i++)
        {
            if (str[i] < 48 || str[i] > 57)
            {
                flag = 0;
            }
        }
    } 
    
    if (i == 10 && flag == 1)
    {
        printf("(");

        for (i = 0; i < 3; i++)
        {
            printf("%c", str[i]);
        }
        printf(")");

        for (i = 3; i < 6; i++)
        {
            printf("%c", str[i]);
        }
        printf("-");

        for (i = 6; i < 10; i++)
        {
            printf("%c", str[i]);
        }
    }
    else
    {
        printf("(___)___-____");
    }
}
