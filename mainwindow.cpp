#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

Med_Center *Head = nullptr;

int row_num = -1, co_de = -1;
int first_time = 0, check[2] = {0,0}, was_saved = 0;

QString path = "", pos_ition="", cen_ter = "", na_me = "";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Man = new Manual();
    Ab = new About();

    QWidget::setWindowTitle("Медицинский центр");

    ui->tableWidget->setColumnWidth(0,50);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,150);
    ui->tableWidget->setColumnWidth(3,150);
    ui->tableWidget->setColumnWidth(6,250);
    ui->tableWidget->setColumnWidth(9,300);

    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->lineEdit_5->hide();
    ui->lineEdit_6->hide();
    ui->lineEdit_7->hide();
    ui->lineEdit_8->hide();

    ui->radioButton->hide();
    ui->radioButton_2->hide();

    ui->dateEdit->hide();

    ui->comboBox->hide();
    ui->comboBox_2->hide();
    ui->comboBox_3->hide();
    ui->comboBox_4->hide();
    ui->comboBox_5->hide();
    ui->comboBox_6->hide();
    ui->comboBox_7->hide();
    ui->comboBox_8->hide();

    ui->pushButton_7->hide();//Готово
    ui->pushButton_8->hide();//Отмена
    ui->pushButton_9->hide();
    ui->pushButton_10->hide();
    ui->pushButton_11->hide();
    ui->pushButton_12->hide();
    ui->pushButton_13->hide();
    ui->pushButton_14->hide();
    ui->pushButton_15->hide();
    ui->pushButton_16->hide();

    ui->label_14->hide();

    ui->tableWidget->setEditTriggers((QHeaderView::EditTriggers)0);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete Man;
    delete Ab;
}

int MainWindow::on_action_7_triggered() //Exit
{
    if(!was_saved && Head)
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,"Выход",\
                                           "При выходе все несохранённые данные будут потеряны. Сохранить?",\
                                           QMessageBox::Ok | QMessageBox::No | QMessageBox::Cancel);
        box->setButtonText(QMessageBox::Ok,"Да");
        box->setButtonText(QMessageBox::No,"Нет");
        box->setButtonText(QMessageBox::Cancel,"Отмена");
        int res = box->exec();
        switch(res)
        {
        case QMessageBox::Ok:
            on_action_5_triggered();
            exit(0);
            break;
        case QMessageBox::No: exit(0);
        case QMessageBox::Cancel: return 1;
        }
    }
    else
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,"Выход","Вы уверены, что хотите выйти?",\
                                           QMessageBox::Ok | QMessageBox::No);
        box->setButtonText(QMessageBox::Ok,"Да");
        box->setButtonText(QMessageBox::No,"Нет");
        int res = box->exec();
        switch(res)
        {
        case QMessageBox::Ok: exit(0);
        case QMessageBox::No: return 1;
        }
    }
}


void MainWindow::closeEvent(QCloseEvent *event)
{
     if (on_action_7_triggered())
     {
         event->ignore();
         return;
     }
     Man->close();
     Ab->close();
     QMainWindow::closeEvent(event);
}


inline int CheckRightText(const QString& str)
{
    if (!str.size()) return 0;
    for(int i=0;i<str.size();i++)
        if (!str[i].isLetter()) return 0;
    return 1;
}


inline int CheckRightNumber(const QString& str)
{
    if (!str.size()) return 0;
    for(int i=0;i<str.size();i++)
        if (!str[i].isDigit()) return 0;
    return 1;
}


void MainWindow::setWidgetsToAddOrEdit()
{
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();

    ui->label->setText("Фамилия:");
    ui->label_2->setText("Имя:");
    ui->label_3->setText("Отчество:");
    ui->label_4->setText("Пол:");
    ui->label_5->setText("Дата рождения:");
    ui->label_6->setText("Место работы:");
    ui->label_7->setText("Должность:");
    ui->label_8->setText("Зарплата:");
    ui->label_14->show();
    ui->label_15->hide();

    ui->lineEdit->show();
    ui->lineEdit_2->show();
    ui->lineEdit_3->show();
    ui->lineEdit_4->show();
    ui->lineEdit_8->show();

    ui->comboBox->show();
    ui->comboBox_2->show();

    ui->radioButton->show();
    ui->radioButton_2->show();

    ui->dateEdit->show();

    ui->pushButton_7->show();
    ui->pushButton_8->show();
    ui->pushButton_9->show();
    ui->pushButton_10->show();
    ui->pushButton_11->show();
    ui->pushButton_12->show();
    ui->pushButton_16->show();
    ui->pushButton_17->hide();
    ui->pushButton_18->hide();
}


void MainWindow::CheckCorrectData(const QString& code, const QString& surname, const QString& name, \
                                 const QString& patronymic, const QString& sex, const QString& organization, \
                                 const QString& position, const QString& salary, const QString& specialization,\
                                 const QString& experience, const QString& category, const QString& experience1, \
                                 const QString& hours_in_month, const QString& rank, const QString& firm, int *array)
{
    QPalette paletteWrong, paletteRight;
    paletteWrong.setColor(QPalette::Base, QColor(255,173,173));
    paletteRight.setColor(QPalette::Base, Qt::white);

    if (!CheckRightNumber(code))
    {
        array[0] = 1;
        array[10] = 1;
    }
    if (!CheckRightText(surname))
    {
        array[1] = 1;
        array[10] = 1;
    }
    if (!CheckRightText(name))
    {
        array[2] = 1;
        array[10] = 1;
    }
    if (!CheckRightText(patronymic))
    {
        array[3] = 1;
        array[10] = 1;
    }

    if (sex == "")
    {
        QMessageBox box;
        box.setText("Вы не выбрали пол!");
        box.setIcon(QMessageBox::Warning);
        box.setWindowTitle("ОШИБКА!");
        box.exec();
        array[10] = 1;
    }

    Med_Center *Tmp = Head;///Проверка на существование кода
    do
    {
        if (Tmp->getName() == organization)
        {
            Worker *Check = Tmp->gethead();
            if (Tmp->gethead())
            {
                do
                {
                    if (Check->getCode() == code.toInt() && code.toInt() != co_de)
                    {
                        QMessageBox box;
                        box.setText("Сотрудник с таким кодом уже есть!");
                        box.setIcon(QMessageBox::Warning);
                        box.setWindowTitle("ОШИБКА!");
                        box.exec();
                        array[0] = 1;
                        array[10] = 1;
                        break;
                    }
                    Check = Check->getNext();
                }
                while(Check != Tmp->gethead());
            }
            break;
        }
        Tmp = Tmp->getNext();
    }
    while(Tmp != Head);

    if (!CheckRightNumber(salary))
    {
        array[4] = 1;
        array[10] = 1;
    }

    if (position=="Врач")
    {
        if (!CheckRightText(specialization))
        {
            array[5] = 1;
            array[10] = 1;
        }
        if (!CheckRightNumber(experience))
        {
            array[6] = 1;
            array[10] = 1;
        }
    }
    else if (position=="Кассир")
    {
        if (!CheckRightNumber(experience1))
        {
            array[7] = 1;
            array[10] = 1;
        }
        if (!CheckRightNumber(hours_in_month))
        {
            array[8] = 1;
            array[10] = 1;
        }
    }
    else if (position=="Охранник")
    {
        if (!firm.size())
        {
            array[9] = 1;
            array[10] = 1;
        }
    }
}


void MainWindow::on_comboBox_2_activated(int index)//Doctor or Security or Cashier
{
    switch(index)
    {
    case 0:
        ui->lineEdit_5->hide();
        ui->lineEdit_6->hide();
        ui->lineEdit_7->hide();
        ui->pushButton_13->hide();
        ui->pushButton_14->hide();
        ui->pushButton_15->hide();

        ui->comboBox_3->hide();
        ui->comboBox_4->hide();

        ui->label_9->setText("");
        ui->label_10->setText("");
        ui->label_11->setText("");
        break;
    case 1:
        ui->lineEdit_5->show();
        ui->lineEdit_6->show();
        ui->lineEdit_7->hide();
        ui->pushButton_13->show();
        ui->pushButton_14->show();
        ui->pushButton_15->hide();

        ui->comboBox_3->hide();
        ui->comboBox_4->show();

        ui->label_9->setText("Специализация:");
        ui->label_10->setText("Опыт:");
        ui->label_11->setText("Категория");
        ui->label_9->show();
        ui->label_10->show();
        ui->label_11->show();
        break;
    case 2:
        ui->lineEdit_5->show();
        ui->lineEdit_6->show();
        ui->lineEdit_7->hide();
        ui->pushButton_13->show();
        ui->pushButton_14->show();
        ui->pushButton_15->hide();

        ui->comboBox_3->hide();
        ui->comboBox_4->hide();

        ui->label_9->setText("Опыт:");
        ui->label_10->setText("Часов в месяц:");
        ui->label_11->setText("");
        ui->label_9->show();
        ui->label_10->show();
        ui->label_11->show();
        break;
    case 3:
        ui->lineEdit_5->hide();
        ui->lineEdit_6->show();
        ui->lineEdit_7->hide();
        ui->pushButton_13->hide();
        ui->pushButton_14->show();
        ui->pushButton_15->hide();

        ui->comboBox_3->show();
        ui->comboBox_4->hide();

        ui->label_9->setText("Ранг:");
        ui->label_10->setText("Организация:");
        ui->label_11->setText("");
        ui->label_9->show();
        ui->label_10->show();
        ui->label_11->show();
        break;
    }
}


