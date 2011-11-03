// DoptestParamDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "DoptestParamDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoptestParamDlg dialog
CString str_BeamName[10] = {"EH","EL",
							"NH","NL",
							"VH","VL",
							"WH","WL",
							"SH","SL"
};
enum{EH=0,EL=1,NH=2,NL=3,VH=4,VL=5,WH=6,WL=7,SH=8,SL=9};


CDoptestParamDlg::CDoptestParamDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDoptestParamDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDoptestParamDlg)
	m_TST_DOP_PHASE = 0;
	m_TST_BEAM_NUM = 0;
	m_TST_RF_FREQ = 0;
	m_TST_COAX_SWITCH = 0;
	m_TST_BM_DIRCHANGE = 0;
	m_TST_LO_PHASE = 0;
	m_TST_NOISE_SOURCE = 0;
	m_TST_SIGNAL_AMP = 0;
	m_TST_SIGNAL_OUTPUT = 0;
	m_TST_SIGNAL_SOURCE = 0;
	m_TST_SM_RESET = 0;
	m_TST_TRANSMITTER = 0;
	m_TST_RF_ATTEN = 0;
	m_TST_DOP_TST_CTRL = 0;
	m_TST_RF_GATEMOVING = 0;
	m_TST_DIF_GATEMOVING = 0;
	m_TST_PCCODE_MOVING = 0;
	//}}AFX_DATA_INIT
}


void CDoptestParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoptestParamDlg)
	DDX_Control(pDX, IDC_TST_BEAM_NUM, m_TST_BEAM_NUM_COMB);
	DDX_CBIndex(pDX, IDC_TST_DOP_PHASE, m_TST_DOP_PHASE);
	DDX_CBIndex(pDX, IDC_TST_BEAM_NUM, m_TST_BEAM_NUM);
	DDX_CBIndex(pDX, IDC_TST_RF_FREQ, m_TST_RF_FREQ);
	DDX_CBIndex(pDX, IDC_TST_COAX_SWITCH, m_TST_COAX_SWITCH);
	DDX_CBIndex(pDX, IDC_TST_BM_DIRCHANGE, m_TST_BM_DIRCHANGE);
	DDX_CBIndex(pDX, IDC_TST_LO_PHASE, m_TST_LO_PHASE);
	DDX_CBIndex(pDX, IDC_TST_NOISE_SOURCE, m_TST_NOISE_SOURCE);
	DDX_CBIndex(pDX, IDC_TST_SIGNAL_AMP, m_TST_SIGNAL_AMP);
	DDX_CBIndex(pDX, IDC_TST_SIGNAL_OUTPUT, m_TST_SIGNAL_OUTPUT);
	DDX_CBIndex(pDX, IDC_TST_SIGNAL_SOURCE, m_TST_SIGNAL_SOURCE);
	DDX_CBIndex(pDX, IDC_TST_SM_RESET, m_TST_SM_RESET);
	DDX_CBIndex(pDX, IDC_TST_TRANSMITTER, m_TST_TRANSMITTER);
	DDX_Text(pDX, IDC_TST_RF_ATTEN, m_TST_RF_ATTEN);
	DDV_MinMaxInt(pDX, m_TST_RF_ATTEN, 0, 103);
	DDX_CBIndex(pDX, IDC_DP_TEST_CTRL, m_TST_DOP_TST_CTRL);
	DDX_Text(pDX, IDC_TST_RF_GATEMOVING, m_TST_RF_GATEMOVING);
	DDV_MinMaxInt(pDX, m_TST_RF_GATEMOVING, 0, 255);
	DDX_Text(pDX, IDC_TST_DIF_GATEMOVING, m_TST_DIF_GATEMOVING);
	DDV_MinMaxInt(pDX, m_TST_DIF_GATEMOVING, 0, 15);
	DDX_Text(pDX, IDC_TST_PCCODEMOVING, m_TST_PCCODE_MOVING);
	DDV_MinMaxInt(pDX, m_TST_PCCODE_MOVING, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDoptestParamDlg, CDialog)
	//{{AFX_MSG_MAP(CDoptestParamDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoptestParamDlg message handlers

BOOL CDoptestParamDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	// For out looking
    m_bkBrush.CreateSolidBrush(RGB(58,58,58));
    
	// For paramer setting
	int Param[17];                  
	CFile inFile;       
	char* pFileName = "TestParam.dat";
	if(inFile.Open(pFileName,CFile::modeRead)!=0)
	{
		inFile.Read( (void*)Param,17*4); 
		inFile.Close();
		m_TST_BEAM_NUM       = Param[0];
		m_TST_DOP_PHASE      = Param[1];
		m_TST_RF_ATTEN       = Param[2];
		m_TST_RF_FREQ        = Param[3];
		m_TST_COAX_SWITCH    = Param[4];
		m_TST_DOP_TST_CTRL   = Param[5];  
		m_TST_BM_DIRCHANGE   = Param[6];
		m_TST_LO_PHASE       = Param[7];
		m_TST_NOISE_SOURCE   = Param[8];
		m_TST_SIGNAL_AMP     = Param[9];
		m_TST_SIGNAL_OUTPUT  = Param[10];
		m_TST_SIGNAL_SOURCE  = Param[11];
		m_TST_SM_RESET       = Param[12];
		m_TST_TRANSMITTER    = Param[13];
		m_TST_RF_GATEMOVING  = Param[14];
		m_TST_DIF_GATEMOVING = Param[15];
		m_TST_PCCODE_MOVING  = Param[16];
	}
	// For beam num sel
	for(int i=EH; i<=SL; i++){
		m_TST_BEAM_NUM_COMB.InsertString(i,str_BeamName[i]);
	} 
	m_TST_BEAM_NUM_COMB.SetCurSel(m_TST_BEAM_NUM-1);

	UpdateData( FALSE );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CDoptestParamDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
		if(nCtlColor == CTLCOLOR_STATIC 
		|| nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetBkColor(RGB(58,58,58));
		pDC->SetTextColor(RGB(255,255,0));
		
	}

	if(nCtlColor == CTLCOLOR_LISTBOX){
			//For Alarm list
        //pDC->SetBkColor(RGB(58,58,58));
		pDC->SetBkMode(0);
		pDC->SetTextColor(RGB(255,255,0));
	}
	// TODO: Return a different brush if the default is not desired
	return m_bkBrush;
	//return hbr;
}
