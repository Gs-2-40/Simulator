#ifndef CONFIG_H
#define CONFIG_H

#include "world.h"
#include "Objects/object.h"
#include "Subjects/subject.h"
#include "Subjects/sat_creator.h"
#include "Subjects/shattle.h"
#include "Objects/mymesh.h"
#include "Objects/mysphere.h"
#include "Objects/mat_point.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;
const std::string filename = "config.json";

extern float scaleFactor;
extern float timeScale;
extern std::string subject;

void initconfig(World*& world, Subject*& player) {

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть конфиг: " << filename << ". Используются дефолтные параметры.\n";
        return;
    }

    try {
        json configData;
        file >> configData;

        if (configData.contains("simulation")) {
            scaleFactor = configData["simulation"].value("scaleFactor", scaleFactor);
            timeScale = configData["simulation"].value("timeScale", timeScale);
            subject = configData["simulation"].value("subject", subject);
        }
        world = new World(); // The only existing world

        if (subject == "SatCreator") {
            player = new SatCreator(world);
        } else if (subject == "Shattle") {
            player = new Shattle(world);
        } else {
            player = new Subject();
        }

        world->world_transform = MatrixScale(scaleFactor, scaleFactor, scaleFactor);

        if (configData.contains("objects") && configData["objects"].is_array()) {
            for (const auto& objJson : configData["objects"]) {
                std::string type = objJson.value("type", "MatPoint");
                
                if (type == "MatPoint") {
                    float radius = objJson.value("radius", 637810.0f);
                    float mass = objJson.value("mass", 450000.0f);
                    
                    // Парсинг цвета [R, G, B, A]
                    Color color = WHITE;
                    if (objJson.contains("color") && objJson["color"].size() == 4) {
                        color.r = objJson["color"][0];
                        color.g = objJson["color"][1];
                        color.b = objJson["color"][2];
                        color.a = objJson["color"][3];
                    }

                    // Парсинг векторов позиции и скорости
                    Vector3 pos = { 0.0f, 0.0f, 0.0f };
                    if (objJson.contains("position") && objJson["position"].size() == 3) {
                        pos.x = objJson["position"][0];
                        pos.y = objJson["position"][1];
                        pos.z = objJson["position"][2];
                    }

                    Vector3 vel = { 0.0f, 0.0f, 0.0f };
                    if (objJson.contains("velocity") && objJson["velocity"].size() == 3) {
                        vel.x = objJson["velocity"][0];
                        vel.y = objJson["velocity"][1];
                        vel.z = objJson["velocity"][2];
                    }

                    // Создаем объект и добавляем в мир
                    world->add_object(new MatPoint(radius, color, mass, pos, vel));
                }
            }
        }
        std::cout << "Конфигурация успешно загружена из " << filename << std::endl;
    } 
    catch (const json::parse_error& e) {
        std::cerr << "Ошибка синтаксиса JSON: " << e.what() << std::endl;
    }
}

#endif