void MainWindow::on_comboBox_5_activated(int index)//Criteria
{
    Med_Center *Tmp = Head->getNext();
    Worker *This;
    switch(index)
    {
    case 0:
        ui->comboBox_6->clear();
        ui->comboBox_6->setDisabled(1);
        break;
    case 1:
        ui->comboBox_6->setDisabled(0);
        ui->comboBox_6->clear();
        do
        {
            if (Tmp->gethead())
            {
                This = Tmp->gethead()->getNext();
                do
                {
                    QString code = QString::number(This->getCode());
                    if (ui->comboBox_6->findText(code) == -1) ui->comboBox_6->addItem(code);
                    This = This->getNext();
                }
                while(This != Tmp->gethead()->getNext());
            }
            Tmp = Tmp->getNext();
        }
        while(Tmp != Head->getNext());
        break;
    case 2:
        ui->comboBox_6->setDisabled(0);
        ui->comboBox_6->clear();
        do
        {
            if (Tmp->gethead())
            {
                This = Tmp->gethead()->getNext();
                do
                {
                    QString surname = This->getSurname();
                    if (ui->comboBox_6->findText(surname) == -1) ui->comboBox_6->addItem(surname);
                    This = This->getNext();
                }
                while(This != Tmp->gethead()->getNext());
            }
            Tmp = Tmp->getNext();
        }
        while(Tmp != Head->getNext());
        break;
    case 3:
        ui->comboBox_6->setDisabled(0);
        ui->comboBox_6->clear();
        do
        {
            QString center = Tmp->getName();
            if (ui->comboBox_6->findText(center) == -1) ui->comboBox_6->addItem(center);
            Tmp = Tmp->getNext();
        }
        while(Tmp != Head->getNext());
        break;
    case 4:
        ui->comboBox_6->setDisabled(0);
        ui->comboBox_6->clear();
        do
        {
            if (Tmp->gethead())
            {
                This = Tmp->gethead();
                do
                {
                    QString position = This->getPosition();
                    if (ui->comboBox_6->findText(position) == -1) ui->comboBox_6->addItem(position);
                    This = This->getNext();
                }
                while(This != Tmp->gethead());
            }
            Tmp = Tmp->getNext();
        }
        while(Tmp != Head->getNext());
        break;
    }
}


void MainWindow::on_comboBox_7_activated(int index)//Data About Center
{
    if (!index)
    {
        ui->lineEdit->setDisabled(1);
        ui->lineEdit_2->setDisabled(1);
        ui->lineEdit_3->setDisabled(1);
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        return;
    }

    ui->lineEdit->setDisabled(0);
    ui->lineEdit_2->setDisabled(0);
    ui->lineEdit_3->setDisabled(0);

    QString Name = ui->comboBox_7->itemText(index);
    na_me = Name;

    if(Head)
    {
        Med_Center *Tmp = Head;
        do
        {
            if (Tmp->getName() == Name)
            {
                ui->lineEdit->setText(Tmp->getName());
                ui->lineEdit_2->setText(Tmp->getAddress());
                ui->lineEdit_3->setText(Tmp->getPhoneNumber());
                break;
            }
            Tmp = Tmp->getNext();
        }
        while(Tmp != Head);
    }
}


void MainWindow::Show(Worker *This, Med_Center *Tmp, const int& row)
{
    ui->tableWidget->setRowHeight(row,60);
    ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(This->getCode())));
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(This->getSurname()));
    ui->tableWidget->setItem(row,2,new QTableWidgetItem(This->getName()));
    ui->tableWidget->setItem(row,3,new QTableWidgetItem(This->getPatronymic()));
    ui->tableWidget->setItem(row,4,new QTableWidgetItem(This->getSex()));
    ui->tableWidget->setItem(row,5,new QTableWidgetItem(This->getBirthday()));
    ui->tableWidget->setItem(row,6,new QTableWidgetItem("Название: " + This->getCenter() + "\nАдрес: " + Tmp->getAddress() + "\nТелефон: " + Tmp->getPhoneNumber()));
    ui->tableWidget->setItem(row,7,new QTableWidgetItem(This->getPosition()));
    ui->tableWidget->setItem(row,8,new QTableWidgetItem(QString::number(This->getSalary())));
    QString Pos = This->getPosition();
    if (Pos == "Врач")
        ui->tableWidget->setItem(row,9,new QTableWidgetItem("Специализация: " + dynamic_cast<Doctor*>(This)->getSpecialization() + "\nОпыт: " + \
                                                            QString::number(dynamic_cast<Doctor*>(This)->getExperience()) + \
                                                            "\nКатегория: " + QString::number(dynamic_cast<Doctor*>(This)->getCategory())));
    else if (Pos == "Кассир")
        ui->tableWidget->setItem(row,9,new QTableWidgetItem("Опыт: " + QString::number(dynamic_cast<Cashier*>(This)->getExperience()) + \
                                                            "\nРаботает часов/месяц: " + QString::number(dynamic_cast<Cashier*>(This)->getHiM())));
    else
        ui->tableWidget->setItem(row,9,new QTableWidgetItem("Ранг: " + QString::number(dynamic_cast<Security*>(This)->getRank()) + \
                                                            "\nФирма охраны: " + dynamic_cast<Security*>(This)->getOrganization()));
}


void MainWindow::on_comboBox_6_activated(int index)
{
    Med_Center *Tmp = Head->getNext();
    Worker *This;
    QString result = ui->comboBox_5->currentText(), crit = ui->comboBox_6->itemText(index);
    ui->tableWidget->setRowCount(0);
    if (result == "Код")
    {
        do
        {
            if (Tmp->gethead())
            {
                This = Tmp->gethead()->getNext();
                do
                {
                    if (QString::number(This->getCode()) == crit)
                    {
                        int row = ui->tableWidget->rowCount();
                        ui->tableWidget->insertRow(row);
                        Show(This,Tmp,row);
                    }
                    This = This->getNext();
                }
                while(This != Tmp->gethead()->getNext());
            }
            Tmp = Tmp->getNext();
        }
        while(Tmp != Head->getNext());
    }
    else if (result == "Фамилия")
    {
        do
        {
            if (Tmp->gethead())
            {
                This = Tmp->gethead()->getNext();
                do
                {
                    if (This->getSurname() == crit)
                    {
                        int row = ui->tableWidget->rowCount();
                        ui->tableWidget->insertRow(row);
                        Show(This,Tmp,row);
                    }
                    This = This->getNext();
                }
                while(This != Tmp->gethead()->getNext());
            }
            Tmp = Tmp->getNext();
        }
        while(Tmp != Head->getNext());
    }
    else if (result == "Организация")
    {
        do
        {
            if (Tmp->getName() == crit)
            {
                if (Tmp->gethead())
                {
                    This = Tmp->gethead()->getNext();
                    do
                    {
                        int row = ui->tableWidget->rowCount();
                        ui->tableWidget->insertRow(row);
                        Show(This,Tmp,row);
                        This = This->getNext();
                    }
                    while(This != Tmp->gethead()->getNext());
                }
                break;
            }
            Tmp = Tmp->getNext();
        }
        while(Tmp != Head->getNext());
    }
    else //Должность
    {
        do
        {
            if (Tmp->gethead())
            {
                This = Tmp->gethead()->getNext();
                do
                {
                    if (This->getPosition() == crit)
                    {
                        int row = ui->tableWidget->rowCount();
                        ui->tableWidget->insertRow(row);
                        Show(This,Tmp,row);
                    }
                    This = This->getNext();
                }
                while(This != Tmp->gethead()->getNext());
            }
            Tmp = Tmp->getNext();
        }
        while(Tmp != Head->getNext());
    }
}


void MainWindow::on_pushButton_clicked()//Add Worker
{
    if (!Head)
    {
        QMessageBox box;
        box.setWindowTitle("ОШИБКА!");
        box.setText("Нет ни одного мединцинского центра!");
        box.setIcon(QMessageBox::Warning);
        box.exec();
        return;
    }
    setWidgetsToAddOrEdit();
}


void MainWindow::on_pushButton_2_clicked()//Add Center
{
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->pushButton_9->show();
    ui->pushButton_11->show();
    ui->pushButton_10->show();
    ui->pushButton_17->hide();
    ui->pushButton_18->hide();

    ui->label->setText("Название:");
    ui->label_2->setText("Адрес:");
    ui->label_3->setText("Телефон:");
    ui->label_15->hide();

    ui->lineEdit->show();
    ui->lineEdit_2->show();
    ui->lineEdit_3->show();

    ui->pushButton_7->show();
    ui->pushButton_8->show();
}


void MainWindow::on_pushButton_3_clicked()//Delete Worker
{
    if (ui->tableWidget->selectedItems().isEmpty())
    {
        QMessageBox box;
        box.setWindowTitle("ОШИБКА!");
        box.setText("Не выбрано ни одной строки!");
        box.setIcon(QMessageBox::Warning);
        box.exec();
        return;
    }

    int row = ui->tableWidget->selectionModel()->currentIndex().row();
    if (row>=0)
    {
        QString code, center;
        code = ui->tableWidget->item(row,0)->text();
        center = ui->tableWidget->item(row,6)->text();
        center = center.right(center.size()-10);
        center = center.left(center.indexOf('\n'));

        Med_Center *Obj = Head;
        do
        {
            if (Obj->getName() == center)
            {
                Worker *Check = Obj->gethead();
                do
                {
                    if (Check->getCode() == code.toInt())
                    {
                        Worker *Link = Obj->gethead();
                        Check->Delete(&Link);
                        Obj->sethead(&Link);
                        break;
                    }
                    Check = Check->getNext();
                }
                while(Check != Obj->gethead());
                break;
            }
            Obj = Obj->getNext();
        }
        while(Obj != Head);

        ui->tableWidget->removeRow(row);
    }

}


void MainWindow::on_pushButton_17_clicked()//Delete Center
{
    if (!Head)
    {
        QMessageBox box;
        box.setWindowTitle("ОШИБКА!");
        box.setText("Нет ни одного центра!");
        box.setIcon(QMessageBox::Warning);
        box.exec();
        return;
    }
    ui->label_14->show();
    ui->label_14->setText("Название центра: ");
    ui->comboBox_8->show();

    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->lineEdit_5->hide();
    ui->lineEdit_6->hide();
    ui->lineEdit_7->hide();

    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->pushButton_7->show();
    ui->pushButton_8->show();
    ui->pushButton_9->hide();
    ui->pushButton_10->hide();
    ui->pushButton_11->hide();
    ui->pushButton_12->hide();
    ui->pushButton_13->hide();
    ui->pushButton_14->hide();
    ui->pushButton_15->hide();
    ui->pushButton_17->hide();
    ui->pushButton_18->hide();

    ui->radioButton->hide();
    ui->radioButton_2->hide();

    ui->comboBox->hide();
    ui->comboBox_2->hide();
    ui->comboBox_3->hide();
    ui->comboBox_4->hide();
    ui->comboBox_5->hide();
    ui->comboBox_6->hide();

    ui->label_15->hide();

    Med_Center *Tmp = Head->getNext();
    do
    {
        ui->comboBox_8->addItem(Tmp->getName());
        Tmp = Tmp->getNext();
    }
    while(Tmp != Head->getNext());
}


