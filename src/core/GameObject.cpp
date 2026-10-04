#include "../../include/core/GameObject.hpp"


GameObject::GameObject(std::string tag) : m_tag(std::move(tag)) {}

  
// Identificación y estado
const std::string& GameObject::GetTag() const { return m_tag; }
void GameObject::SetTag(std::string tag) { m_tag = std::move(tag); }
bool GameObject::IsActive() const { return m_active; }
void GameObject::SetActive(bool active) { m_active = active; }


// Propagación del ciclo de vida a todos los componentes hijos
void GameObject::Update(float dt) {
  if (!m_active) return;
  for (auto &component : m_components)
    component->Update(dt);
}

void GameObject::Render(SDL_Renderer *renderer) {
  if (!m_active) return;
  for (auto &component : m_components)
    component->Render(renderer);
}

void GameObject::OnCollision(GameObject *other) {
  if(!m_active) return;
  for(auto &component : m_components)
    component->OnCollision(other);
}
