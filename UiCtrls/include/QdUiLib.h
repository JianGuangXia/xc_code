// QdUiLib.h : QdUiLib DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#ifndef __QDUILIB_H__
#define __QDUILIB_H__

#if defined(WIN32)
	#ifdef LIB_QDUILIBEXPORT
		#define QDUILIBEXPORT		AFX_CLASS_EXPORT
	#else
		#define QDUILIBEXPORT		AFX_CLASS_IMPORT
	#endif
#else
	#define QDUILIBEXPORT
#endif

#endif // __QDUILIB_H__