void MainWindow::on_pushButton_4_clicked()//Edit Worker
{
    if (ui->tableWidget->selectedItems().isEmpty())
    {
        QMessageBox box;
        box.setWindowTitle("ОШИБКА!");
        box.setText("Не выбрано ни одной строки!");
        box.setIcon(QMessageBox::Warning);
        box.exec();
        return;
    }

    int row = ui->tableWidget->selectionModel()->currentIndex().row();
    if (row>=0)
    {
        QString code, center;
        code = ui->tableWidget->item(row,0)->text();
        center = ui->tableWidget->item(row,6)->text();
        center = center.right(center.size()-10);
        center = center.left(center.indexOf('\n'));

        setWidgetsToAddOrEdit();

        Med_Center *Obj = Head;
        do
        {
            if (Obj->getName() == center)
            {
                Worker *Check = Obj->gethead();
                do
                {
                    if (Check->getCode() == code.toInt())
                    {
                        ui->lineEdit_8->setText(code);
                        ui->lineEdit->setText(Check->getSurname());
                        ui->lineEdit_2->setText(Check->getName());
                        ui->lineEdit_3->setText(Check->getPatronymic());
                        if (Check->getSex() == "Мужчина") ui->radioButton->setChecked(1);
                        else ui->radioButton_2->setChecked(1);
                        ui->dateEdit->setDate(QDate::fromString(Check->getBirthday(),"dd.MM.yyyy"));
                        ui->comboBox->setCurrentText(Check->getCenter());
                        ui->comboBox_2->setCurrentText(Check->getPosition());
                        ui->lineEdit_4->setText(QString::number(Check->getSalary()));
                        if (Check->getPosition() == "Врач")
                        {
                            ui->lineEdit_5->show();
                            ui->lineEdit_5->setText(dynamic_cast<Doctor*>(Check)->getSpecialization());
                            ui->lineEdit_6->show();
                            ui->lineEdit_6->setText(QString::number(dynamic_cast<Doctor*>(Check)->getExperience()));
                            ui->comboBox_4->show();
                            ui->comboBox_4->setCurrentText(QString::number(dynamic_cast<Doctor*>(Check)->getCategory()));
                            ui->label_9->setText("Специализация:");
                            ui->label_10->setText("Опыт:");
                            ui->label_11->setText("Категория");
                            ui->label_9->show();
                            ui->label_10->show();
                            ui->label_11->show();
                            ui->pushButton_13->show();
                            ui->pushButton_14->show();
                        }
                        else if (Check->getPosition() == "Кассир")
                        {
                            ui->lineEdit_5->show();
                            ui->lineEdit_5->setText(QString::number(dynamic_cast<Cashier*>(Check)->getExperience()));
                            ui->lineEdit_6->show();
                            ui->lineEdit_6->setText(QString::number(dynamic_cast<Cashier*>(Check)->getHiM()));
                            ui->label_9->setText("Опыт:");
                            ui->label_10->setText("Часов в месяц:");
                            ui->label_11->setText("");
                            ui->label_9->show();
                            ui->label_10->show();
                            ui->pushButton_14->show();
                            ui->pushButton_13->show();
                        }
                        else
                        {
                            ui->comboBox_3->show();
                            ui->comboBox_3->setCurrentText(QString::number(dynamic_cast<Security*>(Check)->getRank()));
                            ui->lineEdit_6->show();
                            ui->lineEdit_6->setText(dynamic_cast<Security*>(Check)->getOrganization());
                            ui->label_9->setText("Ранг:");
                            ui->label_10->setText("Организация:");
                            ui->label_11->setText("");
                            ui->label_9->show();
                            ui->label_10->show();
                            ui->pushButton_14->show();
                        }
                        break;
                    }
                    Check = Check->getNext();
                }
                while(Check != Obj->gethead());
                break;
            }
            Obj = Obj->getNext();
        }
        while(Obj != Head);

        cen_ter = center;
        co_de = code.toInt();
        row_num = row;
        pos_ition = ui->comboBox_2->currentText();
    }
}


void MainWindow::on_pushButton_18_clicked()//Edit Center
{
    if (!Head)
    {
        QMessageBox box;
        box.setWindowTitle("ОШИБКА!");
        box.setIcon(QMessageBox::Warning);
        box.setText("Нет ни одного центра!");
        box.exec();
        return;
    }
    ui->comboBox_5->show();
    ui->lineEdit->show();
    ui->lineEdit_2->show();
    ui->lineEdit_3->show();

    ui->lineEdit_4->hide();
    ui->lineEdit_5->hide();
    ui->lineEdit_6->hide();
    ui->lineEdit_7->hide();
    ui->lineEdit_8->hide();
    ui->radioButton->hide();
    ui->radioButton_2->hide();
    ui->dateEdit->hide();
    ui->comboBox->hide();
    ui->comboBox_2->hide();
    ui->comboBox_3->hide();
    ui->comboBox_4->hide();
    ui->comboBox_5->hide();
    ui->comboBox_6->hide();
    ui->comboBox_7->show();

    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->pushButton_7->show();
    ui->pushButton_8->show();
    ui->pushButton_9->hide();
    ui->pushButton_10->hide();
    ui->pushButton_11->hide();
    ui->pushButton_12->hide();
    ui->pushButton_13->hide();
    ui->pushButton_14->hide();
    ui->pushButton_15->hide();
    ui->pushButton_17->hide();
    ui->pushButton_18->hide();

    ui->label_14->setText("Организация:");
    ui->label->setText("Название: ");
    ui->label_2->setText("Адрес:");
    ui->label_3->setText("Телефон:");
    ui->label_14->show();
    ui->label->show();
    ui->label_2->show();
    ui->label_3->show();
    ui->label_15->hide();

    ui->comboBox_7->clear();
    ui->comboBox_7->addItem(" ");
    Med_Center *Tmp = Head->getNext();
    do
    {
        if (ui->comboBox_7->findText(Tmp->getName()) == -1) ui->comboBox_7->addItem(Tmp->getName());
        Tmp = Tmp->getNext();
    }
    while(Tmp != Head->getNext());

    ui->lineEdit->setDisabled(1);
    ui->lineEdit_2->setDisabled(1);
    ui->lineEdit_3->setDisabled(1);
    ui->comboBox_7->setCurrentText(" ");
}


void MainWindow::on_pushButton_5_clicked()//Search
{
    if (!Head)
    {
        QMessageBox box;
        box.setWindowTitle("ОШИБКА!");
        box.setText("Нет ни одного центра!");
        box.setIcon(QMessageBox::Warning);
        box.exec();
        return;
    }

    int count_heads = 0, count_zero_heads = 0;

    Med_Center *Tmp = Head;
    do
    {
        count_heads++;
        if (!Tmp->gethead()) count_zero_heads++;
        Tmp = Tmp->getNext();
    }
    while(Tmp != Head);

    if (count_heads == count_zero_heads)
    {
        QMessageBox box;
        box.setText("Нет ни одного сотрудника!");
        box.setWindowTitle("ОШИБКА!");
        box.setIcon(QMessageBox::Warning);
        box.exec();
        return;
    }

    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->pushButton_17->hide();
    ui->pushButton_18->hide();

    ui->label_14->setText("Критерии поиска:");
    ui->label->setText("Значение критерия:");
    ui->label_14->show();
    ui->label_15->hide();

    ui->comboBox_5->show();
    ui->comboBox_6->show();

    ui->pushButton_7->hide();
    ui->pushButton_8->show();

    if (!ui->comboBox_5->currentText().size()) ui->comboBox_6->setDisabled(1);
}


void MainWindow::on_pushButton_6_clicked()//Show
{
    if (!Head)
    {
        QMessageBox box;
        box.setWindowTitle("ОШИБКА!");
        box.setText("Нет ни одного центра!");
        box.setIcon(QMessageBox::Warning);
        box.exec();
        return;
    }

    ui->tableWidget->setRowCount(0);

    Med_Center *Tmp = Head->getNext();
    do
    {
        Worker *This = Tmp->gethead();
        if (This)
        {
            This = This->getNext();
            do
            {
                int row = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(row);
                ui->tableWidget->setRowHeight(row,60);
                ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(This->getCode())));
                ui->tableWidget->setItem(row,1,new QTableWidgetItem(This->getSurname()));
                ui->tableWidget->setItem(row,2,new QTableWidgetItem(This->getName()));
                ui->tableWidget->setItem(row,3,new QTableWidgetItem(This->getPatronymic()));
                ui->tableWidget->setItem(row,4,new QTableWidgetItem(This->getSex()));
                ui->tableWidget->setItem(row,5,new QTableWidgetItem(This->getBirthday()));
                ui->tableWidget->setItem(row,6,new QTableWidgetItem("Название: " + This->getCenter() + "\nАдрес: " + Tmp->getAddress() + "\nТелефон: " + Tmp->getPhoneNumber()));
                ui->tableWidget->setItem(row,7,new QTableWidgetItem(This->getPosition()));
                ui->tableWidget->setItem(row,8,new QTableWidgetItem(QString::number(This->getSalary())));
                QString Pos = This->getPosition();
                if (Pos == "Врач")
                    ui->tableWidget->setItem(row,9,new QTableWidgetItem("Специализация: " + dynamic_cast<Doctor*>(This)->getSpecialization() + "\nОпыт: " + \
                                                                        QString::number(dynamic_cast<Doctor*>(This)->getExperience()) + \
                                                                        "\nКатегория: " + QString::number(dynamic_cast<Doctor*>(This)->getCategory())));
                else if (Pos == "Кассир")
                    ui->tableWidget->setItem(row,9,new QTableWidgetItem("Опыт: " + QString::number(dynamic_cast<Cashier*>(This)->getExperience()) + \
                                                                        "\nРаботает часов/месяц: " + QString::number(dynamic_cast<Cashier*>(This)->getHiM())));
                else
                    ui->tableWidget->setItem(row,9,new QTableWidgetItem("Ранг: " + QString::number(dynamic_cast<Security*>(This)->getRank()) + \
                                                                        "\nФирма охраны: " + dynamic_cast<Security*>(This)->getOrganization()));
                This = This->getNext();
            }
            while(This != Tmp->gethead()->getNext());
        }
        Tmp = Tmp->getNext();
    }
    while(Tmp != Head->getNext());

}


