#ifndef TEST_BDDATA_H
#define TEST_BDDATA_H

//#include <QtTest>
#include <QtTest/QTest>
#include "../../qt_project/convec1/bddata.h"
#include <QObject>
#include <QDir>

class Test_BDData : public QObject
{
    Q_OBJECT
public:
    explicit Test_BDData(QObject *parent = 0);

signals:

public slots:
private slots:
    void readCSV();
  //  void opred_data();
    void readSQL();
    void writeCSV();
    void writeSQL();
    void main_test();
};

#endif // TEST_BDDATA_H
