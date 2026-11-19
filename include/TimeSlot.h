#ifndef TIMESLOT_H
#define TIMESLOT_H

#include <string>

// Length of one bookable slot in a provider's availability
constexpr int SLOT_MINUTES = 15;

struct DateTime {
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;

    bool operator==(const DateTime& other) const;
    bool operator<(const DateTime& other) const;

    // Moves the time forward within the same day
    DateTime plusMinutes(int minutes) const;

    // Formats as YYYY-MM-DD HH:MM
    std::string toString() const;
};

// One SLOT_MINUTES block of a provider's availability
class TimeSlot {
public:
    explicit TimeSlot(const DateTime& dateTime);

    const DateTime& getDateTime() const;
    bool isAvailable() const;
    void book();
    void free();

private:
    DateTime m_dateTime;
    bool m_open = true;
};

#endif