void MainWindow::on_pushButton_7_clicked()//Ready
{
    QPalette paletteWrong, paletteRight;
    paletteWrong.setColor(QPalette::Base, QColor(255,173,173));
    paletteRight.setColor(QPalette::Base, Qt::white);

    if (ui->lineEdit_4->isHidden() && ui->comboBox_5->isHidden() && ui->label_14->text() == "Код:")//Add Center
    {

        QString name, address, phone;
        QString res;
        int flag=0, check_code=0;

        name = ui->lineEdit->text();
        if (!name.size())
        {
            ui->lineEdit->setPalette(paletteWrong);
            flag=1;
        }
        else ui->lineEdit->setPalette(paletteRight);

        Med_Center *Tmp = Head;
        if (Head)
        {
            do
            {
                if (Tmp->getName() == name)
                {
                    QMessageBox box;
                    box.setText("Такой центр уже есть!");
                    box.setIcon(QMessageBox::Warning);
                    box.setWindowTitle("ОШИБКА!");
                    box.exec();
                    ui->lineEdit->setPalette(paletteWrong);
                    check_code=1;
                    flag=1;
                    break;
                }
                Tmp = Tmp->getNext();
            }
            while(Tmp != Head);
        }
        if (!check_code) ui->lineEdit_8->setPalette(paletteRight);

        address = ui->lineEdit_2->text();
        if (!address.size())
        {
            ui->lineEdit_2->setPalette(paletteWrong);
            flag=1;
        }
        else ui->lineEdit_2->setPalette(paletteRight);

        phone = ui->lineEdit_3->text();
        if (!CheckRightNumber(phone))
        {
            ui->lineEdit_3->setPalette(paletteWrong);
            flag=1;
        }
        else ui->lineEdit_3->setPalette(paletteRight);

        if (flag) return;

        Med_Center *Center = new Med_Center(name,address,phone);
        Center->Add(&Head);

        if (ui->comboBox->findText(name) == -1) ui->comboBox->addItem(name);

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit->setPalette(paletteRight);
        ui->lineEdit_2->setPalette(paletteRight);
        ui->lineEdit_3->setPalette(paletteRight);
    }
    else if (!ui->lineEdit_4->isHidden() && !ui->comboBox->isHidden() && co_de==-1)//Add  Worker
    {
        Med_Center *Tmp;
        Worker *New;
        QString code, surname, name, patronymic, sex, birthday, organization, position, salary, specialization, experience, category, experience1, hours_in_month, rank, firm;

        code = ui->lineEdit_8->text();
        surname = ui->lineEdit->text();
        name = ui->lineEdit_2->text();
        patronymic = ui->lineEdit_3->text();

        if (ui->radioButton->isChecked()) sex = "Мужчина";
        else if (ui->radioButton_2->isChecked()) sex = "Женщина";

        birthday = ui->dateEdit->text();
        int day, month, year;
        day = birthday.left(2).toInt();
        birthday = birthday.right(7);
        month = birthday.left(2).toInt();
        birthday = birthday.right(4);
        year = birthday.toInt();

        organization = ui->comboBox->currentText();
        position = ui->comboBox_2->currentText();
        salary = ui->lineEdit_4->text();

        if (position != "")
        {
            if (position == "Врач")
            {
                specialization = ui->lineEdit_5->text();
                experience = ui->lineEdit_6->text();
                category = ui->comboBox_4->currentText();
            }
            else if (position == "Кассир")
            {
                experience1 = ui->lineEdit_5->text();
                hours_in_month = ui->lineEdit_6->text();
            }
            else
            {
                rank = ui->comboBox_3->currentText();
                firm = ui->lineEdit_6->text();
            }
        }
        else
        {
            QMessageBox box;
            box.setText("Вы не выбрали должность!");
            box.setIcon(QMessageBox::Warning);
            box.exec();
        }

        int *array = new int[11]{};
        CheckCorrectData(code, surname, name, patronymic, sex, organization, position, salary, specialization, experience, category, experience1, hours_in_month, rank, firm, array);

        if (array[0]) ui->lineEdit_8->setPalette(paletteWrong);
        else ui->lineEdit_8->setPalette(paletteRight);
        if (array[1]) ui->lineEdit->setPalette(paletteWrong);
        else ui->lineEdit->setPalette(paletteRight);
        if (array[2]) ui->lineEdit_2->setPalette(paletteWrong);
        else ui->lineEdit_2->setPalette(paletteRight);
        if (array[3]) ui->lineEdit_3->setPalette(paletteWrong);
        else ui->lineEdit_3->setPalette(paletteRight);
        if (array[4]) ui->lineEdit_4->setPalette(paletteWrong);
        else ui->lineEdit_4->setPalette(paletteRight);

        if (position == "Врач")
        {
            if (array[5]) ui->lineEdit_5->setPalette(paletteWrong);
            else ui->lineEdit_5->setPalette(paletteRight);
            if (array[6]) ui->lineEdit_6->setPalette(paletteWrong);
            else ui->lineEdit_6->setPalette(paletteRight);
        }
        else if (position == "Кассир")
        {
            if (array[7]) ui->lineEdit_5->setPalette(paletteWrong);
            else ui->lineEdit_5->setPalette(paletteRight);
            if (array[8]) ui->lineEdit_6->setPalette(paletteWrong);
            else ui->lineEdit_6->setPalette(paletteRight);
        }
        else if (position == "Охранник")
        {
            if (array[9]) ui->lineEdit_6->setPalette(paletteWrong);
            else ui->lineEdit_6->setPalette(paletteRight);
        }

        if (array[10]) return;

        if (position == "Врач") New = new Doctor(code.toInt(), surname, name, patronymic, sex, day, month, year, organization, position, salary.toInt(), specialization, experience.toInt(), category.toInt());
        else if (position == "Кассир") New = new Cashier(code.toInt(), surname, name, patronymic, sex, day, month, year, organization, position, salary.toInt(), experience1.toInt(), hours_in_month.toInt());
        else New = new Security(code.toInt(), surname, name, patronymic, sex, day, month, year, organization, position, salary.toInt(), rank.toInt(), firm);

        ui->lineEdit->setPalette(paletteRight);
        ui->lineEdit_2->setPalette(paletteRight);
        ui->lineEdit_3->setPalette(paletteRight);
        ui->lineEdit_4->setPalette(paletteRight);
        ui->lineEdit_5->setPalette(paletteRight);
        ui->lineEdit_6->setPalette(paletteRight);
        ui->lineEdit_7->setPalette(paletteRight);
        ui->lineEdit_8->setPalette(paletteRight);

        Tmp = Head;//Добавление и отображение нового сотрудника в таблице
        do
        {
            if (Tmp->getName() == organization)
            {
                Worker *Link = Tmp->gethead();
                New->Add(&Link);
                Tmp->sethead(&Link);
                int row = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(row);
                Show(New,Tmp,row);
            }

            Tmp = Tmp->getNext();
        }
        while(Tmp != Head);

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_8->clear();

        ui->radioButton->setChecked(0);
        ui->radioButton_2->setChecked(0);

        ui->label_14->setText("Код:");
    }
    else if (!ui->lineEdit_4->isHidden() && !ui->comboBox->isHidden() && co_de!=-1)//Edit Worker
    {
        Worker *New;
        Med_Center *Tmp;
        QString code, surname, name, patronymic, sex, birthday, organization, position, salary, specialization, experience, category, experience1, hours_in_month, rank, firm;

        code = ui->lineEdit_8->text();
        surname = ui->lineEdit->text();
        name = ui->lineEdit_2->text();
        patronymic = ui->lineEdit_3->text();

        if (ui->radioButton->isChecked()) sex = "Мужчина";
        else if (ui->radioButton_2->isChecked()) sex = "Женщина";

        birthday = ui->dateEdit->text();
        int day, month, year;
        day = birthday.left(2).toInt();
        birthday = birthday.right(7);
        month = birthday.left(2).toInt();
        birthday = birthday.right(4);
        year = birthday.toInt();

        organization = ui->comboBox->currentText();
        position = ui->comboBox_2->currentText();
        salary = ui->lineEdit_4->text();

        if (position != "")
        {
            if (position == "Врач")
            {
                specialization = ui->lineEdit_5->text();
                experience = ui->lineEdit_6->text();
                category = ui->comboBox_4->currentText();
            }
            else if (position == "Кассир")
            {
                experience1 = ui->lineEdit_5->text();
                hours_in_month = ui->lineEdit_6->text();
            }
            else
            {
                rank = ui->comboBox_3->currentText();
                firm = ui->lineEdit_6->text();
            }
        }
        else
        {
            QMessageBox box;
            box.setText("Вы не выбрали должность!");
            box.setWindowTitle("ОШИБКА!");
            box.setIcon(QMessageBox::Warning);
            box.exec();
        }

        int *array = new int[11]{};
        CheckCorrectData(code, surname, name, patronymic, sex, organization, position, salary, specialization, experience, category, experience1, hours_in_month, rank, firm, array);

        if (array[0]) ui->lineEdit_8->setPalette(paletteWrong);
        else ui->lineEdit_8->setPalette(paletteRight);
        if (array[1]) ui->lineEdit->setPalette(paletteWrong);
        else ui->lineEdit->setPalette(paletteRight);
        if (array[2]) ui->lineEdit_2->setPalette(paletteWrong);
        else ui->lineEdit_2->setPalette(paletteRight);
        if (array[3]) ui->lineEdit_3->setPalette(paletteWrong);
        else ui->lineEdit_3->setPalette(paletteRight);
        if (array[4]) ui->lineEdit_4->setPalette(paletteWrong);
        else ui->lineEdit_4->setPalette(paletteRight);

        if (position == "Врач")
        {
            if (array[5]) ui->lineEdit_5->setPalette(paletteWrong);
            else ui->lineEdit_5->setPalette(paletteRight);
            if (array[6]) ui->lineEdit_6->setPalette(paletteWrong);
            else ui->lineEdit_6->setPalette(paletteRight);
        }
        else if (position == "Кассир")
        {
            if (array[7]) ui->lineEdit_5->setPalette(paletteWrong);
            else ui->lineEdit_5->setPalette(paletteRight);
            if (array[8]) ui->lineEdit_6->setPalette(paletteWrong);
            else ui->lineEdit_6->setPalette(paletteRight);
        }
        else if (position == "Охранник")
        {
            if (array[9]) ui->lineEdit_6->setPalette(paletteWrong);
            else ui->lineEdit_6->setPalette(paletteRight);
        }

        if (array[10]) return;

        Tmp = Head;
        int checkcode = 0;
        do
        {
            if (Tmp->getName() == organization)
            {
                Worker *This = Tmp->gethead();
                if (This)
                {
                    do
                    {
                        if (This->getCode() == code.toInt())
                        {
                            if (organization == cen_ter && code.toInt() == co_de) checkcode = 0;
                            else checkcode = 1;
                            break;
                        }
                        This = This->getNext();
                    }
                    while(This != Tmp->gethead());
                }
                break;
            }
            Tmp = Tmp->getNext();
        }
        while(Tmp != Head);

        if (checkcode)
        {
            ui->lineEdit_8->setPalette(paletteWrong);
            QMessageBox box;
            box.setWindowTitle("ОШИБКА!");
            box.setText("Сотрудник с таким кодом уже есть!");
            box.setIcon(QMessageBox::Warning);
            box.exec();
            return;
        }

        Tmp = Head;

        if (organization == cen_ter)
        {
            do
            {
                if (Tmp->getName() == cen_ter)
                {
                    Worker *This = Tmp->gethead();
                    do
                    {
                        if (This->getCode() == co_de)
                        {
                            if (position == pos_ition)
                            {
                                This->setCode(code.toInt());
                                This->setSurname(surname);
                                This->setName(name);
                                This->setPatronymic(patronymic);
                                This->setSex(sex);
                                This->setBirthday(day,month,year);
                                This->setCenter(cen_ter);
                                This->setPosition(position);
                                This->setSalary(salary.toInt());
                                QString Pos = This->getPosition();
                                if (Pos == "Врач")
                                {
                                    dynamic_cast<Doctor*>(This)->setSpecialization(specialization);
                                    dynamic_cast<Doctor*>(This)->setExperience(experience.toInt());
                                    dynamic_cast<Doctor*>(This)->setCategory(category.toInt());
                                }
                                else if (Pos == "Кассир")
                                {
                                    dynamic_cast<Cashier*>(This)->setExperience(experience1.toInt());
                                    dynamic_cast<Cashier*>(This)->setHiM(hours_in_month.toInt());
                                }
                                else
                                {
                                    dynamic_cast<Security*>(This)->setRank(rank.toInt());
                                    dynamic_cast<Security*>(This)->setOrganization(organization);
                                }
                                New = This;
                            }
                            else
                            {
                                if (position == "Врач")
                                    New = new Doctor(code.toInt(),surname,name,patronymic,sex,day,month,year,cen_ter,position,salary.toInt(),specialization,experience.toInt(),category.toInt());
                                else if (position == "Кассир")
                                    New = new Cashier(code.toInt(),surname,name,patronymic,sex,day,month,year,cen_ter,position,salary.toInt(),experience1.toInt(),hours_in_month.toInt());
                                else
                                    New = new Security(code.toInt(),surname,name,patronymic,sex,day,month,year,cen_ter,position,salary.toInt(),rank.toInt(),organization);

                                Worker *Link = Tmp->gethead();
                                This->Delete(&Link);
                                Tmp->sethead(&Link);
                                Link = Tmp->gethead();
                                New->Add(&Link);
                                Tmp->sethead(&Link);
                            }
                            break;
                        }
                        This = This->getNext();
                    }
                    while(This != Tmp->gethead());
                    break;
                }
                Tmp = Tmp->getNext();
            }
            while(Tmp != Head);
        }
        else
        {
            do
            {
                if (Tmp->getName() == cen_ter)
                {
                    Worker *This = Tmp->gethead();
                    do
                    {
                        if (This->getCode() == co_de)
                        {
                            Worker *Link = Tmp->gethead();
                            This->Delete(&Link);
                            Tmp->sethead(&Link);
                            break;
                        }
                        This = This->getNext();
                    }
                    while(This != Tmp->gethead());
                    break;
                }
                Tmp = Tmp->getNext();
            }
            while(Tmp != Head);

            if (position == "Врач")
                New = new Doctor(code.toInt(),surname,name,patronymic,sex,day,month,year,organization,position,salary.toInt(),specialization,experience.toInt(),category.toInt());
            else if (position == "Кассир")
                New = new Cashier(code.toInt(),surname,name,patronymic,sex,day,month,year,organization,position,salary.toInt(),experience1.toInt(),hours_in_month.toInt());
            else
                New = new Security(code.toInt(),surname,name,patronymic,sex,day,month,year,organization,position,salary.toInt(),rank.toInt(),organization);

            Tmp = Head;
            do
            {
                if (Tmp->getName() == organization)
                {
                    Worker *Link = Tmp->gethead();
                    New->Add(&Link);
                    Tmp->sethead(&Link);
                    break;
                }
                Tmp = Tmp->getNext();
            }
            while(Tmp != Head);
        }

        ui->tableWidget->item(row_num,0)->setText(QString::number(New->getCode()));
        ui->tableWidget->item(row_num,1)->setText(New->getSurname());
        ui->tableWidget->item(row_num,2)->setText(New->getName());
        ui->tableWidget->item(row_num,3)->setText(New->getPatronymic());
        ui->tableWidget->item(row_num,4)->setText(New->getSex());
        ui->tableWidget->item(row_num,5)->setText(New->getBirthday());
        ui->tableWidget->item(row_num,6)->setText("Название: " + New->getCenter() + "\nАдрес: " + Tmp->getAddress() + "\nТелефон: " + Tmp->getPhoneNumber());
        ui->tableWidget->item(row_num,7)->setText(New->getPosition());
        ui->tableWidget->item(row_num,8)->setText(QString::number(New->getSalary()));
        if (position == "Врач")
            ui->tableWidget->setItem(row_num,9,new QTableWidgetItem("Специализация: " + dynamic_cast<Doctor*>(New)->getSpecialization() + "\nОпыт: " + \
                                                                QString::number(dynamic_cast<Doctor*>(New)->getExperience()) + \
                                                                "\nКатегория: " + QString::number(dynamic_cast<Doctor*>(New)->getCategory())));
        else if (position == "Кассир")
            ui->tableWidget->setItem(row_num,9,new QTableWidgetItem("Опыт: " + QString::number(dynamic_cast<Cashier*>(New)->getExperience()) + \
                                                                "\nРаботает часов/месяц: " + QString::number(dynamic_cast<Cashier*>(New)->getHiM())));
        else
            ui->tableWidget->setItem(row_num,9,new QTableWidgetItem("Ранг: " + QString::number(dynamic_cast<Security*>(New)->getRank()) + \
                                                                "\nФирма охраны: " + dynamic_cast<Security*>(New)->getOrganization()));

        on_pushButton_8_clicked();

    }
    else if (!ui->comboBox_8->isHidden())//Delete Center
    {
        if (!Head)
        {
            QMessageBox box;
            box.setWindowTitle("ОШИБКА!");
            box.setText("Нет ни одного центра!");
            box.setIcon(QMessageBox::Warning);
            box.exec();
            return;
        }

        QString center = ui->comboBox_8->currentText();

        Med_Center *Tmp = Head;
        do
        {
            if (Tmp->getName() == center)
            {
                if (Tmp->gethead())
                {
                    QMessageBox *box = new QMessageBox(QMessageBox::Warning,"Предупреждение",\
                                                       "В данном центре есть сотрудники. При удалении центра данные о них тоже будут удалены. Продолжить?",\
                                                       QMessageBox::Ok | QMessageBox::No);
                    box->setButtonText(QMessageBox::Ok,"Да");
                    box->setButtonText(QMessageBox::No,"Нет");
                    int res = box->exec();
                    switch(res)
                    {
                        case QMessageBox::Ok:
                        {
                            Worker* This = Tmp->gethead()->getNext(), *Next;
                            Tmp->gethead()->setNext(nullptr);
                            do
                            {
                                Next = This->getNext();
                                delete This;
                                This = Next;
                            } while (Next);
                            int row = ui->tableWidget->rowCount(), i;
                            for(i=0;i<row;i++)
                            {
                                QString org = ui->tableWidget->item(i,6)->text();
                                org = org.left(org.indexOf('\n'));
                                org = org.right(org.size()-10);
                                if (org == center)
                                {
                                    ui->tableWidget->removeRow(i);
                                    i--;
                                    row = ui->tableWidget->rowCount();
                                }
                            }
                            break;
                        }
                        case QMessageBox::No: return;
                    }
                }
                Tmp->Delete(&Head);
                ui->comboBox->removeItem(ui->comboBox->findText(center));

                break;
            }
            Tmp = Tmp->getNext();
        }
        while(Tmp != Head);

        ui->comboBox_8->removeItem(ui->comboBox_8->findText(center));
    }
    else if (!ui->comboBox_7->isHidden())//Edit Center
    {
        if (!Head)
        {
            QMessageBox box;
            box.setWindowTitle("ОШИБКА!");
            box.setText("Нет ни одного центра!");
            box.setIcon(QMessageBox::Warning);
            box.exec();
            return;
        }

        Med_Center *Tmp = Head;
        QString name, address, phone;
        int flag = 0;

        name = ui->lineEdit->text();
        if (!name.size())
        {
            flag = 1;
            ui->lineEdit->setPalette(paletteWrong);
        }
        else ui->lineEdit->setPalette(paletteRight);

        int checkname = 0;
        do
        {
            QString NAME = Tmp->getName();
            if (NAME == name && NAME != na_me)
            {
                checkname = 1;
                flag = 1;
                ui->lineEdit->setPalette(paletteWrong);
                QMessageBox box;
                box.setWindowTitle("ОШИБКА!");
                box.setText("Центр с таким названием уже есть!");
                box.setIcon(QMessageBox::Warning);
                box.exec();
                break;
            }
            Tmp = Tmp->getNext();
        }
        while(Tmp != Head);
        if (!checkname) ui->lineEdit->setPalette(paletteRight);

        address = ui->lineEdit_2->text();
        if (!address.size())
        {
            flag = 1;
            ui->lineEdit_2->setPalette(paletteWrong);
        }
        ui->lineEdit_2->setPalette(paletteRight);

        phone = ui->lineEdit_3->text();
        if (!CheckRightNumber(phone))
        {
            flag = 1;
            ui->lineEdit_3->setPalette(paletteWrong);
        }
        ui->lineEdit_3->setPalette(paletteRight);

        if (flag) return;

        do
        {
            if (Tmp->getName() == na_me)
            {
                Tmp->setName(name);
                Tmp->setAddress(address);
                Tmp->setPhoneNumber(phone);
                break;
            }
            Tmp = Tmp->getNext();
        }
        while(Tmp != Head);

        int row = ui->tableWidget->rowCount();
        for(int i=0;i<row;i++)
        {
            QString org = ui->tableWidget->item(i,6)->text();
            org = org.left(org.indexOf('\n'));
            org = org.right(org.size()-10);
            if (org == na_me)
            {
                ui->tableWidget->item(i,6)->setText("Название: " + name + "\nАдрес: " + address + "\nТелефон: " + phone);
            }
        }
        ui->comboBox->removeItem(ui->comboBox->findText(na_me));
        ui->comboBox->addItem(name);

        ui->lineEdit->hide();
        ui->lineEdit_2->hide();
        ui->lineEdit_3->hide();
        ui->label_14->setText("Код: ");
        ui->label_14->hide();
        ui->label->setText("");
        ui->label_2->setText("");
        ui->label_3->setText("");
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_17->show();
        ui->pushButton_4->show();
        ui->pushButton_18->show();
        ui->pushButton_5->show();
        ui->pushButton_6->show();
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->pushButton_7->hide();
        ui->pushButton_8->hide();
        ui->label_15->show();
    }

    ui->comboBox_2->setCurrentIndex(0);
    ui->lineEdit_5->hide();
    ui->lineEdit_6->hide();
    ui->lineEdit_7->hide();
    ui->pushButton_13->hide();
    ui->pushButton_14->hide();
    ui->pushButton_15->hide();
    ui->comboBox_3->hide();
    ui->comboBox_4->hide();
    ui->comboBox_7->hide();
    ui->label_9->hide();
    ui->label_10->hide();
    ui->label_11->hide();
}


