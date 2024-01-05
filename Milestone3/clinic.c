/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Manav Zadafiya
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

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}

// Function to sort the values
void sort(struct Appointment appoints[], int max) {
    int i, j;
    struct Appointment temp;

    for (i = 0; i < max; i++)                                   // Storing all the date and time values in minutes for comparison
    {
        appoints[i].time.min = (appoints[i].date.year * 12 * 30 * 24 * 60) + (appoints[i].date.month * 30 * 24 * 60) + (appoints[i].date.day * 24 * 60) + (appoints[i].time.hour * 60) + appoints[i].time.min;
    }

    for (i = max - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (appoints[j].time.min > appoints[j + 1].time.min)
            {
                temp = appoints[j];
                appoints[j] = appoints[j + 1];
                appoints[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < max; i++)                                   // Converting total minutes back to minutes
    {                       
        appoints[i].time.min = appoints[i].time.min - (appoints[i].date.year * 12 * 30 * 24 * 60) - (appoints[i].date.month * 30 * 24 * 60) - (appoints[i].date.day * 24 * 60) - (appoints[i].time.hour * 60);
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
            menuAppointment(data);
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
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
        printf("*** New patient record added ***\n\n");
    }
    else {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    int number = 0, result = 0;
    char selection;
    struct Patient blankPatient = { 0 };

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

            patient[result] = blankPatient;

            printf("Patient record has been removed!\n\n");
        }
    }
    else {

        putchar('\n');
        printf("ERROR: Patient record not found!\n\n");
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data) {
    int i, j;

    // Sorting the data in the array
    sort(data->appointments, data->maxAppointments);

    // Displaying the patients
    displayScheduleTableHeader(NULL, 1);
    for (i = 0; i < data->maxAppointments; i++) 
    {
        for (j = 0; j < data->maxPatient; j++) 
        {
            if (data->appointments[i].patientNumber && data->patients[j].patientNumber) 
            {
                if (data->appointments[i].patientNumber == data->patients[j].patientNumber)
                {
                    displayScheduleData(&data->patients[j], &data->appointments[i], 1);
                }
            }
        }
    }
    printf("\n");
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data) {
    int lastDay = 31;
    int i, j;
    struct Date date;

    // Taking the year as input
    printf("Year        : ");
    date.year = inputIntPositive();

    // Taking the month as input
    printf("Month (1-12): ");
    date.month = inputIntRange(1, 12);

    // Taking the day as input
    printf("Day (1-");
    if (date.month == 4 || date.month == 9 || date.month == 11) {
        lastDay = 30;
    }
    if (date.month == 2) {
        lastDay = 28;
    }
    if (date.year % 4 == 0 && date.month == 2) {
        lastDay = 29;
    }

    printf("%d)  : ", lastDay);
    date.day = inputIntRange(1, lastDay);
    printf("\n");

    // Sorting the data is the array
    sort(data->appointments, data->maxAppointments);

    // Displaying the patients
    displayScheduleTableHeader(&date, 0);
    for (i = 0; i < data->maxAppointments; i++) 
    {
        for (j = 0; j < data->maxPatient; j++) 
        {
            if (data->appointments[i].patientNumber && data->patients[j].patientNumber) 
            {
                if (data->appointments[i].patientNumber == data->patients[j].patientNumber) 
                {
                    if (data->appointments[i].date.year == date.year && data->appointments[i].date.month == date.month && data->appointments[i].date.day == date.day) 
                    {
                        displayScheduleData(&data->patients[j], &data->appointments[i], 0);
                    }
                }
            }
        }
    }

    printf("\n");

}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* app, int maxAppointments, struct Patient* pt, int maxPatients) {
    // Declaring two temporary structs
    struct Date date;
    struct Time time;

    // Declaring variables
    int lastDay = 31;
    int patientNumber, index, slotNotAvailable = 1;

    // Taking the patient number as input
    printf("Patient Number: ");
    patientNumber = inputIntPositive();
    index = findPatientIndexByPatientNum(patientNumber, pt, maxPatients);

    if (index >= 0) {
        while (slotNotAvailable)
        {
            // Taking the year as input
            printf("Year        : ");
            date.year = inputIntPositive();

            // Taking the month as input
            printf("Month (1-12): ");
            date.month = inputIntRange(1, 12);

            // Taking the day as input
            printf("Day (1-");
            if (date.month == 4 || date.month == 9 || date.month == 11) {
                lastDay = 30;
            }
            if (date.month == 2) {
                lastDay = 28;
            }
            if (date.year % 4 == 0 && date.month == 2) {
                lastDay = 29;
            }

            printf("%d)  : ", lastDay);
            date.day = inputIntRange(1, lastDay);

            printf("Hour (0-23)  : ");
            time.hour = inputIntRange(0, 23);

            printf("Minute (0-59): ");
            time.min = inputIntRange(0, 59);

            // Checking whether time slot is available
            if (availableTimeslot(date, time, app, maxAppointments)) {
                printf("\nERROR: Appointment timeslot is not available!\n\n");
            }
            else {
                while ((time.hour < START_HOUR || time.hour > END_HOUR) || (time.hour == END_HOUR && time.min > 0) || (time.min % MINUTE_INTERVAL != 0)) 
                {
                    printf("ERROR: Time must be between %02d:00 and %02d:00 in %02d minute intervals.\n\n", START_HOUR, END_HOUR, MINUTE_INTERVAL);
                    printf("Hour (0-23)  : ");
                    time.hour = inputIntRange(0, 23);
                    printf("Minute (0-59): ");
                    time.min = inputIntRange(0, 59);
                }
                slotNotAvailable = 0;
            }
        }

        // Assigning the values to the next available slot
        index = availableNextSlot(app, maxAppointments);
        app[index].date = date;
        app[index].time = time;
        app[index].patientNumber = patientNumber;
        printf("\n*** Appointment scheduled! ***\n\n");
    }
    else {
        printf("\nERROR: Patient record not found!\n\n");
    }
    return;
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* app, int maxAppointments, struct Patient* pt, int maxPatients) {
    struct Date date;
    int index, patientNumber, lastDay = 0, aptIndex;

    // Taking the patient number as input
    printf("Patient Number: ");
    patientNumber = inputIntPositive();
    index = findPatientIndexByPatientNum(patientNumber, pt, maxPatients);

    if (index >= 0) {
        // Taking the year as input
        printf("Year        : ");
        date.year = inputIntPositive();

        // Taking the month as input
        printf("Month (1-12): ");
        date.month = inputIntRange(1, 12);

        // Taking the day as input
        printf("Day (1-");
        if (date.month == 4 || date.month == 9 || date.month == 11) {
            lastDay = 30;
        }
        if (date.month == 2) {
            lastDay = 28;
        }
        if (date.year % 4 == 0 && date.month == 2) {
            lastDay = 29;
        }
        printf("%d)  : ", lastDay);
        date.day = inputIntRange(1, lastDay);

        aptIndex = validAppointment(patientNumber, date, app, maxAppointments);

        if (aptIndex >= 0) {
            printf("\n");

            displayPatientData(&pt[index], FMT_FORM);
            printf("Are you sure you want to remove this appointment (y,n): ");

            if (inputCharOption("yn") == 'y') {
                app[aptIndex].patientNumber = 0;
                printf("\nAppointment record has been removed!\n\n");
            }

            else {
                printf("ERROR: No appointment for this date!\n\n");
            }
        }
    }
    else {
        printf("ERROR: Patient record not found!\n\n");
    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber,const struct Patient patient[], int max)
{
    int patientIndex = -1, i;

    for (i = 0; i <= max; i++) {
        if (patient[i].patientNumber == patientNumber) {
            patientIndex = i;
        }
    }
    return patientIndex;
}

// Checks to see whether a time slot is available
int availableTimeslot(struct Date date, struct Time time, struct Appointment* app, int maxAppointments) {
    int i, slotAvailable = 0;

    for (i = 0; i < maxAppointments; i++) {
        // Checking if time slot is available
        if (date.year == app[i].date.year && date.month == app[i].date.month && date.day == app[i].date.day && time.hour == app[i].time.hour && time.min == app[i].time.min) {
            slotAvailable = 1;
        }
    }

    return slotAvailable;
}

// Checks to see which is the next slot that is available and return the index
int availableNextSlot(struct Appointment* app, int maxAppointments) {
    int i = 0, available = 0;
    while (available == 0 && i < maxAppointments) {
        if (app[i].patientNumber < 1) {
            available = 1;
        }
        i++;
    }
    return i;
}

// Checks to see if an appointment is valid
int validAppointment(int patientNumber, struct Date date, struct Appointment* app, int maxAppointments) {
    int i = 0, valid = 0;

    while (valid == 0 && i < maxAppointments)
    {
        if ((app[i].patientNumber == patientNumber) && (app[i].date.day == date.day) && (app[i].date.month == date.month) && (app[i].date.year == date.year)) {
            valid = 1;
        }
        i++;
    }
    return i - 1;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
        printf("Contact: %s\n",
            phone->description);
        printf("Number : ");
        inputNumStr(phone->number, PHONE_LEN);
    }
    else {
        phone->number[0] = '\0';
    }
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max) {
    int i = 0;

    FILE* fp;                         // Opening the file
    fp = fopen(datafile, "r");

    if (fp != NULL) {
        i = 0;
        while (fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]", &patients[i].patientNumber,
            patients[i].name,
            patients[i].phone.description,
            patients[i].phone.number) != EOF)
        {
            i++;
            if (i >= max)
                break;
        }

        fclose(fp);                 // Closing the file
    }

    else {
        printf("ERROR: File could not be read\n");
    }

    return i;
}

