#ifndef PEN_STYLE_H
#define PEN_STYLE_H

#include <QWidget>
#include <QPen>
#include <QColorDialog>

namespace Ui {
class Pen_Style;
}

class Pen_Style : public QWidget
{
    Q_OBJECT

public:
    explicit Pen_Style(QWidget *parent = nullptr);
    ~Pen_Style();
    QColor Pen_Color = Qt::black;
    QColor Fill_Color = Qt::white;
    int Pen_Width = 1;
    Qt::PenStyle Pen_Styles = Qt::SolidLine;

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_Fill_Color_clicked();

    void on_Line_Color_clicked();

    void on_comboBox_activated(const QString &arg1);

private:
    Ui::Pen_Style *ui;
};

#endif // PEN_STYLE_H
