#include "PlayerController.h"
#include "GameObject.h"
#include "Character.h"
#include "InputManager.h"
#include "Camera.h"

PlayerController::PlayerController(GameObject& associated) : Component(associated) {}

void PlayerController::Update(float dt) {

    Character* characterComp = associated.GetComponent<Character>();
    if (characterComp == nullptr) return;

    InputManager& input = InputManager::GetInstance();

    Vec2 moveDir(0, 0);
    if (input.IsKeyDown(SDLK_W) || input.IsKeyDown(UP_ARROW_KEY)) moveDir.y -= 1;
    if (input.IsKeyDown(SDLK_S) || input.IsKeyDown(DOWN_ARROW_KEY)) moveDir.y += 1;
    if (input.IsKeyDown(SDLK_A) || input.IsKeyDown(LEFT_ARROW_KEY)) moveDir.x -= 1;
    if (input.IsKeyDown(SDLK_D) || input.IsKeyDown(RIGHT_ARROW_KEY)) moveDir.x += 1;

    if (moveDir.x != 0 || moveDir.y != 0) {
        characterComp->Issue(Command(Command::MOVE, moveDir.x, moveDir.y));
    }

    if (input.MousePress(LEFT_MOUSE_BUTTON)) {
        Vec2 target(input.GetMouseX(), input.GetMouseY());
        target.x += Camera::pos.x;
        target.y += Camera::pos.y;
        characterComp->Issue(Command(Command::SHOOT, target.x, target.y));
    }
}

void PlayerController::Render() {}

void PlayerController::SetCharacter(std::weak_ptr<GameObject> newCharacter) {
    character = newCharacter;
}
