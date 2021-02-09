/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ui_companyinputarea.h>
#include <views/companyinputarea.h>

Q_LOGGING_CATEGORY(jmbdeWidgetsCompanyInputAreaLog, "jmuelbert.jmbde.widgets.compamyinputarea", QtWarningMsg)

CompanyInputArea::CompanyInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::CompanyInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsCompanyInputAreaLog) << "Init CompanyInputArea for Index :" << index.column();

    this->m_companyModel = new Model::Company();
    this->m_db = this->m_companyModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_companyModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper(this);
    m_mapper->setModel(m_model);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

CompanyInputArea::~CompanyInputArea()
{
    delete ui;
}

// TODO change lineEdit to lineEdit_Number
void CompanyInputArea::setMappings()
{
    m_mapper->addMapping(ui->nameLineEdit, this->m_companyModel->getNameIndex());
    m_mapper->addMapping(ui->name2LineEdit, this->m_companyModel->getName2Index());
    m_mapper->addMapping(ui->streetLineEdit, this->m_companyModel->getStreetIndex());
    m_mapper->addMapping(ui->cityLineEdit, this->m_companyModel->getCityIndex());
    m_mapper->addMapping(ui->zipCodeLineEdit, this->m_companyModel->getCityIndex());
    m_mapper->addMapping(ui->phoneNumberLineEdit, this->m_companyModel->getPhoneNumberIndex());
    m_mapper->addMapping(ui->faxNumberLineEdit, this->m_companyModel->getFaxNumberIndex());
    m_mapper->addMapping(ui->mobileNumberLineEdit, this->m_companyModel->getMobileNumberIndex());
    m_mapper->addMapping(ui->mailAddressLineEdit, this->m_companyModel->getMailAddressIndex());
    m_mapper->addMapping(ui->activeCheckBox, this->m_companyModel->getActiveIndex());
    m_mapper->addMapping(ui->employeeIdComboBox, this->m_companyModel->getEmployeeIdIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_companyModel->getLastUpdateIndex());
}

void CompanyInputArea::setViewOnlyMode(bool mode)
{
    ui->nameLineEdit->setDisabled(mode);
    ui->name2LineEdit->setDisabled(mode);
    ui->streetLineEdit->setDisabled(mode);
    ui->cityLineEdit->setDisabled(mode);
    ui->zipCodeLineEdit->setDisabled(mode);
    ui->phoneNumberLineEdit->setDisabled(mode);
    ui->faxNumberLineEdit->setDisabled(mode);
    ui->mobileNumberLineEdit->setDisabled(mode);
    ui->mailAddressLineEdit->setDisabled(mode);
    ui->activeCheckBox->setDisabled(mode);
    // ui->employeeIdComboBox->setDisabled(mode);
}

void CompanyInputArea::createDataset()
{
    qCDebug(jmbdeWidgetsCompanyInputAreaLog) << "Create a new Dataset for ChipCard...";

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

void CompanyInputArea::retrieveDataset(const QModelIndex index)
{
}

void CompanyInputArea::updateDataset(const QModelIndex index)
{
}

void CompanyInputArea::deleteDataset(const QModelIndex index)
{
}

void CompanyInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void CompanyInputArea::on_pushButton_EditFinish_clicked()
{
    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->pushButton_EditFinish->setText(tr("Finish"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsCompanyInputAreaLog) << "Save Data...";

        m_actualMode = Mode::Edit;
        ui->pushButton_EditFinish->setText(tr("Edit"));
        setViewOnlyMode(false);

        m_mapper->submit();
        m_model->database().transaction();
        if (m_model->submitAll()) {
            m_model->database().commit();
            qCDebug(jmbdeWidgetsCompanyInputAreaLog) << "Commit changes for Chipcard Database Table";
            m_model->database().rollback();
        } else {
            m_model->database().rollback();
            QMessageBox::warning(this, tr("jmbde"), tr("The database reported an error: %1").arg(m_model->lastError().text()));
        }

    } break;

    default: {
        qCCritical(jmbdeWidgetsCompanyInputAreaLog) << "Unknown Mode!";
    }
    }
}
