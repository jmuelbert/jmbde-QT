/*
    Copyright 2020, Jürgen Mülbert

    This file is part of jmbde.

    jmbde is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    Slate is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with jmbde. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <jmbdequick-version.h>
#include <jmbdequick_export.h>

#include <QAbstractListModel>

class EmployeeModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum EmployeeRole { LastNameRole = Qt::DisplayRole, FirstNameRole = Qt::UserRole, StreetRole, ZipRole, CityRole };
    Q_ENUM(EmployeeRole)

    explicit JMBDEQUICK_EXPORT EmployeeModel(QObject *parent = nullptr);

    JMBDEQUICK_EXPORT int rowCount(const QModelIndex & = QModelIndex()) const;
    JMBDEQUICK_EXPORT QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    JMBDEQUICK_EXPORT QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE JMBDEQUICK_EXPORT QVariantMap get(int row) const;
    Q_INVOKABLE JMBDEQUICK_EXPORT void
    append(const QString &firstName, const QString &lastName, const QString &street, const QString &zip, const QString &city);
    Q_INVOKABLE JMBDEQUICK_EXPORT void
    set(int row, const QString &firstName, const QString &lastName, const QString &street, const QString &zip, const QString &city);
    Q_INVOKABLE JMBDEQUICK_EXPORT void remove(int row);

private:
    struct Employee {
        QString firstName;
        QString lastName;
        QString street;
        QString zip;
        QString city;
    };

    QList<Employee> m_employees;
};
