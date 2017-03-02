/************************************************************************/
/* 
	π§æﬂ¿‡
	created by sunhanpt 2017/3/2
*/
/************************************************************************/
#ifndef __I_UTIL_H_INCLUDED__
#define __I_UTIL_H_INCLUDED__

#define A_SAFE_DELETE(T) \
do \
{ \
	if (T) { \
		delete T; \
		T = nullptr; \
	} \
} while (0); \

#define A_SAFE_DELETE_ARRAY(T) \
do \
{ \
	if (T) { \
		delete[] T; \
		T = nullptr; \
	} \
} while (0); \

#endif
