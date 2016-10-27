#-------------------------------------------------
#
# Project created by QtCreator 2016-10-23T20:54:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KG_Kurs
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Base_transform/base_transform.cpp \
    Camera/base_camera_transformations.cpp \
    Camera/camera.cpp \
    canvas/graphical_sys.cpp \
    canvas/painter.cpp \
    Composit_obj/composit_object.cpp \
    Invisible_obj/invisible_obj.cpp \
    Light_source/base_light_source.cpp \
    Light_source/light_source.cpp \
    loader/loader.cpp \
    Model/base_model.cpp \
    Model/model.cpp \
    Model/polygon.cpp \
    Point3D/point3d.cpp \
    Tesselator/tesselator.cpp \
    Visible_obj/visible_obj.cpp \
    Visible_trans/visible_trans.cpp

HEADERS  += mainwindow.h \
    base_error/base_error.h \
    Base_obj/base_obj.h \
    Base_transform/base_transform.h \
    Camera/base_camera.h \
    Camera/base_camera_transformations.h \
    Camera/camera.h \
    Camera/camera_error.h \
    Camera/camera_transformations.h \
    canvas/base_graphical_sys.h \
    canvas/base_painter.h \
    canvas/graphic_sys_error.h \
    canvas/graphical_sys.h \
    canvas/painter.h \
    canvas/painter_error.h \
    Composit_obj/composit_object.h \
    Invisible_obj/invisible_obj.h \
    Invisible_trans/invisible_trans.h \
    Light_source/base_light_source.h \
    Light_source/base_light_source_trans.h \
    Light_source/light_source.h \
    Light_source/light_source_trans.h \
    loader/base_loader.h \
    loader/loader.h \
    loader/loader_error.h \
    Model/base_model.h \
    Model/base_model_transf.h \
    Model/model.h \
    Model/model_transf.h \
    Model/polygon.h \
    Point3D/point3d.h \
    Tesselator/tesselator.h \
    Visible_obj/visible_obj.h \
    Visible_trans/visible_trans.h

FORMS    += mainwindow.ui

DISTFILES += \
    Models/high_cube.txt \
    Models/high_sphere.txt \
    Models/low_cube.txt \
    Models/low_sphere.txt
