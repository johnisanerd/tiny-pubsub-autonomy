#include <gtest/gtest.h>
#include "../src/sim.hpp"

// Test that speed and altitude stay inside of our defined bounds.
TEST(Sim, SpeedAndAltitudeStayInBounds) {
    std::mt19937 rng(42);
    DroneState s{38.8816, -77.0910, 90.0, 120.0, 15.0};
    for (int i = 0; i < 10000; ++i) {
        step(s, 1.0, rng);
        EXPECT_GE(s.speed, 5.0);
        EXPECT_LE(s.speed, 25.0);
        EXPECT_GE(s.alt, 50.0);
        EXPECT_LE(s.alt, 500.0);
    }
}
// Test that the same seed gives the same path.
TEST(Sim, SameSeedGivesSamePath) {
    std::mt19937 a(7), b(7);
    DroneState s1{38.8816, -77.0910, 90.0, 120.0, 15.0};
    DroneState s2 = s1;
    for (int i = 0; i < 100; ++i) { step(s1, 1.0, a); step(s2, 1.0, b); }
    EXPECT_DOUBLE_EQ(s1.lat, s2.lat);
    EXPECT_DOUBLE_EQ(s1.lon, s2.lon);
}