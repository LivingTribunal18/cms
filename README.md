# CMS
Contact Management System

## Project: Contact Management System in `C++` with source code

Contact Management System is based on the concept of recording contact details. This whole system is in the C++ language. Also, the user can perform all the tasks like adding, viewing, modifying, and deleting contact records. There’s no login system for this project.

This is a simple contact details management system which developed using C++. It utilizes file handling and shows the functions of the programming language. This is a simple mini project in C++, built as a console application without using any graphics features.

## About System

The Contact Management System project is designed in `C++` language. This system is based on a concept to store and generate all the records of the Personal or an Organization’s Contact. Also, this program is considered as a simple database of contacts in an office, an organization where the user can add Contact details safely and it’s not time-consuming. 

This System makes easy to store records of each. Moreover, the user can add personal details, view a list of it, modify and remove the details. Also, this mini project contains a validation system for user actions while operationg with contacts.

## Features:

- [1] Add a new Contact
- [2] List all Contacts
- [3] Edit a Contact
- [4] Search for Contact
- [5] Delete a Contact
- [0] Exit

## Code Documentation

### Libraries:
- `iostream` - input/output in console.
- `fstream` - Input/output stream to operate on files. 
- `string` - for working with strings
- `namespace std` - std::

### Functions:
  1. isDigit
  2. isChar
  3. isSpecialChar
  4. removeSpacesFromString
  5. validationPhone
  6. validationEmail
  7. menuDisplay
  8. saveToFile
  9. addContact
  10. searchContact
  11. listContacts
  12. editContact
  13. deleteContact
  14. defineChoice
  15. main

###
1. `bool isDigit(const char c)` - gets the constant char as an argument and checks the given char whether it is represented as a Digit from 0 to 9 or not. If it is a Digit, the function returns true, else it returns false. The argument in function is constant because the function does not modify it.

2. `bool isChar(const char c)` - gets the constant char as an argument and checks the given char whether it is represented as an alphabetic character from ‘a’ to ‘z’ and from ‘A’ to ‘Z’ or not. If it is an alphabetic character, the function returns true, else it returns false. The given argument in the function is constant because the function does not modify it.

3. `bool isSpecialChar(const char c)` - gets the constant char as an argument and checks if the given char is a special character in an email such as ‘-’, ‘_’ or ‘.’. If it is a special character, the function returns true, else it returns false. The given argument in the function is constant because the function does not modify it.

4. `string removeSpacesFromString(const string &str)` - gets the constant string reference as an argument and overwrites the given string into a new string variable without spaces, and then returns the resulting string variable. The argument in function is constant because the function does not modify it. Reference was used in order to not copy the string - improves productivity of the program.

5. `bool validationPhone(const string &phone)` - gets the constant string reference as an argument and checks if the given argument passed to the rules of the world phone numbers. Before checking, it calls the function `removeSpacesFromString()` to remove spaces and to get the string only with digits. Length of the number should not be less than 7 characters, it should have only Digits or spaces and correct country code not starting from ‘0’. If the phone number is correct, the function returns true, else it returns false. The given argument in the function is constant because the function does not modify it. Reference was used in order to not copy the string - improves productivity of the program.

6. `bool validationEmail(const string &email)` - gets the constant string reference as an argument and checks if the given argument passed to the rules of the email. The email should contain at(‘@’) and dot(‘.’). In email are allowed chars, digits and special characters. The dot(.) and at(@) should not be at the end or the beginning of email. At(@) should not be presented more than once, and at(@) should not be next to dot(.), without the domain for email _(wrong - email@.com)_. If the email is correct, the function returns true, else it returns false. The given argument in the function is constant because the function does not modify it. Reference was used in order to not copy the string - improves productivity of the program.

7. `void menuDisplay()` - shows to the user menu actions that can be done to work with CMS. Returns nothing - void function.

8. `void saveToFile(const string &fullInfo)` - gets the constant string reference as an argument. Function opens the database file with ‘Append mode’ and ‘Writing mode’. All output to that file to be appended to the end. It writes the given string with all data about the new contact at the end of the file. Then it closes the file. Returns nothing - void function.

9. `string addContact()` - gets nothing as an argument. Function to ask the user input necessary data about contact in the console. It asks for Phone, Full Name, Email and Address. For input is used the function `getline()`. Then it calls the validationPhone and validationEmail function to check the correctness of the input data, it will continue to ask to input correct format data, until the user writes the right one. Function gets data, adds it to the string and then returns this produced string.

