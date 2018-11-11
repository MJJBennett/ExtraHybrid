#ifndef NOVEMBERGAMEJAM_TIMER_H
#define NOVEMBERGAMEJAM_TIMER_H

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class Timer {
public:
    Timer() {
        clock_.restart();
    }

    void restart() {
        clock_.restart();
        delta_ = sf::Time::Zero;
    }

    bool pause(bool pause = true) {
        if (recording_ && pause) {
            // Stop recording
            recording_ = false;
            // Save time
            delta_ += clock_.restart();
            return true;
        } else if (!recording_ && !pause) {
            // Start recording
            recording_ = true;
            // Restart clock
            clock_.restart();
            return true;
        }
        return false; // Did nothing
    }

    bool paused() { return !recording_; }

    sf::Time get() { return clock_.getElapsedTime() + delta_; }

private:
    sf::Clock clock_;
    bool recording_ = false;
    sf::Time delta_ = sf::Time::Zero;
};

#endif //NOVEMBERGAMEJAM_TIMER_H
