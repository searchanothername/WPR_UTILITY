// NormalSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "NormalSettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Global_SM.h"
/////////////////////////////////////////////////////////////////////////////
// CNormalSettingDlg dialog


CNormalSettingDlg::CNormalSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNormalSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNormalSettingDlg)
	m_nByteSize = 8;
	m_nStopBits = 1;
	m_nSharedMemory = 0;
	m_nPort = 0;
	m_strArchivePath = _T("");
	m_bCycleTest = FALSE;
	m_bRemoteCtrl = FALSE;
	m_nPathBinary = 0;
	m_nByteSize_GM = 8;
	m_nStopBits_GM = 1;
	m_bSM_INUSE = FALSE;
	m_bGM_INUSE = FALSE;
	m_nByteNumber_SM = 0;
	m_nByteNumber_UPS = 0;
	m_bSM_HRD_CHECK = FALSE;
	m_bGM_HRD_CHECK = FALSE;
	//}}AFX_DATA_INIT
}


void CNormalSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNormalSettingDlg)
	DDX_Control(pDX, IDC_IPADDRESS, m_ctlServIP);
	DDX_Control(pDX, IDC_BAUDCOMBO_GM, m_BaudRate_GM);
	DDX_Control(pDX, IDC_PORTCOMBO_GM, m_PortName_GM);
	DDX_Control(pDX, IDC_PARITYCOMBO_GM, m_Parity_GM);
	DDX_Control(pDX, IDC_PARITYCOMBO, m_Parity);
	DDX_Control(pDX, IDC_BAUDCOMBO, m_BaudRate);
	DDX_Control(pDX, IDC_PORTCOMBO, m_PortName);
	DDX_Text(pDX, IDC_BYTESIZE, m_nByteSize);
	DDX_Text(pDX, IDC_STOPBITS, m_nStopBits);
	DDX_Radio(pDX, IDC_SHAREDMEMORY, m_nSharedMemory);
	DDX_Text(pDX, IDC_PORT, m_nPort);
	DDX_Text(pDX, IDC_ARCHIVEPATH, m_strArchivePath);
	DDV_MaxChars(pDX, m_strArchivePath, 199);
	DDX_Check(pDX, IDC_CYCLETEST, m_bCycleTest);
	DDX_Check(pDX, IDC_REMOTECTRL, m_bRemoteCtrl);
	DDX_Radio(pDX, IDC_PATHBINARY, m_nPathBinary);
	DDX_Text(pDX, IDC_BYTESIZE_GM, m_nByteSize_GM);
	DDX_Text(pDX, IDC_STOPBITS_GM, m_nStopBits_GM);
	DDX_Check(pDX, IDC_SM_INUSE, m_bSM_INUSE);
	DDX_Check(pDX, IDC_GM_INUSE, m_bGM_INUSE);
	DDX_Text(pDX, IDC_EDIT_BYTE_READ_SM, m_nByteNumber_SM);
	DDV_MinMaxUInt(pDX, m_nByteNumber_SM, 0, 100);
	DDX_Text(pDX, IDC_EDIT_BYTE_READ_UPS, m_nByteNumber_UPS);
	DDV_MinMaxUInt(pDX, m_nByteNumber_UPS, 0, 100);
	DDX_Check(pDX, IDC_SM_HRD_CHECK, m_bSM_HRD_CHECK);
	DDX_Check(pDX, IDC_GM_HRD_CHECK, m_bGM_HRD_CHECK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNormalSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CNormalSettingDlg)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_TCPIP, OnTcpip)
	ON_BN_CLICKED(IDC_SHAREDMEMORY, OnSharedmemory)
	ON_BN_CLICKED(IDC_UDP, OnUdp)
	ON_BN_CLICKED(IDC_PATHBINARY, OnPathbinary)
	ON_BN_CLICKED(IDC_PATHNONE, OnPathnone)
	ON_BN_CLICKED(IDC_PATHTEXT, OnPathtext)
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_SM_INUSE, OnSmInuse)
	ON_BN_CLICKED(IDC_GM_INUSE, OnGmInuse)
	ON_BN_CLICKED(IDC_SM_HRD_CHECK, OnSmHrdCheck)
	ON_BN_CLICKED(IDC_GM_HRD_CHECK, OnGmHrdCheck)
	ON_EN_CHANGE(IDC_EDIT_BYTE_READ_SM, OnChangeEditByteReadSm)
	ON_EN_CHANGE(IDC_EDIT_BYTE_READ_UPS, OnChangeEditByteReadUps)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNormalSettingDlg message handlers

