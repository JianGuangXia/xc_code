#pragma once
#ifdef _WIN32
#define DWORD unsigned long 
#define QWORD unsigned __int64
#else
#define DWORD unsigned int 
#define QWORD unsigned long long
#endif
#define MaxConnect_Count 10      // �û�����Ĭ������
#define MaxSize 1000             // �����б�����
#define Scdm_SSE "SSE"           // �Ͻ�������
#define Scdm_SZSE "SZSE"         // �������
#define Scdm_SSEOPT "SSEOPT"     // �Ͻ�����Ȩ

#define Msgid_Connect_Successed      0       // ���ӳɹ� 
#define Msgid_Reconnect_Failed    -100       // ����ʧ�� 
#define Msgid_Reconnect_Successed  100       // �����ɹ�
#define Msgid_Reconnect_Connecting 101       // ��������

#define New_Version 1