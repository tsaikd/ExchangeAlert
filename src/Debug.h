/**
 * @file Debug.h
 * @brief General debug functions and MACROs
 *
 * Support for library QT4 \n
 * Support for IDE msvc2005 msvc2008
 *
 * @author tsaikd@gmail.com
 * @version 1.0.1.1
 * @date 2009/09/15
 **/

#ifndef _GENERAL_DEBUG_H
#define _GENERAL_DEBUG_H

#if defined(_DEBUG) && !defined(DEBUG)
	#define DEBUG
#endif//defined(_DEBUG) && !defined(DEBUG)

#if !defined(__PRETTY_FUNCTION__) && defined(__FUNCTION__)
	#define __PRETTY_FUNCTION__ __FUNCTION__
#endif//!defined(__PRETTY_FUNCTION__) && defined(__FUNCTION__)

#ifdef DEBUG
	#define DEBUG_BUFSIZE 65536
	extern char g_debugBuf[DEBUG_BUFSIZE];
	extern char g_debugBuf2[DEBUG_BUFSIZE];
	static int g_debugTraceFuncLineLen;

	#ifdef WIN32
		#include <windows.h>
		#include <crtdbg.h>
		#define TRACES(msg)			OutputDebugStringA(msg)
		#define TRACEBUF_SET(msg)	strcpy_s(g_debugBuf, DEBUG_BUFSIZE, msg)
		#define TRACEBUF_ADD(msg)	strcat_s(g_debugBuf, DEBUG_BUFSIZE, msg)
		#define TRACEBUF_ADD1(fmt, arg1) { sprintf_s(g_debugBuf2, DEBUG_BUFSIZE, fmt, arg1); TRACEBUF_ADD(g_debugBuf2); }
		#define TRACEBUF_ADD2(fmt, arg1, arg2) { sprintf_s(g_debugBuf2, DEBUG_BUFSIZE, fmt, arg1, arg2); TRACEBUF_ADD(g_debugBuf2); }
		#define TRACEBUF_ADD3(fmt, arg1, arg2, arg3) { sprintf_s(g_debugBuf2, DEBUG_BUFSIZE, fmt, arg1, arg2, arg3); TRACEBUF_ADD(g_debugBuf2); }
		#define TRACEBUF_ADD4(fmt, arg1, arg2, arg3, arg4) { sprintf_s(g_debugBuf2, DEBUG_BUFSIZE, fmt, arg1, arg2, arg3, arg4); TRACEBUF_ADD(g_debugBuf2); }
		#define TRACEBUF_ADD5(fmt, arg1, arg2, arg3, arg4, arg5) { sprintf_s(g_debugBuf2, DEBUG_BUFSIZE, fmt, arg1, arg2, arg3, arg4, arg5); TRACEBUF_ADD(g_debugBuf2); }

		#define ASSERT(expr) ((!!(expr)) || \
					(1 != _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, NULL, _CRT_WIDE(#expr))) || \
					(_CrtDbgBreak(), 0))
		#define VERIFY(expr) ASSERT(expr)
	#else//WIN32
		#define TRACEBUF_SET(msg)	strcpy(g_debugBuf, msg)
		#define TRACEBUF_ADD(msg)	strcat(g_debugBuf, msg)
		#define TRACEBUF_ADD1(fmt, arg1) { sprintf(g_debugBuf2, fmt, arg1); TRACEBUF_ADD(g_debugBuf2); }
		#define TRACEBUF_ADD2(fmt, arg1, arg2) { sprintf(g_debugBuf2, fmt, arg1, arg2); TRACEBUF_ADD(g_debugBuf2); }
		#define TRACEBUF_ADD3(fmt, arg1, arg2, arg3) { sprintf(g_debugBuf2, fmt, arg1, arg2, arg3); TRACEBUF_ADD(g_debugBuf2); }
		#define TRACEBUF_ADD4(fmt, arg1, arg2, arg3, arg4) { sprintf(g_debugBuf2, fmt, arg1, arg2, arg3, arg4); TRACEBUF_ADD(g_debugBuf2); }
		#define TRACEBUF_ADD5(fmt, arg1, arg2, arg3, arg4, arg5) { sprintf(g_debugBuf2, fmt, arg1, arg2, arg3, arg4, arg5); TRACEBUF_ADD(g_debugBuf2); }
	#endif//WIN32
	#define TRACEBUF_SEND()			TRACES(g_debugBuf)

	#include <stdio.h>
	extern FILE* g_fpDebugLog;

	#define DOPEN(filename)	{ DCLOSE(); g_fpDebugLog = fopen(filename, "wb"); }
	#define DCLOSE()		{ if (g_fpDebugLog) { fclose(g_fpDebugLog); g_fpDebugLog = NULL; } }
	#define DLOGFUNCLINE()	{ if (g_fpDebugLog) { fprintf(g_fpDebugLog, "%s():%d: ", __PRETTY_FUNCTION__, __LINE__); fflush(g_fpDebugLog); } }
	#define DLOGL(msg)		{ if (g_fpDebugLog) { DLOGFUNCLINE(); fprintf(g_fpDebugLog, "\n"); fflush(g_fpDebugLog); } }
	#define DLOGN(msg)		{ if (g_fpDebugLog) { fprintf(g_fpDebugLog, "\n"); fflush(g_fpDebugLog); } }
	#define DLOGD(var)		{ if (g_fpDebugLog) { DLOG2("%-60s (%3d)", #var, (int)var); } }
	#define DNOTIMP()		{ DLOG0("not implement"); TRACE0("not implement"); ASSERT(0 && "not implement"); }
	#define DNOHERE()		{ DLOG0("should not go here"); TRACE0("should not go here"); ASSERT(0 && "should not go here"); }

	#define DLOG0(msg) { if (g_fpDebugLog) { DLOGFUNCLINE(); fprintf(g_fpDebugLog, msg"\n"); fflush(g_fpDebugLog); } }
	#define DLOG1(fmt, arg1) { if (g_fpDebugLog) { DLOGFUNCLINE(); fprintf(g_fpDebugLog, fmt"\n", arg1); fflush(g_fpDebugLog); } }
	#define DLOG2(fmt, arg1, arg2) { if (g_fpDebugLog) { DLOGFUNCLINE(); fprintf(g_fpDebugLog, fmt"\n", arg1, arg2); fflush(g_fpDebugLog); } }
	#define DLOG3(fmt, arg1, arg2, arg3) { if (g_fpDebugLog) { DLOGFUNCLINE(); fprintf(g_fpDebugLog, fmt"\n", arg1, arg2, arg3); fflush(g_fpDebugLog); } }
	#define DLOG4(fmt, arg1, arg2, arg3, arg4) { if (g_fpDebugLog) { DLOGFUNCLINE(); fprintf(g_fpDebugLog, fmt"\n", arg1, arg2, arg3, arg4); fflush(g_fpDebugLog); } }
	#define DLOG5(fmt, arg1, arg2, arg3, arg4, arg5) { if (g_fpDebugLog) { DLOGFUNCLINE(); fprintf(g_fpDebugLog, fmt"\n", arg1, arg2, arg3, arg4, arg5); fflush(g_fpDebugLog); } }
#endif//DEBUG

#ifdef QT_VERSION
	#ifndef Q_SLOT // fix Qt 4.4.3 compile error
		#define Q_SLOT
	#endif//Q_SLOT
	#include <QtCore/QDebug>
	#ifndef QT_NO_DEBUG_OUTPUT
		#define QTRACE()			((qDebug().nospace() << __PRETTY_FUNCTION__ << ":" << __LINE__ << ":").space())
	#else//QT_NO_DEBUG_OUTPUT
		#define QTRACE()			qDebug()
	#endif//QT_NO_DEBUG_OUTPUT
	#if defined(DEBUG) && !defined(WIN32)
		#define TRACES(msg)			( qDebug() << msg )
	#endif//defined(DEBUG) && !defined(WIN32)

	#ifdef QT_NO_DEBUG_STREAM
		#ifdef QVARIANT_H
			inline QDebug& operator<<(QDebug& debug, const QVariant& var) {
				return debug << var.toString();
			}
		#endif//QVARIANT_H
		#ifdef QHOSTADDRESS_H
			inline QDebug& operator<<(QDebug& debug, const QHostAddress& host) {
				return debug << host.toString();
			}
		#endif//QHOSTADDRESS_H
	#endif
#endif//QT_VERSION

#ifdef TRACES
	#if defined(QT_VERSION) && !defined(WIN32)
		#define TRACE_EOL ""
	#else//defined(QT_VERSION) && !defined(WIN32)
		#define TRACE_EOL "\n"
	#endif//defined(QT_VERSION) && !defined(WIN32)

	#define TRACES1(fmt, arg1) { TRACEBUF_SET(""); TRACEBUF_ADD1(fmt, arg1); TRACEBUF_SEND(); }
	#define TRACES2(fmt, arg1, arg2) { TRACEBUF_SET(""); TRACEBUF_ADD2(fmt, arg1, arg2); TRACEBUF_SEND(); }
	#define TRACES3(fmt, arg1, arg2, arg3) { TRACEBUF_SET(""); TRACEBUF_ADD3(fmt, arg1, arg2, arg3); TRACEBUF_SEND(); }
	#define TRACES4(fmt, arg1, arg2, arg3, arg4) { TRACEBUF_SET(""); TRACEBUF_ADD4(fmt, arg1, arg2, arg3, arg4); TRACEBUF_SEND(); }
	#define TRACES5(fmt, arg1, arg2, arg3, arg4, arg5) { TRACEBUF_SET(""); TRACEBUF_ADD5(fmt, arg1, arg2, arg3, arg4, arg5); TRACEBUF_SEND(); }

	#define TRACEFUNCLINE()			{ TRACES2("%s():%d: ", __PRETTY_FUNCTION__, __LINE__); g_debugTraceFuncLineLen = (int)strlen(g_debugBuf); }
	#define TRACEBUF_SETFUNCLINE()	{ TRACEBUF_SET(__PRETTY_FUNCTION__); TRACEBUF_ADD1(":%d: ", __LINE__); g_debugTraceFuncLineLen = (int)strlen(g_debugBuf); }

	#define TRACEL()	{ TRACE0(""); }
	#define TRACED(var) { TRACE3("%-*s (%3d)", 65-g_debugTraceFuncLineLen, #var, (int)var); }
	#define TRACEN()	{ TRACES(TRACE_EOL); }

	#define TRACE0(msg) { TRACEBUF_SETFUNCLINE(); TRACEBUF_ADD(msg TRACE_EOL); TRACEBUF_SEND(); }
	#define TRACE1(fmt, arg1) { TRACEBUF_SETFUNCLINE(); TRACEBUF_ADD1(fmt TRACE_EOL, arg1); TRACEBUF_SEND(); }
	#define TRACE2(fmt, arg1, arg2) { TRACEBUF_SETFUNCLINE(); TRACEBUF_ADD2(fmt TRACE_EOL, arg1, arg2); TRACEBUF_SEND(); }
	#define TRACE3(fmt, arg1, arg2, arg3) { TRACEBUF_SETFUNCLINE(); TRACEBUF_ADD3(fmt TRACE_EOL, arg1, arg2, arg3); TRACEBUF_SEND(); }
	#define TRACE4(fmt, arg1, arg2, arg3, arg4) { TRACEBUF_SETFUNCLINE(); TRACEBUF_ADD4(fmt TRACE_EOL, arg1, arg2, arg3, arg4); TRACEBUF_SEND(); }
	#define TRACE5(fmt, arg1, arg2, arg3, arg4, arg5) { TRACEBUF_SETFUNCLINE(); TRACEBUF_ADD5(fmt TRACE_EOL, arg1, arg2, arg3, arg4, arg5); TRACEBUF_SEND(); }

	static int _TRACEARR_lnum;
	static int _TRACEARR_vnpl;
	static int _TRACEARR_i;
	/**
	 * @brief Trace all elements in array
	 * @note if var_num_per_line < 0 will force insert a newline before data
	 * @code
	 *   int iarr[100];
	 *   // ... fill integer array iarr
	 *   TRACEARR(int, iarr, "%d", 100, 10);
	 * @endcode
	 **/
	#define TRACEARR(sym_type, arr, sym_fmt, sym_num, var_num_per_line) { \
			_TRACEARR_lnum = 0; \
			TRACEBUF_SETFUNCLINE(); \
			TRACEBUF_ADD(#arr":"); \
			if ((var_num_per_line) > 0) { \
				_TRACEARR_vnpl = (var_num_per_line); \
				TRACEBUF_ADD("\t"); \
			} else { \
				_TRACEARR_vnpl = -(var_num_per_line); \
				TRACEBUF_ADD("\n"); \
			} \
			for (_TRACEARR_i=0 ; _TRACEARR_i<(sym_num) ; _TRACEARR_i++) { \
				if (_TRACEARR_lnum++ >= _TRACEARR_vnpl) { \
					TRACEBUF_ADD("\n"); \
					_TRACEARR_lnum = 1; \
				} \
				TRACEBUF_ADD1(" "sym_fmt, (sym_type)(arr[_TRACEARR_i])); \
			} \
			TRACEBUF_ADD("\n"); \
			TRACES(g_debugBuf); \
		}

	static int _TRACEARR_S2D_sy;
	static int _TRACEARR_S2D_sx;
	static int _TRACEARR_S2D_sh;
	static int _TRACEARR_S2D_sw;
	static int _TRACEARR_S2D_j;
	static int _TRACEARR_S2D_i;
	/**
	 * @brief Trace sub elements in 2D-array
	 * @note MxN == YxX == array[y][x]
	 **/
	#define TRACEARR_S2D(sym_type, arr, sym_fmt, start_y, start_x, height, width) { \
			_TRACEARR_S2D_sy = (start_y); \
			_TRACEARR_S2D_sx = (start_x); \
			_TRACEARR_S2D_sh = _TRACEARR_S2D_sy + (height); \
			_TRACEARR_S2D_sw = _TRACEARR_S2D_sx + (width); \
			TRACEBUF_SETFUNCLINE(); \
			TRACEBUF_ADD(#arr"\n"); \
			for (_TRACEARR_S2D_j=_TRACEARR_S2D_sy ; _TRACEARR_S2D_j<_TRACEARR_S2D_sh ; _TRACEARR_S2D_j++) { \
				for (_TRACEARR_S2D_i=_TRACEARR_S2D_sx ; _TRACEARR_S2D_i<_TRACEARR_S2D_sw ; _TRACEARR_S2D_i++) { \
					TRACEBUF_ADD1(" "sym_fmt, arr[_TRACEARR_S2D_j][_TRACEARR_S2D_i]); \
				} \
				TRACEBUF_ADD("\n"); \
			} \
			TRACES(g_debugBuf); \
		}
	/**
	 * @brief Trace all elements in 2D-array
	 * @see TRACEARR_S2D
	 **/
	#define TRACEARR_2D(sym_type, arr, sym_fmt, m, n) TRACEARR_S2D(sym_type, arr, sym_fmt, 0, 0, m, n)
#endif//TRACES

#ifndef QTRACE
	#define QTRACE()
#endif//QTRACE

#ifndef TRACES
	#define TRACES(msg)
#endif//TRACES
#ifndef TRACES1
	#define TRACES1(fmt, arg1)
#endif//TRACES1
#ifndef TRACES2
	#define TRACES2(fmt, arg1, arg2)
#endif//TRACES2
#ifndef TRACES3
	#define TRACES3(fmt, arg1, arg2, arg3)
#endif//TRACES3
#ifndef TRACES4
	#define TRACES4(fmt, arg1, arg2, arg3, arg4)
#endif//TRACES4
#ifndef TRACES5
	#define TRACES5(fmt, arg1, arg2, arg3, arg4, arg5)
#endif//TRACES5

#ifndef TRACEBUF_SET
	#define TRACEBUF_SET(msg)
#endif//TRACEBUF_SET
#ifndef TRACEBUF_ADD
	#define TRACEBUF_ADD(msg)
#endif//TRACEBUF_ADD
#ifndef TRACEBUF_ADD1
	#define TRACEBUF_ADD1(fmt, arg1)
#endif//TRACEBUF_ADD1
#ifndef TRACEBUF_ADD2
	#define TRACEBUF_ADD2(fmt, arg1, arg2)
#endif//TRACEBUF_ADD2
#ifndef TRACEBUF_ADD3
	#define TRACEBUF_ADD3(fmt, arg1, arg2, arg3)
#endif//TRACEBUF_ADD3
#ifndef TRACEBUF_ADD4
	#define TRACEBUF_ADD4(fmt, arg1, arg2, arg3, arg4)
#endif//TRACEBUF_ADD4
#ifndef TRACEBUF_ADD5
	#define TRACEBUF_ADD5(fmt, arg1, arg2, arg3, arg4, arg5)
#endif//TRACEBUF_ADD5
#ifndef TRACEBUF_SEND
	#define TRACEBUF_SEND()
#endif//TRACEBUF_SEND

#ifndef TRACE0
	#define TRACE0(msg)
#endif//TRACE0
#ifndef TRACE1
	#define TRACE1(fmt, arg1)
#endif//TRACE1
#ifndef TRACE2
	#define TRACE2(fmt, arg1, arg2)
#endif//TRACE2
#ifndef TRACE3
	#define TRACE3(fmt, arg1, arg2, arg3)
#endif//TRACE3
#ifndef TRACE4
	#define TRACE4(fmt, arg1, arg2, arg3, arg4)
#endif//TRACE4
#ifndef TRACE5
	#define TRACE5(fmt, arg1, arg2, arg3, arg4, arg5)
#endif//TRACE5

#ifndef TRACEFUNCLINE
	#define TRACEFUNCLINE()
#endif//TRACEFUNCLINE
#ifndef TRACEBUF_SETFUNCLINE
	#define TRACEBUF_SETFUNCLINE()
#endif//TRACEBUF_SETFUNCLINE
#ifndef TRACEL
	#define TRACEL()
#endif//TRACEL
#ifndef TRACED
	#define TRACED(var)
#endif//TRACED
#ifndef TRACEN
	#define TRACEN()
#endif//TRACEN

#ifndef TRACEARR
	#define TRACEARR(sym_type, arr, sym_fmt, sym_num, var_num_per_line)
#endif//TRACEARR
#ifndef TRACEARR_S2D
	#define TRACEARR_S2D(sym_type, arr, sym_fmt, start_y, start_x, height, width)
#endif//TRACEARR_S2D
#ifndef TRACEARR_2D
	#define TRACEARR_2D(sym_type, arr, sym_fmt, m, n)
#endif//TRACEARR_2D

#ifdef DEBUG
	#ifndef ASSERT
		#define ASSERT(expr) ((expr) || (exit(1), 0))
	#endif//ASSERT
	#ifndef VERIFY
		#define VERIFY(expr) ASSERT(expr)
	#endif//VERIFY
#else//DEBUG
	#ifndef ASSERT
		#define ASSERT(expr)
	#endif//ASSERT
	#ifndef VERIFY
		#define VERIFY(expr) (expr)
	#endif//VERIFY
#endif//DEBUG

#ifndef DOPEN
	#define DOPEN(filename)
#endif//DOPEN
#ifndef DCLOSE
	#define DCLOSE()
#endif//DCLOSE
#ifndef DLOGFUNCLINE
	#define DLOGFUNCLINE()
#endif//DLOGFUNCLINE
#ifndef DLOGL
	#define DLOGL(msg)
#endif//DLOGL
#ifndef DLOGN
	#define DLOGN(msg)
#endif//DLOGN
#ifndef DLOGD
	#define DLOGD(var)
#endif//DLOGD
#ifndef DNOTIMP
	#define DNOTIMP()
#endif//DNOTIMP
#ifndef DNOHERE
	#define DNOHERE()
#endif//DNOHERE

#ifndef DLOG0
	#define DLOG0(msg)
#endif//DLOG0
#ifndef DLOG1
	#define DLOG1(fmt, arg1)
#endif//DLOG1
#ifndef DLOG2
	#define DLOG2(fmt, arg1, arg2)
#endif//DLOG2
#ifndef DLOG3
	#define DLOG3(fmt, arg1, arg2, arg3)
#endif//DLOG3
#ifndef DLOG4
	#define DLOG4(fmt, arg1, arg2, arg3, arg4)
#endif//DLOG4

// the folloing is powerful definition
#ifndef NULL
	#define NULL 0
#endif//NULL

#ifndef SAFE_FREE
	#define SAFE_FREE(x) if (x) { free(x); (x) = NULL; }
#endif//SAFE_FREE

#ifndef SAFE_NEW
	#define SAFE_NEW(var, type) if ((var) == NULL) { (var) = new (type); }
#endif//SAFE_NEW

#ifndef SAFE_DELETE
	#define SAFE_DELETE(x) if (x) { delete (x); (x) = NULL; }
#endif//SAFE_DELETE

#ifndef SAFE_NEWARR
	#define SAFE_NEWARR(var, type, num) if ((var) == NULL) { (var) = new (type)[(num)]; }
#endif//SAFE_NEWARR

#ifndef SAFE_DELETEARR
	#define SAFE_DELETEARR(x) if (x) { delete [] (x); (x) = NULL; }
#endif//SAFE_DELETEARR

#ifndef ZERO_ARR
	#define ZERO_ARR(var) memset(var, 0, sizeof(var));
#endif//ZERO_ARR

#ifndef DECCV	// declare current class variable
	#define DECCV(type, var)			type& var = m_##var
#endif//DECCV
#ifndef DECCP	// declare current class variable pointer
	#define DECCP(type, var)			type& var = *m_##var
#endif//DECCP
#ifndef DECOV	// declare other class variable
	#define DECOV(type, base, var)		type& var = (base).m_##var
#endif//DECOV
#ifndef DECOP	// declare other class variable pointer
	#define DECOP(type, base, var)		type& var = *(base).m_##var
#endif//DECOP
#ifndef DECRV	// declare renamed variable
	#define DECRV(type, var, member)	type& var = (member)
#endif//DECRV
#ifndef DECRP	// declare renamed variable pointer
	#define DECRP(type, var, member)	type& var = *(member)
#endif//DECRP
#ifndef CDCCV	// declare current class const variable
	#define CDCCV(type, var)			const type& var = (const type&) m_##var
#endif//CDCCV
#ifndef CDCCP	// declare current class const variable pointer
	#define CDCCP(type, var)			const type& var = (const type&) *m_##var
#endif//CDCCP
#ifndef CDCOV	// declare other class const variable
	#define CDCOV(type, base, var)		const type& var = (const type&) (base).m_##var
#endif//CDCOV
#ifndef CDCOP	// declare other class const variable pointer
	#define CDCOP(type, base, var)		const type& var = (const type&) *(base).m_##var
#endif//CDCOP
#ifndef CDCRV	// declare renamed variable
	#define CDCRV(type, var, member)	const type& var = (const type&) (member)
#endif//CDCRV
#ifndef CDCRP	// declare renamed variable pointer
	#define CDCRP(type, var, member)	const type& var = (const type&) *(member)
#endif//CDCRP
#ifndef DEWCV	// declare and write current class variable with new value
	#define DEWCV(type, var, val) \
		m_##var = (val); \
		type& var = m_##var
#endif//DEWCV
#ifndef DEWCP	// declare and write current class variable pointer with new value
	#define DEWCP(type, var, val) \
		m_##var = (val); \
		type& var = *m_##var
#endif//DEWCP
#ifndef DEWOV	// declare and write other class variable with new value
	#define DEWOV(type, base, var, val) \
		(base).m_##var = (val); \
		type& var = (base).m_##var
#endif//DEWOV
#ifndef DEWOP	// declare and write other class variable pointer with new value
	#define DEWOP(type, base, var, val) \
		(base).m_##var = (val); \
		type& var = *(base).m_##var
#endif//DEWOP
#ifndef DEWRV	// declare and write renamed variable with new value
	#define DEWRV(type, var, member, val) \
		member = (val); \
		type& var = member
#endif//DEWRV
#ifndef DEWRP	// declare and write renamed variable pointer with new value
	#define DEWRP(type, var, member, val) \
		member = (val); \
		type& var = *member
#endif//DEWRP
#ifndef DEWRA_2D
	/**
	 * @see TRACEARR_S2D
	 **/
	#define DEWRA_2D(type, var, m, n, member) { \
			type* _p; \
			int _m = (m); \
			int _n = (n); \
			int size = _m*sizeof(type*) + _m*_n*sizeof(type); \
			member = (type**)malloc(size); \
			memset(member, 0, size); \
			_p = (type*)(member+_m); \
			for (int _i=0 ; _i<_m ; _i++) { \
				member[_i] = _p; \
				_p+=_n; \
			} \
		} \
		type**& var = member
#endif//DEWRA_2D

#endif//_GENERAL_DEBUG_H
