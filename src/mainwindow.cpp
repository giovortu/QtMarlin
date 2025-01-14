
#include "mainwindow.h"



#include <QList>
#include <QDebug>



#include <iostream>

#include <sstream>
#include <fstream>
#include <vector>

#include <QTimer>

#include <QFont>
#include <QPushButton>
#include <QWidget>
#include <QCheckBox>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QThread>
#include <QStatusBar>
#include <QTreeWidget>
#include <QTabWidget>
#include <QComboBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QDir>
#include <QLabel>
#include <QSerialPortInfo>

#include "tab_pid.h"
#include "tab_raw.h"
#include "tab_eeprom.h"
#include "tab_veltest.h"

#ifdef USE_QSERIALDEVICE
  #include <serialdeviceenumerator.h>
#endif

MainWindow::MainWindow(QWidget *parent): QWidget(parent)
{      
  initSerial();


  serialBinBuffer.resize(0);
  wait_reply=false;
  auto *layout = new QVBoxLayout;
  
  auto *comLayout= new QHBoxLayout;
  portSelector=new QComboBox(this);
  baudSelector=new QComboBox(this);
  
  baudSelector->addItem("115200");
  baudSelector->addItem("57600");
  baudSelector->addItem("230400");
  baudSelector->addItem("250000");
  btConnect= new QPushButton("Connect");;
  btDisconnect=new QPushButton("Disconnect",this);
  btRescan= new QPushButton("Rescan",this);
  comLayout->addWidget(portSelector);
  comLayout->addWidget(baudSelector);
  comLayout->addWidget(btConnect);
  comLayout->addWidget(btDisconnect);
  comLayout->addWidget(btRescan);
  layout->addLayout(comLayout);
  tab=new QTabWidget();
  layout->addWidget(tab);
  
  tabPID=new TabPID(tab);
  tabRaw=new TabRaw(tab);
  tabEEPROM=new TabEEPROM(tab);
  tabVeltest=new TabVeltest(this,nullptr);
  
  tab->addTab(tabRaw,"Raw");
  tab->addTab(tabPID,"PID");
  tab->addTab(tabEEPROM,"EEPROM");
  tab->addTab(tabVeltest,"VelTest");
  
  status=new QStatusBar(this);
 
  
  layout->addWidget(status);
  setLayout(layout);
  clickedRefresh();
  
  connect(btConnect, SIGNAL(clicked(bool)), this, SLOT(clickedConnect()));
  connect(btDisconnect, SIGNAL(clicked(bool)), this, SLOT(clickedDisconnect()));
  connect(btRescan, SIGNAL(clicked(bool)), this, SLOT(clickedRefresh()));
  
  //connect(comport, SIGNAL(readyRead()), this, SLOT(slotRead()));
  connect(tabRaw->sendText,SIGNAL(returnPressed()),this, SLOT(manualSend()));
  
  
  connect(tabPID,SIGNAL(pidChanged()),this, SLOT(sendPID()));
  connect(tabPID->pids[0],SIGNAL(returnPressed()),this, SLOT(sendPID()));
  connect(tabPID->pids[1],SIGNAL(returnPressed()),this, SLOT(sendPID()));
  connect(tabPID->pids[2],SIGNAL(returnPressed()),this, SLOT(sendPID()));
  connect(tabPID->pids[3],SIGNAL(returnPressed()),this, SLOT(sendPID()));
  connect(tabPID->btLoad,SIGNAL(clicked()),this, SLOT(getPID()));
  
  connect(tabPID->temp[hotend1],SIGNAL(returnPressed()),this, SLOT(setHotend1Temp()));
  
  connect(this,SIGNAL(newSerialData()),this,SLOT(processReply()));
  timer = new QTimer(this);
  connect(timer,SIGNAL(timeout()),tabVeltest,SLOT(checkDone()));
  pidloaded=false;
  
  
  connect(tabEEPROM->pbRead,SIGNAL(clicked(bool)),this, SLOT(EEPROM_loadClicked()));
  connect(tabEEPROM->pbWrite,SIGNAL(clicked(bool)),this, SLOT(EEPROM_writeClicked()));
  connect(tabEEPROM->pbReset,SIGNAL(clicked(bool)),this, SLOT(EEPROM_resetClicked()));
  connect(tabEEPROM->pbFactorReset,SIGNAL(clicked(bool)),this, SLOT(EEPROM_factorResetClicked()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::initSerial()
{
  #ifdef USE_QEXTSERIALPORT
    comport=nullptr;
  #endif
}

void MainWindow::closeSerial()
{
  
  #ifdef USE_QEXTSERIALPORT
    if ( comport->isOpen() )
    {
        comport->close();
    }
    delete comport;
    comport=nullptr;
  #endif

  #ifdef USE_QSERIALDEVICE
    comport->close();
  #endif
}

void MainWindow::openSerial()
{
  #ifdef USE_QEXTSERIALPORT
    if(comport)
    {
      closeSerial();
    }
  
    comport = new QSerialPort();
    connect(comport, SIGNAL(readyRead()), this, SLOT(slotRead()));

    QString baud=baudSelector->currentText();
    if(baud=="57600")
    {
      comport->setBaudRate(QSerialPort::Baud57600);
    }
    else if(baud=="115200")
    {
      comport->setBaudRate(QSerialPort::Baud115200);
    }
    else
    {
      qWarning() <<"Unsuppored baudrate";
    }

    comport->setPortName( portSelector->currentText() );

    //TODO add parameters to GUI
    comport->setDataBits( QSerialPort::Data8 );
    comport->setParity( QSerialPort::NoParity );
    comport->setStopBits( QSerialPort::OneStop );
    comport->setFlowControl( QSerialPort::NoFlowControl );

    if (!comport->open(QIODevice::ReadWrite) )
    {
      qWarning() <<"failed opening comport : "<<portSelector->currentText();
    }
  #endif

}



void MainWindow::clickedConnect()
{
  openSerial();
 
  tabPID->startTime();
  
  connect(timer, SIGNAL(timeout()), this, SLOT(measure()));
  timer->start(1000);

  serialBuffer="";
}

void MainWindow::clickedDisconnect()
{
  closeSerial();
}

void MainWindow::clickedRefresh()
{
  QStringList portnames;
  #ifdef USE_QEXTSERIALPORT
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    for (int i = 0; i < ports.size(); i++) 
    {
      portnames<<(ports.at(i).portName() );
    }
  #endif
  

  portSelector->clear();

  foreach (QString s, portnames) 
  {
    portSelector->addItem(s);
  }
}

void MainWindow::getdata(const QString &line,const QString &after, const QString &key,float &target)
{
   int n=line.indexOf(after);
   if(n==-1)
   {
       return;
   }

  QString t=line.mid(n,line.size());
  int m=t.indexOf(key)+key.size();

  if(m==-1)
  {
    return;
  }

  float f;
  QString end=t.mid(m, t.size()).split(" ")[0];
  f=end.toFloat();
  target=f;

}

void MainWindow::getdata(const QString &line,const QString &after, const QString &key,QLineEdit *target)
{
   int n=line.indexOf(after);

   if(n==-1)
   {
       return;
   }

  QString t=line.mid(n,line.size());
  int m=t.indexOf(key)+key.size();
  if(m==-1)
  {
    return;
  }

  QString end=t.mid(m, t.size()).split(" ")[0];

  target->setText(end);
  tabEEPROM->EEPROM_recalculate();
}


void MainWindow::slotRead() 
{
  QByteArray ba = comport->readAll();
  serialBinBuffer.append(ba);
  int lastnewlinepos=serialBinBuffer.lastIndexOf('\n');
 // qDebug()<<"newline@"<<lastnewlinepos;
  if(lastnewlinepos<0) 
  {
    return; //no newline read yet.
  }

  QString readlines=QString(serialBinBuffer.mid(0,lastnewlinepos).append((char)0));
  readSinceLastSend.append(readlines);
  QStringList lines=readlines.split("\n",QString::SkipEmptyParts);
  serialBinBuffer.remove(0,lastnewlinepos);
  
  tabRaw->displayText(readlines);
  
  foreach(QString s, lines) //s =  linecontent
  {
   if(s.contains("endstop"))
   {
     endstopfound=true;
   }
   if(s.startsWith("ok") ||s.startsWith("T"))
   {
     QStringList junks(s.remove(0,3).split(" ",QString::SkipEmptyParts));
     foreach(QString j, junks)
     {
       QStringList ll=j.split(":",QString::SkipEmptyParts);
       if(ll.size()==2)
       {
         bool ok=false;
         float f=ll[1].toDouble(&ok);
         if(ok)
         {
            variables[ll[0]]=f ;
         }
        if(ll[0]=="p")
        {
         tabPID->pids[0]->setText(ll[1]); 
         tabEEPROM->lEPIDp->setText(ll[1]);
        }

        if(ll[0]=="i")
        {
         tabPID->pids[1]->setText(ll[1]); 
         tabEEPROM->lEPIDi->setText(ll[1]);
        }

        if(ll[0]=="d")
        {
         tabPID->pids[2]->setText(ll[1]); 
         tabEEPROM->lEPIDd->setText(ll[1]);
        }

        if(ll[0]=="c")
        {
         tabPID->pids[3]->setText(ll[1]); 
        }
        
       }
     }
     tabPID->addData(variables["T"],variables["B"],0,variables["@"]);
     
   }
   else if(s.startsWith("echo:"))
   {
 
      getdata(s,"M92","X",tabEEPROM->lEstepsperunit[0]);
      getdata(s,"M92","Y",tabEEPROM->lEstepsperunit[1]);
      getdata(s,"M92","Z",tabEEPROM->lEstepsperunit[2]);
      getdata(s,"M92","E",tabEEPROM->lEstepsperunit[3]);
      
      getdata(s,"M203","X",tabEEPROM->lEvmax[0]);
      getdata(s,"M203","Y",tabEEPROM->lEvmax[1]);
      getdata(s,"M203","Z",tabEEPROM->lEvmax[2]);
      getdata(s,"M203","E",tabEEPROM->lEvmax[3]);
      
      getdata(s,"M201","X",tabEEPROM->lEamax[0]);
      getdata(s,"M201","Y",tabEEPROM->lEamax[1]);
      getdata(s,"M201","Z",tabEEPROM->lEamax[2]);
      getdata(s,"M201","E",tabEEPROM->lEamax[3]);
      
      getdata(s,"M204","S",tabEEPROM->lEacceleration);
      getdata(s,"M204","T",tabEEPROM->lEaccelerationRetract);
      
      getdata(s,"M205","S",tabEEPROM->lEvmin);
      getdata(s,"M205","T",tabEEPROM->lEvmin_travel);
      getdata(s,"M205","B",tabEEPROM->lEtmin_segment);
      getdata(s,"M205","X",tabEEPROM->lEvxyjerk);
      getdata(s,"M205","Z",tabEEPROM->lEvzjerk);
      
      getdata(s,"M301","P",tabEEPROM->lEPIDp);
      getdata(s,"M301","I",tabEEPROM->lEPIDi);
      getdata(s,"M301","D",tabEEPROM->lEPIDd);
      
      //qDebug()<<f<<endl;
     /*
      * float stepsperunit[4];
  float vmax[4];
  float amax[4];
  float acceleration, accelerationRetract;
  float vxyjerk,vzjerk;
  float vmin,vmin_travel;
  float tmin_segment;*/
   }
   
  }
  emit newSerialData();
}

void MainWindow::manualSend()
{
  send(tabRaw->sendText->text()+"\n");
}


void MainWindow::send(QString text)
{
  tabRaw->displayTextHtml(QString("<br><b><font color=red>Sending:%0</font></b><br>").arg(text));

  if(!comport->isOpen())
  {
    return;
  }

  QString text2=text.append("\n");
  QByteArray ba=text2.toLocal8Bit(); //data to send
  qint64 bw = 0; //bytes really writed

  bw = comport->write(ba);

}

void MainWindow::sendGcode(const QString &text)
{
  sendcodes<<text;
  if(wait_reply)
  {
    return;
  }
  
  send(sendcodes[0]);
  readSinceLastSend="";
  wait_reply=true;
}

void MainWindow::processReply()
{
  if(sendcodes.empty())
  {
    return;
  }
  
  QStringList lines = readSinceLastSend.split("\n",QString::SkipEmptyParts);
  //qDebug()<<"got reply for command "<<sendcodes[0];
  
  QString overhang="";
  foreach(QString s,lines)
  {
    if(overhang.size())
    {
      overhang.append(s);
    }
    else
    {
      overhang=s;
    }
    
    if(overhang.startsWith("ok"))
    {
      if(!sendcodes.empty())
      {
        sendcodes.removeFirst();
        if(!sendcodes.empty())
        {
          readSinceLastSend="";
          send(sendcodes[0]);
        }
        else
        {
            wait_reply=false;
        }
      }
      
    }
    else
    {
    }

    if(s.size()<2)
    {
      overhang=s;
    }
    else
    {
      overhang="";
    }
  }
  
}

void MainWindow::measure()
{
  if(!pidloaded)
  {
     getPID();
     pidloaded=true;
  }
  else
  if(tabPID->monitor->isChecked())
  {
    sendGcode("M105");
  }
  
}

void MainWindow::setHotend1Temp()
{
  sendGcode(QString("M104 S%1").arg(tabPID->temp[hotend1]->text()));
}

void MainWindow::sendPID()
{
  sendGcode(QString("M301 P%1 I%2 D%3 C%4").arg(tabPID->pids[0]->text()).arg(tabPID->pids[1]->text()).arg(tabPID->pids[2]->text()).arg(tabPID->pids[3]->text()));
}

void MainWindow::getPID()
{
  sendGcode(QString("M301"));
}


void MainWindow::EEPROM_loadClicked()
{
  sendGcode(QString("M503"));
}



void MainWindow::EEPROM_resetClicked()
{
  sendGcode("M501");
  EEPROM_loadClicked();
}


void MainWindow::EEPROM_factorResetClicked()
{
  sendGcode("M502");
  EEPROM_loadClicked();
}

void MainWindow::EEPROM_storeClicked()
{

}

void MainWindow::EEPROM_writeClicked()
{
/*
 * :  M92 X79.87 Y79.87 Z533.00 E953.00
echo:Maximum feedrates (mm/s):
echo:  M203 X200.00 Y200.00 Z19.00 E932.00
echo:Maximum Acceleration (mm/s2):
echo:  M201 X10300 Y10500 Z500 E4700
echo:Acceleration: S=acceleration, T=retract acceleration
echo:  M204 S4700.00 T7000.00
echo:Advanced variables: S=Min feedrate (mm/s), T=Min travel feedrate (mm/s), B=minimum segment time (ms), X=maximum xY jerk (mm/s),  Z=maximum Z jerk (mm/s)
echo:  M205 S0.00 T174.00 B20000 X36.00 Z600.00
echo:PID settings:
echo:   M301 P24.00 I1.02 D141.00
*/
  sendGcode(QString("M92 X%1 Y%2 Z%3 E%4").arg(tabEEPROM->lEstepsperunit[0]->text()).arg(tabEEPROM->lEstepsperunit[1]->text()).arg(tabEEPROM->lEstepsperunit[2]->text()).arg(tabEEPROM->lEstepsperunit[3]->text()) );
  sendGcode(QString("M203 X%1 Y%2 Z%3 E%4").arg(tabEEPROM->lEvmax[0]->text()).arg(tabEEPROM->lEvmax[1]->text()).arg(tabEEPROM->lEvmax[2]->text()).arg(tabEEPROM->lEvmax[3]->text()) );
  sendGcode(QString("M201 X%1 Y%2 Z%3 E%4").arg(tabEEPROM->lEamax[0]->text()).arg(tabEEPROM->lEamax[1]->text()).arg(tabEEPROM->lEamax[2]->text()).arg(tabEEPROM->lEamax[3]->text()) );
  sendGcode(QString("M204 S%1 T%2").arg(tabEEPROM->lEacceleration->text()).arg(tabEEPROM->lEaccelerationRetract->text()));
  sendGcode(QString("M301 P%1 I%2 D%3").arg(tabEEPROM->lEPIDp->text()).arg(tabEEPROM->lEPIDi->text()).arg(tabEEPROM->lEPIDd->text()));
}
