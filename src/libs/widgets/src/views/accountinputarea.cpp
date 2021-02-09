/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "views/accountinputarea.h"

#include "ui_accountinputarea.h"

Q_LOGGING_CATEGORY(jmbdeWidgetsAccoutInputAreaLog, "jmuelbert.jmbde.widgets.accountinputarea", QtWarningMsg)

// Edit an existing Account
AccountInputArea::AccountInputArea(QWidget *parent, const QModelIndex &index)
    : QGroupBox(parent)
    , ui(new Ui::AccountInputArea)
{
    ui->setupUi(this);

    qCDebug(jmbdeWidgetsAccoutInputAreaLog) << "Init AccountInputArea for Index :" << index.column();

    this->m_accountModel = new Model::Account();
    this->m_db = this->m_accountModel->getDB();

    m_actualMode = Mode::Edit;
    setViewOnlyMode(true);

    // Set the Model
    m_model = this->m_accountModel->initializeRelationalModel();

    // Set the mapper
    m_mapper = new QDataWidgetMapper();
    m_mapper->setModel(m_model);
    m_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    setMappings();

    m_mapper->setCurrentIndex(index.row());
}

AccountInputArea::~AccountInputArea()
{
    delete ui;
}

void AccountInputArea::setMappings()
{
    m_mapper->addMapping(ui->userNameLineEdit, this->m_accountModel->getUserNameIndex());
    m_mapper->addMapping(ui->passwordLineEdit, this->m_accountModel->getPasswordIndex());
    m_mapper->addMapping(ui->systemListView, this->m_accountModel->getSystemDataIndex());
    m_mapper->addMapping(ui->lastUpdateLineEdit, this->m_accountModel->getLastUpdateIndex());
}

void AccountInputArea::setViewOnlyMode(bool mode)
{
    ui->userNameLineEdit->setDisabled(mode);
    ui->passwordLineEdit->setDisabled(mode);
    // ui->systemListView->setDisabled(mode);
}

void AccountInputArea::createDataset()
{
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

void AccountInputArea::retrieveDataset(const QModelIndex index)
{
}

void AccountInputArea::updateDataset(const QModelIndex index)
{
}

void AccountInputArea::deleteDataset(const QModelIndex index)
{
}

// Save the actual data

void AccountInputArea::on_pushButton_Add_clicked()
{
    createDataset();
    on_pushButton_EditFinish_clicked();
}

void AccountInputArea::on_pushButton_EditFinish_clicked()
{
    // Set all inputfields to blank

    switch (m_actualMode) {
    case Mode::Edit: {
        m_actualMode = Mode::Finish;
        ui->pushButton_EditFinish->setText(tr("Fertig"));
        setViewOnlyMode(false);

    } break;

    case Mode::Finish: {
        qCDebug(jmbdeWidgetsAccoutInputAreaLog) << tr("Die Daten werden gesichert.");

        m_actualMode = Mode::Edit;
        ui->pushButton_EditFinish->setText(tr("Bearbeiten"));
        setViewOnlyMode(false);

        QString userName = ui->userNameLineEdit->text();

        if (userName.isEmpty()) {
            QString message(tr("Bitte geben Sie den Mitarbeiternamen ein"));

            QMessageBox::information(this, tr("Mitarbeiter hinzufügen"), message);
        } else {
            qCDebug(jmbdeWidgetsAccoutInputAreaLog) << tr("Benutzer Name : ") << ui->userNameLineEdit->text();
            m_mapper->submit();
            m_model->database().transaction();
            if (m_model->submitAll()) {
                m_model->database().commit();
                qCDebug(jmbdeWidgetsAccoutInputAreaLog) << tr("Schreiben der Änderungen in die Datenbank");
                emit dataChanged();
            } else {
                m_model->database().rollback();
                QMessageBox::warning(this, tr("jmbde"), tr("Die Datenbank meldet den Fehler: %1").arg(m_model->lastError().text()));
            }
        }
    } break;

    default: {
        qCDebug(jmbdeWidgetsAccoutInputAreaLog) << tr("Fehler");
    }
    }
}
