#include "views/employeetable.h"
#include "ui_employeetable.h"

EmployeeTable::EmployeeTable(const QString &tableName, QSqlTableModel *model, QWidget *parent)
    : QWidget(parent)
    , m_model(model)
    , ui(new Ui::EmployeeTable)
{
    ui->setupUi(this);

    m_model->setTable(tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_model->select();

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
    connect(revertButton, &QPushButton::clicked, model, &QSqlTableModel::revertAll);
    // connect(quitButton, &QPushButton::clicked, this, &EmployeeTable::close);
}

EmployeeTable::~EmployeeTable()
{
    delete ui;
}

void EmployeeTable ::submit()
{
    m_model->database().transaction();
    if (m_model->submitAll()) {
        m_model->database().commit();
    } else {
        m_model->database().rollback();
        QMessageBox::warning(this, tr("Cached Table"), tr("The database reported an error: %1").arg(m_model->lastError().text()));
    }
}
