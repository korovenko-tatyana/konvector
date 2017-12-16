#include <QCoreApplication>
#include "test_bddata.h"
int main(int argc, char *argv[])
{
  //  QCoreApplication a(argc, argv);

 //   return a.exec();
    freopen("testing.log", "w", stdout);
 //      QApplication a(argc, argv);
       QCoreApplication a(argc, argv);
       QTest::qExec(new Test_BDData, argc, argv);
       return 0;
}
