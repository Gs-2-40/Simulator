#include "world.h"
#include "Objects/object.h"
#include "Subjects/subject.h"
#include "Subjects/sat_creator.h"
#include "Subjects/shattle.h"
#include "Objects/mymesh.h"
#include "Objects/mysphere.h"
#include "Objects/mat_point.h"
#ifndef CONFIG_H
#define CONFIG_H

enum subjects {sateliteCreator=SatCreator, shattle=Shattle, subject=Subject};

float scaleFactor = 1.0f / 6378100.0f;
float timeScale = 60 * 60;

void initconfig(World*& world, Subject*& player) {

    world = new World(); // The only existing world
    player = new subjects::shattle(world); // Example subject
    // player = new subjects::sateliteCreator(world);
    //  player = new subjects::subject(world);

    //Initialization of basic test objects
    world->add_object(new MatPoint(6378100 / 2, BLUE, 5.972f * pow(10, 24), (Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 0.0f, 0.0f}));
    world->add_object(new MatPoint(637810, RED, 450000, (Vector3){6378100 + 400000.0f, 0.0f, 0.0f}, (Vector3){0.0f, 0.0f, 7660.0f}));
    world->add_object(new MatPoint(637810, GREEN, 450000, (Vector3){-6378100 - 600000.0f, 0.0f, 0.0f}, (Vector3){0.0f, 0.0f, -8274.0f}));

}

#endif