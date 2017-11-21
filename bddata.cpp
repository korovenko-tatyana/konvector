#include "bddata.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QDialog>
#include <QTextStream>
#include <QDebug>

#include <QtSql>
#include <QSqlRecord>
#include <QFile>

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
  //      file_name1="/home/student/qt_project/convec/basa.csv";
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
   // filename="/home/student/qt_project/convec/basa_out.csv"; //delete
    QFile file(filename);
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
//qDebug()<<temp;
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







void BDData::load_from_sql(QString filename, QString table_name){
  //  filename="/home/student/qt_project/convec/basa_sql";
 //   table_name="table1";

    if (!QFile::exists(filename)){qDebug()<<"not a database file"; return;}

    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
       sdb.setDatabaseName(filename);

       if (!sdb.open()) {
           qDebug() << "Ошибка: " + sdb.lastError().text();
           return;
       }

       QSqlRecord columns = sdb.record(table_name);

           if (columns.isEmpty()) {
               qDebug() << "Нет таблицы " + table_name;
               return;
           }

           //clearTable();
           if(cols!=0){ cols=0;rows=0; data1.clear();column_name.clear();type_data.clear();
        }

           int j;
           emit beginInsertColumns(QModelIndex(), 0, columns.count()-1);
               for(j = 0; j < columns.count(); j++)
               column_name.append(columns.fieldName(j));
               emit endInsertColumns();
               qDebug()<<column_name;
               cols=columns.count();

         /*      QSqlQuery rowcount("SELECT count(*) FROM " + table_name);
                  rowcount.first();
                  rowcount.exec("SELECT count(*) FROM " + table_name);
                 qDebug()<<cols<<":cols    rows:"<< rowcount.value(0).toInt();
              rows=rowcount.value(0).toInt();*/

              QList<QString> temp;
                  QSqlQuery query("SELECT * FROM " + table_name);
                  emit beginInsertRows(QModelIndex(), 0, rows-1);
                  while (query.next()) {
                    //  rows << QStringList();
                      for(j = 0; j < cols; j++)
                     //      rows.last() << query.value(j).toString();
                         temp.append(query.value(j).toString());
              //     qDebug()<<temp;
                      data1.append(temp); temp.clear(); rows++;
                  }
                  emit endInsertRows();
                  sdb.close();
                  return ;
}

void BDData::out_to_sql(QString filename, QString table_name){
  //  filename="/home/student/qt_project/convec/basa_sql_out";
   // table_name="table2";

    if (!QFile::exists(filename)){qDebug()<<"not a database file"; return;}

    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
       sdb.setDatabaseName(filename);

       if (!sdb.open()) {
           qDebug() << "Ошибка: " + sdb.lastError().text();
           return;
       }
       QSqlRecord columns = sdb.record(table_name);

           if (columns.isEmpty()) { //create table if not it
              // qDebug() << "Нет таблицы " + table_name;
               QSqlQuery query;
               QString tem1="";
               QString t=", ";
               for(int i=0;i<cols;i++){
                   if(i==cols-1)t="";
                   tem1+="'"+column_name[i]+"' "+type_data[i]+t;}
                   if(!query.exec( "CREATE TABLE '" +table_name+ "' ("+tem1+  " )") )
                   { //error of create
                       qDebug() << "DataBase: error of create " ;
                       qDebug() << query.lastError().text();
                       return;
                   }
           }

           //comparator if table is, her column different or not and her content;

           //zapic data
           QString qq="INSERT INTO '"+table_name+"' VALUES ";
           for(int i=0;i<rows;i++){
               QString tem;
               tem="";
               QList<QString> temp;
                  temp=data1[i];
               for(int j=0; j<cols;j++){

                     if(type_data[j]=="TEXT")
                   tem+="'"+temp[j]+"'";
                    else tem+=temp[j];
                     if(j<cols-1)tem+=", ";
               }
             if(i<rows-1)  qq+="("+tem+"), ";else qq+="("+tem+")";
           }
              QSqlQuery qqq;
           if(!qqq.exec(qq)){ qDebug() << "DataBase: error of input data ";
               qDebug() << qqq.lastError().text();
               }
           sdb.close();

}












