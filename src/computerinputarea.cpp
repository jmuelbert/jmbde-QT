/*
   // ComputerInputArea
   // part of jmbde
   //
   // Copyright (c) 2013-2017 Jürgen Mülbert. All rights reserved.
   //
   // Licensed under the EUPL, Version 1.2 or – as soon they
   // will be approved by the European Commission - subsequent
   // versions of the EUPL (the "Licence");
   // You may not use this work except in compliance with the
   // Licence.
   // You may obtain a copy of the Licence at:
   //
   // https://joinup.ec.europa.eu/page/eupl-text-11-12
   //
   // Unless required by applicable law or agreed to in
   // writing, software distributed under the Licence is
   // distributed on an "AS IS" basis,
   // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
   // express or implied.
   // See the Licence for the specific language governing
   // permissions and limitations under the Licence.
   //
   // Lizenziert unter der EUPL, Version 1.2 oder - sobald
   // diese von der Europäischen Kommission genehmigt wurden -
   // Folgeversionen der EUPL ("Lizenz");
   // Sie dürfen dieses Werk ausschließlich gemäß
   // dieser Lizenz nutzen.
   // Eine Kopie der Lizenz finden Sie hier:
   //
   // https://joinup.ec.europa.eu/page/eupl-text-11-12
   //
   // Sofern nicht durch anwendbare Rechtsvorschriften
   // gefordert oder in schriftlicher Form vereinbart, wird
   // die unter der Lizenz verbreitete Software "so wie sie
   // ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
   // ausdrücklich oder stillschweigend - verbreitet.
   // Die sprachspezifischen Genehmigungen und Beschränkungen
   // unter der Lizenz sind dem Lizenztext zu entnehmen.
   //
 */

#include "computerinputarea.h"
#include "ui_computerinputarea.h"

ComputerInputArea::ComputerInputArea(QWidget* parent)
  : QScrollArea(parent), ui(new Ui::ComputerInputArea) {

  ui->setupUi(this);

  model = new QSqlRelationalTableModel(this);
  model->setTable(QLatin1String("computer"));
  model->setEditStrategy(QSqlTableModel::OnManualSubmit);
  model->select();

  mapper = new QDataWidgetMapper(this);
  mapper->setModel(model);
  mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

  mapper->addMapping(ui->lineEdit_ComputerName,
                     model->fieldIndex(QLatin1String("network_name")));
  mapper->toLast();
  int row = mapper->currentIndex();

  mapper->submit();
  model->insertRow(row);
  mapper->setCurrentIndex(row);

  ui->lineEdit_ComputerName->clear();
  ui->lineEdit_ComputerName->setFocus();
}

ComputerInputArea::ComputerInputArea(QWidget* parent, int index)
  : QScrollArea(parent), ui(new Ui::ComputerInputArea) {
  ui->setupUi(this);

  model = new QSqlRelationalTableModel(this);
  model->setTable(QLatin1String("computer"));
  model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  model->select();

  mapper = new QDataWidgetMapper(this);
  mapper->setModel(model);
  mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

  mapper->addMapping(ui->lineEdit_ComputerName,
                     model->fieldIndex(QLatin1String("network_name")));
  mapper->setCurrentIndex(index);
  ui->lineEdit_ComputerName->setFocus();

}

ComputerInputArea::~ComputerInputArea() {
  delete ui;
}

void ComputerInputArea::on_lineEditComputerName_editingFinished()
{
  qDebug() << "Name : " << ui->lineEdit_ComputerName->text();
}

void ComputerInputArea::submitData() {
  mapper->submit();
  model->database().transaction();
  if (model->submitAll()) {
    model->database().commit();
    qDebug() << "Commit changes for Computer Databse Table";
  }
  else {
    model->database().rollback();
    QMessageBox::warning(this, tr("Cached Table"),
                         tr("The database reported an error: %1")
                         .arg(model->lastError().text()));
  }
}

void ComputerInputArea::on_pushButtonEdit_clicked()
{
    qDebug() << "Click Edit";
}

void ComputerInputArea::on_pushButtonAdd_clicked()
{
    qDebug() << "Click Add";
}
