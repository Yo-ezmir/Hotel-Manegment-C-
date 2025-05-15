#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Reservation {
    int roomNumber;
    string guestName;
    string phoneNo;
    int days;
    double rate;
    int checkInDay, checkInMonth, checkInYear;
};

const int MAX_ROOMS = 100;
const int MAX_RESERVATIONS = 100;
Reservation reservations[MAX_RESERVATIONS];
int reservationCount = 0;


void addReservation();
void viewReservations();
void searchReservation();
void deleteReservation();
void saveToFile(const string& filename);
void loadFromFile(const string& filename);
bool isRoomBooked(int roomNumber);
template <typename T>
T getValidInput(const string& prompt, T minVal, T maxVal);
string getValidPhoneNumber();
bool isValidDate(int day, int month, int year);

int main() {
    string filename = "reservations.txt";
    int choice;

    loadFromFile(filename);

    do {
    cout << "\n===== Hotel Reservation System =====" << endl;
    cout << "1. Add Reservation" << endl;
    cout << "2. View Reservations" << endl;
    cout << "3. Search Reservation" << endl;
    cout << "4. Delete Reservation" << endl;
    cout << "5. Save and Exit" << endl;
    cout << "6. Exit Without Saving" << endl;
   choice = getValidInput<int>("Enter your choice: ", 1, 6);

    switch (choice) {
        case 1:
            addReservation();
            break;
        case 2:
            viewReservations();
            break;
        case 3:
            searchReservation();
            break;
        case 4:
            deleteReservation();
            break;
        case 5:
            saveToFile(filename);
            cout << "Data saved. Exiting..." << endl;
            break;
        case 6:
            cout << "Exiting without saving changes..." << endl;
            break;
    }
} while (choice != 5 && choice != 6);


    return 0;
}

bool isValidDate(int day, int month, int year) {
    if (year < 2025) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    return true;
}


template <typename T>
T getValidInput(const string& prompt, T minVal, T maxVal) {
    T num;
    while (true) {
        cout << prompt;
        cin >> num;
        if (cin.fail() || num < minVal || num > maxVal) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a value between " << minVal << " and " << maxVal << "." << endl;
        } else {
            return num;
        }
    }
}

string getValidPhoneNumber() {
    string phoneNo;
    while (true) {
        cout << "Enter Phone Number (10 digits): ";
        cin >> phoneNo;

        if (phoneNo.length() == 10) {
            bool valid = true;

            for (int i = 0; i < phoneNo.length(); ++i) {
                if (phoneNo[i] < '0' || phoneNo[i] > '9') {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                return phoneNo;
            }
        }

        cout << "Invalid phone number! Please enter exactly 10 digits." << endl;
    }
}


bool isRoomBooked(int roomNumber) {
    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].roomNumber == roomNumber) {
            return true;
        }
    }
    return false;
}

void addReservation() {
    if (reservationCount >= MAX_RESERVATIONS) {
        cout << "Reservation list is full!" << endl;
        return;
    }

    Reservation newReservation;
    newReservation.roomNumber = getValidInput<int>("\nEnter Room Number (1-100): ", 1, MAX_ROOMS);

    if (isRoomBooked(newReservation.roomNumber)) {
        cout << "Error: Room " << newReservation.roomNumber << " is already booked!" << endl;
        return;
    }

    cin.ignore();
    cout << "Enter Guest Name: ";
    getline(cin, newReservation.guestName);

    newReservation.phoneNo = getValidPhoneNumber();
    do {
        cout << "Enter Check-in Date (Day Month Year): ";
        cin >> newReservation.checkInDay >> newReservation.checkInMonth >> newReservation.checkInYear;
        if (!isValidDate(newReservation.checkInDay, newReservation.checkInMonth, newReservation.checkInYear)) {
            cout << "Invalid check-in date! Please enter a valid date (Day: 1-31, Month: 1-12, Year: 2025 or later).\n";
        }
    } while (!isValidDate(newReservation.checkInDay, newReservation.checkInMonth, newReservation.checkInYear));

    newReservation.days = getValidInput<int>("Enter Number of Days: ", 1, 365);
    newReservation.rate = getValidInput<double>("Enter Rate per Day: ", 1.0, 10000.0);
    reservations[reservationCount++] = newReservation;
    cout << "Reservation added successfully!" << endl;
}


