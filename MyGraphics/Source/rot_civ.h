#ifndef ROT_CIV_H_
#define ROT_CIV_H_

#include "GameObject.h"
#include "Vector3.h"

class rot_civ : public GameObject {
public:
    rot_civ();
    ~rot_civ();

    void Init(const char *fileLocation);
private:
    Vector3 pos;
};

#endif