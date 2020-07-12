
#ifndef JMBDEMODELS_EXPORT_H
#define JMBDEMODELS_EXPORT_H

#ifdef JMBDEMODELS_STATIC_DEFINE
#  define JMBDEMODELS_EXPORT
#  define JMBDEMODELS_NO_EXPORT
#else
#  ifndef JMBDEMODELS_EXPORT
#    ifdef jmbdemodels_EXPORTS
        /* We are building this library */
#      define JMBDEMODELS_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define JMBDEMODELS_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef JMBDEMODELS_NO_EXPORT
#    define JMBDEMODELS_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef JMBDEMODELS_DEPRECATED
#  define JMBDEMODELS_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef JMBDEMODELS_DEPRECATED_EXPORT
#  define JMBDEMODELS_DEPRECATED_EXPORT JMBDEMODELS_EXPORT JMBDEMODELS_DEPRECATED
#endif

#ifndef JMBDEMODELS_DEPRECATED_NO_EXPORT
#  define JMBDEMODELS_DEPRECATED_NO_EXPORT JMBDEMODELS_NO_EXPORT JMBDEMODELS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef JMBDEMODELS_NO_DEPRECATED
#    define JMBDEMODELS_NO_DEPRECATED
#  endif
#endif

#endif /* JMBDEMODELS_EXPORT_H */