// Import appointment data from file into an Appointment array (returns # of records read)
/*ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max) {
    int i, count = 0;

    FILE* fp;  // Declare a file pointer
    fp = fopen(datafile, "r");  // Open the file for reading

    if (fp != NULL) {
        // Iterate until either max appointments are read or end of file is reached
        for (i = 0; i < max && !feof(fp); i++) {
            // Read values from file and store them
            int patientNumber, year, month, day, hour, min;
            if (fscanf(fp, "%d,%d,%d,%d,%d,%d", &patientNumber, &year, &month, &day, &hour, &min) == 6) {
                appoints[i].patientNumber = patientNumber;
                appoints[i].date.year = year;
                appoints[i].date.month = month;
                appoints[i].date.day = day;
                appoints[i].time.hour = hour;
                appoints[i].time.min = min;
                count++;  // Increment count for each successful read
            }
        }

        fclose(fp);  // Close the file
    }
    else {
        printf("ERROR: File could not be read\n");
    }

    return count;  // Return the number of appointments read
}
*/
int importAppointments(const char* datafile, struct Appointment appoints[], int max) {
    int i, count = 0;

    FILE* fp;  // Declare a file pointer
    fp = fopen(datafile, "r");  // Open the file for reading

    if (fp != NULL) {
        // Iterate until either max appointments are read or end of file is reached
        while (count < max) {
            // Read values from file and store them
            int patientNumber, year, month, day, hour, min;
            int result = fscanf(fp, "%d,%d,%d,%d,%d,%d", &patientNumber, &year, &month, &day, &hour, &min);
            if (result == EOF) {
                break;  // Exit loop when end of file is reached
            }
            else if (result == 6) {
                appoints[count].patientNumber = patientNumber;
                appoints[count].date.year = year;
                appoints[count].date.month = month;
                appoints[count].date.day = day;
                appoints[count].time.hour = hour;
                appoints[count].time.min = min;
                count++;  // Increment count for each successful read
            }
            else {
                printf("ERROR: Invalid data format\n");
                break;  // Exit loop on invalid data format
            }
        }

        fclose(fp);  // Close the file
    }
    else {
        printf("ERROR: File could not be read\n");
    }

    return count;  // Return the number of appointments read
}