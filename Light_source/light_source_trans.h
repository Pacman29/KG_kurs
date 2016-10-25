#ifndef LIGHT_SOURCE_TRANS_H
#define LIGHT_SOURCE_TRANS_H
#include "base_light_source_trans.h"
namespace Light_source_trans {
class move : public base_light_source_trans
{
public:
    move(float posX = 0,float posY = 0,float posZ = 0) : _posX(posX),_posY(posY),_posZ(posZ){}
    void execute(Light_source* _light_source)
    {
        _light_source->move(_posX,_posY,_posZ);
    }

    const char* type_transform()
    {
        return "light_source_trans";
    }
private:
    float _posX;
    float _posY;
    float _posZ;
};
}
#endif // LIGHT_SOURCE_TRANS_H
