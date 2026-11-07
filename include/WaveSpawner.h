#pragma once
#include "Component.h"
#include "Timer.h"
#include <vector>

class Wave {
public:
    int zombies;
    float cooldown;

    Wave(int zombies, float cooldown) : zombies(zombies), cooldown(cooldown) {}
};

class WaveSpawner : public Component {
private:
    int zombieCounter;
    int currentWave;
    Timer zombieCooldownTimer;
    std::vector<Wave> waves;

public:
    WaveSpawner(GameObject& associated);
    void Update(float dt) override;
    void Render() override;
};