#ifndef PRINTERCHOOSERWIDGET_H
#define PRINTERCHOOSERWIDGET_H

#include <QWidget>

namespace Ui {
class PrinterChooserWidget;
}

class PrinterChooserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrinterChooserWidget(QWidget *parent = nullptr);
    ~PrinterChooserWidget();

private:
    Ui::PrinterChooserWidget *ui;
};

#endif // PRINTERCHOOSERWIDGET_H