void MainWindow::on_pushButton_8_clicked()//Cancel
{
    QPalette palette;
    palette.setColor(QPalette::Base,Qt::white);
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit->setDisabled(0);
    ui->lineEdit_2->setDisabled(0);
    ui->lineEdit_3->setDisabled(0);
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit->setPalette(palette);
    ui->lineEdit_2->setPalette(palette);
    ui->lineEdit_3->setPalette(palette);
    ui->lineEdit_4->setPalette(palette);
    ui->lineEdit_5->setPalette(palette);
    ui->lineEdit_6->setPalette(palette);
    ui->lineEdit_7->setPalette(palette);
    ui->lineEdit_8->setPalette(palette);
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->lineEdit_5->hide();
    ui->lineEdit_6->hide();
    ui->lineEdit_7->hide();
    ui->lineEdit_8->hide();

    ui->label->setText("");
    ui->label_2->setText("");
    ui->label_3->setText("");
    ui->label_4->setText("");
    ui->label_5->setText("");
    ui->label_6->setText("");
    ui->label_7->setText("");
    ui->label_8->setText("");
    ui->label_9->setText("");
    ui->label_10->setText("");
    ui->label_11->setText("");
    ui->label_14->setText("Код:");
    ui->label_14->hide();
    ui->label_15->show();

    ui->radioButton->setChecked(0);
    ui->radioButton_2->setChecked(0);
    ui->radioButton->hide();
    ui->radioButton_2->hide();

    ui->dateEdit->clear();
    ui->dateEdit->hide();

    ui->comboBox->hide();
    ui->comboBox_2->setCurrentText("");
    ui->comboBox_2->hide();
    ui->comboBox_3->hide();
    ui->comboBox_4->hide();
    ui->comboBox_5->setCurrentText("");
    ui->comboBox_5->hide();
    ui->comboBox_6->clear();
    ui->comboBox_6->hide();
    ui->comboBox_7->hide();
    ui->comboBox_8->hide();
    ui->comboBox_8->clear();

    ui->pushButton->show();
    ui->pushButton_2->show();
    ui->pushButton_3->show();
    ui->pushButton_4->show();
    ui->pushButton_5->show();
    ui->pushButton_6->show();
    ui->pushButton_17->show();
    ui->pushButton_18->show();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();
    ui->pushButton_10->hide();
    ui->pushButton_11->hide();
    ui->pushButton_12->hide();
    ui->pushButton_13->hide();
    ui->pushButton_14->hide();
    ui->pushButton_15->hide();
    ui->pushButton_16->hide();

    cen_ter = "";
    co_de = -1;
    row_num = -1;
    pos_ition = "";
}


