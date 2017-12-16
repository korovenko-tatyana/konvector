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

//Test_BDData::oped_data(){

//}
