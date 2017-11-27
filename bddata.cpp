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
 /*   // return QVariant();
    if (!index.isValid()) return QVariant();
    if (role == Qt::DisplayRole) return data1.at(index).at(row);
    else return QVariant();*/

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
    if (parent.isValid()) return 0;
    return cols;
    //  return 2;//column_name.count();
}
/*QVariant BDData::headerData(int section, Qt::Orientation orientation, int role) const //???
{
   if (role == Qt::DisplayRole){
        if (orientation == Qt::Horizontal) {
            for(int i=0;i<column_name.count();i++)
            if (section == i) return column_name[i];  // "Time";
           // else return "Difference";
        }
    }
  //  return  QAbstractTableModel::headerData(section, orientation, role);
}*/

QVariant BDData::headerData(int section, Qt::Orientation orientation, int role) const
{ if (role == Qt::DisplayRole)
    { if (orientation == Qt::Horizontal)
        { return column_name[section];
            //
            //  else return "Difference";
        } }
    return QAbstractTableModel::headerData(section, orientation, role);
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
        int cc=col_name.count(";")+1;
        emit beginInsertColumns(QModelIndex(), 0, cc-1);
        for (QString item : col_name.split(";")) {
            column_name.append(item);

            cols++;
            //    qDebug()<<item<<cols;
        }
        emit endInsertColumns();
        QTextStream stream(&file);
        // количество строк.
      int rr=0;
        QString line;
         do
        {
             line = stream.readLine();
             // увеличим счетчик строк
             if(!line.isNull()) { rr++;}
         } while (!line.isNull());
    ;
        emit beginInsertRows(QModelIndex(), 0, rr-2);
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
         emit endInsertRows();
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
   /* for (int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
        {
            d.clear();
            d=data1[i];
            bool flag;
            d[j].toInt(&flag);
            if(flag) temp[j]="INTEGER";
            else {
                d[j].toDouble(&flag);
                if(flag) {temp[j]="REAL";qw[j]=true;}
                else {temp[j]="TEXT"; type_data[j]="TEXT";}
            }
            for(int i=0;i<cols;i++)
            {
                if(qw[i] &&(type_data[i]!="TEXT")) type_data[i]="REAL";
                // else if(type_data[i]!="TEXT") type_data[i]="INTEGER";
            }
        }*/
    for (int j=0;j<cols;j++)
        for (int i=0;i<rows;i++)
        {
             bool flag;
             data1[i][j].toInt(&flag);
             if(flag) temp[j]="INTEGER";
             else
             {
                 data1[i][j].toDouble(&flag);
                 if(flag) {temp[j]="REAL";qw[j]=true;}
                 else {temp[j]="TEXT"; type_data[j]="TEXT";break;}
             }
        }
    for(int i=0;i<cols;i++)
    {
        if(qw[i] &&(type_data[i]!="TEXT")) type_data[i]="REAL";
        // else if(type_data[i]!="TEXT") type_data[i]="INTEGER";
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
        /*    QMessageBox* pmbx =
                                   new QMessageBox("MessageBox",
                                   "<b>A</b> <i>Simple</i>   <u>Message</u>",
                                   QMessageBox::Information,
                                   QMessageBox::Yes,
                                   QMessageBox::No,
                                   QMessageBox::Cancel | QMessageBox::Escape);
               int n = pmbx->exec();
               delete pmbx;
               if (n == QMessageBox::Yes)
               {
                 //Нажата кнопка Yes
               }
               */
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
        create_table(table_name);
        // qDebug() << "Нет таблицы " + table_name;
        /*     QSqlQuery query;
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
                   }*/
    }
    else
    {
        //table is
        // вызов
        int t=comparator(sdb,table_name);
        switch (t) {
        case 1:{
            QMessageBox* pmbx =
                    new QMessageBox("MessageBox",
                                    "Таблица существует. данные не совпадают. Перезаписать?",
                                    QMessageBox::Information,
                                    QMessageBox::Yes,
                                    QMessageBox::No,
                                    QMessageBox::Cancel | QMessageBox::Escape);
            int n1 = pmbx->exec();
            delete pmbx;
            if (n1 == QMessageBox::Yes)
            {
                //Нажата кнопка Yes
                //delete
                QSqlQuery query1;
                if(!query1.exec( "DELETE FROM '" +table_name+"'") )
                { //error of create
                    qDebug() << "DataBase: error of delete data" ;
                    qDebug() << query1.lastError().text();
                    return;
                }
                create_table(table_name);
                break;
            } else return;
        }
        case 0:
        {
            QMessageBox* pmbx1 =
                    new QMessageBox("MessageBox",
                                    "Таблица существует. данные не совпадают. Перезаписать?",
                                    QMessageBox::Information,
                                    QMessageBox::Yes,
                                    QMessageBox::No,
                                    QMessageBox::Cancel | QMessageBox::Escape);
            int n = pmbx1->exec();
            delete pmbx1;
            if (n == QMessageBox::Yes)
            {
                //Нажата кнопка Yes
                QSqlQuery query2;
                if(!query2.exec( "DROP TABLE '" +table_name+"'") )
                { //error of create
                    qDebug() << "DataBase: error of delete table" ;
                    qDebug() << query2.lastError().text();
                    return;
                }
                //delete
                create_table(table_name);
                break;
            } else return;
        }
        case -1:{
            return;}
        default:
            break;
        }
    }
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

void BDData::create_table(QString table_name){
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

int BDData::comparator(QSqlDatabase sdb,QString table_name)
{
    //sravn tables names
    int j;
    QSqlRecord columns = sdb.record(table_name);
    // QList<QString> column_name1;
    emit beginInsertColumns(QModelIndex(), 0, columns.count()-1);
    if (cols!=columns.count()) return 0; //columns is ddifferent
    for(j = 0; j < columns.count(); j++){
        //column_name1.append(columns.fieldName(j));
        if(column_name[j]!=columns.fieldName(j)) return 0;
    }
    emit endInsertColumns();


    //colums same
    QList<QString> temp;
    QSqlQuery query("SELECT * FROM " + table_name);
    emit beginInsertRows(QModelIndex(), 0, rows-1);
    int i=0;
    while (query.next()) {
        //  rows << QStringList();
        temp=data1[i];
        for(j = 0; j < cols; j++){
            //      rows.last() << query.value(j).toString();
            if(temp[j]!=query.value(j).toString()) return 1;
            //temp.append(query.value(j).toString());

        }
        //     qDebug()<<temp;
        data1.append(temp); temp.clear();  i++;
        if (i>rows)return 1; //data is different
    }
    emit endInsertRows();


    return -1; //the same
}

void BDData::load_from_sql1(QString filename, QString name_of_table)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    if( !db.open() ) {
        qDebug() <<  "Cannot open database:" << db.lastError().text();
        return;
    }
    QSqlRecord rec = db.record(name_of_table);
    if (rec.isEmpty())
    {
        qDebug() << "Cannot found table " + name_of_table;
        return;
    }
    if (cols != 0){
       cols=0;
       rows=0;
       data1.clear();
       column_name.clear();
       type_data.clear();
     }

    beginInsertColumns(QModelIndex(), 0, rec.count()-1);
    for(int j = 0; j < rec.count(); j++)
    column_name.append(rec.fieldName(j));
    endInsertColumns();
    cols = rec.count();
qDebug()<<cols;
    QList<QString> temp;
    QSqlQuery countRows;
    countRows.exec("SELECT count(*) FROM " + name_of_table);
    countRows.last();
    qDebug() << countRows.value(countRows.at()).toString();
    rows = countRows.value(countRows.at()).toInt();
    //cout << rows;
    QSqlQuery query("SELECT * FROM " + name_of_table);

    beginInsertRows(QModelIndex(), 0, rows-1);
    while (query.next())
    {
        for (int j = 0; j < cols; j++)
              temp.append(query.value(j).toString());
              data1.append(temp);
              temp.clear();
     }
     endInsertRows();

     db.close();
     return ;
}

void BDData::output_in_sql1(QString filename, QString name_of_table)
{
    if (!QFile::exists(filename)){qDebug()<<"not a database file"; return;}
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    if (!db.open())
    {
        qDebug() << "Cannot open database:" + db.lastError().text();
        return;
    }
    QSqlRecord columns = db.record(name_of_table);

    if (!columns.isEmpty()) { //create table if not it
        QSqlQuery query2;
        if(!query2.exec( "DROP TABLE '" +name_of_table+"'") )
        { //error of create
            qDebug() << "DataBase: error of delete table" ;
            qDebug() << query2.lastError().text();
            return;
        }
        //delete
    }

    QSqlQuery query;
    QString str;
    str = "CREATE TABLE '" + name_of_table + "' ( '";
    str += column_name[0] + "' VARCHAR(255) "+"PRIMARY KEY NOT NULL, '";
    for (int j = 1; j < cols-1; j++)
        str += column_name[j] + "' VARCHAR(255), '";
    str += column_name[cols-1] + "' VARCHAR(255)" +" );";
    qDebug() << str;
    if (!query.exec(str)) {
        qDebug() << "Unable to create a table " + query.lastError().text();
    }

   /* QString strt;
    for (int i = 0; i < rows; i++)
    {
    strt = "INSERT INTO '" + name_of_table+"' (";
    for (int j = 0; j < cols-1; j++)
        strt += column_name[j] + ", ";
    strt += column_name[cols-1] + ")" + " VALUES (";


    strt += "\'" + data1[i][0] + "\'" + ", ";
    for (int j = 1; j < cols-1; j++)
        strt += "\'" + data1[i][j] + "\'" + ", ";
    strt += "\'" + data1[i][cols-1]+ "\'" + ");";
    qDebug() << strt;
    if (!query.exec(strt)) {
        qDebug() << "Unable to do insert operation "+  db.lastError().text();
    }
    }*/
    //zapic data
    QString qq="INSERT INTO '"+name_of_table+"' VALUES ";
    for(int i=0;i<rows;i++){
        QString tem;
        tem="";
        QList<QString> temp;
        temp=data1[i];
        for(int j=0; j<cols;j++){

            if(type_data[j]=="TEXT")
             //   tem+="'"+temp[j]+"'";
                tem+="'"+data1[i][j]+"'";
            else //tem+=temp[j];
                tem+=data1[i][j];
            if(j<cols-1)tem+=", ";
        }
        if(i<rows-1)  qq+="("+tem+"), ";else qq+="("+tem+")";
    }
    QSqlQuery qqq;
    if(!qqq.exec(qq)){ qDebug() << "DataBase: error of input data ";
        qDebug() << qqq.lastError().text();
    }


    db.close();
}




