#include <gtest/gtest.h>
#include <algorithm>
#include "AppointmentManager.h"

// Manager with one patient and one provider available 2026-11-18 09:00-12:00
class ScheduleAppointmentTest : public ::testing::Test {
protected:
    void SetUp() override {
        patientID = manager.addPatient("John", "Smith", Contact("123-456-7891", "100 Main st", "jsmith@umb.com"));
        providerID = manager.addProvider("Dana", "Lee", Contact("617-555-0101", "1 Clinic Way", "dlee@clinic.com"), "Family Medicine");
        manager.addAvailability(providerID, at(9, 0), at(12, 0));
    }

    static DateTime at(int hour, int minute) {
        return DateTime{2026, 11, 18, hour, minute};
    }

    bool isListed(AppointmentType type, const DateTime& time) const {
        std::vector<DateTime> times = manager.getAvailableTimes(providerID, type);
        return std::find(times.begin(), times.end(), time) != times.end();
    }

    AppointmentManager manager;
    int patientID = -1;
    int providerID = -1;
};

TEST_F(ScheduleAppointmentTest, AvailableTimeIsSaved) {
    int id = manager.bookAppt(patientID, providerID, at(10, 0), AppointmentType::Checkup);

    ASSERT_EQ(id, 1);
    ASSERT_EQ(manager.getAppointments().size(), 1u);
    const Appointment& appt = manager.getAppointments().front();
    EXPECT_EQ(appt.getAppointmentID(), id);
    EXPECT_EQ(appt.getPatientID(), patientID);
    EXPECT_EQ(appt.getProviderID(), providerID);
    EXPECT_EQ(appt.getDateTime(), at(10, 0));
    EXPECT_EQ(appt.getType(), AppointmentType::Checkup);
    EXPECT_EQ(appt.getDurationMinutes(), 30);
    EXPECT_EQ(appt.getStatus(), "Scheduled");
}

TEST_F(ScheduleAppointmentTest, BookedTimeNoLongerListed) {
    EXPECT_TRUE(isListed(AppointmentType::FollowUp, at(10, 0)));
    EXPECT_TRUE(isListed(AppointmentType::FollowUp, at(10, 15)));

    manager.bookAppt(patientID, providerID, at(10, 0), AppointmentType::Checkup);

    EXPECT_FALSE(isListed(AppointmentType::FollowUp, at(10, 0)));
    EXPECT_FALSE(isListed(AppointmentType::FollowUp, at(10, 15)));
    EXPECT_TRUE(isListed(AppointmentType::FollowUp, at(10, 30)));
}

TEST_F(ScheduleAppointmentTest, TimeOutsideAvailabilityIsRejected) {
    EXPECT_EQ(manager.bookAppt(patientID, providerID, at(14, 0), AppointmentType::FollowUp), -1);
    EXPECT_EQ(manager.bookAppt(patientID, providerID, at(8, 45), AppointmentType::FollowUp), -1);
    EXPECT_TRUE(manager.getAppointments().empty());
}

TEST_F(ScheduleAppointmentTest, AppointmentRunningPastAvailabilityIsRejected) {
    EXPECT_EQ(manager.bookAppt(patientID, providerID, at(11, 30), AppointmentType::NewPatient), -1);
    EXPECT_TRUE(manager.getAppointments().empty());
    EXPECT_TRUE(isListed(AppointmentType::FollowUp, at(11, 30)));
}

TEST_F(ScheduleAppointmentTest, DoubleBookingIsRejected) {
    ASSERT_NE(manager.bookAppt(patientID, providerID, at(10, 0), AppointmentType::Checkup), -1);

    EXPECT_EQ(manager.bookAppt(patientID, providerID, at(10, 0), AppointmentType::FollowUp), -1);
    EXPECT_EQ(manager.bookAppt(patientID, providerID, at(9, 45), AppointmentType::Checkup), -1);
    EXPECT_EQ(manager.getAppointments().size(), 1u);
}

TEST_F(ScheduleAppointmentTest, UnknownPatientOrProviderIsRejected) {
    EXPECT_EQ(manager.bookAppt(999, providerID, at(10, 0), AppointmentType::FollowUp), -1);
    EXPECT_EQ(manager.bookAppt(patientID, 999, at(10, 0), AppointmentType::FollowUp), -1);
    EXPECT_TRUE(manager.getAppointments().empty());
}

TEST_F(ScheduleAppointmentTest, LongerTypesHaveFewerStartTimes) {
    // 09:00-12:00 is 12 slots
    EXPECT_EQ(manager.getAvailableTimes(providerID, AppointmentType::FollowUp).size(), 12u);
    EXPECT_EQ(manager.getAvailableTimes(providerID, AppointmentType::Checkup).size(), 11u);
    EXPECT_EQ(manager.getAvailableTimes(providerID, AppointmentType::NewPatient).size(), 9u);
}
