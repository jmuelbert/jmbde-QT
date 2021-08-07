/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "tst_widgetstest.h"

void tst_widgetstest::toUpper_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");

    QTest::newRow("all lower") << "hello"
                               << "HELLO";
    QTest::newRow("mixed") << "Hello"
                           << "HELLO";
    QTest::newRow("all upper") << "HELLO"
                               << "HELLO";
}

void tst_widgetstest::toUpper()
{
    QFETCH(QString, string);
    QFETCH(QString, result);

    QCOMPARE(string.toUpper(), result);
}

QTEST_MAIN(tst_widgetstest)
