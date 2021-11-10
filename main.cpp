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
    cout << "\n";
    cout << "=============== MENU ===============\n";
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

void addContact() {
    string phone, name, address, email;
    string fullInfo;

    cout << "Enter the contacts details\n";
    cout << "Phone number (any country): +";
    cin.ignore();
    getline(cin, phone);
    while (!validationPhone(phone)) {
        cout << "\nEnter the phone using ONLY digits, CORRECT country code: +";
        cin.ignore();
        getline(cin, phone);
    }

    cout << "Full Name:";
    getline(cin, name);

    cout << "Email:";
    cin.ignore();
    getline(cin, email);
    while (!validationEmail(email)) {
        cout << "\nEnter the email using correct format without spaces - instance@example.sample:";
        cin >> email;
    }

    cout << "Address:";
    // fixes premature end of input
    // cin adds “\n” to the buffer, because of this the execution may not be stopped for your input
    cin.ignore();
    getline(cin, address);

    fullInfo += "==============================================================================\n";
    fullInfo += "Phone: +" + phone + "\nFull Name: " + name + "\nEmail: " + email + "\nAddress: " + address;
    fullInfo += "\n==============================================================================\n";
    saveToFile(fullInfo);
}

void listContacts() {
    string listContacts;
    int lines = 0;
    ifstream outfile;
    outfile.open("contacts.txt", ios::in);

    while (getline(outfile, listContacts)) {
        lines++;
        cout << listContacts << endl;
    }

    if (lines <= 0) {
        cout << "No contacts found!\n";
    }

    outfile.close();
}

void editContact() {}

void searchContact() {
    string phone;
    bool found = false;
    string breakingPoint = "==============================================================================";
    string line, searchingNum = "Phone: +";
    fstream outfile;
    outfile.open("contacts.txt", ios::in);

    cout << "\nPlease enter the contact phone number #: +";
    cin.ignore();
    getline(cin, phone);
    searchingNum += phone;

    while (getline(outfile, line)) {
        // comparing two strings without spaces
        if (removeSpacesFromString(line) == removeSpacesFromString(searchingNum)) {
            found = true;
        }

        if (found && line != breakingPoint) {
            cout << line << endl;
        } else if (found && line == breakingPoint) {
            break;
        }
    }

    if (!found) {
        cout << "\nNo record found...\n";
    }

    outfile.close();
}

void deleteContact() {
    string phone;
    string line, searchingNum = "Phone: +";
    fstream outfile;
    fstream outfile_tmp;

    cout << "\nPlease enter the contact phone number #: +";
    cin.ignore();
    getline(cin, phone);
    searchingNum += phone;

    outfile.open("contacts.txt", ios::in | ios::out);
    outfile_tmp.open("contacts_tmp.txt", ios::out);
    while (getline(outfile, line)) {
        if (line != searchingNum) {
            outfile_tmp << line;
        }
    }
    outfile_tmp.close();
    outfile.close();

    remove("contacts.txt");
    rename("contacts_tmp.txt", "contacts.txt");

    cout << "\nContact has been successfully Deleted...\n";
}

void defineChoice(char choice) {
    switch (choice) {
        case '1':
            addContact();
            break;
        case '2':
            listContacts();
            break;
        case '3':
            editContact();
            break;
        case '4':
            searchContact();
            break;
        case '5':
            deleteContact();
            break;
        default:
            cout << "Wrong number, please, choose one of a given\n";
            break;
    }
}

int main() {
    cout << "\n=========== Contact Management System ===========\n";

    while (true) {
        char choice;
        menuDisplay();
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "\n";

        if (choice == '0') {
            exit(0);
        } else {
            defineChoice(choice);
        }
    }

    return 0;
}
