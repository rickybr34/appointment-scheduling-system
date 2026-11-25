#include "AppointmentManager.h"
#include <algorithm>

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

// returns saved patients, not in any order
const std::unordered_map<int, Patient>& AppointmentManager::getPatients() const {
    return m_patients;
}

// returns a new sorted list of patient IDs in ascending order
std::vector<int> AppointmentManager::getPatientIDsInOrder() const {
    std::vector<int> ids;
    // patient is [id, Patient]
    for (const auto& patient : m_patients){
        ids.push_back(patient.first);
    }
    std::sort(ids.begin(), ids.end());
    return ids;
}