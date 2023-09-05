#include "used_header.h"
#include "CourseDesign.h"
#include "QMessageBox"
#include "mshape.h"

#define min(a,b) a>b?b:a

CourseDesign::CourseDesign(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CourseDesign)
{
    ui->setupUi(this);

    Copy_Shape.setShape(mShape::eNull);

    this->pen_style.setWindowTitle("画笔格式");
    this->graph_edit.setWindowTitle("编辑");
    this->setWindowTitle("简单矢量图形处理系统");
}

CourseDesign::~CourseDesign()
{
    delete ui;
}

//----------------------------文件菜单栏

void CourseDesign::on_Open_File_triggered (){//打开文件 槽函数
    QFile file(QFileDialog::getOpenFileName(this,"选择文件","*.txt"));

    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this,"Warning","打开文件失败!");
        return;
    }
    //确认打开文件成功
    List.clear();

    this->Choosen_Shape = -1;
    while(!file.atEnd()){
        QString data = file.readLine();
        int order = 0;
        mShape _shape;
        QStringList data_list = data.split(" ");
        int _Point = data_list[0].toInt();order+=_Point*2+1;
        for(int i=1;i<_Point*2+1;i+=2){
            _shape.Point_List.append(QPoint(data_list[i].toInt(),data_list[i+1].toInt()));
        }
        _shape.pen.setColor(qRgb(data_list[order].toInt(),data_list[order+1].toInt(),data_list[order+2].toInt()));
        order+=3;
        _shape.brush.setColor((qRgb(data_list[order].toInt(),data_list[order+1].toInt(),data_list[order+2].toInt())));
        order+=3;
        _shape.pen.setStyle(Qt::PenStyle(data_list[order].toInt()));order++;
        _shape.pen.setWidth(data_list[order].toInt());order++;
        _shape.Set_Shape(mShape::Graph(data_list[order].toInt()));
        List.append(_shape);

        _shape.Point_List.clear();
        Current_Size++;
    }
    If_Draw = true;
    If_Choose = false;
    If_Move = true;
    update();
    file.close();
}

void CourseDesign::on_Save_File_triggered (){//保存文件 槽函数
    QFile file(QFileDialog::getSaveFileName(this,"另存为","untitled.txt","*.txt"));

    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::warning(this,"Warning","保存文件失败!");
        return;
    }
/*
 * QPoint_Size
 * QVector<QPoint0>
 * QPen_Color
 * QFill_Color
 * QPen_Style
 * QPen_Width
 * QGraph
*/
    //确认保存
    int _size = List.size();
    for(int i=0;i<_size;i++){

        //QVector<QPoint>
        int Point_Size = List[i].Point_List.size();
        file.write(QString::number(Point_Size).toUtf8());
        file.write(" ");
        for(int j=0;j<Point_Size;j++){
            file.write(QString::number(List[i].Point_List[j].x()).toUtf8());
            file.write(" ");
            file.write(QString::number(List[i].Point_List[j].y()).toUtf8());
            file.write(" ");
        }

        //QPen_Color
        file.write(QString::number(List[i].pen.color().red()).toUtf8());
        file.write(" ");
        file.write(QString::number(List[i].pen.color().green()).toUtf8());
        file.write(" ");
        file.write(QString::number(List[i].pen.color().blue()).toUtf8());
        file.write(" ");

        //QFill_Color
        file.write((QString::number(List[i].brush.color().red())).toUtf8());
        file.write(" ");
        file.write((QString::number(List[i].brush.color().green())).toUtf8());
        file.write(" ");
        file.write((QString::number(List[i].brush.color().blue())).toUtf8());
        file.write(" ");

        //QPen_Style
        file.write(QString::number(List[i].pen.style()).toUtf8());
        file.write(" ");

        //QPen_Width
        file.write(QString::number(List[i].pen.width()).toUtf8());
        file.write(" ");

        //Graph
        file.write(QString::number(List[i].Current_Graph).toUtf8());

        file.write(" \n");

    }

    file.close();
}

