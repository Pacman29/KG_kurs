#ifndef MODEL_TRANSF_H
#define MODEL_TRANSF_H
#include "base_model_transf.h"
namespace model_trans {
class move : public base_model_trans
{
public:
    move(float posX = 0,float posY = 0,float posZ = 0): _posX(posX),_posY(posY),_posZ(posZ){}
    void execute(model* _model) override final
    {
        _model->move(_posX,_posY,_posZ);
    }
    virtual QString type_transform()
    {
        return "model_trans";
    }
private:
    float _posX;
    float _posY;
    float _posZ;
};

class rotate : public base_model_trans
{
public:
    rotate(float angle, float X,float Y,float Z): _angle(angle),_posX(X),_posY(Y),_posZ(Z){}
    void execute(model* _model) override final
    {
        _model->rotate(_angle,_posX,_posY,_posZ);
    }
    virtual QString type_transform()
    {
        return "model_trans";
    }
private:
    float _angle;
    float _posX;
    float _posY;
    float _posZ;
};


class scale : public base_model_trans
{
public:
    scale(float factor = 1): _factor(factor){}
    void execute(model* _model) override final
    {
        _model->scale(_factor);
    }
    virtual QString type_transform()
    {
        return "model_trans";
    }
private:
    float _factor;
};
}
#endif // MODEL_TRANSF_H
