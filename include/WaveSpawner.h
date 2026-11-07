#pragma once
#include "Component.h"
#include "Timer.h"

class WaveSpawner : public Component {
private:
    Timer waveTimer;
    float spawnInterval;

public:
    WaveSpawner(GameObject& associated, float spawnInterval = 3.0f);
    void Update(float dt) override;
    void Render() override;
};