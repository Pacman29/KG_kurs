#include "tesselator.h"
#include <cfloat>
#include <omp.h>

tesselator::tesselator()
{

}

void tesselator::tesselate(tesselator::tess_state state, model* mdl)
{
    switch (state) {
    case UP:
        tesselate_up(mdl);
        break;
    case DOWN:
        tesselate_down(mdl);
        break;
    }
}

void tesselator::tesselate_up(model *mdl)
{
    if(mdl->polygons.size()*4 > mdl->high_model->polygons.size())
        return;
    mdl->inc_k_ts();
    QVector<Polygon> tmp_pol = mdl->polygons;
    mdl->polygons.clear();

    Point3D p1,p2,p3;
    Polygon tmp, fill;
    int i = 0;
    //int gran = tmp_model.polygons.size()*256/high_model.polygons.size();  // учесть № грани!
    while(!tmp_pol.empty())
    {
        tmp = tmp_pol[0];
        tmp_pol.erase(tmp_pol.begin());
        p1 = tmp.get_middle_side(0,1);
        p2 = tmp.get_middle_side(0,2);
        p3 = tmp.get_middle_side(2,1);

        correct(p1, p2, p3,mdl->high_model->polygons,0);   /*i/gran*256*/
        i++;

        fill.set_color(tmp.get_color());
        fill.set_vertexes(p1,p2,p3);
        mdl->polygons.push_back(fill);
        fill.set_vertexes(p1,p2,tmp[0]);
        mdl->polygons.push_back(fill);
        fill.set_vertexes(p2,p3,tmp[2]);
        mdl->polygons.push_back(fill);
        fill.set_vertexes(p3,p1,tmp[1]);
        mdl->polygons.push_back(fill);
    }

}

void tesselator::tesselate_down(model* mdl)
{
    if(mdl->polygons.size()/4 <= mdl->get_low_size())
        return;
    mdl->dec_k_ts();
    QVector<Polygon> tmp_pol = mdl->polygons;
    Polygon t_pol, res_pol;
    mdl->polygons.clear();
    while (!tmp_pol.empty())
    {
        t_pol = tmp_pol[0];
        tmp_pol.erase(tmp_pol.begin());

        for(unsigned int i = 0; i<3; ++i)
        {
            for(size_t j = 0; j<tmp_pol.size();++j)
                if(check(t_pol,tmp_pol[j]))
                {
                    Point3D t = get(t_pol,tmp_pol[j]);
                    res_pol[i] = t;
                    tmp_pol.erase(tmp_pol.begin()+j);
                    j = tmp_pol.size();
                }
        }
        res_pol.set_color(t_pol.get_color());
        mdl->polygons.push_back(res_pol);
    }
}


void tesselator::correct(Point3D &p1, Point3D &p2, Point3D &p3,QVector<Polygon>& high_pol, int begin)
{
        int size = high_pol.size();
        float tmp;
        QVector<Point3D> pnts;
        pnts.push_back(p1);
        pnts.push_back(p2);
        pnts.push_back(p3);

        for(QVector<Point3D>::iterator it = pnts.begin(); it < pnts.end(); ++it)
        {
            float cur_dist = FLT_MAX;
            int pos = 0;
            int point = 0;
            for (int i=begin; i < size; ++i)
            {
                for(int j = 0; j<3; ++j)
                    if ((tmp = distance(*it, high_pol[i][j]))<cur_dist)
                    {
                        cur_dist = tmp;
                        pos = i;
                        point = j;
                    }
            }
            *it = high_pol[pos][point];
        }
        p1 = pnts[0];
        p2 = pnts[1];
        p3 = pnts[2];



/////old version//////////
//    int size = begin+256;
//    float tmp;
//    float eps = 0.05;
//    QVector<Point3D> pnts;
//    pnts.push_back(p1);
//    pnts.push_back(p2);
//    pnts.push_back(p3);

//    for(QVector<Point3D>::iterator it = pnts.begin(); it != pnts.end(); ++it)
//    {
//        float cur_dist = FLT_MAX;
//        int pos = 0;
//        int point = 0;
//        for (int i=begin; i < size; ++i)
//        {
//            for(int j = 0; j<3; ++j)
//                if ((tmp = distance(*it, high_model.polygons[i][j]))<cur_dist)
//                {
//                    cur_dist = tmp;
//                    pos = i;
//                    point = j+1;
//                }
//            if (cur_dist < eps)
//                i = size;
//        }
//        if(point)
//            *it = high_model.polygons[pos][point-1];
//    }
//    p1 = pnts[0];
//    p2 = pnts[1];
//    p3 = pnts[2];
}

float tesselator::distance(Point3D p1, Point3D p2)
{
    return pow(p1.x() - p2.x(),2) + pow(p1.y()-p2.y(),2)+pow(p1.z()-p2.z(),2);
}

Point3D tesselator::get(Polygon p1, Polygon p2)
{
    bool trust[3] {false,false,false};

    for(unsigned int i = 0; i<3; ++i)
        for(unsigned int j = 0; j<3; ++j)
            if((distance(p1[j],p2[i]) < 1e-5))
                trust[i] = true;

    if (trust[0] && trust[1])
        return p2[2];
    if (trust[0] && trust[2])
        return p2[1];
    else
        return p2[0];
}

bool tesselator::check(Polygon p1, Polygon p2)
{
    int trust[3] {0,0,0};
    for(unsigned int i = 0; i<3; ++i)
        for(unsigned int j = 0; j<3; ++j)
            if((distance(p1[j],p2[i]) < 1e-5))
                trust[i] = 1;

    if (trust[0]+trust[1]+trust[2]>1)
        return true;
    else
        return false;
}