10. `int searchContact()` - gets nothing as an argument. It opens the database file in read only mode. Function asks the user to input the number of the searching contact. Then functions get through each line in the database file and compares two strings without spaces. If the contact was found it stores the number of the line, where contact was found in the integer variable. If contact was found it starts to output the contact and stops when it reaches the breaking point and closes the file. If no such contact is found, it will notify the user. Function returns the integer number of the line, where the contact was found, and if no contact is found it returns false as ‘0’.

11. `void listContacts()` - gets nothing as an argument. Function opens file in read only mode, iterates through the lines in the file and outputs each line of the file. After each breaking point it puts ‘\n’ in the output, in order to improve readability of the Contacts List. If there are no contacts and no line in the file it notifies the user that “No contacts found”. It closes the file. Function returns nothing - void function.

12. `void editContact()` - gets nothing as an argument. Function for editing the existing contact in the database file. It opens a database file in writing, reading mode and creates a new template file in writing mode. Then it calls the `searchContact()` function, in order to know which contact to edit and get the integer number of the line where the contact is placed in the database file. If no contact is found it notifies the user and stops executing the function. Then it asks the user to input the fully or partially new information for the contact and gets it as a ready string. After that the function gets through the lines in the database and writes them into the template file, when it reaches the line where is the changing contact, it skips the old data and writes the updated data from the user in the template file at the same line as it was in the database file. Then the files were closed. The file with old data was removed and the template file was renamed as the main database file. Function returns nothing - void function.

13. `void deleteContact()` - gets nothing as an argument. Function for deleting the existing contact in the database file. It opens a database file in writing, reading mode and creates a new template file in writing mode. Then it calls the `searchContact()` function, in order to know which contact to delete and get the integer number of the line where the contact is placed in the database file. If no contact is found it notifies the user and stops executing the function. After that the function gets through the lines in the database and writes them into the template file, when it reaches the line where the deleting contact is, it skips these old data contacts and does not write it in the template file. Then the files were closed. The file with old data is removed and the template file is renamed as the main database file. Function returns nothing - void function.

14. `void defineChoice(const string &choice)` - gets the constant string reference as an argument. Then it defines which function should be called according to the user's choice. If input was incorrect or the number was out of the range of functions it will keep asking the user for the right choice and notifying “Wrong key, please, choose one of the given”. Function returns nothing - void function.

15. `int main()` - gets nothing as an argument. Function for deleting the existing contact in the database file. The main function to execute the whole CMS program. Executes an infinite loop to let the user always get a choice and stop when the user wants. ‘0’ choice is the breaking statement for the infinite loop. Infinite loop calls the function `menuDisplay()` and asks for input and if the user's choice is not ‘0’, it calls for the function `defineChoice(choice)`, else returns 0 and stops executing the whole program.

16. `getline()` - a standard library function that is used to read a string or a line from an input stream. It is a part of the <string> header. The `getline()` function extracts characters from the input stream and appends it to the string object until the delimiting character is encountered (or the newline character '\n'). In the program it is used, in order to store from the input the whole line with spaces between characters.

### C++ Files and Streams
- `fstream` - This data type represents the file stream generally, and has the capabilities to create files, write information to files, and read information from files. A file must be opened before you can read from it or write to it.
- `ios::app` - Append mode. All output to that file to be appended to the end.
- `ios::in` - Open a file for reading.
- `ios::out` - Open a file for writing.
You can combine two or more of these values by ORing them together. For example if you want to open a file in write mode and read mode in case that already exists, following will be the syntax −
  `ofstream outfile;
  outfile.open("contacts.txt", ios::out | ios::trunc );`

### Closing a File
When a C++ program terminates it automatically flushes all the streams, releases all the allocated memory and closes all the opened files. But it is always a good practice that a programmer should close all the opened files before program termination - 
  `outfile.close();`

### Writing to a File
While doing C++ programming, you write information to a file from your program using the stream insertion operator (<<) just as you use that operator to output information to the screen `cout <<`.

### Reading from a File
You read information from a file into your program using the stream `getline()` function.
  `getline(outfile, line);`
  `cout  <<  line;`

### Deleting a File
You can remove the file at all, using `remove(file_name)` function.
  `remove(“contacts.txt”);`

### Renaming a File
You can rename the file using function `rename(oldname, newname)`.
  `rename(“contacts_tmp.txt”, “contacts.txt”);`






