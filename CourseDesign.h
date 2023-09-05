#ifndef COURSEDESIGN_H
#define COURSEDESIGN_H

#include <QMainWindow>
#include <QVector>
#include <QList>
#include <QPainter>
#include <mshape.h>
#include <Pen_Style.h>
#include <QBrush>
#include <Graph_Edit.h>

namespace Ui {
class CourseDesign;
}

class CourseDesign : public QMainWindow
{
    Q_OBJECT

public:
    CourseDesign(QWidget *parent = nullptr);
    friend class Pen_Style;
    ~CourseDesign();

private slots:

    void on_Open_File_triggered ();

    void on_Draw_Point_triggered ();

    void on_Pen_Style_triggered ();

    void on_Draw_Line_triggered ();

    void on_Draw_Circle_triggered ();

    void on_Draw_Oval_triggered ();

    void on_Draw_Rectangle_triggered ();

    void on_Draw_Polypon_Five_triggered ();

    void on_Draw_Polypon_Six_triggered ();

    void on_Draw_Polypon_Seven_triggered ();

    void on_Draw_Polypon_Eight_triggered ();

    void on_Draw_Polypon_Ten_triggered ();

    void on_Save_File_triggered ();

    void on_Clear_Screen_triggered();

    void on_Select_Mode_triggered();

    void on_Menu_Copy_triggered();

    void on_Menu_Paste_triggered();

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);//鼠标双击
    virtual void mousePressEvent(QMouseEvent *event);//鼠标按下
    virtual void mouseReleaseEvent(QMouseEvent *event);//鼠标释放
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent*event);//绘画事件函数
    virtual void keyPressEvent(QKeyEvent *event);//键盘事件

    void Point_Save();

private:

    Ui::CourseDesign *ui;
    QPoint Start_Point;
    QPoint End_Point;
    mShape shape;
    mShape Copy_Shape;

    QPoint Move_Start;
    QPoint Move_End;

    int Choosen_Shape;
    double side;
    double length;
    double width;
    int Current_Size = 0;

    bool If_Draw = false;
    bool If_Choose = false;
    bool If_Move = false;
    bool If_Press = false;
    bool If_Draw_Sure = false;

    Pen_Style pen_style;
    Graph_Edit graph_edit;

    QList<mShape> List;
};

#endif // COURSEDESIGN_H
