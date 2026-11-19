#ifndef PERSON_H
#define PERSON_H

#include <string>
#include "Contact.h"

// Shared name and contact details for people known to the clinic
class Person {
public:
    Person(const std::string& firstName, const std::string& lastName, const Contact& contact);

    std::string getFullName() const;
    const Contact& getContact() const;

private:
    std::string m_firstName;
    std::string m_lastName;
    Contact m_contact;
};

#endif
