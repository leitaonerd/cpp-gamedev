#include "Timer.h"

Timer::Timer() : elapsed(0.0f) {}

void Timer::Update(float dt) {
    elapsed += dt;
}

void Timer::Restart() {
    elapsed = 0.0f;
}

float Timer::Get() const {
    return elapsed;
}
