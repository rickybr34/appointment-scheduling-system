#include "Provider.h"

Provider::Provider(int patientID, 
                const std::string& firstName, 
                const std::string& lastName, 
                const Contact& contact)
    : m_providerID(patientID), 
      m_firstname(firstName), 
      m_lastname(lastName), 
      m_contact(contact) {}

int Provider::getProviderID() const {
    return m_providerID;
}

std::string Provider::getFullName() const {
    return m_firstname + " " + m_lastname;
}

const Contact& Provider::getContact() const {
    return m_contact;
}

void Provider::addPatient(const Patient& patient) {    
    m_patientlist.push_back(patient);
}

int Provider::getNumPatients() const {
    return m_patientlist.size();
}