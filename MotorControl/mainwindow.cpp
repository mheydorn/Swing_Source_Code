#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qextserialport/src/qextserialport.h"
#include "string.h"
#include <QThread>
#include <QFileDialog>
#include <QTextStream>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QTextStream>

char PortNumber = '0';
int spinBox1 = 0;
int spinBox2 = 0;
int spinBox4 = 0;
bool Motor1 = true;
bool Motor2 = false;
char Direction1 = 'f';
char Direction2 = 'f';
QString CommandSet = "";
bool recording = false;
QextSerialPort * port  = NULL;
QString fileNames;
QString savePath;
class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{



    int p = 0;

    //Find out which USB Port we're on
    bool b = false;
    while(!b && p < 20){
        PortNumber = (char)(p + 48);

    std::string str = "";
    QString qstr = QString::fromStdString(str);

    QString device = "/dev/ttyUSB";
    device.append(PortNumber);
   port = new QextSerialPort(device.toUtf8());

    port->setBaudRate(BAUD57600);
    port->setFlowControl(FLOW_OFF);
    //port->setFlowControl(FLOW_HARDWARE);
   // port->setFlowControl(FLOW_XONXOFF);

    port->setParity(PAR_EVEN);
   // port->setParity(PAR_SPACE);

    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);
    //port->setTimeout(0);
    port->setTimeout(100);

    bool res = false;
    res = port->open(QIODevice::ReadWrite | QIODevice::Unbuffered);


    if(res)
    {
        b = true;
        qDebug("Found port");
      //  ui->textBrowser_2->setText("USB device found on port " + p);

    }
    else
    {
        p++;
        qDebug("Trying another port");
      //  ui->textBrowser_2->setText("USB Device Port Not Found!");

       }
    }





    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //button for motor 1


       QChar MotorId = 'a';

       QString spinBox1String = QString::number(spinBox1);       

       QString speedString = QString::number(spinBox4);

       QString Command = speedString;
       Command.prepend(':');
       for(int i = 0; i < spinBox1String.length(); i++){
           Command.prepend(spinBox1String.at(spinBox1String.length() - 1 - i));
       }

       Command.prepend(Direction1);


       Command.prepend(MotorId);

       if(recording){
           CommandSet.append(Command);
           QString newLine = "\n";
           CommandSet.append(newLine);
           ui->textBrowser->setText(CommandSet);
        }


       char data[Command.length()] = {};
        for(int i = 0; i < Command.length(); i++){

            data[i] = Command.at(i).toLatin1();
        }
        qDebug(Command.toLatin1());

        port->write(data, sizeof(data));





}

void MainWindow::on_spinBox_editingFinished()
{

}

void MainWindow::on_spinBox_valueChanged(const QString &arg1)
{

}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    spinBox1 = arg1;
}


void MainWindow::on_radioButton_toggled(bool checked)
{
    if(checked){
        Direction1 = 'r';
    }
}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    if(checked){
    Direction1 = 'f';
    }
}

void MainWindow::on_radioButton_clicked(bool checked)
{

}

void MainWindow::on_radioButton_2_clicked(bool checked)
{

}

void MainWindow::on_radioButton_3_toggled(bool checked)
{
    if(checked){
        Direction2 = 'f';
    }
}

void MainWindow::on_radioButton_4_toggled(bool checked)
{
    if(checked){
        Direction2 = 'r';
    }
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    spinBox2 = arg1;
}

void MainWindow::on_pushButton_2_clicked()
{


       QChar MotorId = 'b';

       QString spinBox1String = QString::number(spinBox2);
       QString speedString = QString::number(spinBox4);


       QString Command = speedString;
       Command.prepend(':');
       for(int i = 0; i < spinBox1String.length(); i++){
           Command.prepend(spinBox1String.at(spinBox1String.length() - 1 - i));
       }

       Command.prepend(Direction2);

       Command.prepend(MotorId);

       if(recording){
           CommandSet.append(Command);
           QString newLine = "\n";
           CommandSet.append(newLine);
           ui->textBrowser->setText(CommandSet);
        }

       char data[Command.length()] = {};
        for(int i = 0; i < Command.length(); i++){
            data[i] = Command.at(i).toLatin1();
        }
        qDebug(Command.toLatin1());
        port->write(data, sizeof(data));

}

void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    PortNumber = (char)(arg1 + 48);
    port->close();

    std::string str = "";
    QString qstr = QString::fromStdString(str);

    QString device = "/dev/ttyUSB";
    device.append(PortNumber);
   port = new QextSerialPort(device.toUtf8());

    port->setBaudRate(BAUD9600);
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_ODD);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_2);
    port->setTimeout(0);
    bool res = false;
    res = port->open(QIODevice::ReadWrite | QIODevice::Unbuffered);


    if(res)
    {

        qDebug("Connection created");



    }
    else{

        qDebug("Failed to connect");
       }
    }


void MainWindow::on_pushButton_3_clicked()
{

    //the clear Button

       CommandSet = "";
       ui->textBrowser->setText(CommandSet);



}

