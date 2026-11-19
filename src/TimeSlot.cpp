#include "TimeSlot.h"
#include <cstdio>
#include <tuple>

bool DateTime::operator==(const DateTime& other) const {
    return std::tie(year, month, day, hour, minute) ==
           std::tie(other.year, other.month, other.day, other.hour, other.minute);
}

bool DateTime::operator<(const DateTime& other) const {
    return std::tie(year, month, day, hour, minute) <
           std::tie(other.year, other.month, other.day, other.hour, other.minute);
}

DateTime DateTime::plusMinutes(int minutes) const {
    DateTime result = *this;
    int total = hour * 60 + minute + minutes;
    result.hour = total / 60;
    result.minute = total % 60;
    return result;
}

std::string DateTime::toString() const {
    char buffer[64];
    std::snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d", year, month, day, hour, minute);
    return buffer;
}

TimeSlot::TimeSlot(const DateTime& dateTime) : m_dateTime(dateTime) {}

const DateTime& TimeSlot::getDateTime() const {
    return m_dateTime;
}
bool TimeSlot::isAvailable() const {
    return m_open;
}
void TimeSlot::book() {
    m_open = false;
}
void TimeSlot::free() {
    m_open = true;
}
