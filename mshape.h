#ifndef MSHAPE_H
#define MSHAPE_H
#include <mline.h>
#include <mpoint.h>
#include <QBrush>

class mShape:public mLine,public mPoint
{
public:

    mShape();
    enum Graph{
        eNull,
        ePoint,
        eLine,
        eCircle,
        eOval,
        eRectangle,
        ePolypon_Five,
        ePolypon_Six,
        ePolypon_Seven,
        ePolypon_Eight,
        ePolypon_Ten
    };
    friend class Graph_Edit;
    bool edited = false;

    Graph Current_Graph;
    QColor Fill_Color;
    QBrush brush;

    void setShape(Graph _graph);
    void Set_Shape(Graph _graph);
};

#endif // MSHAPE_H
