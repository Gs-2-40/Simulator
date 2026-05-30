#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <vector>
#include "object.h"

#ifndef MYMESH_H
#define MYMESH_H
class MyMesh : public Object {
private:
    std::vector<Vector3> vertices;
    std::vector<int> indices;
    Color color;
public:
    MyMesh(std::vector<Vector3> v, std::vector<int> i, Color c) : vertices(v), indices(i), color(c) {
        object_transform = MatrixIdentity();
        position = {0.0f, 0.0f, 0.0f};
    }
    MyMesh(std::vector<Vector3> v, std::vector<int> i, Color c, Matrix o_t, Vector3 pos) 
        : vertices(v), indices(i), color(c) {
        object_transform = o_t;
        position = pos;
    }
    MyMesh(std::vector<Vector3> v, std::vector<int> i, Color c, Vector3 pos) : vertices(v), indices(i), color(c) {
        object_transform = MatrixIdentity();
        position = pos;
    }
    MyMesh(std::vector<Vector3> v, std::vector<int> i, Color c, Matrix o_t) 
        : vertices(v), indices(i), color(c) {
        object_transform = o_t;
        position = {0.0f, 0.0f, 0.0f};
    }

    void draw(Matrix world_transform) const override {
        rlPushMatrix();
            rlMultMatrixf(MatrixToFloat(MatrixMultiply(object_transform, world_transform)));

            rlBegin(RL_TRIANGLES);
                rlColor4ub(color.r, color.g, color.b, color.a);

                for (int i = 0; i < indices.size(); i++) {
                    int index = indices[i];
                    Vector3 v = vertices[index];
                    rlVertex3f(v.x, v.y, v.z);
                }
            rlEnd();
        rlPopMatrix();
    }
};
#endif