void viewReservations() {
    if (reservationCount == 0) {
        cout << "No reservations found!" << endl;
        return;
    }

    cout << "\n===== All Reservations =====" << endl;
    for (int i = 0; i < reservationCount; i++) {
        cout << "Room Number: " << reservations[i].roomNumber << endl;
        cout << "Guest Name: " << reservations[i].guestName << endl;
        cout << "Phone Number: " << reservations[i].phoneNo << endl;
        cout << "Days: " << reservations[i].days << endl;
        cout << "Rate: $" << reservations[i].rate << endl;
        cout << "Check-in Date: " << reservations[i].checkInDay << "/" << reservations[i].checkInMonth << "/" << reservations[i].checkInYear << endl;
        cout << "Total Cost: $" << reservations[i].days * reservations[i].rate << endl;
        cout << "-----------------------------" << endl;
    }
}



void searchReservation() {
    if (reservationCount == 0) {
        cout << "No reservations found!" << endl;
        return;
    }

 int roomNumber = getValidInput<int>("\nEnter Room Number to search: ", 1, MAX_ROOMS);
    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].roomNumber == roomNumber) {
            cout << "\nReservation found!" << endl;
            cout << "Room Number: " << reservations[i].roomNumber << endl;
            cout << "Guest Name: " << reservations[i].guestName << endl;
            cout << "Phone Number: " << reservations[i].phoneNo << endl;
            cout << "Check-in day: " << reservations[i].checkInDay << " "
                                    << reservations[i].checkInMonth << " "
                                    << reservations[i].checkInYear << endl;
            cout << "Days: " << reservations[i].days << endl;
            cout << "Rate: $" << reservations[i].rate << endl;
            cout << "Total Cost: $" << reservations[i].days * reservations[i].rate << endl;
            return;
        }
    }
    cout << "Reservation not found!" << endl;
}

void deleteReservation() {
    if (reservationCount == 0) {
        cout << "No reservations found!" << endl;
        return;
    }

    int roomNumber = getValidInput<int>("\nEnter Room Number to delete: ", 1, MAX_ROOMS);
    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].roomNumber == roomNumber) {
            for (int j = i; j < reservationCount - 1; j++) {
                reservations[j] = reservations[j + 1];
            }
            reservationCount--;
            cout << "Reservation deleted successfully!" << endl;
            return;
        }
    }
    cout << "Reservation not found!" << endl;
}


void saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Error opening file for saving!" << endl;
        return;
    }

    for (int i = 0; i < reservationCount; i++) {
        file << reservations[i].roomNumber << endl;
        file << reservations[i].guestName << endl;
        file << reservations[i].phoneNo << endl;
        file << reservations[i].days << endl;
        file << reservations[i].rate << endl;
        file << reservations[i].checkInDay << " " << reservations[i].checkInMonth << " " << reservations[i].checkInYear << endl;
            }

    file.close();
    cout << "Reservations saved to file!" << endl;
}



void loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "No existing file found. Starting with an empty list." << endl;
        return;
    }

    reservationCount = 0;
    while (file >> reservations[reservationCount].roomNumber) {
        file.ignore();
        getline(file, reservations[reservationCount].guestName);
        file >> reservations[reservationCount].phoneNo;
        file >> reservations[reservationCount].days;
        file >> reservations[reservationCount].rate;
        file >> reservations[reservationCount].checkInDay >> reservations[reservationCount].checkInMonth >> reservations[reservationCount].checkInYear;
        reservationCount++;
        if (reservationCount >= MAX_RESERVATIONS) break;
    }

    file.close();
    cout << "Reservations loaded from file!" << endl;
}

