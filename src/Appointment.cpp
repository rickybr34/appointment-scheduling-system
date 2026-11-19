#include "Appointment.h"

int getDurationMinutes(AppointmentType type) {
    switch (type) {
        case AppointmentType::FollowUp:   return 15;
        case AppointmentType::Checkup:    return 30;
        case AppointmentType::NewPatient: return 60;
    }
    return 0;
}

std::string toString(AppointmentType type) {
    switch (type) {
        case AppointmentType::FollowUp:   return "Follow-up";
        case AppointmentType::Checkup:    return "Checkup";
        case AppointmentType::NewPatient: return "New Patient";
    }
    return "Unknown";
}

Appointment::Appointment(int appointmentID, int patientID, int providerID, const DateTime& dateTime, AppointmentType type)
    : m_appointmentID(appointmentID), m_patientID(patientID), m_providerID(providerID),
      m_dateTime(dateTime), m_type(type) {}

int Appointment::getAppointmentID() const {
    return m_appointmentID;
}
int Appointment::getPatientID() const {
    return m_patientID;
}
int Appointment::getProviderID() const {
    return m_providerID;
}
const DateTime& Appointment::getDateTime() const {
    return m_dateTime;
}
AppointmentType Appointment::getType() const {
    return m_type;
}
int Appointment::getDurationMinutes() const {
    return ::getDurationMinutes(m_type);
}
const std::string& Appointment::getStatus() const {
    return m_status;
}
