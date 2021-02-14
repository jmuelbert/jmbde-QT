/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_departmentinputarea.h>
#include <views/departmentinputarea.h>

Q_LOGGING_CATEGORY(jmbdeWidgetsDepartmentInputAreaLog, "jmuelbert.jmbde.widgets.departmentinputarea", QtWarningMsg)

DepartmentInputArea::DepartmentInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::DepartmentInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsDepartmentInputAreaLog) << "Init DepartmentInputArea for Index :" << index.column();

    this->m_departmentModel = new Model::Department();
    this->m_db = this->m_departmentModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_departmentModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());

    connect(ui->priorityHorizontalSlider, &QSlider::valueChanged, ui->priorityLCDNumber, &QLCDNumber::intValue);
}

DepartmentInputArea::~DepartmentInputArea()
{
    delete ui;
}

// TODO change lineEdit to lineEdit_Number
void DepartmentInputArea::setMappings()
{
    m_mapper->addMapping(ui->nameLineEdit, this->m_departmentModel->getNameIndex());
    m_mapper->addMapping(ui->priorityHorizontalSlider, this->m_departmentModel->getPriorityIndex());
    m_mapper->addMapping(ui->printerComboBox, this->m_departmentModel->getPrinterIdIndex());
    m_mapper->addMapping(ui->faxComboBox, this->m_departmentModel->getFaxIdIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, m_departmentModel->getLastUpdateIndex());
}

void DepartmentInputArea::setViewOnlyMode(bool mode)
{
    ui->nameLineEdit->setDisabled(mode);
    ui->priorityHorizontalSlider->setDisabled(mode);
    // ui->printerComboBox->setDisabled(mode);
    // ui->faxComboBox->setDisabled(mode);
}

void DepartmentInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsDepartmentInputAreaLog) << "Create a new Dataset for ChipCard...";

    // Set all inputfields to blank
    m_mapper->toLast();

    int row = m_mapper->currentIndex();
    if (row < 0) {
        row = 0;
    }
    m_mapper->submit();
    m_model->insertRow(row);
    m_mapper->setCurrentIndex(row);
}

void DepartmentInputArea::retrieveDataset(const QModelIndex index)
{
}

void DepartmentInputArea::updateDataset(const QModelIndex index)
{
}

void DepartmentInputArea::deleteDataset(const QModelIndex index)
{
}

void DepartmentInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void DepartmentInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->pushButton_EditFinish->setText(tr("Finish"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsDepartmentInputAreaLog) << "Save Data...";

        m_actualMode = Mode::Edit;
        ui->pushButton_EditFinish->setText(tr("Edit"));
        setViewOnlyMode(false);

        QString name = ui->nameLineEdit->text();

        if (name.isEmpty()) {
            QString message(tr("Please provide the chipcard number."));

            QMessageBox::information(this, tr("Add Department"), message);
        } else {
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(jmbdeWidgetsDepartmentInputAreaLog) << "Commit changes for Chipcard Database Table";
                m_model->database().rollback();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("The database reported an error: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCCritical(jmbdeWidgetsDepartmentInputAreaLog) << "Unknown Mode!";
    }
    }
}
