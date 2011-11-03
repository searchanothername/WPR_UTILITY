/*
* Copyright (c) 2006 ,成都远望科技有限责任公司软件产品开发部,  
* All rights reserved
*
* 文件名称：WPRDriverlib.h
* 文件标识：
* 摘    要：该文件为风廓线雷达数据采集处理卡驱动程序接口文件。
			主要内容有：接口函数原型申明、函数返回状态类型定义。
*
* 当前版本：0.1
* 作者：王文明
* 完成日期：2006年4月30日
*
*/
#ifndef WPRAPIDRIVER
#define WPRAPIDRIVER
//库函数声明
bool WPRAPI_Init();//初始化
void WPRAPI_Release();//释放
bool WPRAPI_InstallCallback(void (*pCallBack)(void *Buff,int len));
bool WPRAPI_UninstallCallback();
bool WPRAPI_GetVersion( char *pVer);
bool WPRAPI_ReadData(int WPR_BAR,unsigned int Offset,unsigned int *InBuffer,int len);
bool WPRAPI_WriteData (int WPR_BAR,unsigned int Offset,unsigned int *OutBuffer,int len);
bool WPRAPI_DMASet (int Size);
bool WPRAPI_EnableInterrupt();//局部中断、DMA中断使能
bool WPRAPI_DisableInterrupt();//禁止局部中断、DMA中断

#endif
