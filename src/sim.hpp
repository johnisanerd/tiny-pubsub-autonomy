#pragma once
#include <cmath>
#include <random>

constexpr double kPi = 3.14159265358979323846;
constexpr double kMetersPerDegLat = 111320.0;

struct DroneState {
    double lat, lon, heading, alt, speed;
};

inline double clamp(double v, double lo, double hi) {
    return v < lo ? lo : (v > hi ? hi : v);
}

inline void step(DroneState& s, double dt, std::mt19937& rng) {
    // paste your existing step body here, unchanged
}