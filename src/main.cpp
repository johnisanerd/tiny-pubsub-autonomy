// Create random path and the gps coordinates for it.
// Each step is 1 second.  So this will output a single minute of realistic flight.

#include <cmath>
#include <cstdio>
#include <random>

const unsigned seed = 42;


constexpr double kPi = 3.14159265358979323846;  // Pi constant.
constexpr double kMetersPerDegLat = 111320.0;   // Thousand meters per degree lattitude.

struct DroneState {         // Structure for holding the Drone state.
    double lat; // degrees
    double lon; // degrees
    double heading; // degrees, 0 = north, 90 = east

    double alt; // meters
    double speed; // meters per second.  Keep between 
};
// Function to take three inputs, low, high.  This pins a number inside a range.
double clamp(double v, double lo, double hi) {
    return v < lo ? lo : (v > hi ? hi : v);
}

// Take in the DroneState; dt = change in time; random number generator.
void step(DroneState& s, double dt, std::mt19937& rng) {
    std::normal_distribution<double> turn(0.0, 5.0); // degrees per step: mean, second standard deviation.
    std::normal_distribution<double> accel(0.0, 0.5); // m/s per step:   mean, second standard deviation.
    std::normal_distribution<double> climb(0.0, 0.3); // meters per step:   mean, second standard deviation.

    s.heading = std::fmod(s.heading + turn(rng) + 360.0, 360.0);    // Take the current heading, add random turn.  360, and wraps.  fmod is the remainder after dividing 2 decimals.
    s.speed = clamp(s.speed + accel(rng), 5.0, 25.0);               // Current speed, random acceleration, then clamps between 5 and 25.
    s.alt = clamp(s.alt + climb(rng), 50.0, 500.0);                 // New alt is current alt, random climb, and then clamped between 50 and 500.

    double dist = s.speed * dt;
    double hdg = s.heading * kPi / 180.0;   // Convert degrees to radians. 
    double north = dist * std::cos(hdg);    // Relative meters changed from last coord.
    double east = dist * std::sin(hdg);     // Relative meters changed from last coord.

    s.lat += north / kMetersPerDegLat;
    s.lon += east / (kMetersPerDegLat * std::cos(s.lat * kPi / 180.0));
}

int main() {
    std::mt19937 rng(seed);
    DroneState s{38.8816, -77.0910, 120.0, 90.0, 15.0}; // starts over Arlington, VA

    // Print it to the terminal as we go.
    std::printf("t,lat,lon,alt,heading,speed\n");
    for (int t = 0; t <= 60; ++t) {
        std::printf("%d,%.6f,%.6f,%.1f,%.1f,%.1f\n",
            t, 
            s.lat, 
            s.lon, 
            s.alt, 
            s.heading, 
            s.speed);
        step(s, 1.0, rng);
    }
    return 0;
}