#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <vector>
#include <iostream>
#include "../Objects/mat_point.h"
#include "subject.h"

#ifndef SHATTLE_H
#define SHATTLE_H
class Shattle : public Subject {
private:
    Vector3 velocity = {0.0f, 0.0f, 0.0f};
    float speed = 10000000.0f;
    float mass = 900000.0f;
    World* world;
    Vector3 position;
    bool is_gravitated = false;

public:
    Shattle(World* w) : Subject() {
        this->world = w;
        camera.position = (Vector3){0.0f, 1.0f, -1.0f};
        this->position = Vector3Transform(camera.position, MatrixInvert(world->world_transform));
    }
    void updatePos() override {
        direction = Vector3Normalize(camera.target - camera.position);
        float deltaTime = GetFrameTime();
        if (IsKeyDown(KEY_W)) this->velocity = Vector3Add(this->velocity, Vector3Scale(direction, speed * deltaTime));
        if (IsKeyDown(KEY_S)) this->velocity = Vector3Subtract(this->velocity, Vector3Scale(direction, speed * deltaTime));
        if (IsKeyDown(KEY_A)) this->velocity = Vector3Subtract(this->velocity, Vector3Scale(Vector3Normalize(Vector3CrossProduct(direction, camera.up)), speed * deltaTime));
        if (IsKeyDown(KEY_D)) this->velocity = Vector3Add(this->velocity, Vector3Scale(Vector3Normalize(Vector3CrossProduct(direction, camera.up)), speed * deltaTime));
        if (IsKeyPressed(KEY_G)) {
            is_gravitated = !is_gravitated;
        }
        if (is_gravitated) this->process(deltaTime);
        this->position = Vector3Add(this->position, Vector3Scale(this->velocity, deltaTime));
        camera.position = Vector3Transform(this->position, world->world_transform);
    }

    Vector3 force(MatPoint* object) {
        Vector3 direction = Vector3Normalize(Vector3Subtract(object->position, this->position));
        float distance = Vector3Length(Vector3Subtract(object->position, this->position));
        if (distance < object->getRadius()) distance = object->getRadius();
        float force = 6.6743f * pow(10, -11) * this->mass * object->getMass() / (distance * distance);
        return Vector3Scale(direction, force);
    }

    void process(float deltaTime) {
        Vector3 force = {0.0f, 0.0f, 0.0f};
        std::vector<Object*>* objects = world->get_objects();
        for (int i = 0; i < (*objects).size(); i++) {
            force = Vector3Add(force, this->force((MatPoint*)((*objects)[i])));
        }
        this->velocity = Vector3Add(this->velocity, Vector3Scale(force, deltaTime)); 
    }

    virtual void updateDirection() {
        camera.fovy -= GetMouseWheelMove() * 2.0f;
        if (camera.fovy < 5.0f) camera.fovy = 5.0f;   // Максимальный зум
        if (camera.fovy > 120.0f) camera.fovy = 120.0f; // Минимальный зум

        Vector2 mouseDelta = GetMouseDelta();
        float sensitivity = 0.002f;

        if (!isPaused) {
            angleH -= mouseDelta.x * sensitivity;
            angleV -= mouseDelta.y * sensitivity;
        }

        if (angleV > 3.1415f / 2.0f) angleV = 3.1415f / 2.0f;
        if (angleV < -3.1415f / 2.0f) angleV = -3.1415f / 2.0f;

        camera.target.x = camera.position.x + cosf(angleV) * sinf(angleH);
        camera.target.y = camera.position.y + sinf(angleV);
        camera.target.z = camera.position.z + cosf(angleV) * cosf(angleH);
    }
};
#endif