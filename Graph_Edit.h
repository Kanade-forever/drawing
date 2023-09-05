#ifndef GRAPH_EDIT_H
#define GRAPH_EDIT_H

#include <QWidget>
#include <QColorDialog>
#include <QColor>
#include <QSlider>


namespace Ui {
class Graph_Edit;
}

class Graph_Edit : public QWidget
{
    Q_OBJECT

public:
    explicit Graph_Edit(QWidget *parent = nullptr);

    QColor Pen_Color;
    QColor Fill_Color;
    Qt::PenStyle Pen_Style = Qt::SolidLine;
    int  Scale = 100;
    int Line_Width = 1;

    ~Graph_Edit();

private slots:
    void on_comboBox_2_activated(const QString &arg1);

    void on_horizontalSlider_valueChanged(int value);

    void on_Fill_Color_clicked();

    void on_Line_Color_clicked();

    void on_Slider_Scale_valueChanged(int value);

//    void on_Slider_Spin_valueChanged(int value);


private:
    Ui::Graph_Edit *ui;
};

#endif // GRAPH_EDIT_H
