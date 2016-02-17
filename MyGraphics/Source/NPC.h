#include "GameObject.h"
#include "Vector3.h"
class NPC : public GameObject
{
public:
    NPC();
    ~NPC();

    float NPC_getposition_x(float x);
    float NPC_getposition_z(float z);

private:
    Vector3 NPC_pos;
    float x, z;
protected:
};