void SaveData(string pathname)//Save Data In File
{
    int flag = 0;
    was_saved = 1;
    string extension = pathname.substr(pathname.rfind(".")+1);
    Med_Center *Tmp = Head;
    if (extension == "txt")
    {
        ofstream file(pathname, ios::binary);
        do
        {
            if (Tmp->gethead())
            {
                Worker *This = Tmp->gethead();
                do
                {
                    QString position = This->getPosition();
                    file<<This->getCode()<<";"<<This->getSurname().toStdString()<<";"<<This->getName().toStdString()<<";"<<This->getPatronymic().toStdString()\
                       <<";"<<This->getSex().toStdString()<<";"<<This->getBirthday().toStdString()<<";"<<Tmp->getName().toStdString()<<";"<<Tmp->getAddress().toStdString()\
                       <<";"<<Tmp->getPhoneNumber().toStdString()<<";"<<position.toStdString()<<";"<<This->getSalary()<<";";
                    if (position == "Врач")
                        file<<dynamic_cast<Doctor*>(This)->getSpecialization().toStdString()<<";"<<dynamic_cast<Doctor*>(This)->getExperience()<<";"\
                           <<dynamic_cast<Doctor*>(This)->getCategory()<<endl;
                    else if (position == "Охранник")
                        file<<dynamic_cast<Security*>(This)->getRank()<<";"<<dynamic_cast<Security*>(This)->getOrganization().toStdString()<<endl;
                    else file<<dynamic_cast<Cashier*>(This)->getExperience()<<";"<<dynamic_cast<Cashier*>(This)->getHiM()<<endl;
                    This = This->getNext();
                }
                while(This != Tmp->gethead());
            }
            else flag = 1;
            Tmp = Tmp->getNext();
        }
        while(Tmp != Head);
        file.close();
    }
    else if (extension == "xlsx" || extension =="xls")
    {
        QAxObject *excel = new QAxObject("Excel.Application",0);
        excel->dynamicCall("SetVisible(bool)",0);
        QAxObject *workbooks = excel->querySubObject("Workbooks");
        QAxObject *workbook = workbooks->querySubObject("Open(const QString&)",QString::fromStdString(pathname));
        QAxObject *sheets = workbook->querySubObject("Worksheets");
        QAxObject *sheet = sheets->querySubObject("Item(int)",1);
        QAxObject *worksheet = workbook->querySubObject("WorkSheets(int)",1);
        QAxObject *usedrange = worksheet->querySubObject("UsedRange");
        QAxObject *rows = usedrange->querySubObject("Rows");
        QAxObject *columns = usedrange->querySubObject("Columns");
        QAxObject *cell;
        int row = 0;

        int intCols = columns->property("Count").toInt();
        int intRows = rows->property("Count").toInt();

        for(int i=0;i<intRows;i++)
        {
            for(int j=0;j<intCols;j++)
            {
                cell = sheet->querySubObject("Cells(int,int)",i+1,j+1);
                cell-> dynamicCall("ClearContents ()");
            }
        }

        do
        {
            if (Tmp->gethead())
            {
                Worker *This = Tmp->gethead();
                do
                {
                    row++;
                    cell = sheet->querySubObject("Cells(int,int)",row,1);
                    cell->dynamicCall("SetValue(const QVariant&)",This->getCode());
                    cell = sheet->querySubObject("Cells(int,int)",row,2);
                    cell->dynamicCall("SetValue(const QVariant&)",This->getSurname());
                    cell = sheet->querySubObject("Cells(int,int)",row,3);
                    cell->dynamicCall("SetValue(const QVariant&)",This->getName());
                    cell = sheet->querySubObject("Cells(int,int)",row,4);
                    cell->dynamicCall("SetValue(const QVariant&)",This->getPatronymic());
                    cell = sheet->querySubObject("Cells(int,int)",row,5);
                    cell->dynamicCall("SetValue(const QVariant&)",This->getSex());
                    cell = sheet->querySubObject("Cells(int,int)",row,6);
                    cell->dynamicCall("SetValue(const QVariant&)",This->getBirthday());
                    cell = sheet->querySubObject("Cells(int,int)",row,7);
                    cell->dynamicCall("SetValue(const QVariant&)","Название: " + This->getCenter() + "\nАдрес: " + Tmp->getAddress() + "\nТелефон: " + Tmp->getPhoneNumber());
                    cell = sheet->querySubObject("Cells(int,int)",row,8);
                    cell->dynamicCall("SetValue(const QVariant&)",This->getPosition());
                    cell = sheet->querySubObject("Cells(int,int)",row,9);
                    cell->dynamicCall("SetValue(const QVariant&)",This->getSalary());
                    QString Pos = This->getPosition();
                    if (Pos == "Врач")
                    {
                        cell = sheet->querySubObject("Cells(int,int)",row,10);
                        cell->dynamicCall("SetValue(const QVariant&)",dynamic_cast<Doctor*>(This)->getSpecialization());
                        cell = sheet->querySubObject("Cells(int,int)",row,11);
                        cell->dynamicCall("SetValue(const QVariant&)",dynamic_cast<Doctor*>(This)->getExperience());
                        cell = sheet->querySubObject("Cells(int,int)",row,12);
                        cell->dynamicCall("SetValue(const QVariant&)",dynamic_cast<Doctor*>(This)->getCategory());
                    }
                    else if (Pos == "Кассир")
                    {
                        cell = sheet->querySubObject("Cells(int,int)",row,10);
                        cell->dynamicCall("SetValue(const QVariant&)",dynamic_cast<Cashier*>(This)->getExperience());
                        cell = sheet->querySubObject("Cells(int,int)",row,11);
                        cell->dynamicCall("SetValue(const QVariant&)",dynamic_cast<Cashier*>(This)->getHiM());
                    }
                    else
                    {
                        cell = sheet->querySubObject("Cells(int,int)",row,10);
                        cell->dynamicCall("SetValue(const QVariant&)",dynamic_cast<Security*>(This)->getRank());
                        cell = sheet->querySubObject("Cells(int,int)",row,11);
                        cell->dynamicCall("SetValue(const QVariant&)",dynamic_cast<Security*>(This)->getOrganization());
                    }
                    This = This->getNext();
                }
                while(This != Tmp->gethead());
            }
            else flag=1;
            Tmp = Tmp->getNext();
        }
        while(Tmp != Head);

        workbooks->dynamicCall("Close()");
        excel->dynamicCall("Close()");

        delete cell;
        delete columns;
        delete rows;
        delete usedrange;
        delete worksheet;
        delete sheet;
        delete sheets;
        delete workbook;
        delete workbooks;
        delete excel;
    }
    if (flag)
    {
        QMessageBox box;
        box.setWindowTitle("Предупреждение!");
        if (flag==1) box.setText("Один из центров не был сохранён в файл, поскольку не содержит ни одного работника.");
        else box.setText("Несколько центрв не были сохранены в файл, поскольку не содержат ни одного работника.");
        box.setIcon(QMessageBox::Warning);
        box.exec();
    }
}


