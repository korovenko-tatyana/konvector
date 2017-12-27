#include "test_bddata.h"

Test_BDData::Test_BDData(QObject *parent) : QObject(parent)
{

}

void Test_BDData::readCSV(){
    QDir dir;
      QString fileName = dir.absoluteFilePath("test_file.csv");
      BDData tab;
      QList<QString> col_name={"1","2","Text2","3","real"};
    QList<QList<QString>> d;
    d.push_back({"19","Мышка","А правильней использовать; \"Ёлочки\"","Ct;rl","4.9"});
     QList<QString> types={"INTEGER","TEXT","TEXT","TEXT","REAL"};
     BDData test_tab(col_name,types,d);
     tab.CSVRead(fileName);
     tab.opred_data_type();
     QCOMPARE(tab, test_tab);
}

void Test_BDData::readSQL(){
    QDir dir;
      QString fileName = dir.absoluteFilePath("test.sql");
      QString tableName = "test";
      BDData tab;
      QList<QString> col_name={"Name","Number","Street","1991","2017"};
    QList<QList<QString>> d;
    d.push_back({"Tomas","1734275","Street \"Nussknacker\"","","60.9"});
     QList<QString> types={"TEXT","INTEGER","TEXT","TEXT","REAL"};
     BDData test_tab(col_name,types,d);
     tab.load_from_sql1(fileName,tableName);
     QCOMPARE(tab, test_tab);
}

void Test_BDData::writeCSV(){
    QDir dir;
 //     QString fileName = dir.absoluteFilePath("test_file.csv");
       QString fileName1 = dir.absoluteFilePath("test_file_out.csv");
    // BDData tab;
      QList<QString> col_name={"1","2","Text2","3","real"};
    QList<QList<QString>> d;
    d.push_back({"19","Мышка","А правильней использовать; \"Ёлочки\"","Ct;rl","4.9"});
     QList<QString> types={"INTEGER","TEXT","TEXT","TEXT","REAL"};
     BDData test_tab(col_name,types,d);
     BDData tab(col_name,types,d);
     tab.output_in_csv(fileName1);
     tab.CSVRead(fileName1);
     tab.opred_data_type();
     QCOMPARE(tab, test_tab);
}

void Test_BDData::writeSQL(){
    QDir dir;
       QString fileName1 = dir.absoluteFilePath("testout.sql");
       QString tableName = "test";
     QList<QString> col_name={"Name","Number","Street","1991","2017"};
     QList<QList<QString>> d;
     d.push_back({"Tomas","1734275","Street \"Nussknacker\"","","60.9"});
     QList<QString> types={"TEXT","INTEGER","TEXT","TEXT","REAL"};

     BDData test_tab(col_name,types,d);
     BDData tab(col_name,types,d);

     tab.output_in_sql1(fileName1,tableName);
     tab.load_from_sql1(fileName1,tableName);
     QCOMPARE(tab, test_tab);
}

void Test_BDData::main_test(){
    //from csv
    QDir dir;
      QString fileName = dir.absoluteFilePath("basa.csv");
       QString fileName1 = dir.absoluteFilePath("basa.db");
     BDData tab,tab_csv,tab1;
     tab_csv.CSVRead(fileName);
     tab.CSVRead(fileName);
     tab_csv.output_in_sql1(fileName1,"test_table");
     tab_csv.load_from_sql1(fileName1,"test_table");
     tab_csv.output_in_csv(fileName);
     tab_csv.CSVRead(fileName);

     QCOMPARE(tab, tab_csv);
     fileName = dir.absoluteFilePath("basa1.csv");
QString table="test_table";
     tab.load_from_sql1(fileName1,table);
     tab1.load_from_sql1(fileName1,table);
     tab1.output_in_csv(fileName);
     tab1.CSVRead(fileName);
     tab1.output_in_sql1(fileName1,table);
     tab1.load_from_sql1(fileName1,table);
      QCOMPARE(tab, tab1);
}
