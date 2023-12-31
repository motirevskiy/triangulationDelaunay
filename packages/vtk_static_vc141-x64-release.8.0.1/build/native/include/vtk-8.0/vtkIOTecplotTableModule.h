
#ifndef VTKIOTECPLOTTABLE_EXPORT_H
#define VTKIOTECPLOTTABLE_EXPORT_H

#ifdef VTKIOTECPLOTTABLE_STATIC_DEFINE
#  define VTKIOTECPLOTTABLE_EXPORT
#  define VTKIOTECPLOTTABLE_NO_EXPORT
#else
#  ifndef VTKIOTECPLOTTABLE_EXPORT
#    ifdef vtkIOTecplotTable_EXPORTS
        /* We are building this library */
#      define VTKIOTECPLOTTABLE_EXPORT 
#    else
        /* We are using this library */
#      define VTKIOTECPLOTTABLE_EXPORT 
#    endif
#  endif

#  ifndef VTKIOTECPLOTTABLE_NO_EXPORT
#    define VTKIOTECPLOTTABLE_NO_EXPORT 
#  endif
#endif

#ifndef VTKIOTECPLOTTABLE_DEPRECATED
#  define VTKIOTECPLOTTABLE_DEPRECATED __declspec(deprecated)
#  define VTKIOTECPLOTTABLE_DEPRECATED_EXPORT VTKIOTECPLOTTABLE_EXPORT __declspec(deprecated)
#  define VTKIOTECPLOTTABLE_DEPRECATED_NO_EXPORT VTKIOTECPLOTTABLE_NO_EXPORT __declspec(deprecated)
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define VTKIOTECPLOTTABLE_NO_DEPRECATED
#endif



#endif
