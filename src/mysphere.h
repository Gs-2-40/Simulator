#include "raylib.h"
#include "raymath.h"
#include "object.h"
#ifndef MYSPHERE_H
#define MYSPHERE_H

class MySphere : public Object {
protected:
    float radius;
    Color color;
public:

    MySphere(float radius, Color c, Matrix o_t, Vector3 pos) : radius(radius), color(c) {
        object_transform = o_t;
        position = pos;
    }

    MySphere(float r, Color c) : radius(r), color(c) {
        object_transform = MatrixIdentity();
        position = {0.0f, 0.0f, 0.0f};
    }
    MySphere(float r, Color c, Matrix o_t) : radius(r), color(c) {
        object_transform = o_t;
        position = {0.0f, 0.0f, 0.0f};
    }

    MySphere(float r, Color c, Vector3 pos) : radius(r), color(c) {
        object_transform = MatrixIdentity();
        position = pos;
    }

    void draw(Matrix world_transform) const override {
            // Вычисляем итоговую матрицу (объект -> мир)
        Matrix finalTransform = MatrixMultiply(object_transform, world_transform);
        
        // Передаем трансформацию в OpenGL (rlgl)
        rlPushMatrix();
            rlMultMatrixf(MatrixToFloat(finalTransform));
            DrawSphere(position, radius, color); 
        rlPopMatrix();
    }
};

#endif