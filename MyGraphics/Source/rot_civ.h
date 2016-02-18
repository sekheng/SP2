#ifndef ROT_CIV_H_
#define ROT_CIV_H_

#include "objectsForDisplay.h"
#include "Camera3.h"

class rot_civ : public objectsForDisplay {
public:
    rot_civ();
    ~rot_civ();

    void InitDialogues(const char* fileLocation, Camera3& camera);
    vector<string> dialogues;

    void update(double dt);
private:
    Vector3 pos;
    Camera3 *dub_camera;
    float boundaryX, boundaryZ;
};

#endif