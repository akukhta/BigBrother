#ifndef PACKETVIEWER_H
#define PACKETVIEWER_H

#include <QDialog>

namespace Ui {
class PacketViewer;
}

class PacketViewer : public QDialog
{
    Q_OBJECT

public:
    explicit PacketViewer(QWidget *parent = nullptr);
    ~PacketViewer();

private:
    Ui::PacketViewer *ui;
};

#endif // PACKETVIEWER_H
