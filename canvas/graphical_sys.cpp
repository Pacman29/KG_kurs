#include "graphical_sys.h"
#include "Model/model.h"
#include <typeinfo>
#include <iostream>
void Graphical_sysImpl::Draw_scene(base_painter *pntr,composit_object& composit, base_camera& cam)
{
    //throw graphic_sys_error::model_empty();

    QVector<Light_source> lights;
    QVector<Polygon> polygons;
    QMatrix4x4 camMatrix = cam.GetViewMatrix();

    for(composit_object::iterator it = composit.begin(); it != composit.end(); ++it)
    {
        const char* type_obj = ((base_obj*)*it)->type_object();
        if( !strcmp(type_obj,"model") )
        {
            model* tmp_model = (model*)*it;
            for(base_model::const_iterator it_polygon = tmp_model->begin(); it_polygon != tmp_model->end(); ++it_polygon)
            {
                Polygon tmp = *it_polygon;
                tmp.change_point(camMatrix);
                polygons.push_back(tmp);
            }
        }
        else
            if( !strcmp(type_obj,"light_source") )
                lights.push_back(*((Light_source*)it));
    }

    qSort(polygons.begin(),polygons.end(),compare_polygons);
    for(QVector<Polygon>::iterator it = polygons.begin(); it!= polygons.end(); ++it )
    {
        QVector3D tmp = it->normal();
        if(lights.size())
        {
            float cos_tetha = 0;
            for(QVector<Light_source>::iterator it_ligth = lights.begin(); it_ligth != lights.end(); ++it_ligth )
            {
                QVector3D pos_ligth = it_ligth->get_position();
                QVector3D tmp_ligth_vector(tmp.x()-pos_ligth.x(),tmp.y()-pos_ligth.y(),tmp.z()-pos_ligth.z());
                float tmp_cos = QVector3D::dotProduct(tmp,tmp_ligth_vector)/(tmp.length()*tmp_ligth_vector.length());
                if(cos_tetha<tmp_cos)
                    cos_tetha = tmp_cos;
            }
            qreal h,s,l;
            it->get_color().getHslF(&h,&s,&l);
            l = cos_tetha;
            it->set_color(h,s,l);
        }
        pntr->draw_polygon(*it);
    }
 ///////////////////   // debug centre
//    for(composit_object::iterator it = composit.begin(); it != composit.end(); ++it)
//    {
//        const char* type_obj = ((base_obj*)*it)->type_object();
//        if( !strcmp(type_obj,"model") )
//        {
//            model* tmp_model = (model*)*it;
//            pntr->draw_centre(tmp_model->get_centre());
//        }
//    }
 ////////////////////////
}

void Graphical_sysImpl::clear_scene(base_painter *pntr)
{
    pntr->clear_scene();
}


