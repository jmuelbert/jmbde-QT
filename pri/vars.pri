APP_NAME                      = "jmBDE"
APP_LOW_NAME                  = "jmbde"
APP_REVERSE_NAME              = "io.github.jmuelbert.jmbde-QT"
APP_AUTHOR                    = "Jürgen Mülbert"
APP_COPYRIGHT                 = "(C) 2013-2018 $$APP_AUTHOR"
APP_VERSION                   = "0.4.22"
APP_LONG_NAME                 = "$$APP_NAME $$APP_VERSION"
APP_EMAIL                     = "juergen.muelbert@gmail.com"
APP_URL                       = "https://github.com/jmuelbert/jmbde-QT"
APP_URL_ISSUES                = "https://github.com/jmuelbert/jmbde-QT/issues"
APP_URL_ISSUES_NEW            = "https://github.com/jmuelbert/jmbde-QT/issues/new"
APP_URL_WIKI                  = "https://github.com/jmuelbert/jmbde-QT/wiki"
APP_USERAGENT                 = "jmBDE/$$APP_VERSION (io.github.jmuelbert.jmbde-QT)"
APP_DONATE_URL                = "https://jmuelbert.github.io/donate"
APP_WIN_ARCH                  = "win64"

message($$MSG_PREFIX: Welcome to $$MSG_PREFIX qmake script.)

lessThan(QT_MAJOR_VERSION, 5)|lessThan(QT_MINOR_VERSION, 6) {
  error($$MSG_PREFIX: At least Qt \"5.6.3\" is required!!!)
}
