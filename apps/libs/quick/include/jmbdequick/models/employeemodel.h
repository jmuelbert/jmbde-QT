/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <jmbdequick_export.h>

#include <QAbstractListModel>

class EmployeeModel : public QAbstractListModel
{
  Q_OBJECT
  Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
public:
  enum EmployeeRole { LastNameRole = Qt::DisplayRole, FirstNameRole = Qt::UserRole, StreetRole, ZipRole, CityRole };
  Q_ENUM(EmployeeRole)

  explicit JMBDEQUICK_EXPORT EmployeeModel(QObject *parent = nullptr);

  auto count() const -> int { return m_count; }

  JMBDEQUICK_EXPORT int rowCount(const QModelIndex &p) const
  {
    Q_UNUSED(p)
    return static_cast<int>(m_employees.size());
  }

  JMBDEQUICK_EXPORT QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  JMBDEQUICK_EXPORT QHash<int, QByteArray> roleNames() const;

  Q_INVOKABLE JMBDEQUICK_EXPORT QVariantMap get(int row) const;
  Q_INVOKABLE JMBDEQUICK_EXPORT void append(const QString &firstName,
    const QString &lastName,
    const QString &street,
    const QString &zip,
    const QString &city);
  Q_INVOKABLE JMBDEQUICK_EXPORT void set(int row,
    const QString &firstName,
    const QString &lastName,
    const QString &street,
    const QString &zip,
    const QString &city);
  Q_INVOKABLE JMBDEQUICK_EXPORT void remove(int row);

signals:
  void countChanged(int count);

public slots:
  void setCount(int count);

private:
  struct Employee
  {
    QString firstName;
    QString lastName;
    QString street;
    QString zip;
    QString city;
  };

  QList<Employee> m_employees;

  int m_count;
};
