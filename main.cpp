#include <iostream>
#include <fstream> // library for working with files
#include <string> // library for working with strings

using namespace std;

// Function to check the character is a digit or not
bool isDigit(const char c) {
    return (c >= '0' && c <= '9');
}

// Function to check the character is an alphabet or not
bool isChar(const char c) {
    return ((c >= 'a' && c <= 'z')
            || (c >= 'A' && c <= 'Z'));
}

// Function to check the special character in a string(email) or not
bool isSpecialChar(const char c) {
    return (c == '_' || c == '.' || c == '-');
}

//function to remove all spaces from string
string removeSpacesFromString(const string &str) { // using constant references to put string into function without copying
    string tmp_str;
    // Iterate through the given string
    for (int i = 0; i < str.length(); i++) {
        if (str[i] != ' ') {
            tmp_str += str[i]; //if current character is not space, then place it at tmp_str
        } else {
            // if current character is space, then continue to iterate
            continue;
        }
    }
    return tmp_str; //return new string without spaces
}

//validate phone number
bool validationPhone(const string &phone) {
//    string allowedChars = "12 340 567 89";
    if (phone.length() > 15 || phone.length() < 7) {
        return false;
    } else {
        for (int i = 0; i < phone.length(); i++) {
            // wrong country code
            if (phone[0] == '0') {
                return false;
            } else {
                // if the character is not digit
                if (!isDigit(phone[i]) && phone[i] != ' ') {
                    return false;
                }
            }
        }
    }
    return true;
}

//validate email for correctness
bool validationEmail(const string &email) {
    // example@any.domen
    int at = -1, dot = -1, atCounter = 0; // Variable to store position of at - (@) and dot - (.)

    if (email.length() < 5) {
        return false;
    }

    // Iterate over the email id string to find position of dot and at
    for (int i = 0; i < email.length(); i++) {
        if (email[i] == '@') {
            at = i;
            atCounter += 1;
        } else if (email[i] == '.') {
            dot = i;
        } else if (!isChar(email[i]) && !isDigit(email[i]) && !isSpecialChar(email[i])) {
            // if email string contains not only allowed chars
            return false;
        }
        // if at(@) or dot(.) is at the beginning
        if (at == 0 || dot == 0) {
            return false;
        }
    }

    // If at - (@) and dot - (.) is not present
    if (at == -1 || dot == -1) {
        return false;
    }

    // if there is more than one at(@)
    if (atCounter > 1){
        return false;
    }
    // If dot is present before at(@)
    if (at > dot) {
        return false;
    }

    // If dot(.) is present at the end
    return dot < (email.length() - 1);
}

// function to display menu with commands for user
void menuDisplay() {
    cout << "\n=============== MENU ===============\n";
    cout << "[1] Add Contact\n";
    cout << "[2] List Contacts\n";
    cout << "[3] Edit Contact\n";
    cout << "[4] Search Contact\n";
    cout << "[5] Delete Contact\n";
    cout << "[0] Exit\n";
    cout << "==============================\n";
}

// save(add) any data as a string at the end of the file
void saveToFile(const string &fullInfo) {
    ofstream outfile; //creates and writes to file
    outfile.open("contacts.txt", ios::out | ios::app); // open file for appending at the end
    outfile << fullInfo << endl; // write into file
    outfile.close(); //close file

    cout << "\nContact has been successfully added! \n";
}

//function to get data about contact from user
string addContact() {
    string phone, name, address, email;
    string fullInfo;

    cout << "Enter the contacts details\n";

    cout << "Phone number (any country 123456789): +";
    getline(cin, phone);
    // checking of input phone is correct
    while (!validationPhone(phone)) {
        cout << "\nEnter the phone using ONLY digits, CORRECT country code: +";
        getline(cin, phone);
    }

    cout << "Full Name:";
    getline(cin, name);

    cout << "Email:";
    getline(cin, email);
    // checking of input email is correct
    while (!validationEmail(email)) {
        cout << "\nEnter the email using correct format without spaces - instance@example.sample:";
        getline(cin, email);
    }

    cout << "Address:";
    getline(cin, address);

    // make a string for contact data
    fullInfo += "Phone: +" + phone + "\nFull Name: " + name + "\nEmail: " + email + "\nAddress: " + address + "\n";
    fullInfo += "==============================================================================";
    return fullInfo; // return contact data
}

