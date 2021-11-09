#include <iostream>
#include <fstream>

using namespace std;

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

void saveToFile(string fullInfo){
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
    cout << "Phone number: ";
    cin >> phone;
    cout << "Name: ";
    cin >> name;
    cout << "Email: ";
    cin >> email;
    cout << "Address: ";
    cin >> address;

    fullInfo += "Phone: " + phone + "\nName: " + name + "\nEmail: " + email + "\nAddress: " + address;
    fullInfo += "\n==============================================================================\n\n";

    saveToFile(fullInfo);
}
void listContacts() {}
void editContact() {}
void searchContact() {}
void deleteContact() {}

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
