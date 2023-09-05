#include "Graph_Edit.h"
#include "ui_Graph_Edit.h"


Graph_Edit::Graph_Edit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graph_Edit)
{
    ui->setupUi(this);
    ui->Slider_Scale->setValue(100);
    this->Fill_Color = Qt::white;
}

Graph_Edit::~Graph_Edit()
{
    delete ui;
}

void Graph_Edit::on_comboBox_2_activated(const QString &arg1)
{
    if(arg1 == "—"){
        this->Pen_Style = Qt::SolidLine;
    }
    else if(arg1 == "-----------"){
        this->Pen_Style = Qt::DashLine;
    }
    else if(arg1 == "················"){
        this->Pen_Style = Qt::DotLine;
    }
    else if(arg1 == "-·-·-·-·-·-·-"){
        this->Pen_Style = Qt::DashDotLine;
    }
    else if(arg1 == "-··-··-··-··-··"){
        this->Pen_Style = Qt::DashDotDotLine;
    }
}

void Graph_Edit::on_horizontalSlider_valueChanged(int value)
{
    this->Line_Width = value;
    ui->Pre_Line_Width->setText(QString::number(value));
}

void Graph_Edit::on_Slider_Scale_valueChanged(int value)
{
    this->Scale = value;
    ui->Pre_Scale->setText(QString::number(value) + "%");
}

void Graph_Edit::on_Fill_Color_clicked()
{
    this->Fill_Color = QColorDialog::getColor(Qt::white,this,"选择填充颜色");
}

void Graph_Edit::on_Line_Color_clicked()
{
    this->Pen_Color = QColorDialog::getColor(Qt::white,this,"选择线的颜色");
}
