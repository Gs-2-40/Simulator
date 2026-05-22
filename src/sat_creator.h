#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <vector>
#include <iostream>
#include "mat_point.h"
#include "subject.h"

#ifndef SATCREATOR_H
#define SATCREATOR_H
class SatCreator : public Subject {
private:
    World* world;

public:
    SatCreator(World* w) : Subject() {
        world = w;
    }

    void onClick() override {
        std::cout << "Sat clicked!" << std::endl;
        // Переводим позицию камеры из масштабированных единиц в метры
        Vector3 realPos = Vector3Transform(camera.position, world->world_transform);
        world->add_object(new MatPoint(637810, BLACK, 450000,
                                    realPos,
                                    Vector3Scale(direction, 7660.0f)));
    }

};
#endif