int MainWindow::on_action_triggered() //Create
{
    if (!was_saved && Head)
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,"Предупреждение",\
                "Старые данные будут утеряны. Хотите сохранить?",QMessageBox::Ok | QMessageBox::Cancel | QMessageBox::No);
        box->setButtonText(QMessageBox::Ok,"Да");
        box->setButtonText(QMessageBox::No,"Нет");
        box->setButtonText(QMessageBox::Cancel,"Отмена");
        int res = box->exec();
        switch(res)
        {
            case QMessageBox::Ok:
            {
                QString filename = QFileDialog::getSaveFileName(0,"Выбор файла","C:\\Users\\shely\\Desktop",tr("TXT (*.txt);; EXCL (*xlsx)"));
                if(filename.isEmpty()&& filename.isNull()) return 1;
                SaveData(filename.toStdString());
                break;
            }
            case QMessageBox::Cancel: return 1;
        }
    }
    path = "";
    first_time = 0;
    check[0] = check[1] = 0;
    was_saved = 0;
    ui->comboBox->clear();
    if (Head)
    {
        Med_Center* Tmp = Head->getNext(), *Link;
        Head->setNext(nullptr);
        do
        {
            Link = Tmp->getNext();
            if (Tmp->gethead())
            {
                Worker* This = Tmp->gethead()->getNext(), *Next;
                Tmp->gethead()->setNext(nullptr);
                do
                {
                    Next = This->getNext();
                    delete This;
                    This = Next;
                } while (Next);
            }
            delete Tmp;
            Tmp = Link;
        } while (Link);
        Head = nullptr;

        ui->tableWidget->setRowCount(0);
    }
    return 0;
}


void MainWindow::on_action_2_triggered() //Open
{
    int res = on_action_triggered();
    if (res==1) return;

    QString filepath = QFileDialog::getOpenFileName(0,"Выбор файла","C:\\Users\\shely\\Desktop",tr("TXT (*.txt);; EXCL (*xlsx)"));
    QString code, name, surname, patronymic, sex, birthday, center_name, center_address, center_phone, position, salary, add1, add2, add3;
    string extension = filepath.toStdString().substr(filepath.toStdString().rfind(".")+1);
    int flag = 0, day, month, year;
    int *array = new int[11]{};

    was_saved = 0;
    if (!first_time)
    {
        check[0] = 1;
        path = filepath;
        first_time++;
    }
    else
    {
        if (filepath != path) check[1] = 1;
    }

    if (extension == "txt")
    {
        fstream file(filepath.toStdString(), ios::in | ios::out | ios::binary);
        string str;

        while(getline(file,str))
        {
            code = QString::fromStdString(str.substr(0,str.find(";")));
            str = str.substr(str.find(";")+1);
            if (!CheckRightNumber(code))
            {
                flag = 1;
                continue;
            }

            surname = QString::fromStdString(str.substr(0,str.find(";")));
            str = str.substr(str.find(";")+1);
            if (!CheckRightText(surname))
            {
                flag = 1;
                continue;
            }

            name = QString::fromStdString(str.substr(0,str.find(";")));
            str = str.substr(str.find(";")+1);
            if (!CheckRightText(name))
            {
                flag = 1;
                continue;
            }

            patronymic = QString::fromStdString(str.substr(0,str.find(";")));
            str = str.substr(str.find(";")+1);
            if (!CheckRightText(patronymic))
            {
                flag = 1;
                continue;
            }

            sex = QString::fromStdString(str.substr(0,str.find(";")));
            str = str.substr(str.find(";")+1);
            if (!CheckRightText(sex))
            {
                flag = 1;
                continue;
            }

            birthday = QString::fromStdString(str.substr(0,str.find(";")));
            str = str.substr(str.find(";")+1);
            int check = 0;
            for(int i=0;i<birthday.size();i++)
                if (!birthday[i].isDigit() && birthday[i]!='.')
                {
                    check = 1;
                    break;
                }
            if (check)
            {
                flag = 1;
                continue;
            }
            day = birthday.left(2).toInt();
            birthday = birthday.right(7);
            month = birthday.left(2).toInt();
            birthday = birthday.right(4);
            year = birthday.toInt();

            center_name = QString::fromStdString(str.substr(0,str.find(";")));
            str = str.substr(str.find(";")+1);

            if (Head)///Проверка на существование такого кода
            {
                int checkcode = 0;
                Med_Center *Tmp = Head;
                do
                {
                    if (Tmp->getName() == center_name)
                    {
                        if (Tmp->gethead())
                        {
                            Worker *This = Tmp->gethead();
                            do
                            {
                                if (This->getCode() == code.toInt())
                                {
                                    flag = 1;
                                    checkcode = 1;
                                    break;
                                }
                                This = This->getNext();
                            }
                            while(This != Tmp->gethead());
                        }
                        break;
                    }
                    Tmp = Tmp->getNext();
                }
                while(Tmp != Head);
                if (checkcode) continue;
            }

            center_address = QString::fromStdString(str.substr(0,str.find(";")));
            str = str.substr(str.find(";")+1);

            center_phone = QString::fromStdString(str.substr(0,str.find(";")));
            str = str.substr(str.find(";")+1);
            if(!CheckRightNumber(center_phone))
            {
                flag = 1;
                continue;
            }

            position = QString::fromStdString(str.substr(0,str.find(";")));
            str = str.substr(str.find(";")+1);
            if(!CheckRightText(position))
            {
                flag = 1;
                continue;
            }

            salary = QString::fromStdString(str.substr(0,str.find(";")));
            str = str.substr(str.find(";")+1);
            if (!CheckRightNumber(salary))
            {
                flag = 1;
                continue;
            }

            if (position == "Врач")
            {
                add1 = QString::fromStdString(str.substr(0,str.find(";")));
                str = str.substr(str.find(";")+1);
                if (!CheckRightText(add1))
                {
                    flag = 1;
                    continue;
                }

                add2 = QString::fromStdString(str.substr(0,str.find(";")));
                str = str.substr(str.find(";")+1);
                if (!CheckRightNumber(add2))
                {
                    flag = 1;
                    continue;
                }

                add3 = QString::fromStdString(str);
                if (!CheckRightNumber(add3))
                {
                    flag = 1;
                    continue;
                }
            }
            else if (position == "Охранник")
            {
                add1 = QString::fromStdString(str.substr(0,str.find(";")));
                str = str.substr(str.find(";")+1);
                if (!CheckRightNumber(add1))
                {
                    flag = 1;
                    continue;
                }

                add2 = QString::fromStdString(str);
            }
            else if (position == "Кассир")
            {
                add1 = QString::fromStdString(str.substr(0,str.find(";")));
                str = str.substr(str.find(";")+1);
                if (!CheckRightNumber(add1))
                {
                    flag = 1;
                    continue;
                }

                add2 = QString::fromStdString(str);
                if (!CheckRightNumber(add2))
                {
                    flag = 1;
                    continue;
                }
            }
            else
            {
                flag = 1;
                continue;
            }

            int exists = 0;
            if (Head)
            {
                Med_Center *Tmp = Head;
                do
                {
                    if (Tmp->getName() == center_name)
                    {
                        Worker *This = Tmp->gethead(), *New;
                        if (position == "Врач") New = new Doctor(code.toInt(), surname, name, patronymic, sex, day, month, year, center_name, position, salary.toInt(), add1, add2.toInt(), add3.toInt());
                        else if (position == "Кассир") New = new Cashier(code.toInt(), surname, name, patronymic, sex, day, month, year, center_name, position, salary.toInt(), add1.toInt(), add2.toInt());
                        else New = new Security(code.toInt(), surname, name, patronymic, sex, day, month, year, center_name, position, salary.toInt(), add1.toInt(), add2);
                        New->Add(&This);
                        Tmp->sethead(&This);
                        int row = ui->tableWidget->rowCount();
                        ui->tableWidget->insertRow(row);
                        Show(New,Tmp,row);
                        exists = 1;
                        break;
                    }
                    Tmp = Tmp->getNext();
                }
                while(Tmp != Head);
            }

            if (!exists)
            {
                Med_Center *New_Center = new Med_Center(center_name,center_address,center_phone);
                New_Center->Add(&Head);
                Worker *Link = New_Center->gethead(), *New;
                if (position == "Врач") New = new Doctor(code.toInt(), surname, name, patronymic, sex, day, month, year, center_name, position, salary.toInt(), add1, add2.toInt(), add3.toInt());
                else if (position == "Кассир") New = new Cashier(code.toInt(), surname, name, patronymic, sex, day, month, year, center_name, position, salary.toInt(), add1.toInt(), add2.toInt());
                else New = new Security(code.toInt(), surname, name, patronymic, sex, day, month, year, center_name, position, salary.toInt(), add1.toInt(), add2);
                New->Add(&Link);
                New_Center->sethead(&Link);
                int row = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(row);
                Show(New,New_Center,row);
            }

            if (ui->comboBox->findText(center_name)==-1) ui->comboBox->addItem(center_name);
        }
        file.close();
    }
    else if (extension == "xlsx" || extension == "xls")
    {
        QAxObject *excel = new QAxObject("Excel.Application",this);
        QAxObject *workbooks = excel->querySubObject("Workbooks");
        QAxObject *workbook = workbooks->querySubObject("Open(const QString&)",filepath);
        excel->dynamicCall("SetVisible(bool)",0);

        QAxObject *worksheet = workbook->querySubObject("WorkSheets(int)",1);

        QAxObject *usedrange = worksheet->querySubObject("UsedRange");
        QAxObject *rows = usedrange->querySubObject("Rows");
        QAxObject *columns = usedrange->querySubObject("Columns");
        QAxObject *cell;
        QVariant value;

        int intRowStart = usedrange->property("Row").toInt();
        int intColStart = usedrange->property("Column").toInt();
        int intCols = columns->property("Count").toInt();
        int intRows = rows->property("Count").toInt();

        for(int row = 0; row < intRows; row++)
        {
            cell = worksheet->querySubObject("Cells(int,int)",row + 1, 1);
            value = cell->dynamicCall("Value()");
            code = value.toString();
            if (!CheckRightNumber(code))
            {
                flag = 1;
                continue;
            }

            cell = worksheet->querySubObject("Cells(int,int)",row + 1, 2);
            value = cell->dynamicCall("Value()");
            surname = value.toString();
            if (!CheckRightText(surname))
            {
                flag = 1;
                continue;
            }

            cell = worksheet->querySubObject("Cells(int,int)",row + 1, 3);
            value = cell->dynamicCall("Value()");
            name = value.toString();
            if (!CheckRightText(name))
            {
                flag = 1;
                return;
            }

            cell = worksheet->querySubObject("Cells(int,int)",row + 1, 4);
            value = cell->dynamicCall("Value()");
            patronymic = value.toString();
            if (!CheckRightText(patronymic))
            {
                flag = 1;
                continue;
            }

            cell = worksheet->querySubObject("Cells(int,int)",row + 1, 5);
            value = cell->dynamicCall("Value()");
            sex = value.toString();
            if (!CheckRightText(sex))
            {
                flag = 1;
                continue;
            }

            cell = worksheet->querySubObject("Cells(int,int)",row + 1, 6);
            value = cell->dynamicCall("Value()");
            birthday = value.toString();
            birthday = birthday.left(10);

            int check = 0;
            for(int j=0;j<birthday.size();j++)
                if (!birthday[j].isDigit() && birthday[j]!='-')
                {
                    check = 1;
                    break;
                }
            if (check)
            {
                flag = 1;
                continue;
            }
            year = birthday.left(4).toInt();
            birthday = birthday.right(5);
            month = birthday.left(2).toInt();
            day = birthday.right(2).toInt();

            cell = worksheet->querySubObject("Cells(int,int)",row + 1, 7);
            value = cell->dynamicCall("Value()");
            QString info = value.toString();
            center_name = info.left(info.indexOf("\n"));
            center_name = center_name.right(center_name.size()-10);
            info = info.right(info.size()-info.indexOf("\n")-1);
            center_address = info.left(info.indexOf("\n"));
            center_address = center_address.right(center_address.size()-7);
            info = info.right(info.size()-info.indexOf("\n")-1);
            center_phone = info.right(info.size()-9);
            if(!CheckRightNumber(center_phone))
            {
                flag = 1;
                continue;
            }

            if (Head)///Проверка на существование такого кода
            {
                int checkcode = 0;
                Med_Center *Tmp = Head;
                do
                {
                    if (Tmp->getName() == center_name)
                    {
                        if (Tmp->gethead())
                        {
                            Worker *This = Tmp->gethead();
                            do
                            {
                                if (This->getCode() == code.toInt())
                                {
                                    flag = 1;
                                    checkcode = 1;
                                    break;
                                }
                                This = This->getNext();
                            }
                            while(This != Tmp->gethead());
                        }
                        break;
                    }
                    Tmp = Tmp->getNext();
                }
                while(Tmp != Head);
                if (checkcode) continue;
            }

            cell = worksheet->querySubObject("Cells(int,int)",row + 1, 8);
            value = cell->dynamicCall("Value()");
            position = value.toString();
            if(!CheckRightText(position))
            {
                flag = 1;
                continue;
            }

            cell = worksheet->querySubObject("Cells(int,int)",row + 1, 9);
            value = cell->dynamicCall("Value()");
            salary = value.toString();
            if (!CheckRightNumber(salary))
            {
                flag = 1;
                continue;
            }

            if (position == "Врач")
            {
                cell = worksheet->querySubObject("Cells(int,int)",row + 1, 10);
                value = cell->dynamicCall("Value()");
                add1 = value.toString();
                if (!CheckRightText(add1))
                {
                    flag = 1;
                    continue;
                }

                cell = worksheet->querySubObject("Cells(int,int)",row + 1, 11);
                value = cell->dynamicCall("Value()");
                add2 = value.toString();
                if (!CheckRightNumber(add2))
                {
                    flag = 1;
                    continue;
                }

                cell = worksheet->querySubObject("Cells(int,int)",row + 1, 12);
                value = cell->dynamicCall("Value()");
                add3 = value.toString();
                if (!CheckRightNumber(add3))
                {
                    flag = 1;
                    continue;
                }

            }
            else if (position == "Охранник")
            {
                cell = worksheet->querySubObject("Cells(int,int)",row + 1, 10);
                value = cell->dynamicCall("Value()");
                add1 = value.toString();
                if (!CheckRightNumber(add1))
                {
                    flag = 1;
                    continue;
                }

                cell = worksheet->querySubObject("Cells(int,int)",row + 1, 11);
                value = cell->dynamicCall("Value()");
                add2 = value.toString();
            }
            else if (position == "Кассир")
            {
                cell = worksheet->querySubObject("Cells(int,int)",row + 1, 10);
                value = cell->dynamicCall("Value()");
                add1 = value.toString();
                if (!CheckRightNumber(add1))
                {
                    flag = 1;
                    continue;
                }

                cell = worksheet->querySubObject("Cells(int,int)",row + 1, 11);
                value = cell->dynamicCall("Value()");
                add2 = value.toString();
                if (!CheckRightNumber(add2))
                {
                    flag = 1;
                    continue;
                }
            }
            else
            {
                flag = 1;
                continue;
            }

            int exists = 0;
            if (Head)
            {
                Med_Center *Tmp = Head;
                do
                {
                    if (Tmp->getName() == center_name)
                    {
                        Worker *This = Tmp->gethead(), *New;
                        if (position == "Врач") New = new Doctor(code.toInt(), surname, name, patronymic, sex, day, month, year, center_name, position, salary.toInt(), add1, add2.toInt(), add3.toInt());
                        else if (position == "Кассир") New = new Cashier(code.toInt(), surname, name, patronymic, sex, day, month, year, center_name, position, salary.toInt(), add1.toInt(), add2.toInt());
                        else New = new Security(code.toInt(), surname, name, patronymic, sex, day, month, year, center_name, position, salary.toInt(), add1.toInt(), add2);
                        New->Add(&This);
                        Tmp->sethead(&This);
                        int row = ui->tableWidget->rowCount();
                        ui->tableWidget->insertRow(row);
                        Show(New,Tmp,row);
                        exists = 1;
                        break;
                    }
                    Tmp = Tmp->getNext();
                }
                while(Tmp != Head);
            }

            if (!exists)
            {
                Med_Center *New_Center = new Med_Center(center_name,center_address,center_phone);
                New_Center->Add(&Head);
                Worker *Link = New_Center->gethead(), *New;
                if (position == "Врач") New = new Doctor(code.toInt(), surname, name, patronymic, sex, day, month, year, center_name, position, salary.toInt(), add1, add2.toInt(), add3.toInt());
                else if (position == "Кассир") New = new Cashier(code.toInt(), surname, name, patronymic, sex, day, month, year, center_name, position, salary.toInt(), add1.toInt(), add2.toInt());
                else New = new Security(code.toInt(), surname, name, patronymic, sex, day, month, year, center_name, position, salary.toInt(), add1.toInt(), add2);
                New->Add(&Link);
                New_Center->sethead(&Link);
                int row = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(row);
                Show(New,New_Center,row);
            }

            if (ui->comboBox->findText(center_name)==-1) ui->comboBox->addItem(center_name);
        }

        workbook->dynamicCall("Close");
        excel->dynamicCall("Quit");

        delete cell;
        delete columns;
        delete rows;
        delete usedrange;
        delete worksheet;
        delete workbook;
        delete workbooks;
        delete excel;

    }
    if (flag)
    {
        QMessageBox box;
        box.setWindowTitle("ОШИБКА");
        box.setIcon(QMessageBox::Warning);
        box.setText("Не удалось считать всю информацию! В файле есть неверные данные!");
        box.exec();
    }
}


