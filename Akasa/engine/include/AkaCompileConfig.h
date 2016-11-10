// // ±àÒëÅäÖÃ
#ifndef __AKA_COMPILE_CONFIG_H_INCLUDED__
#define __AKA_COMPILE_CONFIG_H_INCLUDED__


//! Uncomment this line to compile with the SDL device
#define _AKA_COMPILE_WITH_SDL_DEVICE_
#ifdef NO_AKA_COMPILE_WITH_SDL_DEVICE_
#undef _AKA_COMPILE_WITH_SDL_DEVICE_
#endif

//! Comment this line to compile without the fallback console device.
//#define _IRR_COMPILE_WITH_CONSOLE_DEVICE_
#ifdef NO_AKA_COMPILE_WITH_CONSOLE_DEVICE_
#undef _AKA_COMPILE_WITH_CONSOLE_DEVICE_
#endif

//! WIN32 for Windows32
//! WIN64 for Windows64
// The windows platform and API support SDL and WINDOW device
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#define _AKA_WINDOWS_
#define _AKA_WINDOWS_API_
#define _AKA_COMPILE_WITH_WINDOWS_DEVICE_
#endif

//! Define __IRR_HAS_S64 if the irr::s64 type should be enable (needs long long, available on most platforms, but not part of ISO C++ 98)
#define __AKA_HAS_S64
#ifdef NO__AKA_HAS_S64
#undef __AKA_HAS_S64
#endif

//! Defines an override macro, to protect virtual functions from typos and other mismatches
/** Usage in a derived class:
virtual void somefunc() _IRR_OVERRIDE_;
*/
#if ( ((__GNUC__ > 4 ) || ((__GNUC__ == 4 ) && (__GNUC_MINOR__ >= 7))) && (defined(__GXX_EXPERIMENTAL_CXX0X) || __cplusplus >= 201103L) )
#define _AKA_OVERRIDE_ override
#elif (_MSC_VER >= 1600 ) /* supported since MSVC 2010 */
#define _AKA_OVERRIDE_ override
#elif (__clang_major__ >= 3)
#define _AKA_OVERRIDE_ override
#else
#define _AKA_OVERRIDE_
#endif


#endif