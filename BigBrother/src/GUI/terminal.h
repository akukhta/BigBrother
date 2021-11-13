#ifndef TERMINAL_H
#define TERMINAL_H

#include <QWidget>
#include <chrono>
#include <QTime>
#include <fstream>

namespace Ui {
class Terminal;
}

class Terminal : public QWidget
{
    Q_OBJECT

public:
    explicit Terminal(QWidget *parent = nullptr);
    void printMessage(std::string const &str);
    void printMessage(unsigned char *str, size_t size);
    ~Terminal();

private:
    Ui::Terminal *ui;
    static QString getTime();
    std::ofstream out;
};

#endif // TERMINAL_H
