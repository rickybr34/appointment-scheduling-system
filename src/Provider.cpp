#include "Provider.h"
#include <algorithm>

Provider::Provider(int providerID, const std::string& firstName, const std::string& lastName,
                   const Contact& contact, const std::string& speciality)
    : Person(firstName, lastName, contact), m_providerID(providerID), m_speciality(speciality) {}

int Provider::getProviderID() const {
    return m_providerID;
}
const std::string& Provider::getSpeciality() const {
    return m_speciality;
}

void Provider::addAvailability(const TimeSlot& slot) {
    if (findSlot(slot.getDateTime()) != nullptr) {
        return;
    }
    // keep slots sorted so available times are listed in order
    auto pos = std::lower_bound(m_availability.begin(), m_availability.end(), slot,
        [](const TimeSlot& a, const TimeSlot& b) { return a.getDateTime() < b.getDateTime(); });
    m_availability.insert(pos, slot);
}

bool Provider::isAvailable(const DateTime& start, int minutes) const {
    if (minutes <= 0 || minutes % SLOT_MINUTES != 0) {
        return false;
    }
    for (int offset = 0; offset < minutes; offset += SLOT_MINUTES) {
        const TimeSlot* slot = findSlot(start.plusMinutes(offset));
        if (slot == nullptr || !slot->isAvailable()) {
            return false;
        }
    }
    return true;
}

std::vector<DateTime> Provider::getAvailableStartTimes(int minutes) const {
    std::vector<DateTime> times;
    for (const TimeSlot& slot : m_availability) {
        if (isAvailable(slot.getDateTime(), minutes)) {
            times.push_back(slot.getDateTime());
        }
    }
    return times;
}

bool Provider::bookSlots(const DateTime& start, int minutes) {
    if (!isAvailable(start, minutes)) {
        return false;
    }
    for (int offset = 0; offset < minutes; offset += SLOT_MINUTES) {
        findSlot(start.plusMinutes(offset))->book();
    }
    return true;
}

TimeSlot* Provider::findSlot(const DateTime& dateTime) {
    for (TimeSlot& slot : m_availability) {
        if (slot.getDateTime() == dateTime) {
            return &slot;
        }
    }
    return nullptr;
}

const TimeSlot* Provider::findSlot(const DateTime& dateTime) const {
    for (const TimeSlot& slot : m_availability) {
        if (slot.getDateTime() == dateTime) {
            return &slot;
        }
    }
    return nullptr;
}