BOOL CNormalSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	///////////////////////////////
	//For outlook
    m_bkBrush.CreateSolidBrush(RGB(58,58,58));

	//READ ADAPTOR

	//FOR STATUS MONITOR PORT
    for(int i=0; i<3; i++){
		m_BaudRate.AddString(baudrate[i]);
		m_Parity.AddString(parity[i]);

		m_BaudRate_GM.AddString(baudrate[i]);
		m_Parity_GM.AddString(parity[i]);
	}
	//m_Parity.AddString(parity[2]);
	//m_Parity_GM.AddString(parity[2]);

	for(i=0; i<6; i++){
		m_PortName.AddString(portname[i]);
		m_PortName_GM.AddString(portname[i]);
	}

	switch(g_sm_port_config.baudrate){
	case 2400:
		m_BaudRate.SetCurSel(0);
		break;
	case 9600:
		m_BaudRate.SetCurSel(1);
		break;
	case 19200:
		m_BaudRate.SetCurSel(2);
		break;
	default:
		break;
	};

	CString curPortName;
	curPortName.Format("%s",g_sm_port_config.str_portname);
	for(i=0; i<6; i++){
		if(0==curPortName.Compare(portname[i])){
				m_PortName.SetCurSel(i);
		}
	}
    
    switch(g_sm_port_config.parity){
	case 0:
		m_Parity.SetCurSel(0);
		break;
	case 1:
		m_Parity.SetCurSel(1);
		break;
	case 2:
		m_Parity.SetCurSel(2);
	default:
		break;
	};


	m_nByteNumber_SM  = g_sm_port_config.byte_num;

	///////////////////////////////////////////////
	//FOR FREQ GENERATOR(GM) PORT
    switch(g_sg_port_config.baudrate){
	case 2400:
		m_BaudRate_GM.SetCurSel(0);
		break;
	case 9600:
		m_BaudRate_GM.SetCurSel(1);
		break;
	case 19200:
		m_BaudRate_GM.SetCurSel(2);
	default:
		break;
	};


	curPortName.Format("%s",g_sg_port_config.str_portname);
	for(i=0; i<6; i++){
		if(0==curPortName.Compare(portname[i])){
				m_PortName_GM.SetCurSel(i);
		}
	}
    
    switch(g_sg_port_config.parity){
	case 0:
		m_Parity_GM.SetCurSel(0);
		break;
	case 1:
		m_Parity_GM.SetCurSel(1);
		break;
	case 2:
		m_Parity_GM.SetCurSel(2);
	default:
		break;
	};

	
	m_nByteNumber_UPS  = g_sg_port_config.byte_num;

	//SEE WHICH PORT WILL BE AVAILABLE
	m_bSM_INUSE = g_sm_port_config.bInUse;
    m_bGM_INUSE = g_sg_port_config.bInUse;

	//IF WE NEED TO CHECK THE HEADER
	m_bGM_HRD_CHECK = g_sg_port_config.bHRDCheck;
	m_bSM_HRD_CHECK = g_sm_port_config.bHRDCheck;

	//FOR COMMUNICATION WITH THIERRY
	m_nSharedMemory = g_communication_config.selection;
	m_ctlServIP.SetAddress(g_communication_config.server_ip);
	m_nPort = g_communication_config.port;

	//FOR CONTROL SETTING
	m_strArchivePath.Format("%s",g_ctrl_config.str_archive_path);
	m_bCycleTest = g_ctrl_config.b_CycleTest;
	m_bRemoteCtrl = g_ctrl_config.b_RemoteCtrl;
	m_nPathBinary  = g_ctrl_config.selection;


	

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNormalSettingDlg::OnOK() 
{
	// TODO: Add extra validation here
    //Save Adaptor	
	UpdateData(TRUE);
	int baudsel = m_BaudRate.GetCurSel();
	switch(baudsel){
	case 0:
		g_sm_port_config.baudrate = 2400;
		break;
	case 1:
		g_sm_port_config.baudrate = 9600;
		break;
	case 2:
		g_sm_port_config.baudrate = 19200;
		break;
	default:
		break;
	};

	baudsel = m_BaudRate_GM.GetCurSel();
	switch(baudsel)
	{
	case 0:
		g_sg_port_config.baudrate = 2400;
		break;
	case 1:
		g_sg_port_config.baudrate = 9600;
		break;
	case 2:
		g_sg_port_config.baudrate = 19200;
		break;
	default:
		break;
	};

	
	int length = portname[m_PortName.GetCurSel()].GetLength()+1;
	char* pString = portname[m_PortName.GetCurSel()].GetBufferSetLength(length);
	sprintf(g_sm_port_config.str_portname,pString);

    length = portname[m_PortName_GM.GetCurSel()].GetLength()+1;
    pString = portname[m_PortName_GM.GetCurSel()].GetBufferSetLength(length);
	sprintf(g_sg_port_config.str_portname,pString);
	
	g_sm_port_config.parity = m_Parity.GetCurSel();
	g_sg_port_config.parity = m_Parity_GM.GetCurSel();

	g_communication_config.selection = m_nSharedMemory;
	m_ctlServIP.GetAddress(g_communication_config.server_ip);
	g_communication_config.port = m_nPort;

	//SAVE THE CONTROL SETTING
	length = m_strArchivePath.GetLength()+1;
	pString = m_strArchivePath.GetBufferSetLength(length);
	sprintf(g_ctrl_config.str_archive_path,pString);
    g_ctrl_config.b_CycleTest = m_bCycleTest;
	g_ctrl_config.b_RemoteCtrl = m_bRemoteCtrl;
	g_ctrl_config.selection = m_nPathBinary;


	//SAVE THE BYTES NUMBER OF UPS
	g_sm_port_config.byte_num = this->m_nByteNumber_SM;
	g_sg_port_config.byte_num = this->m_nByteNumber_UPS;

	SavePortAdapor();
	CDialog::OnOK();
}

