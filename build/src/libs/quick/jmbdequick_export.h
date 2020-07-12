
#ifndef JMBDEQUICK_EXPORT_H
#define JMBDEQUICK_EXPORT_H

#ifdef JMBDEQUICK_STATIC_DEFINE
#  define JMBDEQUICK_EXPORT
#  define JMBDEQUICK_NO_EXPORT
#else
#  ifndef JMBDEQUICK_EXPORT
#    ifdef jmbdequick_EXPORTS
        /* We are building this library */
#      define JMBDEQUICK_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define JMBDEQUICK_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef JMBDEQUICK_NO_EXPORT
#    define JMBDEQUICK_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef JMBDEQUICK_DEPRECATED
#  define JMBDEQUICK_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef JMBDEQUICK_DEPRECATED_EXPORT
#  define JMBDEQUICK_DEPRECATED_EXPORT JMBDEQUICK_EXPORT JMBDEQUICK_DEPRECATED
#endif

#ifndef JMBDEQUICK_DEPRECATED_NO_EXPORT
#  define JMBDEQUICK_DEPRECATED_NO_EXPORT JMBDEQUICK_NO_EXPORT JMBDEQUICK_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef JMBDEQUICK_NO_DEPRECATED
#    define JMBDEQUICK_NO_DEPRECATED
#  endif
#endif

#endif /* JMBDEQUICK_EXPORT_H */
