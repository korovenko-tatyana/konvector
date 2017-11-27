#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Раскоментировать и проверить видимость в порядке мледования, для удобство отладки закоменчено
    /*  ui->groupBox_4->hide();
   ui->download->hide();
   ui->go->hide();
   ui->groupBox_2->hide();*/
    ui->go->setEnabled(false);
    ui->download->setEnabled(false);
    //   ui->path_label_2->hide();
    connect (ui->csv_sql, SIGNAL(clicked(bool)), this, SLOT(choose_napr1(bool)));
    connect (ui->sql_csv, SIGNAL(clicked(bool)), this, SLOT(choose_napr2(bool)));
    connect (ui->choose_file, SIGNAL(clicked(bool)), this, SLOT(choose_file_click()));
    connect (ui->go, SIGNAL(clicked(bool)), this, SLOT(go_click()));
    connect (ui->path, SIGNAL(clicked(bool)), this, SLOT(path_click()));
    connect (ui->download, SIGNAL(clicked(bool)), this, SLOT(download_click()));
    //BDData tab=new(BDData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::choose_napr1(bool checked){
    if (checked)
    {
        napr=1;
        //  ui->groupBox_4->show();
        // ui->label->hide();
        ui->label->setEnabled(false);
        // ui->table_name->hide();
        ui->table_name->setEnabled(false);
        // ui->label_2->show();
        // ui->table_name_out->show();
        ui->label_2->setEnabled(true);
        ui->table_name_out->setEnabled(true);
        table_name_from="";
    }
}
void MainWindow::choose_napr2(bool checked){
    if (checked)
    {
        napr=-1;
        // ui->groupBox_4->show();
        // ui->label->show();
        ui->label->setEnabled(true);
        ui->table_name->setEnabled(true);
        //  ui->table_name->show();
        //  ui->label_2->hide();
        // ui->table_name_out->hide();
        ui->label_2->setEnabled(false);
        ui->table_name_out->setEnabled(false);
        table_name_from="";
    }
}
//  if(napr==1){ui->label_2->show();ui->table_name_out->show();}{ui->label_2->hide();ui->table_name_out->hide();}


int MainWindow::get_napr() {return napr;}
//QString MainWindow::get_file_name(){return file_name_load;}

void MainWindow::path_click(){ //choose 2 in
    // ui->go->show();
    ui->go->setEnabled(true);

    // ui->groupBox_2->show();
    QString filename=//QFileDialog::getOpenFileName(this, tr("Save File"),"","");
      QFileDialog::getSaveFileName(this,
                                QString::fromUtf8("Сохранить файл"),
                                QDir::currentPath(),
                                "Fiels (*.db *.csv *.*);;All files (*.*)");
    if (filename!=""){
        /*  QFile file(filename);
        if(!file.open(QIODevice::WriteOnly)){
            QMessageBox::critical(this,tr("Error"),tr("Could not open file"));
            return;
        }else*/

        /*      if(napr==1){
            //   if( filename.indexOf(".db")==-1)
                   if(!filename.contains(".db"))
                filename+=".db";}
            else {*/
        if(napr==-1)
            if(!filename.contains(".csv"))

                filename+=".csv";
        ui->path_label->setText(filename);
        file_name_out=filename;
        //  file.close();
        //}
    }

}

void MainWindow::choose_file_click(){ //сhoose 1 from
    //  ui->download->show();
    //  ui->groupBox_2->show();
    ui->download->setEnabled(true);
    QString filename=QFileDialog::getOpenFileName(this, tr("Open File"),"","");
    // QDebug(filename);
    //  if(filename !="")
    if(!filename.isEmpty())
    {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this,tr("Error"),tr("Could not open file"));
            return;
        }
        file.close();
    }
    // ui->path_label_in
    ui->path_label_in->setText(filename);
    file_name_load=filename;
    //table.filename=...
}

void MainWindow::download_click(){
    if (file_name_load=="")
    {
        QMessageBox::critical(this,tr("Error"),tr("Not a file name"));
        return;
    }
    else{
        //зависи от логики или в функции загрузчика делать выбор по направлению или в интерфейсе
        switch (napr) {
        case 1: //in sql
            if(file_name_load!=""){
                table.load_from_csv(file_name_load);
                load_to_view();

                //отобразить в модели
            }
            else  QMessageBox::critical(this,tr("Error"),tr("Not a file name to open"));
            break;
        case -1:
            //download from sql
            //load_to_view();
            //opred table_name
            table_name_from=  ui->table_name->text();
            // qDebug()<<table_name_from;
            if(table_name_from==""){QMessageBox::critical(this,tr("Error"),tr("Not a table name")); break;}
            table.load_from_sql(file_name_load,table_name_from);
            load_to_view();

            break;
        default:
            QMessageBox::critical(this,tr("Error"),tr("Not a napravlenie convertachii"));
            break;
        }
    }
}


void MainWindow::go_click(){
    if (file_name_load=="")
    {
        QMessageBox::critical(this,tr("Error"),tr("Not a file name to open"));
        return;
    }
    if (file_name_out=="")
    {
        QMessageBox::critical(this,tr("Error"),tr("Not a file name to save"));
        return;
    }
    switch (napr) {
    case 1: //in sql
        //download from csv

        //раскоментрировать

        table_name_from=  ui->table_name_out->text();
        if(table_name_from==""){QMessageBox::critical(this,tr("Error"),tr("Not a table name")); break;}
        table.load_from_csv(file_name_load);
        table.opred_data_type();
        load_to_view();
       // table.out_to_sql(file_name_out,table_name_from);
        table.output_in_sql1(file_name_out,table_name_from);
        //table.out_to_sql("/home/student/qt_project/convec/basa_sql_out",table_name_from);
        break;

    case -1: //in csv
        table_name_from=  ui->table_name->text();
        if(table_name_from==""){QMessageBox::critical(this,tr("Error"),tr("Not a table name")); break;}
      //  table.load_from_sql(file_name_load, table_name_from);
        table.load_from_sql1(file_name_load, table_name_from);
        load_to_view();
        table.opred_data_type();
        table.output_in_csv(file_name_out);
        break;
    default:
        QMessageBox::critical(this,tr("Error"),tr("Not a napravlenie")); return;
        break;
    }

    /*   table.load_from_sql(file_name_load, table_name_from);
//    table.load_from_csv(file_name_load);
    table.opred_data_type();
 //   table.output_in_csv(file_name_out); //delete
    load_to_view();
table.out_to_sql(file_name_out,table_name_from);*/
}


void MainWindow::load_to_view()
{
    model=new QStandardItemModel;
    QStringList hor_head;
    QList<QString> name_col=table.get_column_name();
    int cols=table.get_col(), rows=table.get_row();
    for(int i=0;i<cols;i++)
    {
        hor_head.append(name_col[i]);
    }
    model->setHorizontalHeaderLabels(hor_head);
    QList<QList<QString>> dat=table.get_data();
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
        {
            QList<QString>temp;
            temp.clear();
            temp=dat[i];
            item=new QStandardItem(temp[j]);
            model->setItem(i,j,item);

        }
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}
