/*
* Copyright (c) 2006 ,�ɶ�Զ���Ƽ��������ι�˾�����Ʒ������,  
* All rights reserved
*
* �ļ����ƣ�WPRDriverlib.h
* �ļ���ʶ��
* ժ    Ҫ�����ļ�Ϊ�������״����ݲɼ�������������ӿ��ļ���
			��Ҫ�����У��ӿں���ԭ����������������״̬���Ͷ��塣
*
* ��ǰ�汾��0.1
* ���ߣ�������
* ������ڣ�2006��4��30��
*
*/
#ifndef WPRAPIDRIVER
#define WPRAPIDRIVER
//�⺯������
bool WPRAPI_Init();//��ʼ��
void WPRAPI_Release();//�ͷ�
bool WPRAPI_InstallCallback(void (*pCallBack)(void *Buff,int len));
bool WPRAPI_UninstallCallback();
bool WPRAPI_GetVersion( char *pVer);
bool WPRAPI_ReadData(int WPR_BAR,unsigned int Offset,unsigned int *InBuffer,int len);
bool WPRAPI_WriteData (int WPR_BAR,unsigned int Offset,unsigned int *OutBuffer,int len);
bool WPRAPI_DMASet (int Size);
bool WPRAPI_EnableInterrupt();//�ֲ��жϡ�DMA�ж�ʹ��
bool WPRAPI_DisableInterrupt();//��ֹ�ֲ��жϡ�DMA�ж�

#endif
