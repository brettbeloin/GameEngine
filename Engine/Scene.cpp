//
// Created by brett on 7/21/26.
//
#include "Scene.h"
#include "Actor.h"

void Engine::Scene::AddActor(Actor *actor) {
    actor->m_scene = this;
    m_actors.push_back(actor);
};

void Engine::Scene::Update(float dt) {
    for (auto actor : m_actors) {
        actor->Update(dt);
    }

    // update collision
    UpdateCollisions();
}

void Engine::Scene::Draw(const Renderer &renderer) const {
    for (auto actor : m_actors) {
        actor->Draw(renderer);
    }
}

void Engine::Scene::UpdateCollisions() {
    for (const auto& actorA : m_actors) {
        for (const auto& actorB : m_actors) {
            if (actorA == actorB || actorA->GetDestroyed() || actorB->GetDestroyed()) {
                continue;
            }

            float distance = (actorA->m_transform.position - actorB->m_transform.position).length();

            if (distance <= actorA->GetRadius() + actorB->GetRadius()) {
                actorA->OnCollison(actorB);
                actorB->OnCollison(actorA);
            }
        }
    }
}
