#include "bddata.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QDialog>
#include <QTextStream>
#include <QDebug>

/*BDData::BDData()
{

}*/
BDData::BDData(QObject *parent): QAbstractTableModel(parent)
{

}
QVariant BDData::data(const QModelIndex &index, int role) const
{
   // return QVariant();
}

int BDData::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return rows;
  /*  if (parent.isValid()) return 0;
    return 1;//data1.count();*/

}

int BDData::columnCount(const QModelIndex &parent) const
{
    return cols;
  //  return 2;//column_name.count();
}
QVariant BDData::headerData(int section, Qt::Orientation orientation, int role) const //???
{
 /*   if (role == Qt::DisplayRole){
        if (orientation == Qt::Horizontal) {
            for(int i=0;i<column_name.count();i++)
            if (section == i) return column_name[i];  // "Time";
           // else return "Difference";
        }
    }*/
  //  return  QAbstractTableModel::headerData(section, orientation, role);
}

void BDData::load_from_csv(QString file_name1){
    if(cols!=0){ cols=0;rows=0; data1.clear();column_name.clear();type_data.clear();
 }
    {
        file_name1="/home/student/qt_project/convec/basa.csv";
    QFile file(file_name1);

       if (!file.open(QIODevice::ReadOnly))
       {
         //  QMessageBox::critical(,tr("Error"),tr("Could not open file"));
           qDebug()<<"error from open file"<<endl;;
           return;
       }
       QTextStream in(&file);
      QString col_name= in.readLine();

      for (QString item : col_name.split(";")) {
                      column_name.append(item);

                      cols++;
                  //    qDebug()<<item<<cols;
      }
      while (!in.atEnd())
            {
                // ... построчно
                QString line = in.readLine();
                // Добавляем в модель по строке с элементами
              //  QList<QStandardItem *> standardItemsList;
                QList<QString> temp;
               // int k=-1;
                // учитываем, что строка разделяется точкой с запятой на колонки
                for (QString item : line.split(";")) {
                    //if(k==cols+1)k=0; else k++;
                //    data1[1][k].append(item);
                    temp.append(item);
                //            qDebug()<<item;
                }
                data1.append(temp); temp.clear();
                qDebug()<<data1[rows];
               // csvModel->insertRow(csvModel->rowCount(), standardItemsList);
          rows++;
      }
                  // for(int i=0;i<5;i++)   qDebug()<<column_name[i];

        //   qDebug()<<rows;
       file.close();
    }
   // else qDebug()<<"also data is in prog";
}

void BDData::output_in_csv(QString filename){
    if(cols==0){qDebug()<<"No data in prog";}
   /* QString name="";
    for (int i=0;i<cols;i++)
    name+=column_name[i];*/
    filename="/home/student/qt_project/convec/basa_out.csv"; //delete
    QFile file(filename); //заменить на filename
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream text_stream(&file);
        QStringList str;
        for(int k=0;k<cols;k++){
            str<<column_name[k];
        }
        text_stream<<str.join(';')+"\n";
        for (int i=0;i<rows;i++)
        {
            str.clear();
            for (int j =0;j<cols;j++){
                QList<QString> temp;
            temp=data1[i];
                str<<temp[j];

            }
            text_stream<<str.join(';')+"\n";
        }

        file.close();
    }
    else qDebug()<<"error open file to write";
}

void BDData::opred_data_type() //INTEGER -> REAL -> TEXT
{
QList <QString>temp,d;bool qw[cols];
for (int i=0;i<cols;i++){
    temp.append("TEXT");
    type_data.append("INTEGER");
    qw[i]=false;
}
for (int i=0;i<rows;i++)
    for(int j=0;j<cols;j++)
    {
        d.clear();
        d=data1[i];
        bool flag;
        d[j].toInt(&flag);
        if(flag) temp[j]="INTEGER";
        else {d[j].toDouble(&flag);
            if(flag) {temp[j]="REAL";qw[j]=true;}
            else {temp[j]="TEXT"; type_data[j]="TEXT";}
    }
for(int i=0;i<cols;i++)
{
    if(qw[i] &&(type_data[i]!="TEXT")) type_data[i]="REAL";
   // else if(type_data[i]!="TEXT") type_data[i]="INTEGER";
}
}
qDebug()<<temp;
qDebug()<<type_data;
}

QList<QString> BDData::get_column_name(){
    return column_name;
}

QList<QList<QString>> BDData::get_data(){
    return data1;
}

int BDData::get_row(){
    return rows;
}

int BDData::get_col(){
    return cols;
}
