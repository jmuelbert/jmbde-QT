/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "models/employeemodel.h"

EmployeeModel::EmployeeModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_employees.append({QLatin1String("Magee V."), QLatin1String("Dean"), QLatin1String("1296 Cursus. St."), QLatin1String("3084"), QLatin1String("Montreal")});
    m_employees.append(
        {QLatin1String("Akeem"), QLatin1String("Beard"), QLatin1String("P.O. Box 329, 1588 Arcu Rd."), QLatin1String("9650"), QLatin1String("Colchane")});
    m_employees.append(
        {QLatin1String("Cruz I."), QLatin1String("Wade"), QLatin1String("561-9860 Tristique St."), QLatin1String("60207"), QLatin1String("Orvault")});
    m_employees.append(
        {QLatin1String("Rahim J."), QLatin1String("Bullock"), QLatin1String("Ap #322-1878 Sit Ave"), QLatin1String("6110"), QLatin1String("Newbury")});
    m_employees.append(
        {QLatin1String("Ciara G."), QLatin1String("Long"), QLatin1String("Ap #789-4821 Diam Ave"), QLatin1String("T4M 0B9"), QLatin1String("Peralillo")});
    m_employees.append(
        {QLatin1String("Autumn H."), QLatin1String("Stuart"), QLatin1String("951-3107 A Av."), QLatin1String("Z8077"), QLatin1String("Camerino")});
    m_employees.append(
        {QLatin1String("Drew Z."), QLatin1String("Dominguez"), QLatin1String("131-2126 Quis St."), QLatin1String("79376"), QLatin1String("Chiclayo")});
    m_employees.append(
        {QLatin1String("Florence K."), QLatin1String("Marks"), QLatin1String("389-8683 Odio St."), QLatin1String("12095"), QLatin1String("Solingen")});
    m_employees.append(
        {QLatin1String("Fletcher U."), QLatin1String("Clark"), QLatin1String("4408 Urna. St."), QLatin1String("9176 XC"), QLatin1String("Corroy-le-Chateau")});
    m_employees.append(
        {QLatin1String("Akeem H."), QLatin1String("Hardin"), QLatin1String("543-3082 Orci. Street"), QLatin1String("04155"), QLatin1String("Niort")});
}

auto EmployeeModel::rowCount(const QModelIndex &) const -> int
{
    return m_employees.count();
}

auto EmployeeModel::data(const QModelIndex &index, int role) const -> QVariant
{
    if (index.row() < rowCount()) {
        switch (role) {
        case FirstNameRole:
            return m_employees.at(index.row()).firstName;
        case LastNameRole:
            return m_employees.at(index.row()).lastName;
        case StreetRole:
            return m_employees.at(index.row()).street;
        case ZipRole:
            return m_employees.at(index.row()).zip;
        case CityRole:
            return m_employees.at(index.row()).city;
        default:
            return QVariant();
        }
    }
    return QVariant();
}

auto EmployeeModel::roleNames() const -> QHash<int, QByteArray>
{
    static const QHash<int, QByteArray> roles{{FirstNameRole, "firstName"},
                                              {LastNameRole, "lastName"},
                                              {StreetRole, "street"},
                                              {ZipRole, "zip"},
                                              {CityRole, "city"}};
    return roles;
}

auto EmployeeModel::get(int row) const -> QVariantMap
{
    const Employee employee = m_employees.value(row);
    return {{QLatin1String("firstName"), employee.firstName},
            {QLatin1String("lastName"), employee.lastName},
            {QLatin1String("street"), employee.street},
            {QLatin1String("zip"), employee.zip},
            {QLatin1String("city"), employee.city}};
}

void EmployeeModel::append(const QString &firstName, const QString &lastName, const QString &street, const QString &zip, const QString &city)
{
    int row = 0;
    while (row < m_employees.count() && (lastName > m_employees.at(row).lastName)) {
        ++row;
    }
    beginInsertRows(QModelIndex(), row, row);
    m_employees.insert(row, {firstName, lastName, street, zip, city});
    endInsertRows();
}

void EmployeeModel::set(int row, const QString &firstName, const QString &lastName, const QString &street, const QString &zip, const QString &city)
{
    if (row < 0 || row >= m_employees.count()) {
        return;
    }

    m_employees.replace(row, {firstName, lastName, street, zip, city});
    emit dataChanged(index(row, 0), index(row, 0), {FirstNameRole, LastNameRole, StreetRole, ZipRole, CityRole});
}

void EmployeeModel::remove(int row)
{
    if (row < 0 || row >= m_employees.count()) {
        return;
    }

    beginRemoveRows(QModelIndex(), row, row);
    m_employees.removeAt(row);
    endRemoveRows();
}
