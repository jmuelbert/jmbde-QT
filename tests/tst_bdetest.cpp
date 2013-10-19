/*
* Copyright 2007 Jürgen Mülbert
*
* Lizenziert unter der EUPL, Version 1.1 oder - sobald
  diese von der Europäischen Kommission genehmigt wurden -
  Folgeversionen der EUPL ("Lizenz");
* Sie dürfen dieses Werk ausschließlich gemäß
dieser Lizenz nutzen.
* Eine Kopie der Lizenz finden Sie hier:
*
* http://ec.europa.eu/idabc/eupl5
*
* Sofern nicht durch anwendbare Rechtsvorschriften
  gefordert oder in schriftlicher Form vereinbart, wird
  die unter der Lizenz verbreitete Software "so wie sie
  ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
  ausdrücklich oder stillschweigend - verbreitet.
* Die sprachspezifischen Genehmigungen und Beschränkungen
  unter der Lizenz sind dem Lizenztext zu entnehmen.
*/
#include <QString>
#include <QtTest>



class BdeTest : public QObject
{
    Q_OBJECT
    
public:
    BdeTest();
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    void testCase1_data();
};

BdeTest::BdeTest()
{
}

void BdeTest::initTestCase()
{
}

void BdeTest::cleanupTestCase()
{
}

void BdeTest::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}


void BdeTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}


QTEST_APPLESS_MAIN(BdeTest)

#include "tst_bdetest.moc"
