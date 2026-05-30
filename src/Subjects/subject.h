#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <vector>

#ifndef SUBJECT_H
#define SUBJECT_H
class Subject {
protected:
    float angleH = 0.0f; // Горизонтальный угол
    float angleV = 0.0f; // Вертикальный угол
    float speed = 0.1f;
    Vector3 direction;
    bool isPaused = false;

public:
    Camera3D camera;
    Matrix subject_transform;

    Subject() {
        camera = Camera3D();
        camera.target = (Vector3){ 0.0f, 0.0f, 1.0f };      // Куда смотрим
        camera.position = (Vector3){0.0f, 0.0f, 0.0f}; // Где мы находимся
        camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Где у нас "верх"
        camera.fovy = 45.0f;                                // Угол обзора
        camera.projection = CAMERA_PERSPECTIVE;             // Режим перспективы
        subject_transform = MatrixIdentity();
        DisableCursor();
    }

    virtual void onClick() {};

    virtual void updatePos() {
        direction = Vector3Normalize(camera.target - camera.position);
        float deltaTime = GetFrameTime();
        if (IsKeyDown(KEY_W)) camera.position = Vector3Add(camera.position, Vector3Scale(direction, speed * 60.0f * deltaTime));
        if (IsKeyDown(KEY_S)) camera.position = Vector3Subtract(camera.position, Vector3Scale(direction, speed * 60.0f * deltaTime));
        if (IsKeyDown(KEY_A)) camera.position = Vector3Subtract(camera.position, Vector3Scale(Vector3Normalize(Vector3CrossProduct(direction, camera.up)), speed * 60.0f * deltaTime));
        if (IsKeyDown(KEY_D)) camera.position = Vector3Add(camera.position, Vector3Scale(Vector3Normalize(Vector3CrossProduct(direction, camera.up)), speed * 60.0f * deltaTime)); 

    }

    virtual void updateDirection() {
        camera.fovy -= GetMouseWheelMove() * 2.0f;
        if (camera.fovy < 5.0f) camera.fovy = 5.0f;   // Максимальный зум
        if (camera.fovy > 120.0f) camera.fovy = 120.0f; // минимальный зум

        Vector2 mouseDelta = GetMouseDelta();
        float sensitivity = 0.003f;

        if (!isPaused) {
            angleH -= mouseDelta.x * sensitivity;
            angleV -= mouseDelta.y * sensitivity;
        }

        // Ограничиваем вертикальный угол, чтобы камера не перевернулась
        if (angleV > 3.1415f / 2.0f) angleV = 3.1415f / 2.0f;
        if (angleV < -3.1415f / 2.0f) angleV = -3.1415f / 2.0f;


        camera.target.x = camera.position.x + cosf(angleV) * sinf(angleH);
        camera.target.y = camera.position.y + sinf(angleV);
        camera.target.z = camera.position.z + cosf(angleV) * cosf(angleH);
    }

    void UpdateCamera() {
        this->updatePos();

        this->updateDirection();

        if (IsKeyPressed(KEY_TAB)) {
            if (!isPaused) {
                EnableCursor();
                isPaused = true;
            } else {
                DisableCursor();
                isPaused = false;
            }
        }
        if (IsKeyPressed(KEY_SPACE)) {
            onClick();
        }
    }
};
#endif