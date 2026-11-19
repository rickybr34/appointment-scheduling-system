#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "AppointmentManager.h"


// prints a prompt (ex. "First name: "), reads one line of user input and returns it
std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

// reads a whole number from the user; returns -1 if the input is not a number
int readInt(const std::string& prompt) {
    std::string line = readLine(prompt);
    try {
        size_t used = 0;
        int value = std::stoi(line, &used);
        return used == line.size() ? value : -1;
    } catch (const std::exception&) {
        return -1;
    }
}

// sample providers so staff have someone to book with
void addDemoProviders(AppointmentManager& manager) {
    int lee = manager.addProvider("Dana", "Lee", Contact("617-555-0101", "1 Clinic Way", "dlee@clinic.com"), "Family Medicine");
    manager.addAvailability(lee, DateTime{2026, 11, 18, 9, 0}, DateTime{2026, 11, 18, 12, 0});
    manager.addAvailability(lee, DateTime{2026, 11, 19, 9, 0}, DateTime{2026, 11, 19, 12, 0});

    int patel = manager.addProvider("Raj", "Patel", Contact("617-555-0102", "1 Clinic Way", "rpatel@clinic.com"), "Pediatrics");
    manager.addAvailability(patel, DateTime{2026, 11, 18, 13, 0}, DateTime{2026, 11, 18, 16, 0});
    manager.addAvailability(patel, DateTime{2026, 11, 20, 9, 0}, DateTime{2026, 11, 20, 12, 0});
}

// walks staff through picking a patient, provider, type and time, then books the appointment
void scheduleAppointment(AppointmentManager& manager) {
    if (manager.getPatients().empty()) {
        std::cout << "No patients registered yet. Add a patient first.\n\n";
        return;
    }

    std::vector<int> patientIds;
    for (const auto& entry : manager.getPatients()) {
        patientIds.push_back(entry.first);
    }
    std::sort(patientIds.begin(), patientIds.end());
    std::cout << "\nPatients:\n";
    for (int id : patientIds) {
        std::cout << "  " << id << ") " << manager.getPatients().at(id).getFullName() << "\n";
    }
    int patientID = readInt("Patient ID: ");
    while (manager.getPatients().count(patientID) == 0) {
        std::cout << "Unknown patient ID. Try again.\n";
        patientID = readInt("Patient ID: ");
    }

    std::vector<int> providerIds;
    for (const auto& entry : manager.getProviders()) {
        providerIds.push_back(entry.first);
    }
    std::sort(providerIds.begin(), providerIds.end());
    std::cout << "\nProviders:\n";
    for (int id : providerIds) {
        const Provider& provider = manager.getProviders().at(id);
        std::cout << "  " << id << ") " << provider.getFullName() << " (" << provider.getSpeciality() << ")\n";
    }
    int providerID = readInt("Provider ID: ");
    while (manager.getProviders().count(providerID) == 0) {
        std::cout << "Unknown provider ID. Try again.\n";
        providerID = readInt("Provider ID: ");
    }

    const std::vector<AppointmentType> types = {
        AppointmentType::FollowUp, AppointmentType::Checkup, AppointmentType::NewPatient
    };
    std::cout << "\nAppointment types:\n";
    for (size_t i = 0; i < types.size(); i++) {
        std::cout << "  " << i + 1 << ") " << toString(types[i]) << " (" << getDurationMinutes(types[i]) << " min)\n";
    }
    int typeChoice = readInt("Type: ");
    while (typeChoice < 1 || typeChoice > static_cast<int>(types.size())) {
        std::cout << "Choose a listed type. Try again.\n";
        typeChoice = readInt("Type: ");
    }
    AppointmentType type = types[typeChoice - 1];

    std::vector<DateTime> times = manager.getAvailableTimes(providerID, type);
    if (times.empty()) {
        std::cout << "No available times for this provider and appointment type.\n\n";
        return;
    }
    std::cout << "\nAvailable times:\n";
    for (size_t i = 0; i < times.size(); i++) {
        std::cout << "  " << i + 1 << ") " << times[i].toString() << "\n";
    }
    int timeChoice = readInt("Time: ");
    while (timeChoice < 1 || timeChoice > static_cast<int>(times.size())) {
        std::cout << "Choose a listed time. Try again.\n";
        timeChoice = readInt("Time: ");
    }
    DateTime start = times[timeChoice - 1];

    int appointmentID = manager.bookAppt(patientID, providerID, start, type);
    if (appointmentID == -1) {
        std::cout << "Error: Appointment could not be scheduled. The time is not available.\n\n";
        return;
    }
    std::cout << "\nAppointment " << appointmentID << " scheduled:\n"
              << "  Patient:  " << manager.getPatients().at(patientID).getFullName() << "\n"
              << "  Provider: " << manager.getProviders().at(providerID).getFullName() << "\n"
              << "  Time:     " << start.toString() << "\n"
              << "  Type:     " << toString(type) << " (" << getDurationMinutes(type) << " min)\n\n";
}

int main() {
    std::cout << "\nClinic Appointment System\n" << std::endl;
    
    AppointmentManager manager;
    addDemoProviders(manager);

    // Demo menu to add patients or exit
    while (true){
        std::cout << "1) Add Patient\n2) Schedule Appointment\n0) Exit\n" << std::endl;
        std::string choice = readLine("Choose 1, 2 or 0: ");

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
            scheduleAppointment(manager);
        } else if (choice == "0") {
            break;
        }
    }
    return 0;
}
