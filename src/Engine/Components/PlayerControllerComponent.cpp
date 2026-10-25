#include "Engine/Components/PlayerControllerComponent.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Component.hpp"
#include "Engine/Components/TransformComponent.hpp"


void PlayerControllerComponent::Update(float dt) {
  if (!owner) return;

  TransformComponent *transform = owner->GetComponent<TransformComponent>();
  if (!transform) return;

  // 1. Lectura continua de teclado
  const bool *keys = SDL_GetKeyboardState(nullptr);
  Vector2 input_dir{0.0f, 0.0f};

  if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) input_dir.x-= 1.0f;

  if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) input_dir.x+= 1.0f;

  Vector2 final_dir = input_dir;

  // 2. Normalización del vector resultante
  if (final_dir.length_squared() > 0.01f)
    final_dir = final_dir.normalized();
  else
    final_dir = {0.0f, 0.0f};

  // 3. Traslación del transform
  Vector2 displacement = final_dir * (300 * dt);
  transform->Translate(displacement);

}

std::unique_ptr<Component> PlayerControllerComponent::Clone() const{
  return std::make_unique<PlayerControllerComponent>(*this);
}
