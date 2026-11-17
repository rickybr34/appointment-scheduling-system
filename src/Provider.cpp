
#include "Provider.h"

int Provider::nextProviderID = 1;

// Initializes provider information and assigns a unique ID
Provider::Provider(const std::string& first,
                   const std::string& last,
                   const std::string& providerSpecialty)
    : providerID(nextProviderID++),
      firstName(first),
      lastName(last),
      specialty(providerSpecialty) {
}

// 1. to returns the provider ID
int Provider::getProviderID() const {
    return providerID;
}

// 2. to returns the provider's first name
std::string Provider::getFirstName() const {
    return firstName;
}

// 3. to returns the provider's last name
std::string Provider::getLastName() const {
    return lastName;
}

// 4. to returns the provider's specialty
std::string Provider::getSpecialty() const {
    return specialty;
}
