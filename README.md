# Tiny PubSub Demo for Autonomy

A small C++17 drone flight simulator. It generates a smooth, random GPS trajectory over time, the kind of fake sensor feed you'd use to test autonomy software without a real aircraft.

Drone state sub that holds latitude, longitude, altitude, heading and speed.

Each tick, every second, the speed and heading change by a small random amount, so the path stays smooth and continuous rather than jumping around.

Then you move the drone. Distance is speed times time, and you convert that to changes in latitude and longitude using the heading, with about 111 km per degree of latitude.  Each point gets printed as a line of CSV, so you could later plot it on a map.

## What it does

- Starts a simulated drone over Arlington, VA.
- Each 1-second step nudges heading, speed, and altitude by small random amounts (normal distributions).
- Keeps speed between 5 and 25 m/s and altitude between 50 and 500 m.
- Moves the drone by speed × time along its heading and converts that to latitude and longitude.
- Prints one minute of flight as CSV: t, lat, lon, alt, heading, speed.

A fixed random seed makes every run identical, which keeps it testable.

# Setup

Clang - compiler
    Apple clang version 15.0.0 (clang-1500.0.40.1)
Cmake -
    I installed with homebrew: `brew install cmake`

# Build

`cmake --build build`

## Build and run

Requires CMake and a C++17 compiler (Clang or GCC).

    `cmake -S . -B build`
    `cmake --build build`
    `./build/drone_sim > track.csv`

## Roadmap

- [x] Unit tests with GoogleTest
- [ ] Smooth turns by randomizing turn rate instead of heading
- [ ] Publish-subscribe bus: a sensor plugin publishes GPS, a planner plugin subscribes
- [ ]Simulated GPS jamming and dead reckoning
