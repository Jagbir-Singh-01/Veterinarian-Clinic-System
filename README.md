# Veterinarian Clinic System

**Project Overview**

This project implements a basic patient (pet) appointment system for a veterinary clinic. It manages patient contact information, appointment scheduling, and data import from text files.

**Milestones**

*   **Milestone 1:** Develops helper functions for input validation, string manipulation, and user interaction.
*   **Milestone 2:** Implements core data structures (`Patient`, `Phone`) and functions for managing patient records (adding, editing, searching, removing).
*   **Milestone 3:** Introduces appointment management functionality, including data structures (`Time`, `Date`, `Appointment`) and functions for scheduling, viewing, and removing appointments.

**Core Module**

Provides essential helper functions used throughout the project:

*   `clearInputBuffer()`: Clears the standard input buffer.
*   `suspend()`: Waits for the user to press Enter to continue.
*   `inputInt()`, `inputIntPositive()`, `inputIntRange()`: Get validated integer input from the user.
*   `inputCharOption()`: Get validated character input from a list of options.
*   `inputCString()`: Get validated C string input with length restrictions.
*   `displayFormattedPhone()`: Displays a formatted phone number.

**Clinic Module**

Manages patient and appointment data:

*   **Data Structures:**
    *   `Phone`: Stores phone description and number.
    *   `Patient`: Stores patient number, name, and phone information.
    *   `Time`: Stores hour and minute.
    *   `Date`: Stores year, month, and day.
    *   `Appointment`: Stores patient number, date, and time.
*   **Functions:**
    *   `displayAllPatients()`: Displays all patient records in a specified format.
    *   `searchPatientData()`: Searches for patient records by number or phone.
    *   `addPatient()`: Adds a new patient record.
    *   `editPatient()`: Edits an existing patient record.
    *   `removePatient()`: Removes a patient record.
    *   `importPatients()`, `importAppointments()`: Import data from text files.
    *   `viewAllAppointments()`: Views all appointments.
    *   `viewAppointmentSchedule()`: Views appointments for a specific date.
    *   `addAppointment()`: Adds a new appointment.
    *   `removeAppointment()`: Removes an existing appointment.

**How to Compile and Run**

```bash
gcc -Wall a1ms3.c core.c clinic.c -o ms3 
./ms3
