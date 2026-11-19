#include "Person.h"

Person::Person(const std::string& firstName, const std::string& lastName, const Contact& contact)
    : m_firstName(firstName), m_lastName(lastName), m_contact(contact) {}

std::string Person::getFullName() const {
    return m_firstName + " " + m_lastName;
}
const Contact& Person::getContact() const {
    return m_contact;
}