void CourseDesign::on_Clear_Screen_triggered(){//清空画板
    Current_Size = 0;
    List.clear();
    If_Move = false;
    update();
}

void CourseDesign::on_Menu_Copy_triggered(){//复制图形
    if(Choosen_Shape<0) return;
    this->Copy_Shape = List[Choosen_Shape];
}

void CourseDesign::on_Menu_Paste_triggered(){//粘贴图形
    if(Copy_Shape.Current_Graph == mShape::eNull) return;
    Current_Size++;
    List.append(Copy_Shape);
}

//-----------------------------绘制菜单栏

void CourseDesign::on_Select_Mode_triggered()//不绘制模式
{
    shape.setShape(mShape::eNull);
    If_Move = true;
    If_Choose = true;
}

void CourseDesign::on_Draw_Point_triggered (){//绘制点
    shape.setShape(mShape::ePoint);
    If_Choose = false;
    If_Move = false;
}

void CourseDesign::on_Draw_Line_triggered (){//绘制直线
    shape.setShape(mShape::eLine);
    If_Choose = false;
    If_Move = false;
}

void CourseDesign::on_Draw_Circle_triggered (){//绘制圆
    shape.setShape(mShape::eCircle);
    If_Choose = false;
    If_Move = false;
}

void CourseDesign::on_Draw_Oval_triggered (){//绘制椭圆
    shape.setShape(mShape::eOval);
    If_Choose = false;
    If_Move = false;
}

void CourseDesign::on_Draw_Rectangle_triggered (){//绘制矩形
    shape.setShape(mShape::eRectangle);
    If_Choose = false;
    If_Move = false;
}

void CourseDesign::on_Draw_Polypon_Five_triggered (){//绘制五边形
    shape.setShape(mShape::ePolypon_Five);
    If_Choose = false;
    If_Move = false;
}

void CourseDesign::on_Draw_Polypon_Six_triggered (){//绘制六边形
    shape.setShape(mShape::ePolypon_Six);
    If_Choose = false;
    If_Move = false;
}

void CourseDesign::on_Draw_Polypon_Seven_triggered (){//绘制七边形
    shape.setShape(mShape::ePolypon_Seven);
    If_Choose = false;
    If_Move = false;
}

void CourseDesign::on_Draw_Polypon_Eight_triggered (){//绘制八边形
    shape.setShape(mShape::ePolypon_Eight);
    If_Choose = false;
    If_Move = false;
}

void CourseDesign::on_Draw_Polypon_Ten_triggered (){//绘制十边形
    shape.setShape(mShape::ePolypon_Ten);
    If_Choose = false;
    If_Move = false;
}

//-----------------------------格式菜单栏

void CourseDesign::on_Pen_Style_triggered (){//设置画笔格式
    pen_style.show();
}
//-----------------------------鼠标事件
void CourseDesign::mousePressEvent(QMouseEvent *event){//按下鼠标
    If_Press = true;
    //设置shape 的pen
    if(If_Move) Move_Start = event->pos();
    Start_Point = event->pos();

    shape.pen.setColor(pen_style.Pen_Color);
    shape.pen.setStyle(pen_style.Pen_Styles);
    shape.pen.setWidth(pen_style.Pen_Width);
    shape.brush.setColor(pen_style.Fill_Color);
    shape.Fill_Color = pen_style.Fill_Color;

    if(If_Choose){
        int index = List.size()-1;
        QPoint Clicked_Point = event->pos();

        for(;index>=0;index--){
                if(QRect(List[index].Point_List[0],List[index].Point_List[1]).contains(Clicked_Point)){
                    break;
            }
        }
        if(index<0) return;
        Choosen_Shape = index;
        graph_edit.Pen_Color = List[index].pen.color();
        graph_edit.Pen_Style = List[index].pen.style();
        graph_edit.Fill_Color = List[index].Fill_Color;
        graph_edit.Line_Width = List[index].pen.width();
    }
}

