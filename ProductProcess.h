// ProductProcess.h: interface for the CProductProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRODUCTPROCESS_H__32B04788_236A_4C1D_8E96_171D6092D04B__INCLUDED_)
#define AFX_PRODUCTPROCESS_H__32B04788_236A_4C1D_8E96_171D6092D04B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thread.h"

enum SWITCHOR{
	SWITCHOR_A,
	SWITCHOR_B
};
class CWPR_UTILITIESDlg;

class CProductProcess : public CThread  
{
	friend DWORD WINAPI limit_cal(LPVOID lParam);
	friend DWORD WINAPI products_cal(LPVOID lParam);
	friend DWORD WINAPI spectra_cal(LPVOID lParam);

public:
	CProductProcess();
	virtual ~CProductProcess();
	DWORD Run(void* pParam);
	DWORD Stop(void* pParam);

public:
	void set_switchor(SWITCHOR s){_sw = s;}
	SWITCHOR get_switchor(){return _sw;}
	void SetParent(CWPR_UTILITIESDlg* pWindow);

private:
    void calculateLimit();
    void calculateProducts();
	void cal_noise_level(const int rangebin);
	void cal_base_product(const int rangebin);
    void findSignal(int &nlowBin,int &nHighBin, int &nPeakbin,const int rangebin);
    double cal_velocity (int bin_no, double& klambda);

private:
    int n_specId;
	int n_beamId;
	int n_rangebin;
	int n_fft;
	double prt;
	double tda;
	SWITCHOR _sw;
	CWPR_UTILITIESDlg* g_utility;

};

#endif // !defined(AFX_PRODUCTPROCESS_H__32B04788_236A_4C1D_8E96_171D6092D04B__INCLUDED_)
