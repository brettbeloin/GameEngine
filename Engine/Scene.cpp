//
// Created by brett on 7/21/26.
//
#include "Scene.h"
#include "Actor.h"

void Engine::Scene::Update(float dt) {
    for (auto actor : m_actors) {
        actor->Update(dt);
    }
}

void Engine::Scene::Draw(const Renderer &renderer) const {
    for (auto actor : m_actors) {
        actor->Draw(renderer);
    }
}