void CourseDesign::mouseMoveEvent(QMouseEvent *event){//鼠标移动
    if(If_Move){

        Move_End = event->pos();
        if(Choosen_Shape<0) return;

        Move_End = event->pos();
        int _x = Move_End.x()-Move_Start.x();
        int _y = Move_End.y()-Move_Start.y();
        for(int i=List[Choosen_Shape].Point_List.size()-1;i>=0;i--){
            List[Choosen_Shape].Point_List[i] = QPoint(List[Choosen_Shape].Point_List[i].x()+_x,List[Choosen_Shape].Point_List[i].y()+_y);
        }
        Move_Start = Move_End;
        If_Draw = true;
    }

    if(!If_Move&&If_Press){
        End_Point = event->pos();
        If_Draw = true;
        If_Draw_Sure = false;

        this->Point_Save();
        //刷新画板
    }
    update();
}

void CourseDesign::mouseReleaseEvent(QMouseEvent *event){//鼠标松开
    End_Point = event->pos();
    If_Draw = true;
    If_Press = false;
    If_Draw_Sure = true;
    if(!If_Move){
        Current_Size++;
    }

    this->Point_Save();
    //刷新画板
    update();
}

void CourseDesign::Point_Save(){
    switch(shape.Current_Graph){
        case mShape::ePoint:{
                shape.Point_List.append(Start_Point);
                List.append(shape);
                shape.Point_List.clear();
            }break;
        case mShape::eLine:{
                shape.Point_List.append(Start_Point);
                shape.Point_List.append(End_Point);
                List.append(shape);
                shape.Point_List.clear();
            }break;
        case mShape::eCircle:{
                shape.Point_List.append(Start_Point);
                shape.Point_List.append(End_Point);
                shape.Point_List.append(0.5*(Start_Point+End_Point));
                List.append(shape);
                shape.Point_List.clear();
            }break;
        case mShape::eOval:{
                shape.Point_List.append(Start_Point);
                shape.Point_List.append(End_Point);
                List.append(shape);
                shape.Point_List.clear();
            }break;
        case mShape::eRectangle:{
                shape.Point_List.append(Start_Point);
                shape.Point_List.append(End_Point);
                List.append(shape);
                shape.Point_List.clear();
            }break;
        case mShape::ePolypon_Five:{
                shape.Point_List.append(Start_Point);
                shape.Point_List.append(End_Point);

                double length = End_Point.x()-Start_Point.x();
                double width  = End_Point.y()-Start_Point.y();
                int _x = Start_Point.x();
                int _y = Start_Point.y();

                shape.Point_List.append(QPoint(int(_x+     0.5 * length),int(_y          )));
                shape.Point_List.append(QPoint(int(_x+           length),int(_y+0.4*width)));
                shape.Point_List.append(QPoint(int(_x+0.766667 * length),int(_y+    width)));
                shape.Point_List.append(QPoint(int(_x+0.233333 * length),int(_y+    width)));
                shape.Point_List.append(QPoint(int(_x                  ),int(_y+0.4*width)));

                List.append(shape);
                shape.Point_List.clear();
            }break;
        case mShape::ePolypon_Six:{
                shape.Point_List.append(Start_Point);
                shape.Point_List.append(End_Point);

                double length = End_Point.x()-Start_Point.x();
                double width  = End_Point.y()-Start_Point.y();
                int _x = Start_Point.x();
                int _y = Start_Point.y();

                shape.Point_List.append(QPoint(int(_x+0.233 * length),int(_y            )));
                shape.Point_List.append(QPoint(int(_x+0.733 * length),int(_y            )));
                shape.Point_List.append(QPoint(int(_x+        length),int(_y+0.5 * width)));
                shape.Point_List.append(QPoint(int(_x+0.733 * length),int(_y+      width)));
                shape.Point_List.append(QPoint(int(_x+0.266 * length),int(_y+      width)));
                shape.Point_List.append(QPoint(int(_x               ),int(_y+0.5 * width)));

                List.append(shape);
                shape.Point_List.clear();
            }break;
        case mShape::ePolypon_Seven:{
                shape.Point_List.append(Start_Point);
                shape.Point_List.append(End_Point);

                double length = End_Point.x()-Start_Point.x();
                double width  = End_Point.y()-Start_Point.y();
                int _x = Start_Point.x();
                int _y = Start_Point.y();

                shape.Point_List.append(QPoint(int(_x+     0.5 * length),int(_y            )));
                shape.Point_List.append(QPoint(int(_x+           length),int(_y+0.4 * width)));
                shape.Point_List.append(QPoint(int(_x+           length),int(_y+0.7 * width)));
                shape.Point_List.append(QPoint(int(_x+0.766667 * length),int(_y+      width)));
                shape.Point_List.append(QPoint(int(_x+0.233333 * length),int(_y+      width)));
                shape.Point_List.append(QPoint(int(_x                  ),int(_y+0.7 * width)));
                shape.Point_List.append(QPoint(int(_x                  ),int(_y+0.4 * width)));

                List.append(shape);
                shape.Point_List.clear();
            }break;
        case mShape::ePolypon_Eight:{
                shape.Point_List.append(Start_Point);
                shape.Point_List.append(End_Point);

                double length = End_Point.x()-Start_Point.x();
                double width  = End_Point.y()-Start_Point.y();
                int _x = Start_Point.x();
                int _y = Start_Point.y();

                shape.Point_List.append(QPoint(int(_x+0.333333 * length),int(_y                 )));
                shape.Point_List.append(QPoint(int(_x+0.666667 * length),int(_y                 )));
                shape.Point_List.append(QPoint(int(_x+           length),int(_y+0.333333 * width)));
                shape.Point_List.append(QPoint(int(_x+           length),int(_y+0.666667 * width)));
                shape.Point_List.append(QPoint(int(_x+0.666667 * length),int(_y+           width)));
                shape.Point_List.append(QPoint(int(_x+0.333333 * length),int(_y+           width)));
                shape.Point_List.append(QPoint(int(_x                  ),int(_y+0.666667 * width)));
                shape.Point_List.append(QPoint(int(_x                  ),int(_y+0.333333 * width)));

                List.append(shape);
                shape.Point_List.clear();
            }break;
        case mShape::ePolypon_Ten:{

                shape.Point_List.append(Start_Point);
                shape.Point_List.append(End_Point);

                double length = End_Point.x()-Start_Point.x();
                double width  = End_Point.y()-Start_Point.y();
                int _x = Start_Point.x();
                int _y = Start_Point.y();

                shape.Point_List.append(QPoint(_x+int(0.0666667 * length),_y+int(0.25 * width)));
                shape.Point_List.append(QPoint(_x+int(0.3333333 * length),_y                  ));
                shape.Point_List.append(QPoint(_x+int(0.6666667 * length),_y                  ));
                shape.Point_List.append(QPoint(_x+int(0.9333333 * length),_y+int(0.25 * width)));
                shape.Point_List.append(QPoint(_x+int(length            ),int(_y+0.5 * width )));
                shape.Point_List.append(QPoint(_x+int(0.9333333 * length),int(_y+0.75 * width)));
                shape.Point_List.append(QPoint(_x+int(0.6666667 * length),int(_y+width)       ));
                shape.Point_List.append(QPoint(_x+int(0.3333333 * length),int(_y+width)       ));
                shape.Point_List.append(QPoint(_x+int(0.0666667 * length),int(_y+0.75 * width)));
                shape.Point_List.append(QPoint(_x                        ,int(_y+0.5 * width )));

                List.append(shape);
                shape.Point_List.clear();
            }break;
        default: ;
    }
}

