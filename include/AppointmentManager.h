#ifndef APPOINTMENT_MANAGER_H
#define APPOINTMENT_MANAGER_H

#include <string>
#include <unordered_map>
#include <vector>
#include "Appointment.h"
#include "Patient.h"
#include "Provider.h"

class AppointmentManager {
public:
    // Registers a new patient and assigns them a unique numerical id
    // returns -1 if a name is empty or phone is not valid, otherwise returns new id
    int addPatient(const std::string& firstName, const std::string& lastName, const Contact& contact);

    // Registers a new provider; returns -1 if a name or speciality is empty, otherwise returns new id
    int addProvider(const std::string& firstName, const std::string& lastName, const Contact& contact,
                    const std::string& speciality);

    // Adds a slot every SLOT_MINUTES from start up to (not including) end, on the same day
    // returns false if the provider is unknown or the range is invalid
    bool addAvailability(int providerID, const DateTime& start, const DateTime& end);

    // Start times where the provider can fit an appointment of the given type
    std::vector<DateTime> getAvailableTimes(int providerID, AppointmentType type) const;

    // Books an appointment and closes the provider's slots it covers
    // returns -1 if the patient or provider is unknown or the time is not fully available, otherwise returns new id
    int bookAppt(int patientID, int providerID, const DateTime& start, AppointmentType type);

    const std::unordered_map<int, Patient>& getPatients() const;
    const std::unordered_map<int, Provider>& getProviders() const;
    const std::vector<Appointment>& getAppointments() const;

private:
    std::unordered_map<int, Patient> m_patients;
    int m_nextPatientId = 1;
    std::unordered_map<int, Provider> m_providers;
    int m_nextProviderId = 1;
    std::vector<Appointment> m_appointments;
    int m_nextAppointmentId = 1;
};

#endif