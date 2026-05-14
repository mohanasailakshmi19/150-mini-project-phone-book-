#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string name;
    string phone;
    Node* next;

    Node(string n, string p) {
        name = n;
        phone = p;
        next = NULL;
    }
};

class PhoneBook {
    int size;
    Node** table;

public:
    PhoneBook(int s) {
        size = s;

        table = new Node*[size];

        for (int i = 0; i < size; i++) {
            table[i] = NULL;
        }
    }

    // Hash Function
    int hashFunction(string name) {
        int sum = 0;

        for (int i = 0; i < name.length(); i++) {
            sum = sum + name[i];
        }

        return sum % size;
    }

    // Add Contact
    void addContact(string name, string phone) {
        int index = hashFunction(name);

        Node* newNode = new Node(name, phone);

        // If no contact exists
        if (table[index] == NULL) {
            table[index] = newNode;
        }
        else {
            // Chaining using linked list
            Node* temp = table[index];

            while (temp->next != NULL) {
                temp = temp->next;
            }

            temp->next = newNode;
        }

        cout << "Contact Added Successfully\n";
    }

    // Search Contact
    void searchContact(string name) {
        int index = hashFunction(name);

        Node* temp = table[index];

        while (temp != NULL) {

            if (temp->name == name) {
                cout << "\nContact Found\n";
                cout << "Name  : " << temp->name << endl;
                cout << "Phone : " << temp->phone << endl;
                return;
            }

            temp = temp->next;
        }

        cout << "Contact Not Found\n";
    }

    // Delete Contact
    void deleteContact(string name) {
        int index = hashFunction(name);

        Node* temp = table[index];
        Node* prev = NULL;

        while (temp != NULL) {

            if (temp->name == name) {

                // First node delete
                if (prev == NULL) {
                    table[index] = temp->next;
                }
                else {
                    prev->next = temp->next;
                }

                delete temp;

                cout << "Contact Deleted Successfully\n";
                return;
            }

            prev = temp;
            temp = temp->next;
        }

        cout << "Contact Not Found\n";
    }

    // Display All Contacts
    void displayContacts() {

        cout << "\n------ PHONE BOOK ------\n";

        for (int i = 0; i < size; i++) {

            cout << "\nIndex " << i << " : ";

            Node* temp = table[i];

            if (temp == NULL) {
                cout << "Empty";
            }

            while (temp != NULL) {

                cout << "[" << temp->name
                     << " - " << temp->phone << "] ";

                temp = temp->next;
            }
        }

        cout << endl;
    }
};

int main() {

    PhoneBook pb(10);

    int choice;
    string name, phone;

    do {

        cout << "\n===== PHONE BOOK MENU =====\n";
        cout << "1. Add Contact\n";
        cout << "2. Search Contact\n";
        cout << "3. Delete Contact\n";
        cout << "4. Display Contacts\n";
        cout << "5. Exit\n";

        cout << "Enter your choice : ";
        cin >> choice;

        switch(choice) {

        case 1:
            cout << "Enter Name : ";
            cin >> name;

            cout << "Enter Phone Number : ";
            cin >> phone;

            pb.addContact(name, phone);
            break;

        case 2:
            cout << "Enter Name to Search : ";
            cin >> name;

            pb.searchContact(name);
            break;

        case 3:
            cout << "Enter Name to Delete : ";
            cin >> name;

            pb.deleteContact(name);
            break;

        case 4:
            pb.displayContacts();
            break;

        case 5:
            cout << "Program Ended\n";
            break;

        default:
            cout << "Invalid Choice\n";
        }

    } while(choice != 5);

    return 0;
}