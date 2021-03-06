#ifndef PACKETVIEWER_H
#define PACKETVIEWER_H

#include <QDialog>
#include <sstream>
#include <math.h>

namespace Ui {
class PacketViewer;
}

class PacketViewer : public QDialog
{
    Q_OBJECT

public:
    explicit PacketViewer(QWidget *parent = nullptr);
    void printPacket(std::string const &packet, std::vector<unsigned char> const &data);
    ~PacketViewer();

private:
    Ui::PacketViewer *ui;
    static QString intToHex(int num, short countOfZeroes = 1);\
    QStringList vLabels;
};

#endif // PACKETVIEWER_H
