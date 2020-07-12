
#ifndef JMBDEWIDGETS_EXPORT_H
#define JMBDEWIDGETS_EXPORT_H

#ifdef JMBDEWIDGETS_STATIC_DEFINE
#  define JMBDEWIDGETS_EXPORT
#  define JMBDEWIDGETS_NO_EXPORT
#else
#  ifndef JMBDEWIDGETS_EXPORT
#    ifdef jmbdewidgets_EXPORTS
        /* We are building this library */
#      define JMBDEWIDGETS_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define JMBDEWIDGETS_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef JMBDEWIDGETS_NO_EXPORT
#    define JMBDEWIDGETS_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef JMBDEWIDGETS_DEPRECATED
#  define JMBDEWIDGETS_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef JMBDEWIDGETS_DEPRECATED_EXPORT
#  define JMBDEWIDGETS_DEPRECATED_EXPORT JMBDEWIDGETS_EXPORT JMBDEWIDGETS_DEPRECATED
#endif

#ifndef JMBDEWIDGETS_DEPRECATED_NO_EXPORT
#  define JMBDEWIDGETS_DEPRECATED_NO_EXPORT JMBDEWIDGETS_NO_EXPORT JMBDEWIDGETS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef JMBDEWIDGETS_NO_DEPRECATED
#    define JMBDEWIDGETS_NO_DEPRECATED
#  endif
#endif

#endif /* JMBDEWIDGETS_EXPORT_H */
