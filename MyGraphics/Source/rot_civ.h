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
    string returnDialogue(size_t order);
    bool interaction();

private:
    Camera3 *dub_camera;
    float interatingRadius;
    double time;
};

#endif