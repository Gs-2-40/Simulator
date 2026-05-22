#include "object.h"
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
    void add_object(Object* object) {
        objects.push_back(object);
    }
    void draw() {
        for (int i = 0; i < objects.size(); i++) {
            objects[i]->draw(world_transform);
        }
    }


    void process(float timeScale) {
        std::cout << objects.size();
        for (int i = 0; i < objects.size(); i++) {
            objects[i]->process(objects, timeScale);
            std::cout << "{" << objects[i]->position.x << " " << objects[i]->position.y << " " << objects[i]->position.z << "} ";
        }
        std::cout << std::endl;
    }

    void process() {
        for (int i = 0; i < objects.size(); i++) {
            objects[i]->process(objects);
            //std::cout << objects[i]->position.x << "|" << objects[i]->position.y << "|" << objects[i]->position.z << ' ';
        }
        std::cout << std::endl;
    }

    ~World() {
        for (int i = 0; i < objects.size(); i++) {
            delete objects[i];
        }
    }
};
#endif