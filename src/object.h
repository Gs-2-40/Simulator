#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <vector>

#ifndef OBJECT_H
#define OBJECT_H
//Interface
class Object {
public:
    Matrix object_transform;
    Vector3 position;

    virtual ~Object() {}

    // Метод для отрисовки (соблюдаем инкапсуляцию)
    virtual void draw(Matrix world_transform) const = 0;

    virtual void process(std::vector<Object*>& objects) {};

    virtual void process(std::vector<Object*>& objects, float timeScale) {};
};
#endif