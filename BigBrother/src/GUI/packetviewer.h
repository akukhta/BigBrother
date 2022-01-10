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
    void printPacket(std::string const &data);
    ~PacketViewer();

private:
    Ui::PacketViewer *ui;
    static QString intToHex(int num, short countOfZeroes = 1);
};

#endif // PACKETVIEWER_H
