#include "Pen_Style.h"
#include "ui_Pen_Style.h"

Pen_Style::Pen_Style(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pen_Style)
{
    ui->setupUi(this);
    this->Fill_Color = Qt::white;
}

Pen_Style::~Pen_Style()
{
    delete ui;
}


void Pen_Style::on_horizontalSlider_valueChanged(int value)
{
    this->Pen_Width = value;
    ui->Line_Width->setText(QString::number(value));
}


void Pen_Style::on_Fill_Color_clicked()
{
    this->Fill_Color = QColorDialog::getColor(Qt::white,this,"请选择填充颜色");

}



void Pen_Style::on_Line_Color_clicked()
{
    this->Pen_Color = QColorDialog::getColor(Qt::white,this,"请选择线的颜色");
}

void Pen_Style::on_comboBox_activated(const QString &arg1)
{
    if(arg1 == "—"){
        this->Pen_Styles = Qt::SolidLine;
    }
    else if(arg1 == "-----------"){
        this->Pen_Styles = Qt::DashLine;
    }
    else if(arg1 == "················"){
        this->Pen_Styles = Qt::DotLine;
    }
    else if(arg1 == "-·-·-·-·-·-·-"){
        this->Pen_Styles = Qt::DashDotLine;
    }
    else if(arg1 == "-··-··-··-··-··"){
        this->Pen_Styles = Qt::DashDotDotLine;
    }
}
