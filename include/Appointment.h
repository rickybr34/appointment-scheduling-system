#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include "TimeSlot.h"

// Each type has a fixed length that is a multiple of SLOT_MINUTES
enum class AppointmentType { FollowUp, Checkup, NewPatient };

int getDurationMinutes(AppointmentType type);
std::string toString(AppointmentType type);

class Appointment {
public:
    Appointment(int appointmentID, int patientID, int providerID, const DateTime& dateTime, AppointmentType type);

    int getAppointmentID() const;
    int getPatientID() const;
    int getProviderID() const;
    const DateTime& getDateTime() const;
    AppointmentType getType() const;
    int getDurationMinutes() const;
    const std::string& getStatus() const;

private:
    int m_appointmentID;
    int m_patientID;
    int m_providerID;
    DateTime m_dateTime;
    AppointmentType m_type;
    std::string m_status = "Scheduled";
};

#endif
