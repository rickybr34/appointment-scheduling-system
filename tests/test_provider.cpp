
#include <gtest/gtest.h>
#include "Provider.h"

// Build the tests provider information
TEST(ProviderTest, CreateProvider) {

    // setup examples format
    Provider provider("Tien", "Le", "Ophthalmologist");


    EXPECT_EQ(provider.getFirstName(), "Tien");
    EXPECT_EQ(provider.getLastName(), "Le");
    EXPECT_EQ(provider.getSpecialty(), "Ophthalmologist");
    EXPECT_GT(provider.getProviderID(), 0);
}

// Tests that providers receive unique IDs
TEST(ProviderTest, UniqueProviderIDs) {
    Provider provider1("Justin", "Bieber", "Primary Care");
    Provider provider2("Jennie", "Kim", "Obstetrician");

    EXPECT_NE(provider1.getProviderID(),
              provider2.getProviderID());
}
