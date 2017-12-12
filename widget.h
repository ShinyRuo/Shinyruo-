#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextStream>
#include <QStringList>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    bool numbers(QChar c);
    void fillList(QString str);
    bool characters(QChar c);
    ~Widget();
    void getErrorRowCount();
    void pause_E();           //E->TX;
    void pause_X();           //X->+TX | e
    void pause_T();           //T->FY
    void pause_Y();           //Y->*FY | e
    void pause_F();           //F->(E) | i

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    int errorRow;
    QStringList list;
    bool correct ;
    QString output;
    int errorCount;
};

#endif // WIDGET_H
