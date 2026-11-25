#include <iostream>
#include <string>
#include "AppointmentManager.h"


// prints a prompt (ex. "First name: "), reads one line of user input and returns it
std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

// prints every registered patient in no particular order
void viewPatients(const AppointmentManager& manager){
    const std::unordered_map<int, Patient>& patientsRegistered = manager.getPatients();
    if(!patientsRegistered.empty()){
        for (const auto& patient : patientsRegistered){
            std::cout << "\nName: " << patient.second.getFullName() << std::endl;
            std::cout << "ID: " << patient.first << std::endl;
            const Contact& contact = patient.second.getContact();
            std::cout << "Email: " << contact.getEmail() << std::endl;
            std::cout << "Phone: " << contact.getPhoneNum() << std::endl;
            std::cout << "Address: " << contact.getAddress() << std::endl;
        }
    } else {
        std::cout << "No Patients Registered.\n" << std::endl;
    }

}

int main() {
    std::cout << "\nClinic Appointment System\n" << std::endl;
    
    AppointmentManager manager;

    // Demo menu to add patients or exit
    while (true){
        std::cout << "\n1) Add Patient\n2) View Patients\n0) Exit\n" << std::endl;
        std::string choice = readLine("Choose number: ");

        if (choice == "1") {
            std::string firstName = readLine("First name: ");
            while (firstName.empty()) {
                std::cout << "First name is required. Try again.\n";
                firstName = readLine("First name: ");
            }
            std::string lastName = readLine("Last name: ");
            while (lastName.empty()) {
                std::cout << "Last name is required. Try again.\n";
                lastName = readLine("Last name: ");
            }
            std::string phone = readLine("Phone: ");
            while (!Contact::isPhoneValid(phone)) {
                std::cout << "Phone must have 10 digits. Try again.\n";
                phone = readLine("Phone: ");
            }
            std::string email = readLine("Email: ");
            std::string address = readLine("Address: ");

            int id = manager.addPatient(firstName, lastName, Contact(phone, address, email));
            if (id == -1) {
                std::cout << "Error: Patient failed to be registered. Make sure all fields are input correctly.\n";
            } else {
                std::cout << "\nNew patient " << firstName << " " << lastName << " registered with ID: " << id << "\n\n";
            }
        } else if (choice == "2") {
            std::cout << "\nPatients:" << std::endl;
            viewPatients(manager);
        } else if (choice == "0") {
            break;
        }
    }
    return 0;
}
