#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <vector>
#include "mysphere.h"

#ifndef MAT_POINT_H
#define MAT_POINT_H

class MatPoint : public MySphere {
private:
    float mass;
    Vector3 velocity;
public:
    MatPoint(float r, Color c, float m, Matrix o_t, Vector3 pos) : MySphere(r, c, o_t, pos) {
        this->mass = m;
    }
    MatPoint(float r, Color c, float m, Matrix o_t) : MySphere(r, c, o_t) {
        this->mass = m;
    }
    MatPoint(float r, Color c, float m, Vector3 pos) : MySphere(r, c, pos) {
        this->mass = m;
    }
    MatPoint(float r, Color c, float m) : MySphere(r, c) {
        this->mass = m;
    }

    MatPoint(float r, Color c, float m, Vector3 pos, Vector3 vel) : MySphere(r, c, pos) {
        this->mass = m;
        this->velocity = vel;
    }
    
    void process(std::vector<Object*>& objects) override {
        
        // 1. Суммируем все силы, действующие на тело
        Vector3 totalForce = {0.0f, 0.0f, 0.0f};
        for (auto* obj : objects) {
            auto* other = dynamic_cast<MatPoint*>(obj);
            if (other && other != this) {
                totalForce = Vector3Add(totalForce, this->force(other));
            }
        }
            
        // 2. Обновляем скорость
        this->velocity = Vector3Add(this->velocity, Vector3Scale(totalForce, 1.0f / this->mass));
        
        // 3. Обновляем позицию (один раз!)
        this->position = Vector3Add(this->position, Vector3Scale(this->velocity, 1.0f));
    }

    void process(std::vector<Object*>& objects, float timeScale) override {
        float deltaTime = GetFrameTime() * timeScale;
        
        // 1. Суммируем все силы, действующие на тело
        Vector3 totalForce = {0.0f, 0.0f, 0.0f};
        for (auto* obj : objects) {
            auto* other = dynamic_cast<MatPoint*>(obj);
            if (other && other != this) {
                totalForce = Vector3Add(totalForce, this->force(other));
            }
        }
            
        // 2. Обновляем скорость
        this->velocity = Vector3Add(this->velocity, Vector3Scale(totalForce, deltaTime / this->mass));
        
        // 3. Обновляем позицию (один раз!)
        this->position = Vector3Add(this->position, Vector3Scale(this->velocity, deltaTime));
    }


    Vector3 force(MatPoint* other) {
        float distance = Vector3Distance(this->position, other->position);
        if (distance < (other->radius + this->radius)) distance = other->radius + this->radius;
        float force = 6.6743f * pow(10, -11) * this->mass * other->mass / (distance * distance);
        Vector3 direction = Vector3Normalize(Vector3Subtract(other->position, this->position));
        return Vector3Scale(direction, force);
    }
};

#endif