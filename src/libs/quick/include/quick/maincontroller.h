#include <QCoreApplication>
#include <QDebug>
#include <QGuiApplication>
#include <QLoggingCategory>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>

#include <jmbdequick-version.h>
#include <jmbdequick_export.h>
#include <loggingcategory.h>

#pragma once

class QQmlApplicationEngine;

class JMBDEQUICK_EXPORT MainController : public QObject {
  Q_OBJECT

public:
  explicit MainController(/* QObject *parent = nullptr */);

  ~MainController();

  Q_REQUIRED_RESULT bool initialize();

private:
  QQmlApplicationEngine *mEngine = nullptr;
};
