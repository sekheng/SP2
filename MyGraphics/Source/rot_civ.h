#ifndef ROT_CIV_H_
#define ROT_CIV_H_

#include "GameObject.h"
#include "Camera3.h"

class rot_civ : public GameObject {
public:
    rot_civ();
    ~rot_civ();

    void Init(string& fileLocation, Camera3& camera);
    bool boundaryCheck(float posX, float posZ);
    vector<string> dialogues;

    void update(double dt);
private:
    Vector3 pos;
    Camera3 *dub_camera;
    float boundaryX, boundaryZ;
};

#endif