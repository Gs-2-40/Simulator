#include "Objects/object.h"
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <iostream>

#include <typeinfo>
#include <cmath>

#ifndef WORLD_H
#define WORLD_H
class World {
private:
    std::vector<Object*> objects;
public:
    Matrix world_transform;

    World() {
        world_transform = MatrixIdentity();
    }

    std::vector<Object*>* get_objects() {
        return &objects;
    }

    void add_object(Object* object) {
        objects.push_back(object);
    }
    void draw() {
        for (int i = 0; i < objects.size(); i++) {
            objects[i]->draw(world_transform);
        }
    }


    void process(float timeScale) {
        for (int i = 0; i < objects.size(); i++) {
            objects[i]->process(objects, timeScale);
        }
    }

    void process() {
        for (int i = 0; i < objects.size(); i++) {
            objects[i]->process(objects);
        }
    }

    ~World() {
        for (int i = 0; i < objects.size(); i++) {
            delete objects[i];
        }
    }
};
#endif