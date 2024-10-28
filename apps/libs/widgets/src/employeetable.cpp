/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jmbdewidgets/employeetable.h"

#include "ui_employeetable.h"

EmployeeTable::EmployeeTable(QWidget *parent, const QModelIndex &index) : QWidget(parent), ui(new Ui::EmployeeTable)
{
  ui->setupUi(this);

  qDebug() << "Init ComputerInputArea for Index :" << index.column();

  this->m_employeeModel = new Model::Employee();
  this->m_db = this->m_employeeModel->getDB();

  m_actualMode = Mode::Edit;
  setViewOnlyMode(true);

  // Set the Model
  m_model = this->m_employeeModel->initializeRelationalModel();

  m_model->setHeaderData(0, Qt::Horizontal, tr("ID"));
  m_model->setHeaderData(1, Qt::Horizontal, tr("First name"));
  m_model->setHeaderData(2, Qt::Horizontal, tr("Last name"));

  ui->tableView->setModel(m_model);
  ui->tableView->resizeColumnsToContents();

  submitButton = new QPushButton(tr("Submit"));
  submitButton->setDefault(true);
  revertButton = new QPushButton(tr("&Revert"));
  quitButton = new QPushButton(tr("Quit"));

  buttonBox = new QDialogButtonBox(Qt::Vertical);
  buttonBox->addButton(submitButton, QDialogButtonBox::ActionRole);
  buttonBox->addButton(revertButton, QDialogButtonBox::ActionRole);
  buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

  ui->verticalLayout->addWidget(buttonBox);

  connect(submitButton, &QPushButton::clicked, this, &EmployeeTable::submit);
  connect(revertButton, &QPushButton::clicked, m_model, &QSqlTableModel::revertAll);
}

EmployeeTable::~EmployeeTable() { delete ui; }

void EmployeeTable::setMappings()
{
  // Model::Employee *employeeModel = new Model::Employee();
  // Set the fields to the mapper
  // Line 1.
  // m_mapper->addMapping(ui->, employeeModel->getTitleIdIndex());
  // m_mapper->addMapping(ui->comboBox_Gender, employeeModel->getGenderIndex());
}

void EmployeeTable::setViewOnlyMode(bool mode) { qDebug() << tr("mployeeTable::setViewOnlyMode set to: ") << mode; }

void EmployeeTable::createDataset()
{
  // Set all inputfields to blank
  m_mapper->toLast();

  int row = m_mapper->currentIndex();
  if (row < 0) { row = 0; }
  m_mapper->submit();
  m_model->insertRow(row);
  m_mapper->setCurrentIndex(row);
}

void EmployeeTable::retrieveDataset(const QModelIndex index)
{
  qDebug() << tr("EmployeeTable::retrieveDataset set to: ") << index;
}

void EmployeeTable::updateDataset(const QModelIndex index)
{
  qDebug() << tr("EmployeeTable::updateDataset set to: ") << index;
}

void EmployeeTable::deleteDataset(const QModelIndex index)
{
  qDebug() << tr("EmployeeTable::deleteDataset set to: ") << index;
}

// Save the actual data

void EmployeeTable::on_pushButton_Add_clicked()
{
  createDataset();
  on_pushButton_EditFinish_clicked();
}

void EmployeeTable::on_pushButton_EditFinish_clicked()
{
  // Set all inputfields to blank

  switch (m_actualMode) {
  case Mode::Edit: {
    m_actualMode = Mode::Finish;
    // TODO: To Implement
    // ui->pushButton_EditFinish->setText(tr("Fertig"));
    setViewOnlyMode(false);

  } break;

  case Mode::Finish: {
    qDebug() << tr("Die Daten werden gesichert.");

    m_actualMode = Mode::Edit;
    // TODO: To Implement
    // ui->pushButton_EditFinish->setText(tr("Bearbeiten"));
    setViewOnlyMode(false);
    // TODO: To Implement
    // QString lastName = ui->lineEdit_Lastname->text();

    // if (lastName.isEmpty()) {
    //    QString message(tr("Bitte geben Sie den Mitarbeiternamen ein"));

    //    QMessageBox::information(this, tr("Mitarbeiter hinzufügen"), message);
    // } else {
    {
      // TODO: To Implement
      // qCDebug(m_EmployeeTableLog) << tr("Mitarbeiter : ") << ui->lineEdit_Lastname->text();
      m_mapper->submit();
      m_model->database().transaction();
      if (m_model->submitAll()) {
        m_model->database().commit();
        qDebug() << tr("Schreiben der Änderungen in die Datenbank");
      } else {
        m_model->database().rollback();
        QMessageBox::warning(
          this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
      }
    }
  } break;

  default: {
    qDebug() << tr("Fehler");
  }
  }
}

void EmployeeTable ::submit()
{
  m_model->database().transaction();
  if (m_model->submitAll()) {
    m_model->database().commit();
  } else {
    m_model->database().rollback();
    QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
  }
}
