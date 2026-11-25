#include <gtest/gtest.h>
#include "AppointmentManager.h"

TEST(ViewPatientsTest, OnePatientRegistered){
    AppointmentManager manager;
    Contact contact("123-555-7189", "10 Main Blvd", "denzel@gmail.com");
    manager.addPatient("Denzel", "Washington", contact);
    EXPECT_EQ(manager.getPatients().size(), 1);
}

TEST(ViewPatientsTest, NoPatientRegistered){
    AppointmentManager manager;
    EXPECT_EQ(manager.getPatients().size(), 0);
    EXPECT_TRUE(manager.getPatients().empty());
}

TEST(ViewPatientsTest, MultiplePatientsRegistered){
    AppointmentManager manager;
    Contact contact1("123-555-7189", "10 Main Blvd", "denzel@gmail.com");
    Contact contact2("123-000-1232", "25 cali drive", "ariana@gmail.com");
    Contact contact3("(222) 555 4425", "100 boston rd", "beyonce@gmail.com");
    Contact contact4("789 784 3452", "25 canton ave", "gordon@gmail.com");
    manager.addPatient("Denzel", "Washington", contact1);
    manager.addPatient("Ariana", "Grande", contact2);
    manager.addPatient("Beyonce", "Knowles", contact3);
    manager.addPatient("Gordon", "Ramsey", contact4);
    EXPECT_EQ(manager.getPatients().size(), 4);
}