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
// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("\nPatient record updated!\n\n");
        }

    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
	int recordsfound = 0, i;

	displayPatientTableHeader();

	for (i = 0; i < max; i++) {

		if (patient[i].patientNumber != 0) {

			recordsfound = 1;
			displayPatientData(&patient[i], fmt);
		}
	}
	if (!recordsfound) {

		printf("*** no records found ***");
	}

	putchar('\n');
}



// Search for a patient record based on patient number or phone number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientData(const struct Patient patient[], int max)
{
	int selection;


	do {

		printf("Search Options\n"
			"==========================\n"
			"1) By patient number\n"
			"2) By phone number\n"
			"..........................\n"
			"0) Previous menu\n"
			"..........................\n"
			"Selection: ");

		selection = inputIntRange(0, 2);
		putchar('\n');

		if (selection == 1) {

			searchPatientByPatientNumber(patient, max);
			putchar('\n');
			suspend();
		}
		else if (selection == 2) {

			searchPatientByPhoneNumber(patient, max);
			putchar('\n');
			suspend();
		}

	} while (selection);
}


// Add a new patient record to the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void addPatient(struct Patient patient[], int max)
{
	int emptyIndex = 0, foundSpace = 0, i;


	for (i = 0; i <= max && !foundSpace; i++) {

		if (patient[i].patientNumber == 0) {

			foundSpace = 1;
			emptyIndex = i;
		}
	}
	if (foundSpace && emptyIndex < max) {

		patient[emptyIndex].patientNumber = nextPatientNumber(patient, max);

		inputPatient(&patient[emptyIndex]);
		putchar('\n');
		printf("*** New patient record added ***\n\n");
	}
	else {
		printf("ERROR: Patient listing is FULL!\n\n");
	}

}


// Edit a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void editPatient(struct Patient patient[], int max)
{
	int number = 0, result = 0;

	printf("Enter the patient number: ");

	number = inputIntPositive();

	putchar('\n');

	result = findPatientIndexByPatientNum(number, patient, max);

	if (result != -1) {
		menuPatientEdit(&patient[result]);
	}
	else {
		printf("ERROR: Patient record not found!\n");
	}
}


// Remove a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void removePatient(struct Patient patient[], int max)
{
	int number = 0, result = 0;
	char selection;

	printf("Enter the patient number: ");
	number = inputIntPositive();

	result = findPatientIndexByPatientNum(number, patient, max);
	if (result != -1) {

		putchar('\n');
		displayPatientData(&patient[result], FMT_FORM);

		putchar('\n');
		printf("Are you sure you want to remove this patient record? (y/n): ");

		selection = !(inputCharOption("yn") == 'y');

		if (!selection) {

			patient[result].patientNumber = 0;
			strcpy(patient[result].name, "\0");
			strcpy(patient[result].phone.description, "\0");
			strcpy(patient[result].phone.number, "\0");

			printf("Patient record has been removed!\n\n");
		}

		else {

			printf("Operation aborted.\n\n");
		}
	}
	else {

		putchar('\n');
		printf("ERROR: Patient record not found!\n\n");
	}
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
	int number = 0, searchResult = 0;

	printf("Search by patient number: ");

	number = inputIntPositive();

	putchar('\n');
	searchResult = findPatientIndexByPatientNum(number, patient, max);

	if (searchResult != -1) {

		displayPatientData(&patient[searchResult], FMT_FORM);
	}
	else {

		printf("*** No records found ***\n");
	}
}



// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
	int recordsFound = 0, i;
	char phone[PHONE_LEN + 1] = { 0 };

	printf("Search by phone number: ");

	inputCString(phone, PHONE_LEN, PHONE_LEN);
	putchar('\n');

	displayPatientTableHeader();

	for (i = 0; i <= max; i++) {

		if (strcmp(patient[i].phone.number, phone) == 0) {

			recordsFound = 1;
			displayPatientData(&patient[i], FMT_TABLE);
		}
	}
	if (!recordsFound) {

		putchar('\n');
		printf("*** No records found ***\n");
	}
}


// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int nextPatientNumber(const struct Patient patient[], int max)
{
	int largestNum = 0, i;

	for (i = 0; i <= max; i++) {

		if (patient[i].patientNumber > largestNum) {

			largestNum = patient[i].patientNumber;
		}
	}

	largestNum += 1;

	return largestNum;
}


// Find the patient array index by patient number (returns -1 if not found)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int findPatientIndexByPatientNum(int patientNumber,
	const struct Patient patient[], int max)
{
	int patientIndex, i;

	patientIndex = -1;

	for (i = 0; i <= max; i++) {

		if (patient[i].patientNumber == patientNumber) {

			patientIndex = i;
		}
	}

	return patientIndex;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPatient(struct Patient* patient)
{
	printf("Patient Data Input\n"
		"------------------\n"
		"Number: %05d\n"
		"Name  : ",
		patient->patientNumber);

	inputCString(patient->name, 2, NAME_LEN);
	putchar('\n');
	inputPhoneData(&patient->phone);

}


// Get user input for phone contact information
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPhoneData(struct Phone* phone)
{
	int selection = 0;

	printf("Phone Information\n"
		"-----------------\n"
		"How will the patient like to be contacted?\n"
		"1. Cell\n"
		"2. Home\n"
		"3. Work\n"
		"4. TBD\n"
		"Selection: ");

	selection = inputIntRange(1, 4);

	switch (selection) {
	case 1:
		strcpy(phone->description, "CELL");
		break;

	case 2:
		strcpy(phone->description, "HOME");
		break;

	case 3:
		strcpy(phone->description, "WORK");
		break;

	case 4:
		strcpy(phone->description, "TBD");
		break;
	}

	if (selection != 4) {

		putchar('\n');
		printf("Contact: %s\n"
			"Number : ",
			phone->description);
		inputCString(phone->number, PHONE_LEN, PHONE_LEN);
	}
	else {
		phone->number[0] = '\0';
	}
}