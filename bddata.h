#ifndef BDDATA_H
#define BDDATA_H

#include <QObject>
#include <QList>
#include <QAbstractTableModel>

#include<QString>


class BDData :public QAbstractTableModel// public QAbctractTableModel {

{
    Q_OBJECT
public:
//    BDData();
BDData(QObject *parent = nullptr);
virtual int rowCount(const QModelIndex &parent) const override;
   virtual int columnCount(const QModelIndex &parent) const override;
 virtual QVariant data(const QModelIndex &index, int role) const override;

public slots:


private:
  QList<QString> column_name;
  QList<QString> type_data; //еипы данных для скюэл
QList<QList<QString>> data1;
QString file_name;
QString table_name;
int cols=0,rows=0;

public:
void load_from_csv(QString filename);//имена столбцов из первой строчки
void output_in_csv(QString filename); //заголовки это будет имя таблицы
virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override; //установить имена столбцов в отображении таблицы
void opred_data_type();
QList<QString> get_column_name();
QList<QList<QString>> get_data();
int get_row();
int get_col();

};

#endif // BDDATA_H
