#ifndef PROVIDER_H
#define PROVIDER_H

#include <string>
#include <vector>
#include "Contact.h"
#include "Patient.h"

class Provider {
    private:
        int m_providerID;
        std::string m_firstname;
        std::string m_lastname;
        Contact m_contact;
        std::vector<Patient> m_patientlist;
    
    public:
        Provider(int providerID, 
            const std::string& firstname, 
            const std::string& lastname, 
            const Contact& contact);

        int getProviderID() const;
        std::string getFullName() const;
        const Contact& getContact() const;
        const std::vector<Patient>& m_getPaitentList() const;
        
        void addPatient(const Patient& Patient);
        int getNumPatients() const;
        //add a function to control providers available slots
        //Ex: int getNumFreeSlots()

};

#endif