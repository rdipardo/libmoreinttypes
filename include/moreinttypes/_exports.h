#ifndef MOREINTTYPES_EXPORTS_H
#define MOREINTTYPES_EXPORTS_H 1

#ifndef _MSC_VER
#    define MOREINTTYPES_EXPORTS_BUILT_AS_STATIC 1
#endif

#ifdef MOREINTTYPES_EXPORTS_BUILT_AS_STATIC
#    define MOREINTTYPES_EXPORTS
#    define MOREINTTYPES_NO_EXPORT
#else
#    ifndef MOREINTTYPES_EXPORTS
#        ifdef BUILDING_MOREINTTYPES
/* We are building this library */
#            define MOREINTTYPES_EXPORTS __declspec(dllexport)
#        else
/* We are using this library */
#            define MOREINTTYPES_EXPORTS __declspec(dllimport)
#        endif
#    endif

#    ifndef MOREINTTYPES_NO_EXPORT
#        define MOREINTTYPES_NO_EXPORT
#    endif
#endif

#ifndef MOREINTTYPES_DEPRECATED
#    define MOREINTTYPES_DEPRECATED __declspec(deprecated)
#endif

#ifndef MOREINTTYPES_DEPRECATED_EXPORT
#    define MOREINTTYPES_DEPRECATED_EXPORT                                     \
        MOREINTTYPES_EXPORTS MOREINTTYPES_DEPRECATED
#endif

#ifndef MOREINTTYPES_DEPRECATED_NO_EXPORT
#    define MOREINTTYPES_DEPRECATED_NO_EXPORT                                  \
        MOREINTTYPES_NO_EXPORT MOREINTTYPES_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#    ifndef MOREINTTYPES_NO_DEPRECATED
#        define MOREINTTYPES_NO_DEPRECATED
#    endif
#endif

#endif /* !MOREINTTYPES_EXPORTS_H */
