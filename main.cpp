#include <iostream>
#include <fstream>
#include <string>

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

// Function to check the special character in a string or not
bool isSpecialChar(const char c) {
    return (c == '_' || c == '.' || c == '-');
}

string removeSpacesFromString(string str) {
    // To keep track of non-space character count
    unsigned long long length = str.length();

    // Traverse the given string. If current character is not space, then place it at index 'count++'
    for (int i = 0; i < length; i++) {
        if (str[i] == ' ') {
            for (int j = i; j < length; j++) {
                str[j] = str[j + 1];
            }
            length--;
        }
    }
    return str;
}

bool validationPhone(const string &phone) {
//    string allowedChars = "0123456789";
    for (int i = 0; i < phone.length(); i++) {
        if (phone[0] == '0') {
            return false;
        } else {
            if (!isDigit(phone[i]) && phone[i] != ' ') {
                return false;
            }
        }
    }
    return true;
}

bool validationEmail(const string &email) {
    // example@any.format
    // Variable to store position of at - (@) and dot - (.)
    int at = -1, dot = -1;

    if (email.length() < 5) {
        return false;
    }

    // Iterate over the email id string to find position of dot and at
    for (int i = 0; i < email.length(); i++) {
        if (email[i] == '@') {
            at = i;
        } else if (email[i] == '.') {
            dot = i;
        } else if (!isChar(email[i]) && !isDigit(email[i]) && !isSpecialChar(email[i])) {
            return false;
        }
    }

    // If at or dot is not present
    if (at == -1 || dot == -1) {
        return false;
    }
    // If dot is present before at
    if (at > dot) {
        return false;
    }

    // If dot is present at the end
    return dot < (email.length() - 1);
}

//bool validationName(string name) {}
//bool validationAddress(string address){}

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

void saveToFile(const string &fullInfo) {
    ofstream outfile;
    outfile.open("contacts.txt", ios::out | ios::app);
    outfile << fullInfo << endl;
    outfile.close();

    cout << "\nContact has been successfully added! \n";
}

string addContact() {
    string phone, name, address, email;
    string fullInfo;

    cout << "Enter the contacts details\n";
    cout << "Phone number (any country 123456789): +";
    getline(cin, phone);

    while (!validationPhone(phone)) {
        cout << "\nEnter the phone using ONLY digits, CORRECT country code: +";
        getline(cin, phone);
    }

    cout << "Full Name:";
    getline(cin, name);

    cout << "Email:";
    getline(cin, email);

    while (!validationEmail(email)) {
        cout << "\nEnter the email using correct format without spaces - instance@example.sample:";
        cin >> email;
        cin.ignore(); // delete \n from buffer
    }

    cout << "Address:";
    getline(cin, address);

    fullInfo += "Phone: +" + phone + "\nFull Name: " + name + "\nEmail: " + email + "\nAddress: " + address + "\n";
    fullInfo += "==============================================================================";
    return fullInfo;
//    saveToFile(fullInfo);
}

int searchContact() {
    int counter = 0, lineFound = 0;
    bool found = false;
    string breakingPoint = "==============================================================================";
    string phone, line, searchingNum = "Phone: +";

    fstream outfile;
    outfile.open("contacts.txt", ios::in);

    cout << "\nPlease enter the contact phone number: +";
    getline(cin, phone);

    while (!validationPhone(phone)) {
        cout << "\nEnter the phone using ONLY digits, CORRECT country code: +";
        getline(cin, phone);
    }

    searchingNum += phone;

    while (getline(outfile, line)) {
        counter++;
        // comparing two strings without spaces
        if (removeSpacesFromString(line) == removeSpacesFromString(searchingNum)) {
            found = true;
            lineFound = counter;
        }

        if (found && line != breakingPoint) {
            cout << line << endl;
        } else if (found && line == breakingPoint) {
            cout << line << endl;
            break;
        }
    }
    outfile.close();

    if (!found) {
        lineFound = 0;
        cout << "\nNo contact found...\n";
        return lineFound;
    }

    return lineFound;
}

void listContacts() {
    int lines = 0;
    string breakingPoint = "==============================================================================";
    string listContacts;

    ifstream outfile;
    outfile.open("contacts.txt", ios::in);

    while (getline(outfile, listContacts)) {
        lines++;
        cout << listContacts << endl;
        if (listContacts == breakingPoint) {
            cout << "\n";
        }
    }

    if (lines <= 0) {
        cout << "No contacts found...\n";
    }

    outfile.close();
}

void editContact() {
    int counter = 0, lineFound;
    bool found = false;
    string editedFullInfo, phone, line;
    string breakingPoint = "==============================================================================";

    fstream outfile;
    fstream outfile_tmp;
    outfile.open("contacts.txt", ios::in | ios::out);
    outfile_tmp.open("contacts_tmp.txt", ios::out);

    lineFound = searchContact();
    cout << "\n";
    if (!lineFound) {
        return;
    }
    editedFullInfo = addContact();

    while (getline(outfile, line)) {
        counter++;

        if (counter == lineFound) {
            outfile_tmp << editedFullInfo << "\n";
            found = true;
        }

        if (!found) {
            outfile_tmp << line << "\n";
        } else if (line == breakingPoint) {
            found = false;
        }
    }

    cout << "\n Contact Successfully Updated...\n";

    outfile_tmp.close();
    outfile.close();
    remove("contacts.txt");
    rename("contacts_tmp.txt", "contacts.txt");
}

void deleteContact() {
    int counter = 0, lineFound;
    bool found = false;
    string phone, line;
    string breakingPoint = "==============================================================================";

    fstream outfile;
    fstream outfile_tmp;

    lineFound = searchContact();
    cout << "\n";
    if (!lineFound) {
        return;
    }

    outfile.open("contacts.txt", ios::in | ios::out);
    outfile_tmp.open("contacts_tmp.txt", ios::out);

    while (getline(outfile, line)) {
        counter++;
        if (counter == lineFound) {
            found = true;
        }

        if (!found) {
            outfile_tmp << line << "\n";
        } else if (line == breakingPoint) {
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

void defineChoice(const char& choice) {
    if (choice == '1'){
        saveToFile(addContact());
    }else if (choice == '2'){
        listContacts();
    }else if (choice == '3'){
        editContact();
    }else if (choice == '4'){
        searchContact();
    }else if (choice == '5'){
        deleteContact();
    }else{
        cout << "Wrong key, please, choose one of the given\n";
    }
}

int main() {
    cout << "\n=========== Contact Management System ===========\n";

    while (true) {
        char choice;
        menuDisplay();
        cout << "Enter your choice:";
        cin >> choice;
        cin.ignore(); // deletes `\n` from input buffer

        if (choice == '0') {
            return 0;
        } else {
            defineChoice(choice);
        }
    }
}