HBRUSH CNormalSettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	 if(nCtlColor == CTLCOLOR_STATIC || nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetBkColor(RGB(58,58,58));
		pDC->SetTextColor(RGB(255,255,0));
	}
	if(nCtlColor == CTLCOLOR_LISTBOX){
		pDC->SetBkMode(0);
		pDC->SetTextColor(RGB(255,255,0));	
	}

	return m_bkBrush;
	// TODO: Return a different brush if the default is not desired
	//return hbr;
}

void CNormalSettingDlg::OnTcpip() 
{
	// TODO: Add your control notification handler code here
    m_nSharedMemory = 1;
}

void CNormalSettingDlg::OnSharedmemory() 
{
	// TODO: Add your control notification handler code here
	m_nSharedMemory = 0;
}

void CNormalSettingDlg::OnUdp() 
{
	// TODO: Add your control notification handler code here
	m_nSharedMemory = 2;
}

void CNormalSettingDlg::OnPathbinary() 
{
	// TODO: Add your control notification handler code here
	m_nPathBinary = SAVE_BINARY;	
}

void CNormalSettingDlg::OnPathnone() 
{
	// TODO: Add your control notification handler code here
	m_nPathBinary = SAVE_NONE;
}

void CNormalSettingDlg::OnPathtext() 
{
	// TODO: Add your control notification handler code here
	m_nPathBinary = SAVE_TEXT;
}

