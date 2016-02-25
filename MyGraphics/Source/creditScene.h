#ifndef CREDITSCENE_H_
#define CREDITSCENE_H_

#include <vector>
#include <string>

using std::vector;
using std::string;

class creditScene {
public:
    creditScene();
    ~creditScene();

    void initCredit(char *fileLocation);
    void updateCredit(double& dt);
    void activateCredit();
    bool goRollCredit();

    float getRollingTitle();
    float getRollingTitleCaption();
    float getMovePositionY();

    vector<string> position;
    vector<string> names;

private:
    float rollingTitle;
    float rollingTitleCaption;
    bool rollCredits;
    float movePositionY;
};

#endif