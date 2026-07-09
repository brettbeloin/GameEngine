#include "Engine.h"
#include "Input.h"
#include "random.h"
#include "vector2.h"
#include <vector>

#include <iostream>

struct Transform {
    Engine::Vector2 position;
    float           rotation;
    float           scale;
};

class Actor {
  public:
    Actor() = default;
    Actor(const Transform &transform) : m_transform{transform} {};

    void Update(float dt) {
        m_transform.position += (m_velocity * dt);
        m_velocity *= .9;

        // m_transform.scale = 50;
        m_transform.position.x = Engine::Math::Clamp(0.f, 500.f, m_transform.position.x);
        m_transform.position.y = Engine::Math::Wrap(0.f, 500.f, m_transform.position.y);
    }

    void Draw(const Engine::Renderer &renderer) {
        renderer.SetColor(static_cast<Uint8>(255), 0.0, 0.0, 255);
        renderer.DrawFillRect(m_transform.position.x - (m_transform.scale * .5f),
                              m_transform.position.y - (m_transform.scale * .5f), m_transform.scale, m_transform.scale);
    }

    const Transform &GetTransform() const {
        return m_transform;
    }

    const Engine::Vector2 &GetVelocity() const {
        return m_velocity;
    }

    void SetScale(float scale) {
        m_transform.scale = scale;
    }

    void SetVelocity(const Engine::Vector2 &position) {
        m_velocity = position;
    }

    void SetRotation(float rotation) {
        m_transform.rotation = rotation;
    }

    // const Engine::Vector2 &SetVector() {
    // }

  protected:
    Transform       m_transform;
    Engine::Vector2 m_velocity;
};

int main(int argc, char *argv[]) {
    Engine::Renderer     renderer;
    const Engine::Window window = {"Game Engine", 500, 500}; // Set the window width and height

    Actor                player{
        Transform{Engine::Vector2{(static_cast<float>(window.window_width) / 2),
                                  (static_cast<float>(window.window_height) / 2)},
                  0.f, 50.0f}
    };
    Engine::Time                 time;

    Engine::Input                input;

    std::vector<Engine::Vector2> points;

    float                        speed = 50.f;
    Engine::Vector2              volocity{0.0f, 0.0f};

    if (const bool initSuccess = renderer.Initialize(window); !initSuccess) {
        std::cerr << "Failed to initialize the renderer." << std::endl;
        return -1;
    }

    std::cout << "Successfully initialized the renderer." << std::endl;
    input.Initialize();

    // MAIN LOOP
    bool quit = false;
    while (!quit) {

        // UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }

            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }

        // Engine
        input.Update();
        time.Tick();

        Engine::Vector2 force{.0f, 0.f};
        if (input.GetKeyDown(SDL_SCANCODE_A)) {
            force.x += 1 - speed;
        }

        if (input.GetKeyDown(SDL_SCANCODE_D)) {
            force.x += 1 + speed;
        }
        if (input.GetKeyDown(SDL_SCANCODE_W)) {
            force.y += 1 - speed;
        }
        if (input.GetKeyDown(SDL_SCANCODE_S)) {
            force.y += 1 + speed;
        }

        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));
        player.Update(time.GetDeltaTime());

        // if (pos.x > window.window_width)
        //     pos.x = 0;
        // if (pos.x < 0) {
        //     pos.x = window.window_width;
        // }

        // RENDERER

        Engine::Vector2 mouse_pos;
        SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);

        renderer.SetColor(0.f, 0.f, 0.f, 255.f); // Set draw color to black

        renderer.Clear();                        // Clear the screen

        // step one
        if (input.GetButtonPressed(Engine::Input::MouseButton::LEFT)) {
            // TODO: Add mouse position to std::vector.
            points.push_back(input.GetMousePosition());
        }

        // step two
        Engine::Vector2 position = input.GetMousePosition();
        if (input.GetButtonDown(Engine::Input::MouseButton::LEFT)) {
            if (points.empty()) {
                points.push_back(input.GetMousePosition());
            } else if ((position - points.back()).length() > 10) {
                points.push_back(input.GetMousePosition());
            }
        }

        for (int i = 0; i < static_cast<int>(points.size()) - 1; i++) {
            // TODO: Set color or random color.
            // TODO: Call Renderer DrawLine with the std::vector [i] and [i + 1]
            renderer.SetColor(Engine::RandomFloat(256), Engine::RandomFloat(256), Engine::RandomFloat(256), 255);
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        // for (int i = 0; i < static_cast<int>(points.size()) - 1; i++) {
        //     renderer.SetColor(Engine::RandomFloat(256), Engine::RandomFloat(256), Engine::RandomFloat(256), 255);
        //     renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        // }

        player.Draw(renderer);

        renderer.Present(); // Present the rendered content to the
                            // screen
    }
    // SHUTDOWN

    renderer.Destroy(); // Clean up the renderer and window

    return 0;
}
