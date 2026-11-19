
#ifndef PROVIDER_H
#define PROVIDER_H

#include <string>

class Provider {
private:
    static int nextProviderID;

    int providerID;
    std::string firstName;
    std::string lastName;
    std::string specialty;

public:
    // Creates a provider with a unique ID
    Provider(const std::string& first,
             const std::string& last,
             const std::string& providerSpecialty);

    // Setup the returns provider information (for id,fName,lName,specialty)
    int getProviderID() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getSpecialty() const;
};

#endif
