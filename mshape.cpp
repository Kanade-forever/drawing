#include "mshape.h"

mShape::mShape(){
    this->pen.setColor(Qt::black);
    this->pen.brush().setColor(Qt::white);
    this->pen.setWidth(1);
    this->Fill_Color = Qt::white;

}
void mShape::setShape(Graph _graph){
    this->brush.setColor(Qt::white);
    this->brush.setStyle(Qt::SolidPattern);
    Current_Graph = _graph;
    this->Point_List.clear();
}

void mShape::Set_Shape(Graph _graph){
    this->Current_Graph = _graph;
}