/////////////////////////////////////////////////////////////////////////
//THIS FUNCTION IS TO SELECT THE PATH FOR SAVE THE DATA
/////////////////////////////////////////////////////////////////////////
void CNormalSettingDlg::OnOpen() 
{
	// TODO: Add your control notification handler code here
	CString strResult =""; 
    LPMALLOC lpMalloc;  // POINTER TO IMALLOC 
    if (::SHGetMalloc(&lpMalloc) != NOERROR) 
	{ 
		AfxMessageBox("PATH OPERATION ERROR!"); 
		return ; 
	} 

    char szDisplayName[_MAX_PATH]; 
    char szBuffer[_MAX_PATH]; 
    BROWSEINFO browseInfo; 
    browseInfo.hwndOwner = this->m_hWnd; 
    // set root at Desktop 
    browseInfo.pidlRoot = NULL; 
    browseInfo.pszDisplayName = szDisplayName; 
    browseInfo.lpszTitle = "PATH FOR SAVE IQ DATA";  
    browseInfo.ulFlags = BIF_RETURNFSANCESTORS|BIF_RETURNONLYFSDIRS; 
    browseInfo.lpfn = NULL;   
    browseInfo.lParam = 0;      

    LPITEMIDLIST lpItemIDList; 
    if ((lpItemIDList = ::SHBrowseForFolder(&browseInfo)) 
        != NULL) 
    { 
        // GET THE PATH OF THE SELECTED FOLDER FROM THE  ITEM ID LIST. 
        if (::SHGetPathFromIDList(lpItemIDList, szBuffer)) 
        { 
            // AT THIS POINT, SZBUFFER CONTAINS THE PATH THE USER CHOSE. 
            if (szBuffer[0] == '\0') 
            { 
                // SHGETPATHFROMIDLIST FAILED, OR SHBROWSEFORFOLDER FAILED. 
                AfxMessageBox("FAIL TO GET DIRECTORY!", 
                    MB_ICONSTOP|MB_OK); 
                return ; 
            } 
            // WE HAVE A PATH IN SZBUFFER! RETURN IT. 
            strResult = szBuffer; 
        } 
        else 
        { 
            // THE THING REFERRED TO BY LPITEMIDLIST 
            // MIGHT NOT HAVE BEEN A FILE SYSTEM OBJECT. 
            // FOR WHATEVER REASON, SHGETPATHFROMIDLIST DIDN'T WORK! 
            AfxMessageBox("FAIL TO GET DIRECTORY!", 
                MB_ICONSTOP|MB_OK); 
            return ; 
        } 
        lpMalloc->Free(lpItemIDList); 
        lpMalloc->Release(); 
    } 

	m_strArchivePath = strResult;
	UpdateData(FALSE); 	
}

void CNormalSettingDlg::OnSmInuse() 
{
	// TODO: Add your control notification handler code here
	m_bSM_INUSE = !m_bSM_INUSE;
	g_sm_port_config.bInUse = m_bSM_INUSE;
	UpdateData(FALSE);
  
}

void CNormalSettingDlg::OnGmInuse() 
{
	// TODO: Add your control notification handler code here
	m_bGM_INUSE = !m_bGM_INUSE;
    g_sg_port_config.bInUse =  m_bGM_INUSE;
	UpdateData(FALSE);
}

void CNormalSettingDlg::OnSmHrdCheck() 
{
	// TODO: Add your control notification handler code here
	m_bSM_HRD_CHECK = !m_bSM_HRD_CHECK;
	g_sm_port_config.bHRDCheck = m_bSM_HRD_CHECK;
	UpdateData(FALSE);
}

void CNormalSettingDlg::OnGmHrdCheck() 
{
	// TODO: Add your control notification handler code here
	m_bGM_HRD_CHECK = !m_bGM_HRD_CHECK;
	g_sg_port_config.bHRDCheck = m_bGM_HRD_CHECK;
	UpdateData(FALSE);
}

void CNormalSettingDlg::OnChangeEditByteReadSm() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CNormalSettingDlg::OnChangeEditByteReadUps() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}
