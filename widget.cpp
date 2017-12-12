#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    errorRow = 0;
    correct = true;
    ui->setupUi(this);
}

bool Widget::numbers(QChar c)
{
    if (c <= '9' && c >= '0')
    {
        return true;
    }
    return false;
}

void Widget::fillList(QString str)
{
    QString s="";
    QChar ch;
    int p=0;
     while(p<str.size())
     {
         ch=str[p++];
         while(ch==' ')
         {
            ch=str[p];
            p++;
         }
         if(characters(ch))
            {
                while(characters(ch)||numbers(ch))
                {
                    s+=ch;
                    ch=str[p++];
                }
                p--;
                list<<s;
                s.clear();
         }
         else if(numbers(ch))
             {
                 while(numbers(ch))
                 {
                     s+=ch;
                     ch=str[p++];
                 }
                 p--;
                 list<<s;
                 s.clear();
             }
         else {
             s+=ch;
             list<<s;
             s.clear();
         }
     }
     list<<"_EOF_";
}

bool Widget::characters(QChar c)
{
    if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
    {
        return true;
    }
    return false;
}
Widget::~Widget()
{
    delete ui;
}

void Widget::getErrorRowCount()
{
    errorCount=0;
    for(int i =0;i<errorRow;++i)
    {
        errorCount+=list[i].size();
    }
}




void Widget::pause_E()
{
    if(correct){
    pause_T();
    pause_X();
    }
}

void Widget::pause_X()
{
    if(correct){
    if(list[errorRow] == "+"||list[errorRow] == "-")
    {
        ++errorRow;
        pause_T();
        pause_X();
    }

    //什么都不做是空移

    }
}

void Widget::pause_T()
{
    if(correct){
    pause_F();
    pause_Y();
    }
}

void Widget::pause_Y()
{
    if(correct){
    if(list[errorRow] == "*"||list[errorRow] == "/")
    {
        ++errorRow;
        pause_F();
        pause_Y();
    }
    //什么都不做是空移
    }
}

void Widget::pause_F()
{
    if(correct){
    if(characters(list[errorRow][0])||numbers(list[errorRow][0]))
    {
        ++errorRow;
    }
    else if(list[errorRow]=="(")
    {
        ++errorRow;
        pause_E();
        if(list[errorRow]==")")
        {
            ++errorRow;
        }
        else
        {
            getErrorRowCount();
            output="Syntax error!\nThe location of the error occurred is "+list[errorRow]+"\nthe position is "+QString::number(errorCount,10);
            ui->resultText->append(output);
            correct =false;
        }
    }
    else{
        getErrorRowCount();
        output="Syntax error!\nThe location of the error occurred is "+list[errorRow]+"\nthe position is "+QString::number(errorCount,10);
        ui->resultText->append(output);
        correct =false;
    }
    }
}

void Widget::on_pushButton_clicked()
{
    ui->resultText->clear();
    QString input = ui->inputLine->text();
    fillList(input);
    foreach(QString s,list)
    {
        qDebug()<<s<<endl;
    }

    pause_E();

    if(errorRow<list.size()-1){ //空移导致的字符串未读完错误
        correct = false;
        getErrorRowCount();
        output="Syntax error!\nThe location of the error occurred is "+list[errorRow]+"\nthe position is "+QString::number(errorCount,10);
        ui->resultText->append(output);
      }

    if(correct)
    {
        output="Compile successfully!";
        ui->resultText->append(output);
    }
    list.clear();
    errorRow=0;
    correct =true;
}
