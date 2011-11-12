#include "tab_pid.h"

#include <QPushButton>
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
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>

TabPID::TabPID(QWidget* parent): QWidget(parent)
{
  QVBoxLayout *layout = new QVBoxLayout;
 
  
  tempPlot = new QwtPlot( this);
  //myPlot->setAxisTitle(QwtPlot::xBottom,"");
  tempPlot->setAxisTitle(QwtPlot::yLeft,"Celsius");
  heaterPlot= new QwtPlot(this);
  heaterPlot->setAxisTitle(QwtPlot::yLeft,"Heating Powert");
  QwtPlotGrid *myGrid=new QwtPlotGrid();
  myGrid->attach(tempPlot);
  QwtPlotGrid *myhGrid=new QwtPlotGrid();
  myhGrid->attach(heaterPlot);
  tempPlot->insertLegend(new QwtLegend());
  heaterPlot->insertLegend(new QwtLegend());
  double x[2]={0,0};
  double y[2]={0,0};
  
  curve[hotend1] = new QwtPlotCurve("Hotend 1");
  curve[bed] = new QwtPlotCurve("Bed");
  curve[hotend2] = new QwtPlotCurve("Hotend 2");
  curve[heater] = new QwtPlotCurve("Heater");
  for(int i=0;i<4;i++)
  {
    curve[i]->setData(x,y,2);
    curve[i]->setPen(QPen(QColor::fromHsv((255*i)/10,255,255),2));

  }
  curve[0]->attach(tempPlot);
  curve[1]->attach(tempPlot);
  curve[2]->attach(tempPlot);
  curve[3]->attach(heaterPlot);
  tempPlot->replot();
  heaterPlot->replot();

  
  
  
  layout->addWidget(tempPlot);
  layout->addWidget(heaterPlot);
  QHBoxLayout *h1layout = new QHBoxLayout;
  
  QGroupBox *gb1=new QGroupBox("Temperature:");
  QGroupBox *gb2=new QGroupBox("PID values:");
  QGroupBox *gb3=new QGroupBox("Ziegler-Nichols:");
  
  QGridLayout *gb1g=new QGridLayout;
  gb1g->addWidget(new QLabel("Hotend 1:"),0,0);
  gb1g->addWidget(temp[0]=new QLineEdit("0"),0,1);
  gb1g->addWidget(new QLabel("Bed:"),1,0);
  gb1g->addWidget(temp[1]=new QLineEdit("0"),1,1);
  gb1g->addWidget(new QLabel("Hotend 2:"),2,0);
  gb1g->addWidget(temp[2]=new QLineEdit("0"),2,1);
  gb1->setLayout(gb1g);
  temp[0]->setMaxLength(3);
  temp[1]->setMaxLength(3);
  temp[2]->setMaxLength(3);
  
  QGridLayout *gb2g=new QGridLayout;
  gb2g->addWidget(new QLabel("Proportional:"),0,0);
  gb2g->addWidget(pids[0]=new QLineEdit("0"),0,1);
  gb2g->addWidget(new QLabel("Integral:"),1,0);
  gb2g->addWidget(pids[1]=new QLineEdit("0"),1,1);
  gb2g->addWidget(new QLabel("Differential:"),2,0);
  gb2g->addWidget(pids[2]=new QLineEdit("0"),2,1);
  gb2g->addWidget(new QLabel("Extruder speed prop:"),3,0);
  gb2g->addWidget(pids[3]=new QLineEdit("0"),3,1);
  gb2->setLayout(gb2g);
//   pids[0]->setMaxLength(3);
//   pids[1]->setMaxLength(3);
//   pids[2]->setMaxLength(3);
//   pids[3]->setMaxLength(3);
  
  
  h1layout->addWidget(gb1);
  h1layout->addWidget(gb2);
  h1layout->addWidget(gb3);
  layout->addLayout(h1layout);
  
  QHBoxLayout *h2layout = new QHBoxLayout;
  differential=new QCheckBox("differential",this);
  h2layout->addWidget(differential);
  btClear=new QPushButton("Clear");
  h2layout->addWidget(btClear);
  h2layout->addWidget(new QLabel("Period:"));
  h2layout->addWidget(lPeriod=new QLabel("0"));
  h2layout->addWidget(new QLabel(" sec"));
  layout->addLayout(h2layout);
  setLayout(layout);
  
  

  
}


void TabPID::addData(float t1, float b, float t2, float h)
{
  QTime now=QTime::currentTime();
  float dt=starttime.msecsTo(now);
  time.push_back(dt);
  value_hotend1.push_back(t1);
  value_bed.push_back(b);
  value_hotend2.push_back(t2);
  value_heater.push_back(h/255.);
  
  target_hotend1.push_back(temp[hotend1]->text().toDouble());
  target_hotend2.push_back(temp[hotend2]->text().toDouble());
  target_bed.push_back(temp[bed]->text().toDouble());
  
  if(differential->checkState())
  {
    QVector<double> d[3];
    
    d[0].resize(value_hotend1.size());
    d[1].resize(value_hotend1.size());
    d[2].resize(value_hotend1.size());
    for(int i=0;i<value_hotend1.size();i++)
    {
      d[0][i]=value_hotend1[i]-target_hotend1[i];
      d[1][i]=value_bed[i]-target_bed[i];
      d[2][i]=value_hotend2[i]-target_hotend2[i];
    }
    curve[hotend1]->setData(time,d[0]);
    curve[hotend2]->setData(time,d[2]);
    curve[bed]->setData(time,d[1]);
  }
  else
  {
    curve[hotend1]->setData(time,value_hotend1);
    curve[hotend2]->setData(time,value_hotend2);
    curve[bed]->setData(time,value_bed);
  }
  curve[heater]->setData(time,value_heater);
  tempPlot->replot();
  heaterPlot->replot();
  calculatePeriodicity();
}

void TabPID::calculatePeriodicity()
{
  if(value_hotend1.size()<5)
    return;
  float t=value_hotend1.last();
  int previouslast=value_hotend1.size()-1;
  bool firsteventfound=false;
  for(int i=value_hotend1.size()-2;i>0;i--)
  {
    if( ((value_hotend1[i]>=t)&&(value_hotend1[i-1]<t))   || ((value_hotend1[i]<=t)&&(value_hotend1[i-1]>t))  )
    {
     if(previouslast-i>5)
     {
       if(firsteventfound)
       {
         lPeriod->setText(QString("%1").arg(value_hotend1.size()-i));
         return;
       }
       else
       {
        firsteventfound=true;
        previouslast=i;
       }
      
     }
     else //in proximity
     {
       previouslast=i;
       
     }
    }
  }
}

void TabPID::startTime()
{
  starttime= QTime::currentTime();
}

