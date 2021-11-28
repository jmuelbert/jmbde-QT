

#include <QScopedpointer>
#include <QTextStream>
#include <QDateTime>
#include <QLoggingCategory>

class Logger {
  Logger::Logger() { }

  void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
private:
  QScopedPointer<QFile> m_logFile;