void MainWindow::on_action_4_triggered() //Save
{
    if (Head)
    {
        if (check[1] || (!check[0] && !check[1]))
        {
             QString filename = QFileDialog::getSaveFileName(0,"Выбор файла","C:\\Users\\shely\\Desktop",tr("TXT (*.txt);; EXCL (*xlsx)"));
             if (filename=="") return;
             SaveData(filename.toStdString());
        }
        else SaveData(path.toStdString());
    }
    else
    {
        QMessageBox box;
        box.setWindowTitle("ОШИБКА!");
        box.setIcon(QMessageBox::Warning);
        box.setText("Ни одного центра и ни одного клиента не обнаружено!");
        box.exec();
    }

}


void MainWindow::on_action_5_triggered() //Save As
{
    if (Head)
    {
        QString filename = QFileDialog::getSaveFileName(0,"Выбор файла","C:\\Users\\shely\\Desktop",tr("TXT (*.txt);; EXCL (*xlsx)"));
        if (filename=="") return;
        SaveData(filename.toStdString());
    }
    else
    {
        QMessageBox box;
        box.setWindowTitle("ОШИБКА!");
        box.setIcon(QMessageBox::Warning);
        box.setText("Ни одного центра и ни одного клиента не обнаружено!");
        box.exec();
    }
}


void MainWindow::on_action_8_triggered() //Manual
{
    Man->setWindowTitle("Руководство:");
    Man->show();
}


void MainWindow::on_action_9_triggered() //About Programm
{
    Ab->setWindowTitle("О программе");
    Ab->show();
}


void MainWindow::on_pushButton_9_clicked()
{
    ui->lineEdit->clear();
}


void MainWindow::on_pushButton_10_clicked()
{
    ui->lineEdit_2->clear();
}


void MainWindow::on_pushButton_11_clicked()
{
    ui->lineEdit_3->clear();
}


void MainWindow::on_pushButton_12_clicked()
{
    ui->lineEdit_4->clear();
}


void MainWindow::on_pushButton_13_clicked()
{
    ui->lineEdit_5->clear();
}


void MainWindow::on_pushButton_14_clicked()
{
    ui->lineEdit_6->clear();
}


void MainWindow::on_pushButton_15_clicked()
{
    ui->lineEdit_7->clear();
}


void MainWindow::on_pushButton_16_clicked()
{
    ui->lineEdit_8->clear();
}