void MainWindow::on_checkBox_clicked(bool checked)
{
    recording = checked;
}

void MainWindow::on_pushButton_4_clicked()
{
    //the Play Button
    //create an array of commands
    //split command every 50 chars to make mltiple commandsets
    QVector<QString> CommandVector;
    for(int i = 0; i < CommandSet.length(); i++){

    }

    char data[CommandSet.length()] = {};
     for(int i = 0; i < CommandSet.length(); i++){

         data[i] = CommandSet.at(i).toLatin1();
     }
     qDebug(CommandSet.toLatin1());

     port->write(data, sizeof(data));





}

//Backup for play button
/*
 *
 * void MainWindow::on_pushButton_4_clicked()
{
    //the Play Button
    //create an array of commands
   QVector<QString> commands;

   QString currentCommand = "";


   for(int i = 0; i < CommandSet.length(); i++){
       if(CommandSet.at(i) == '\n'){
           commands.append(currentCommand);
           currentCommand = "";
       }else{
           currentCommand.append(CommandSet.at(i));
       }
   }
   for(int i = 0; i < commands.length(); i++){
       QString CommandTemp = commands.at(i);

        char data[CommandTemp.length()] = {};
         for(int i = 0; i < CommandTemp.length(); i++){

             data[i] = CommandTemp.at(i).toLatin1();
         }
         qDebug(CommandTemp.toLatin1());

         port->write(data, sizeof(data));
         Sleeper::sleep(3);

   }



}

*/

void MainWindow::on_pushButton_5_clicked()
{
    //Save a copy button
    savePath = QFileDialog::getSaveFileName(this, tr("Save a Copy"),"/path/to/file/",tr(""));


    /* Try and open a file for output */
    QString outputFilename = savePath;
    QFile outputFile(outputFilename);
    outputFile.open(QIODevice::WriteOnly);

    /* Check it opened OK */
    if(!outputFile.isOpen()){
        ui->textBrowser_2->clear();
        ui->textBrowser_2->setText("Could not Save to file");
        return;
    }

    /* Point a QTextStream object at the file */
    QTextStream outStream(&outputFile);

    /* Write the line to the file */
    outStream << CommandSet;

    /* Close the file */
    outputFile.close();
    ui->textBrowser_2->setText("Saved to " + savePath);


}

void MainWindow::on_pushButton_6_clicked()
{
    //The Load Button
    fileNames = QFileDialog::getOpenFileName(this, tr("Open File"),"/path/to/file/",tr(""));
    //fileNames = QFileDialog::getSaveFileName(this, tr("Save as"),"/path/to/file/",tr(""));

    ui->listWidget->clear();
    ui->listWidget->addItem(fileNames);

    QFile f1(fileNames);

    f1.open(QIODevice::ReadOnly | QIODevice::Text);

    QString s;

    QTextStream s1(&f1);

    while (!s1.atEnd()){
        s.append(s1.readLine());
        s.append('\n');
       // if (i != 2)s.append("\n");
    }
    qDebug(s.toLatin1());
    CommandSet = s;
    ui->textBrowser->setText(CommandSet);
}

void MainWindow::on_pushButton_7_clicked()
{
    //Save As button
    savePath = QFileDialog::getSaveFileName(this, tr("Save as"),"/path/to/file/",tr(""));
    fileNames = savePath;
    ui->listWidget->clear();
    ui->listWidget->addItem(fileNames);

    /* Try and open a file for output */
    QString outputFilename = savePath;
    QFile outputFile(outputFilename);
    outputFile.open(QIODevice::WriteOnly);

    /* Check it opened OK */
    if(!outputFile.isOpen()){
        ui->textBrowser_2->clear();
        ui->textBrowser_2->setText("Could not Save to file");
        return;
    }

    /* Point a QTextStream object at the file */
    QTextStream outStream(&outputFile);

    /* Write the line to the file */
    outStream << CommandSet;

    /* Close the file */
    outputFile.close();
    ui->textBrowser_2->setText("Saved to " + savePath);


}

void MainWindow::on_pushButton_8_clicked()
{
    //Save button
    savePath = fileNames;


    /* Try and open a file for output */
    QString outputFilename = savePath;
    QFile outputFile(outputFilename);
    outputFile.open(QIODevice::WriteOnly);

    /* Check it opened OK */
    if(!outputFile.isOpen()){
        ui->textBrowser_2->clear();
        ui->textBrowser_2->setText("Could not Save to file");
        return;
    }

    /* Point a QTextStream object at the file */
    QTextStream outStream(&outputFile);

    /* Write the line to the file */
    outStream << CommandSet;

    /* Close the file */
    outputFile.close();
    ui->textBrowser_2->setText("Saved to " + savePath);

}

void MainWindow::on_spinBox_2_editingFinished()
{

}

void MainWindow::on_spinBox_4_valueChanged(int arg1)
{
    spinBox4 = arg1;
}
