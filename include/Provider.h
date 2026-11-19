#ifndef PROVIDER_H
#define PROVIDER_H

#include <string>
#include <vector>
#include "Person.h"
#include "TimeSlot.h"

// A clinician whose availability is a sorted list of SLOT_MINUTES time slots
class Provider : public Person {
public:
    Provider(int providerID, const std::string& firstName, const std::string& lastName,
             const Contact& contact, const std::string& speciality);

    int getProviderID() const;
    const std::string& getSpeciality() const;

    // Adds a slot to the availability; ignored if a slot already exists at that time
    void addAvailability(const TimeSlot& slot);

    // True if every slot covering [start, start + minutes) exists and is open
    bool isAvailable(const DateTime& start, int minutes) const;

    // Start times where an appointment of the given length fits, in time order
    std::vector<DateTime> getAvailableStartTimes(int minutes) const;

    // Books every slot covering [start, start + minutes); returns false and books nothing if not available
    bool bookSlots(const DateTime& start, int minutes);

private:
    TimeSlot* findSlot(const DateTime& dateTime);
    const TimeSlot* findSlot(const DateTime& dateTime) const;

    int m_providerID;
    std::string m_speciality;
    std::vector<TimeSlot> m_availability;
};

#endif
