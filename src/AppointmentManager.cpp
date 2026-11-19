#include "AppointmentManager.h"

int AppointmentManager::addPatient(const std::string& firstName, const std::string& lastName, const Contact& contact) {
    // input validation before assigning new id
    if (firstName.empty() || lastName.empty()) {
        return -1;
    }
    if (!Contact::isPhoneValid(contact.getPhoneNum())){
        return -1;
    }
    int id = m_nextPatientId++;
    m_patients.insert({id, Patient(id, firstName, lastName, contact)});
    return id;

}

int AppointmentManager::addProvider(const std::string& firstName, const std::string& lastName, const Contact& contact,
                                    const std::string& speciality) {
    if (firstName.empty() || lastName.empty() || speciality.empty()) {
        return -1;
    }
    int id = m_nextProviderId++;
    m_providers.insert({id, Provider(id, firstName, lastName, contact, speciality)});
    return id;
}

bool AppointmentManager::addAvailability(int providerID, const DateTime& start, const DateTime& end) {
    auto it = m_providers.find(providerID);
    if (it == m_providers.end()) {
        return false;
    }
    bool sameDay = start.year == end.year && start.month == end.month && start.day == end.day;
    if (!sameDay || !(start < end)) {
        return false;
    }
    for (DateTime time = start; time < end; time = time.plusMinutes(SLOT_MINUTES)) {
        it->second.addAvailability(TimeSlot(time));
    }
    return true;
}

std::vector<DateTime> AppointmentManager::getAvailableTimes(int providerID, AppointmentType type) const {
    auto it = m_providers.find(providerID);
    if (it == m_providers.end()) {
        return {};
    }
    return it->second.getAvailableStartTimes(getDurationMinutes(type));
}

int AppointmentManager::bookAppt(int patientID, int providerID, const DateTime& start, AppointmentType type) {
    if (m_patients.find(patientID) == m_patients.end()) {
        return -1;
    }
    auto provider = m_providers.find(providerID);
    if (provider == m_providers.end()) {
        return -1;
    }
    if (!provider->second.bookSlots(start, getDurationMinutes(type))) {
        return -1;
    }
    int id = m_nextAppointmentId++;
    m_appointments.emplace_back(id, patientID, providerID, start, type);
    return id;
}

const std::unordered_map<int, Patient>& AppointmentManager::getPatients() const {
    return m_patients;
}
const std::unordered_map<int, Provider>& AppointmentManager::getProviders() const {
    return m_providers;
}
const std::vector<Appointment>& AppointmentManager::getAppointments() const {
    return m_appointments;
}