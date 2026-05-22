#include "world.h"
#include "object.h"
#include "subject.h"
#include "sat_creator.h"
#include "mymesh.h"
#include "mysphere.h"
#include "mat_point.h"
#ifndef CONFIG_H
#define CONFIG_H
// Данные для пирамиды
std::vector<Vector3> verts = {
    { 0, 1, 0 },    // 0: Верхушка
    {-1, 0, 1 },    // 1: Лево-перед
    { 1, 0, 1 },    // 2: Право-перед
    { 0, 0,-1 }     // 3: Зад
};

// Описываем грани через индексы вершин (по 3 на треугольник)
std::vector<int> idx = {
    0, 1, 2, // Передняя грань
    0, 2, 3, // Правая грань
    0, 3, 1, // Левая грань
    1, 3, 2  // Основание
};

float scaleFactor = 1.0f / 6378100.0f;
float timeScale = 60 * 60;

void initconfig(World*& world, Subject*& player) {
    world = new World();
    player = new SatCreator(world);
    world->add_object(new MatPoint(6378100 / 2, BLUE, 5.972f * pow(10, 24), (Vector3){0.0f, 0.0f, 0.0f}));

    world->add_object(new MatPoint(637810, RED, 450000, (Vector3){6378100 + 400000.0f, 0.0f, 0.0f}, (Vector3){0.0f, 0.0f, 7660.0f}));

    world->add_object(new MatPoint(637810, GREEN, 450000, (Vector3){-6378100 - 600000.0f, 0.0f, 0.0f}, (Vector3){0.0f, 0.0f, -8274.0f}));

}

#endif