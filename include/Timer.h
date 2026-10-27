#pragma once

class Timer {
private:
    float elapsed;

public:
    Timer();
    void Update(float dt);
    void Restart();
    float Get() const;
};
