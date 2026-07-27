#pragma once
#include <string>

#include "Model.h"
#include "Scene.h"
#include "Transform.h"

namespace Engine {
    class Scene;

    class Actor {

      public:
        struct ActorDesc {
            std::string name;
            std::string tag;
            Transform   transform;
            Vector2     velocity;
            Model       model;
        };

      public:
        Actor() = default;

        explicit Actor(const ActorDesc &actor_desc)
            : m_name{actor_desc.name}, m_tag{actor_desc.tag}, m_transform{actor_desc.transform},
              m_velocity{actor_desc.velocity}, m_model{actor_desc.model} {};
        explicit Actor(const Transform &transform) : m_transform{transform} {};
        explicit Actor(const Transform &transform, const Model &model) : m_transform{transform}, m_model{model} {};

        virtual void Update(float dt);

        virtual void Draw(const class Renderer &renderer) const;

        virtual void OnCollison(Actor *other) {};

        Transform   &GetTransform() {
            return m_transform;
        }

        void SetPosition(const Vector2 &position) {
            m_transform.position = position;
        }

        void SetScale(const float scale) {
            m_transform.scale = scale;
        }

        void SetRotation(const float rotation) {
            m_transform.rotation = rotation;
        }

        const Vector2 &GetVelocity() const {
            return m_velocity;
        }

        void SetVelocity(const Vector2 &position) {
            m_velocity = position;
        }

        void AddVelocity(const Vector2 &position) {
            m_velocity = position;
        }

        const std::string &GetName() const {
            return m_name;
        }

        const std::string &GetTag() const {
            return m_tag;
        }

        Scene *GetScene() const {
            return m_scene;
        }

        bool GetDestroyed() const {
            return m_destroyed;
        };

        void SetDestroyed(bool destroyed = true) {
            m_destroyed = destroyed;
        }

        // Scene *m_scene = nullptr;

        float GetRadius() const;
        friend Scene;

      protected:
        std::string m_name;
        std::string m_tag;

        Transform   m_transform;
        Vector2     m_velocity{0, 0};

        Model       m_model;
        Scene      *m_scene = nullptr;

        bool m_destroyed = false;
    };
} // namespace Engine
