/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Jagbir Singh
Student ID#: 144019221
Email      : jagbir-singh1@mysenecacollege.ca
Section    : NBB

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
void displayAllPatients(const struct Patient patient[], int max, int fmt) {
    int i;

    if (fmt == FMT_TABLE) {
        displayPatientTableHeader();

        if (patient == NULL) {
            printf("\n*** No records found ***\n");
        }
        else {
            for (i = 0; i < max; i++) {
                if (patient[i].patientNumber != 0) {
                    displayPatientData(&patient[i], fmt);
                }
            }
            putchar('\n');
        }
    }
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max) {
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
        switch (selection)
        {
        case 1:
            searchPatientByPatientNumber(patient, max);
            suspend();
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max) {
    int i, value, check = -1;

    for (i = 0; i < max && check == -1; i++) {
        if (patient[i].patientNumber == 0)
            check = i;
    }

    if (check == -1) {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else {
        value = nextPatientNumber(patient, max);

        patient[check].patientNumber = value;

        inputPatient(&patient[check]);

        printf("*** New patient record added ***\n\n");
    }
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max) {
    int patNum, num;

    printf("Enter the patient number: ");
    patNum = inputIntPositive();

    num = findPatientIndexByPatientNum(patNum, patient, max);

    if (num == -1) {
        printf("\nERROR: Patient record not found!\n");
    }
    else {
        putchar('\n');
        menuPatientEdit(&patient[num]);
    }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max) {
    int patNum, num;
    char character;

    printf("Enter the patient number: ");
    patNum = inputIntPositive();

    num = findPatientIndexByPatientNum(patNum, patient, max);

    if (num == -1) {
        printf("\nERROR: Patient record not found!\n\n");
    }
    else {
        putchar('\n');
        displayPatientData(&patient[num], FMT_FORM);
        putchar('\n');

        printf("Are you sure you want to remove this patient record? (y/n): ");
        character = inputCharOption("yn");

        if (character == 'y') {
            patient[num].patientNumber = 0;
            strcpy(patient[num].name, "0");
            strcpy(patient[num].phone.number, "0");
            strcpy(patient[num].phone.description, "0");

            printf("Patient record has been removed!\n\n");
        }
        else {
            printf("Operation aborted.\n\n");
        }
    }

}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// Sorting appointment by using bubble sort
void bubbleSort(struct Appointment* appoints, int max) {
    int i, j;
    struct Appointment temp;

    for (i = 0; i < max; i++) {
        appoints[i].time.min = (appoints[i].date.year * 10000000) + (appoints[i].date.month * 100000) + (appoints[i].date.day * 1000) + (appoints[i].time.hour * 100) + (appoints[i].time.min);

    }

    for (i = 0; i < max - 1; i++) {
        for (j = 0; j < max - i - 1; j++) {
            if (appoints[j].time.min > appoints[j + 1].time.min) {
                temp = appoints[j];
                appoints[j] = appoints[j + 1];
                appoints[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < max; i++) {
        appoints[i].time.min -= (appoints[i].date.year * 10000000) + (appoints[i].date.month * 100000) + (appoints[i].date.day * 1000) + (appoints[i].time.hour * 100);
    }
}

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData data[]) {
    int i, j;

    bubbleSort(data->appointments, data->maxAppointments);

    displayScheduleTableHeader(NULL, 1);

    for (i = 0; i < data->maxAppointments; i++) {
        for (j = 0; j < data->maxPatient; j++) {
            if (data->appointments[i].patientNumber != 0 && (data->appointments[i].patientNumber == data->patients[j].patientNumber)) {
                displayScheduleData(&data->patients[j], &data->appointments[i], 1);
            }
        }
    }
    putchar('\n');
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData data[]) {
    int i, j, maxDay = 31;
    struct Date date;

    bubbleSort(data->appointments, data->maxAppointments);

    printf("Year        : ");
    date.year = inputIntPositive();

    printf("Month (1-12): ");
    date.month = inputIntRange(1, 12);

    if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) {
        maxDay = 30;
    }
    else if (date.year % 4 == 0 && date.month == 2) {
        maxDay = 29;
    }
    else if (date.month == 2) {
        maxDay = 28;
    }

    printf("Day (1-%d)  : ", maxDay);
    date.day = inputIntRange(1, maxDay);

    putchar('\n');

    displayScheduleTableHeader(&date, 0);

    for (i = 0; i < data->maxAppointments; i++) {
        for (j = 0; j < data->maxPatient; j++) {
            if (data->appointments[i].patientNumber != 0 && (data->appointments[i].patientNumber == data->patients[j].patientNumber) && (data->appointments[i].date.year == date.year && data->appointments[i].date.month == date.month && data->appointments[i].date.day == date.day)) {
                displayScheduleData(&data->patients[j], &data->appointments[i], 0);
            }
        }
    }
    putchar('\n');
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* appointments, int maxAppointments,const struct Patient* patients, int maxPatients) {
    int patNum, i, index = -1, maxDay = 31, check = 1, check1 = 1, check2 = -1;
    struct Date date;
    struct Time time;

    printf("Patient Number: ");
    patNum = inputIntPositive();
    index = findPatientIndexByPatientNum(patNum, patients, maxPatients);

    if (index == -1) {
        printf("\nERROR: Patient record not found!\n\n");
    }
    else {
        while (check == 1) {
            printf("Year        : ");
            date.year = inputIntPositive();

            printf("Month (1-12): ");
            date.month = inputIntRange(1, 12);

            if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) {
                maxDay = 30;
            }
            else if (date.year % 4 == 0 && date.month == 2) {
                maxDay = 29;
            }
            else if (date.month == 2) {
                maxDay = 28;
            }

            printf("Day (1-%d)  : ", maxDay);
            date.day = inputIntRange(1, maxDay);

            printf("Hour (0-23)  : ");
            time.hour = inputIntRange(0, 23);

            printf("Minute (0-59): ");
            time.min = inputIntRange(0, 59);

            for (i = 0; i < maxAppointments; i++) {
                if (date.year == appointments[i].date.year && date.month == appointments[i].date.month && date.day == appointments[i].date.day && time.hour == appointments[i].time.hour && time.min == appointments[i].time.min) {
                    check1 = 0;
                }
            }

            if (check1 == 0) {
                printf("\nERROR: Appointment timeslot is not available!\n\n");
                check1 = 1;
            }
            else {
                while ((time.hour < START_HOUR || time.hour > END_HOUR) || (time.hour == END_HOUR && time.min > 0) || (time.min % MIN_INTERVAL != 0)) {
                    printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", START_HOUR, END_HOUR, MIN_INTERVAL);
                    printf("Hour (0-23)  : ");
                    time.hour = inputIntRange(0, 23);
                    printf("Minute (0-59): ");
                    time.min = inputIntRange(0, 59);
                }
                check = 0;
            }
        }
        for (i = 0; i < maxAppointments && check2 == -1; i++) {
            if (appointments[i].patientNumber == 0) {
                check2 = i;
            }
        }
        appointments[check2].date = date;
        appointments[check2].time = time;
        appointments[check2].patientNumber = patNum;
        printf("\n*** Appointment scheduled! ***\n\n");
    }
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatients) {
    int patNum, i, index = -1, index1 = -1, maxDay = 31;
    struct Date date;

    printf("Patient Number: ");
    patNum = inputIntPositive();
    index = findPatientIndexByPatientNum(patNum, patients, maxPatients);

    if (index == -1) {
        printf("ERROR: Patient record not found!\n\n");
    }
    else {
        printf("Year        : ");
        date.year = inputIntPositive();

        printf("Month (1-12): ");
        date.month = inputIntRange(1, 12);

        if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) {
            maxDay = 30;
        }
        else if (date.year % 4 == 0 && date.month == 2) {
            maxDay = 29;
        }
        else if (date.month == 2) {
            maxDay = 28;
        }

        printf("Day (1-%d)  : ", maxDay);
        date.day = inputIntRange(1, maxDay);

        for (i = 0; i < maxAppointments && index1 == -1; i++) {
            if ((appointments[i].patientNumber == patNum) && (appointments[i].date.day == date.day) && (appointments[i].date.month == date.month) && (appointments[i].date.year == date.year)) {
                index1 = i;
            }
        }

        if (index1 == -1) {
            printf("ERROR: Patient record not found!\n\n");
        }
        else {
            printf("\n");

            displayPatientData(&patients[index], FMT_FORM);
            printf("Are you sure you want to remove this appointment (y,n): ");

            if (inputCharOption("yn") == 'y') {
                appointments[index1].patientNumber = 0;
                printf("\nAppointment record has been removed!\n\n");
            }
            else {
                printf("ERROR: No appointment for this date!\n\n");
            }
        }
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max) {
    int num, patNum;

    printf("Search by patient number: ");
    patNum = inputIntPositive();

    num = findPatientIndexByPatientNum(patNum, patient, max);
    putchar('\n');

    if (num == -1) {
        printf("*** No records found ***\n");
    }
    else {
        displayPatientData(&patient[num], FMT_FORM);
    }
    putchar('\n');
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
    int i, check = 0;
    char phoneNum[PHONE_LEN + 1];

    printf("Search by phone number: ");
    inputCString(phoneNum, PHONE_LEN, PHONE_LEN);
    putchar('\n');

    displayPatientTableHeader();
    for (i = 0; i < max; i++) {
        if (strcmp(patient[i].phone.number, phoneNum) == 0) {
            displayPatientData(&patient[i], FMT_TABLE);
            check = 1;
        }

    }

    if (check == 0) {
        printf("\n*** No records found ***\n");
    }

    putchar('\n');
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max) {
    int i, maxValue = 0;

    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber > maxValue) {
            maxValue = patient[i].patientNumber;
        }
    }

    return maxValue + 1;
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max) {
    int i, check = -1;

    for (i = 0; i < max && check == -1; i++) {
        if (patient[i].patientNumber == patientNumber) {
            check = i;
        }
    }

    return check;
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient) {
    printf("Patient Data Input\n"
        "------------------\n"
        "Number: %05d\n"
        "Name  : ", patient->patientNumber);
    inputCString(patient->name, 1, NAME_LEN);
    putchar('\n');

    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone) {
    int selection;

    printf("Phone Information\n"
        "-----------------\n"
        "How will the patient like to be contacted?\n"
        "1. Cell\n"
        "2. Home\n"
        "3. Work\n"
        "4. TBD\n"
        "Selection: ");
    selection = inputIntRange(1, 4);

    if (selection == 1) {
        putchar('\n');
        strcpy(phone->description, "CELL");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, 10, 10);
    }
    else if (selection == 2) {
        putchar('\n');
        strcpy(phone->description, "HOME");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, 10, 10);
    }
    else if (selection == 3) {
        putchar('\n');
        strcpy(phone->description, "WORK");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, 10, 10);
    }
    else {
        strcpy(phone->description, "TBD");
    }
    putchar('\n');
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max) {
    int i = 0, flag = 1;

    FILE* fp = NULL;
    fp = fopen(datafile, "r");

    if (fp != NULL) {
        while (flag == 1 && fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]", &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number) != EOF)
        {
            i++;
            if (i >= max)
                flag = 0;
        }
        fclose(fp);
    }

    return i;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max) {
    int i = 0, flag = 1;

    FILE* fp = NULL;
    fp = fopen(datafile, "r");

    if (fp != NULL) {
        while (flag == 1 && fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[i].patientNumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min) != EOF)
        {
            i++;
            if (i >= max)
                flag = 0;
        }
        fclose(fp);
    }

    return i;
}