//function to search contact by phone number in the contact list
int searchContact() {
    int counter = 0, lineFound = 0;
    bool found = false;
    string breakingPoint = "==============================================================================";
    string phone, line, searchingNum = "Phone: +";

    fstream outfile;
    outfile.open("contacts.txt", ios::in); // open file for reading only

    cout << "\nPlease enter the contact phone number: +";
    getline(cin, phone);
    while (!validationPhone(phone)) {
        cout << "\nEnter the phone using ONLY digits, CORRECT country code: +";
        getline(cin, phone);
    }

    searchingNum += phone; //make a string for comparison

    while (getline(outfile, line)) {
        counter++;
        if (removeSpacesFromString(line) == removeSpacesFromString(searchingNum)) { // comparing two strings without spaces
            found = true;
            lineFound = counter; // get the line number where contact wa found
        }

        // show the found contact details
        if (found && line != breakingPoint) {
            cout << line << endl;
        } else if (found && line == breakingPoint) {
            cout << line << endl;
            break;
        }
    }
    outfile.close();

    // check if contact was not found in the list
    if (!found) {
        lineFound = 0;
        cout << "\nNo contact found...\n";
        return lineFound;
    }

    return lineFound; // return the number of line, where the contact was found
}

// function to show the whole contact list
void listContacts() {
    int lines = 0;
    string breakingPoint = "==============================================================================";
    string listContacts;

    ifstream outfile;
    outfile.open("contacts.txt", ios::in); // open file for read only

    while (getline(outfile, listContacts)) {// read lines from file
        lines++;
        cout << listContacts << endl;
        if (listContacts == breakingPoint) {
            cout << "\n"; //enter new line between contacts for better readability
        }
    }

    // if the file was empty
    if (lines <= 0) {
        cout << "No contacts found...\n";
    }

    outfile.close();
}

// function for editing the existing contact
void editContact() {
    int counter = 0, lineFound;
    bool found = false;
    string editedFullInfo, line;
    string breakingPoint = "==============================================================================";

    fstream outfile;
    fstream outfile_tmp;
    outfile.open("contacts.txt", ios::in | ios::out);
    outfile_tmp.open("contacts_tmp.txt", ios::out);

    lineFound = searchContact(); // search for contact and get the line in the file where the contact was found
    cout << "\n";
    if (!lineFound) {
        return; // if contact not found exit from function
    }
    editedFullInfo = addContact(); // get new updated data about contact from user

    while (getline(outfile, line)) {
        counter++;

        if (counter == lineFound) { // write to the new file at the same line updated data about contact
            outfile_tmp << editedFullInfo << "\n";
            found = true;
        }

        //write other lines except the older info about contact to the new file accordingly
        if (!found) {
            outfile_tmp << line << "\n";
        } else if (line == breakingPoint) { //skip the lines with older contact info until it reaches the end of this contact
            found = false;
        }
    }

    cout << "\n Contact Successfully Updated...\n";

    outfile_tmp.close();
    outfile.close();
    remove("contacts.txt"); // delete file with old info about contact
    rename("contacts_tmp.txt", "contacts.txt"); // rename the file with edited contact info
}

// function to delete the contact from the contact list
void deleteContact() {
    int counter = 0, lineFound;
    bool found = false;
    string line;
    string breakingPoint = "==============================================================================";

    fstream outfile;
    fstream outfile_tmp;

    lineFound = searchContact(); // found the contact and line where it is in file
    cout << "\n";
    if (!lineFound) { // exit from function if no contact with this number found
        return;
    }

    outfile.open("contacts.txt", ios::in | ios::out);
    outfile_tmp.open("contacts_tmp.txt", ios::out); // open temporary file for writing

    while (getline(outfile, line)) {
        counter++;
        if (counter == lineFound) { // if counter reached the line where deleting contact found in file
            found = true;
        }

        if (!found) { // write lines of other contacts into new file
            outfile_tmp << line << "\n";
        } else if (line == breakingPoint) { // skip lines of contact the user wanted to delete
            found = false;
            continue;
        }
    }

    outfile_tmp.close();
    outfile.close();
    remove("contacts.txt");
    rename("contacts_tmp.txt", "contacts.txt");

    cout << "\nContact has been successfully Deleted...\n";
}

// function to call needed function according to the user's choice
void defineChoice(const string &choice) {
    if (choice == "1") {
        saveToFile(addContact());
    } else if (choice == "2") {
        listContacts();
    } else if (choice == "3") {
        editContact();
    } else if (choice == "4") {
        searchContact();
    } else if (choice == "5") {
        deleteContact();
    } else {
        cout << "Wrong key, please, choose one of the given\n";
    }
}

int main() {
    cout << "\n=========== Contact Management System ===========\n";

    //infinite loop with break point
    while (true) {
        string choice;
        menuDisplay(); // show the menu
        cout << "Enter your choice:";
        getline(cin, choice); // if user by fault inputs the `space`

        // continue executing until the user enters `0`
        if (choice == "0") {
            return 0; // exit from program
        } else {
            defineChoice(choice); //process the user's choice
        }
    }
}