void CourseDesign::mouseDoubleClickEvent(QMouseEvent *event){

    int index = List.size()-1;
    QPoint Clicked_Point = event->pos();

    for(;index>=0;index--){
            if(QRect(List[index].Point_List[0],List[index].Point_List[1]).contains(Clicked_Point)){
                break;
        }
    }
    if(index<0) return;
    List[index].edited = true;
    graph_edit.show();
}

void CourseDesign::keyPressEvent(QKeyEvent *event){//删除当前选中图形
    for(int i=List.size()-1;i>=0;i--){
        if(i == Choosen_Shape){
            if(event->key() == Qt::Key_Delete){
                List.removeAt(i);
                Choosen_Shape = -1;
                update();
                return;
            }
        }
    }
}

//----------------------------画笔
void CourseDesign::paintEvent(QPaintEvent *){
    if(!If_Draw){
        return;
    }
    int List_size = List.size();
    for(int i=0;i<List_size;i++){
        if(i == Choosen_Shape){
            //设置当前选中图形 格式
            List[i].pen.setColor(graph_edit.Pen_Color);
            List[i].pen.setStyle(graph_edit.Pen_Style);
            List[i].pen.setWidth(graph_edit.Line_Width);

            List[i].brush.setColor(graph_edit.Fill_Color);
            List[i].Fill_Color = graph_edit.Fill_Color;

            //对当前选中图形进行放缩
            int _x = List[i].Point_List[1].x()-List[i].Point_List[0].x();
            int _y = List[i].Point_List[1].y()-List[i].Point_List[0].y();
            double percent = double(graph_edit.Scale)*0.01;

            List[i].Point_List[1] = QPoint(int(List[i].Point_List[0].x()+_x*percent),int(List[i].Point_List[0].y()+_y*percent));
            for(int j = List[i].Point_List.size()-1;j>0;j--){
                List[i].Point_List[j] = QPoint(List[i].Point_List[0].x()+int((List[i].Point_List[j].x()-List[i].Point_List[0].x())*percent),
                        List[i].Point_List[0].y()+int((List[i].Point_List[j].y()-List[i].Point_List[0].y())*percent));
            }
            graph_edit.Scale = 100;
        }

        //初始化 第i个图形的画笔
        QPainter Painter(this);
        Painter.setPen(List[i].pen);
        Painter.setBrush(List[i].brush);

        //根据shape进行绘制
        switch(List[i].Current_Graph){
            case mShape::ePoint:{
                Painter.drawPoint(List[i].Point_List[0]);
                }break;
            case mShape::eLine:{
                Painter.drawLine(List[i].Point_List[0],List[i].Point_List[1]);
                }break;
            case mShape::eCircle:{
                QPoint center = List[i].Point_List[2];
                int radius = min(center.x()-List[i].Point_List[0].x(),center.y()-List[i].Point_List[0].y());
                Painter.drawEllipse(QRect(QPoint(center.x()-radius,center.y()-radius),QPoint(center.x()+radius,center.y()+radius)));
                }break;
            case mShape::eOval:{
                Painter.drawEllipse(QRect(List[i].Point_List[0],List[i].Point_List[1]));
                }break;
            case mShape::eRectangle:{
                Painter.drawRect(QRect(List[i].Point_List[0],List[i].Point_List[1]));
                }break;
            case mShape::ePolypon_Five:{
                    QPoint points[5];
                    for(int j=2;j<7;j++){
                        points[j-2] = List[i].Point_List[j];
                    }
                    Painter.drawPolygon(points,5);//(点的数组,点的数量)
                }break;
            case mShape::ePolypon_Six:{
                    QPoint points[6];
                    for(int j=2;j<8;j++){
                        points[j-2] = List[i].Point_List[j];
                    }
                    Painter.drawPolygon(points,6);
                }break;
            case mShape::ePolypon_Seven:{
                    QPoint points[7];
                    for(int j=2;j<9;j++){
                        points[j-2] = List[i].Point_List[j];
                    }
                    Painter.drawPolygon(points,7);
                }break;
            case mShape::ePolypon_Eight:{
                    QPoint points[8];
                    for(int j=2;j<10;j++){
                        points[j-2] = List[i].Point_List[j];
                    }
                    Painter.drawPolygon(points,8);
                }break;
            case mShape::ePolypon_Ten:{
                QPoint points[10];
                for(int j=2;j<12;j++){
                    points[j-2] = List[i].Point_List[j];
                }
                Painter.drawPolygon(points,10);
                }break;
            default: ;
        }
        Painter.end();
    }
    if(List_size>Current_Size) List.pop_back();
}



