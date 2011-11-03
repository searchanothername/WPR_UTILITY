// WPR_UTILITIESDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WPR_UTILITIES.h"
#include "WPR_UTILITIESDlg.h"
#include "BasicSettingDlg.h"
#include "NormalSettingDlg.h"
#include "AdvancedSettingDlg.h"
#include "TotalSpecDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Global.h"
#include "Global_SM.h"
#include "Global_CtrlWords.h"
#include "Global_Advanced.h"
#include "A44_sm_handler.h"
#include "Performance.h"
#include "Global_CtrlWords.h"
#include "PerformanceDlg.h"
#include <math.h>
#include "UPSDlg.h"
#include "StatusMonitorDlg.h"
#include "DataView.h"
#include "TotalSpecDlg.h"


//#include "Pf_sundries_1.h"

#define IDEvent 1000
#define IDEventTxInfo (IDEvent+1)
#define IDEventStatusBarTime (IDEventTxInfo+1)


void LogsmCtrlWords(char* str);
BOOL bSMOn = TRUE;

int old_value = 0;//-103;
volatile int cur_value = 0;
volatile int RFAttenuationChanged = 0;
int old_rtac_value = -60;
volatile int cur_rtac_value = 0;
volatile int RTACChanged = 0;

#define EAST_DIREC		1
#define NORTH_DIREC		2
#define VERTICAL_DIREC	4
#define WEST_DIREC		5
#define SOUTH_DIREC		6

static UINT BASED_CODE indicators[2] = {
	ID_INDICATOR_INFORMATION,
	ID_INDICATOR_TIME
};
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
        
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWPR_UTILITIESDlg dialog

CWPR_UTILITIESDlg::CWPR_UTILITIESDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWPR_UTILITIESDlg::IDD, pParent),
	bDataViewEnable(FALSE),
	bSpectrasViewEnable(FALSE)
{
	//{{AFX_DATA_INIT(CWPR_UTILITIESDlg)
	m_HPA0_ON = FALSE;
	m_str_ups_status = _T("");
	m_b_west = FALSE;
	m_b_virtical = FALSE;
	m_b_south = FALSE;
	m_b_north = FALSE;
	m_b_east = FALSE;
	m_strSysInfo = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWPR_UTILITIESDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWPR_UTILITIESDlg)
	DDX_Control(pDX, IDC_STATIC_SM_DATA, m_sm_data_display);
	DDX_Control(pDX, IDC_INTRCOUNT, m_InterCount);
	DDX_Control(pDX, IDC_EDIT_SYSINFO, m_SysInfo);
	DDX_Control(pDX, IDC_LIST_ALARMSHOW, m_alarmdisplist);
	DDX_Control(pDX, IDC_STATIC_WIQCLK, m_static_dsp_wiqclk);
	DDX_Control(pDX, IDC_STATIC_WDVCC, m_static_dsp_wdvcc);
	DDX_Control(pDX, IDC_STATIC_WAVCC, m_static_dsp_wavcc);
	DDX_Control(pDX, IDC_STATIC_WADCLK, m_static_dsp_wadclk);
	DDX_Control(pDX, IDC_STATIC_TXBIAS, m_static_dsp_txbias);
	DDX_Control(pDX, IDC_STATIC_LRB, m_static_dsp_lrb);
	DDX_Control(pDX, IDC_STATIC_TRAMP, m_static_dsp_tramp);
	DDX_Control(pDX, IDC_STATIC_T0, m_static_dsp_t0);
	DDX_Control(pDX, IDC_STATIC_STC, m_static_dsp_stc);
	DDX_Control(pDX, IDC_STATIC_RD, m_static_dsp_rd);
	DDX_Control(pDX, IDC_STATIC_TX_SWR, m_static_tx_swr);
	DDX_Control(pDX, IDC_STATIC_TX_RFON, m_static_tx_rf_on);
	DDX_Control(pDX, IDC_STATIC_TX_PS, m_static_txps);
	DDX_Control(pDX, IDC_STATIC_TX_OVERTEMP, m_static_overtemp);
	DDX_Control(pDX, IDC_STATIC_TX_OUTPUT, m_static_tx_output);
	DDX_Control(pDX, IDC_STATIC_TX_INPUT, m_static_tx_input);
	DDX_Control(pDX, IDC_STATIC_DUTY, m_static_duty);
	DDX_Control(pDX, IDC_STATIC_OUTPUT_PWR, m_static_output_pwr);
	DDX_Control(pDX, IDC_STATIC_INPUT_PWR, m_static_input_pwr);
	DDX_Control(pDX, IDC_CHECK_EAST, m_button_east);
	DDX_Control(pDX, IDC_CHECK_NORTH, m_button_north);
	DDX_Control(pDX, IDC_CHECK_SOUTH, m_button_south);
	DDX_Control(pDX, IDC_CHECK_VIRTICAL, m_button_virtical);
	DDX_Control(pDX, IDC_CHECK_WEST, m_button_west);
	DDX_Control(pDX, IDC_EDIT_UPS, m_ups_status);
	DDX_Control(pDX, IDC_BUTTON_UPS, m_button_ups);
	DDX_Control(pDX, IDC_PHA0, m_HPA0);
	DDX_Control(pDX, IDC_HPA0_STATUS, m_hpa0_status);
	DDX_Control(pDX, IDC_RTACSLIDER, m_RTACSlider);
	DDX_Control(pDX, IDC_ALARM_LIST, m_ListCtrl);
	DDX_Control(pDX, IDC_SLIDER, m_RFAttenSlider);
	DDX_Check(pDX, IDC_PHA0, m_HPA0_ON);
	DDX_Text(pDX, IDC_EDIT_UPS, m_str_ups_status);
	DDX_Check(pDX, IDC_CHECK_WEST, m_b_west);
	DDX_Check(pDX, IDC_CHECK_VIRTICAL, m_b_virtical);
	DDX_Check(pDX, IDC_CHECK_SOUTH, m_b_south);
	DDX_Check(pDX, IDC_CHECK_NORTH, m_b_north);
	DDX_Check(pDX, IDC_CHECK_EAST, m_b_east);
	DDX_Text(pDX, IDC_EDIT_SYSINFO, m_strSysInfo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWPR_UTILITIESDlg, CDialog)
	//{{AFX_MSG_MAP(CWPR_UTILITIESDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDM_EXIT, OnExit)
	ON_WM_CTLCOLOR()
	ON_COMMAND(IDM_NORTEST_SETTING, OnNortestSetting)
	ON_COMMAND(IDM_SIMULATOR, OnSimulator)
	ON_COMMAND(IDM_SM, OnSm)
	ON_COMMAND(IDM_BASIC_SETTING, OnBasicSetting)
	ON_BN_CLICKED(IDC_PHA0, OnPha0)
	ON_COMMAND(IDM_TEST_STOP, OnTestStop)
	ON_COMMAND(IDM_TESTANDGETDATA, OnTestandgetdata)
	ON_WM_TIMER()
	ON_COMMAND(IDM_START_SM, OnStartSm)
	ON_COMMAND(IDM_STOP_SM, OnStopSm)
	ON_COMMAND(IDM_ADVANCED_SETTING, OnAdvancedSetting)
	ON_WM_HSCROLL()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN, OnDeltaposSpin)
	ON_COMMAND(IDM_START_UPS, OnStartUps)
	ON_COMMAND(IDM_STOP_UPS, OnStopUps)
	ON_BN_CLICKED(IDC_BUTTON_UPS, OnButtonUps)
	ON_BN_CLICKED(IDC_BUTTON_STATUS, OnButtonStatus)
	ON_BN_CLICKED(IDC_CHECK_EAST, OnCheckEast)
	ON_BN_CLICKED(IDC_CHECK_NORTH, OnCheckNorth)
	ON_BN_CLICKED(IDC_CHECK_SOUTH, OnCheckSouth)
	ON_BN_CLICKED(IDC_CHECK_VIRTICAL, OnCheckVirtical)
	ON_BN_CLICKED(IDC_CHECK_WEST, OnCheckWest)
	ON_COMMAND(IDM_DATAVIEW, OnDataview)
	ON_UPDATE_COMMAND_UI(IDM_START_SM, OnUpdateStartSm)
	ON_UPDATE_COMMAND_UI(IDM_STOP_SM, OnUpdateStopSm)
	ON_WM_COPYDATA()
	ON_BN_CLICKED(IDC_BUTTON_DYNTEST, OnButtonDyntest)
	ON_COMMAND(IDM_TOTALSPEC_VIEW, OnTotalspecView)
	ON_MESSAGE(WM_MYSHOW,ShowData)
	ON_MESSAGE(WM_SHOW_SPEC_SINGLE, ShowSpecSingle)
	ON_MESSAGE(WM_SHOW_SPEC_AVG, ShowSpecAvg)
	ON_MESSAGE(WM_SHOW_SPEC_TOTAL,ShowSpecTotal)
	ON_BN_CLICKED(IDC_BUTTON_INCLINOMETER, OnButtonInclinometer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWPR_UTILITIESDlg message handlers

BOOL CWPR_UTILITIESDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	/*ADD A STATUS BAR*/
	m_StatusBar.Create(this);
	m_StatusBar.SetIndicators(indicators,2);
	CRect rectWin;
	GetClientRect(&rectWin);
	m_StatusBar.SetPaneInfo(0,ID_INDICATOR_INFORMATION,SBPS_NORMAL,rectWin.Width()-100);
	m_StatusBar.SetPaneInfo(1,ID_INDICATOR_TIME,SBPS_STRETCH ,0);
	m_StatusBar.GetStatusBarCtrl().SetBkColor(RGB(100,100,100));
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,
		ID_INDICATOR_TIME);
	SetTimer(IDEventStatusBarTime,1000,NULL);

	/* SAVE THE MAIN DLG'S POINTER */
    testtask.SetParent(this);
    smtask.SetParent(this);
	upstask.SetParent(this);

	/* FOR THE TOOL BAR */
	const int BUTNUM = 6;
	TBBUTTON button[BUTNUM];
	int i=0,nStringLength;
	CString string;
	TCHAR * pString; 
	
	m_ImageList.Create(48,48,ILC_COLOR32|ILC_MASK,0,0);     
	m_ToolBar.EnableAutomation();
	m_ToolBar.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDR_TOOLBAR);
	
	for(i=IDI_ICON2;i<=IDI_ICON6;i++)
	{
		m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(i))); 
	}
	//ADD A BUTTON FOR SHOW THE SPECTRAS
	m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON19)));

	m_ToolBar.SetImageList(&m_ImageList);   
	for(i=0;i<BUTNUM;i++)
	{
		button[i].dwData=0;
		button[i].fsState=TBSTATE_ENABLED;
		button[i].fsStyle=TBSTYLE_BUTTON;
		button[i].iBitmap=i;

		string.LoadString(i + IDS_STRING1);

		nStringLength= string.GetLength() + 1;
		pString = string.GetBufferSetLength(nStringLength);

		button[i].iString =m_ToolBar.AddStrings(pString);
		string.ReleaseBuffer();
		
	}
	button[0].idCommand = IDM_BASIC_SETTING;
	button[1].idCommand = IDM_NORTEST_SETTING;
	button[2].idCommand = IDM_ADVANCED_SETTING;
	button[3].idCommand = IDM_SM;
	button[4].idCommand = IDM_DATAVIEW;
	button[5].idCommand = IDM_TOTALSPEC_VIEW;

	m_ToolBar.AddButtons(BUTNUM,button); 
	button[0].fsStyle=TBSTYLE_SEP ;
	m_ToolBar.InsertButton(3,&button[0]);
	m_ToolBar.AutoSize();		
	m_ToolBar.SetStyle(TBSTYLE_FLAT|CCS_TOP);


	/* FOR THE WHOLE DIALOG OUTLOOK */
	m_bkBrush.CreateSolidBrush(RGB(58,58,58));
	HICON hIcon = 	AfxGetApp()->LoadIcon(IDI_ICON1);
	AfxGetApp()->m_pMainWnd->SetIcon(hIcon,FALSE);


	/* FOR THE LIST CTRL */
	DWORD dwStyle = GetWindowLong(m_ListCtrl.m_hWnd,GWL_STYLE);
	SetWindowLong(m_ListCtrl.m_hWnd,GWL_STYLE,dwStyle|LVS_REPORT);
	DWORD style= m_ListCtrl.GetExtendedStyle();
	m_ListCtrl.SetExtendedStyle(style|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ListCtrl.SetBkColor(RGB(58,58,58));
	m_ListCtrl.SetTextBkColor(RGB(58,58,58));
	m_ListCtrl.SetTextColor(RGB(255,255,0));

	CRect rect;
	m_ListCtrl.GetWindowRect(&rect);
	int n_ColumnWidth = rect.Width() / 2;
	char* str_Column[2] = {"SM BYTE","VALUE"};
	m_ListCtrl.InsertColumn(0,str_Column[0],LVCFMT_LEFT,n_ColumnWidth);
	m_ListCtrl.InsertColumn(1,str_Column[1],LVCFMT_LEFT,n_ColumnWidth);


	for( i=0; i< g_sm_port_config.byte_num;i++){
		CString str_Id;
		CString str_Data;
		str_Id.Format("%d",i);
		str_Data.Format("%0x",0);
			
		m_ListCtrl.DeleteItem(i);
		m_ListCtrl.InsertItem(i,str_Id);
		m_ListCtrl.SetItemText(i,1,str_Data);	
	}

    //FOR ALARM SHOW
	dwStyle = GetWindowLong(m_alarmdisplist.m_hWnd,GWL_STYLE);
	SetWindowLong(m_alarmdisplist.m_hWnd,GWL_STYLE,dwStyle|LVS_REPORT);
	style= m_alarmdisplist.GetExtendedStyle();
	m_alarmdisplist.SetExtendedStyle(style|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_alarmdisplist.SetBkColor(RGB(58,58,58));
	m_alarmdisplist.SetTextBkColor(RGB(58,58,58));
	m_alarmdisplist.SetTextColor(RGB(255,255,0));


	m_alarmdisplist.GetWindowRect(&rect);
	n_ColumnWidth = rect.Width() / 3;
	char* alarm_Column[3] = {"LEVEL","INFORMATION"};
	m_alarmdisplist.InsertColumn(0,alarm_Column[0],LVCFMT_LEFT,n_ColumnWidth+10);
	m_alarmdisplist.InsertColumn(1,alarm_Column[1],LVCFMT_LEFT,n_ColumnWidth*2-10);


	m_ImageListAlarm.Create(16,16,ILC_COLOR32|ILC_MASK,0,0); 	
	m_ImageListAlarm.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON14)));   //YELLOW
	m_ImageListAlarm.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON16)));   //RED
	m_alarmdisplist.SetImageList(&m_ImageListAlarm,LVSIL_SMALL);


	//SET SLIDER
	m_RFAttenSlider.SetRange(0,103,TRUE);
	m_RFAttenSlider.SetPos(0);

	m_RTACSlider.SetRange(0,15,TRUE);
	m_RTACSlider.SetPos(0);
	//SetTimer(IDEvent,100,NULL);

	//SET FOR HPA STATUS
	br_hpa_fault.CreateSolidBrush(RGB(255,0,0));
	br_hpa_on.CreateSolidBrush( RGB(0,255,0));
	br_hpa_off.CreateSolidBrush(RGB(255,255,0));

    pStatusArray = &m_hpa0_status;
	pHpaDC = pStatusArray->GetDC();

	//FOR STATUS MONITOR
	cmparam.cparam[0] = (char) 0;//(char)0xfe;
	cmparam.cparam[1] = (char) 0;//(char)0xbe;

	//FOR CONTROL WORDS
	SetCtrlWordsForEveryBeam();

	//SET THE BEAM DIRECTION
    m_hBeam[EAST] = ::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_EAST));
	m_hBeam[WEST] = ::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_WEST));
	m_hBeam[VIRTICAL] = ::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_VIRTICAL));
	m_hBeam[NORTH] = ::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_NORTH));
	m_hBeam[SOUTH] = ::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_SOUTH));
	
	m_hBeamSelected[EAST] = ::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_EAST_SELECTED));
	m_hBeamSelected[WEST] = ::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_WEST_SELECTED));
	m_hBeamSelected[VIRTICAL] = ::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_VIRTICAL_SELECTED));
	m_hBeamSelected[NORTH] = ::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_NORTH_SELECTED));
	m_hBeamSelected[SOUTH] = ::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_SOUTH_SELECTED));

	m_hBeam[EAST] = ::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_EAST));
	m_hBeam[WEST] = ::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_WEST));
	m_hBeam[VIRTICAL] = ::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_VIRTICAL));
	m_hBeam[NORTH] = ::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_NORTH));
	m_hBeam[SOUTH] = ::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_SOUTH));

	m_button_west.SetIcon(m_hBeam[WEST]);
	m_button_east.SetIcon(m_hBeam[EAST]);
	m_button_north.SetIcon(m_hBeam[NORTH]);
	m_button_south.SetIcon(m_hBeam[SOUTH]);
	m_button_virtical.SetIcon(m_hBeam[VIRTICAL]);
	
	//SET THE DATA FOR PWR AND DUTY
	m_static_input_pwr.SetBkColor(RGB(58,58,58));
	m_static_input_pwr.SetTextColor(RGB(0,128,255));

	m_static_output_pwr.SetBkColor(RGB(58,58,58));
	m_static_output_pwr.SetTextColor(RGB(0,128,255));

	m_static_duty.SetBkColor(RGB(58,58,58));
	m_static_duty.SetTextColor(RGB(0,128,255));

	//START THE NETWORK TASK
    if(g_communication_config.selection == COMM_NETWORK){
		global.cs_network.TurnOn();
		servertask.setPort(g_communication_config.port);
		servertask.Start();
	}

	SetTimer(IDEventTxInfo,10,NULL);

	//START TASK TO GENERATE PRODUCTS
	producttask.set_switchor(SWITCHOR_A);
	producttask.SetParent(this);
	global.cs_product.TurnOn();
	producttask.Start();


	//SHOW THE SYSTEM INFORMATION
	ShowSysInfo();

	//INITIALIZE THE INTERCOUNTER
	m_InterCount.SetColours(RGB(255,255,0), RGB(58,58,58), RGB(0,0,150));

	//INITIALIZE THE DIGITAL PWR METER.
    memset(&_f_tx_pwr_input, 0, sizeof(TX_FLOAT));
	memset(&_f_tx_pwr_output, 0, sizeof(TX_FLOAT));
	memset(&_f_tx_pwr_reflect, 0, sizeof(TX_FLOAT));


	//DISPLAY THE TITLE OF SMDATA DISPLAY
	CString str;
	str.Format("SM DATA (%d Bytes)",g_sm_port_config.byte_num);
	m_sm_data_display.SetWindowText(str);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWPR_UTILITIESDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}

	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWPR_UTILITIESDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialog::OnPaint();
	}
   
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWPR_UTILITIESDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWPR_UTILITIESDlg::OnExit() 
{
	// TODO: Add your command handler code here
	//IF TEST TASK IS STOP. THE INTERRUPT WILL BE STOPED
	if(testtask.IsStarted())
		testtask.Stop(NULL);

	//BEFORE WE STOP SM TASK . WE MUST CLOSE ALL THE HPA MODULE.
	if(smtask.IsStarted())
		smtask.Stop(NULL);

	if(servertask.IsStarted())
		servertask.Stop(NULL);

	if(producttask.IsStarted())
		producttask.Stop(NULL);


	exit(EXIT_SUCCESS);
}


void CWPR_UTILITIESDlg::ShowData(UINT wParam, UINT lParam){

	if(bDataViewEnable){
		::PostMessage(dataview->m_hWnd,WM_SHOW_DATA,wParam,lParam);
	}

	CString str_CurBeam;
	CString str_PRT;
	CString str_FFTPoints;
	CString str_SpectraNum;
	CString str_InterruptCounts;//count spectra

	str_CurBeam.Format("%s",str_Beam[g_curbeamnum]);
	str_PRT.Format("%d",g_cur_prt[g_curbeamnum]);
	str_FFTPoints.Format("%d",global.basic.basicinfo.nfft);
	str_SpectraNum.Format("%d",g_knumber_of_spectra[g_curbeamnum]);
    str_InterruptCounts.Format("SID:%d | R: %d",wParam, global.series_fifo.length());

	GetDlgItem(IDC_BEAM)->SetWindowText(str_CurBeam);
	GetDlgItem(IDC_PRT)->SetWindowText(str_PRT);
	GetDlgItem(IDC_FFTPOINTS)->SetWindowText(str_FFTPoints);
    GetDlgItem(IDC_SWEEPNUM)->SetWindowText(str_SpectraNum); 
    //GetDlgItem(IDC_INTRCOUNT)->SetWindowText(str_InterruptCounts);
	m_InterCount.SetPos( ((int)(wParam))%g_knumber_of_spectra[g_curbeamnum], true, 0, g_knumber_of_spectra[g_curbeamnum]-1);
}

void CWPR_UTILITIESDlg::ShowSpecSingle(UINT wParam, UINT lParam)
{
    if(bDataViewEnable){
		::PostMessage(dataview->m_hWnd,WM_SHOW_SPEC_SINGLE,wParam,lParam);
	}
	return;
}

void CWPR_UTILITIESDlg::ShowSpecAvg(UINT wParam, UINT lParam)
{
    if(bDataViewEnable){
		::PostMessage(dataview->m_hWnd,WM_SHOW_SPEC_AVG,wParam,lParam);
	}
	return;
}

HBRUSH CWPR_UTILITIESDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_STATIC ) 
	{
		pDC->SetBkColor(RGB(58,58,58));
		pDC->SetTextColor(RGB(0,255,0));
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

void CWPR_UTILITIESDlg::OnNortestSetting() 
{
	// TODO: Add your command handler code here
	CNormalSettingDlg  dlg;
	if(dlg.DoModal() == IDOK){
       //YOU MAY ADD SOME CODE HERE
	   //BUT I JUST LET IT SHOW PARAMETERS
	   //WHEN ALEXANDRA EXIT, THESE PARAMETERS
	   //WILL BE SAVED.
	}
	
}

void CWPR_UTILITIESDlg::OnSimulator() 
{
	// TODO: Add your command handler code here
	//HERE I WANT TO RUN SM SIMULATOR THERE ARE
	//2 SOLUTION: ONE IS TO RUN IT BY SHELL THE OTHER IS TO CREATE
	//A PROCESS. THE FIRST WAY IS TOO EASY SO I WANT TO
	//TRY ANOTHER.
    PROCESS_INFORMATION pi;
	STARTUPINFO si;

	//Initialization
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwFlags=STARTF_USESHOWWINDOW;

	//Open
	BOOL fRet=CreateProcess(NULL,
							"SM SIMULATOR.exe",
							NULL,
							NULL,
							FALSE,
							NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE,
							NULL,
							NULL,
							&si,
							&pi);

	if(!fRet)
	{//Report the fail information
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
						FORMAT_MESSAGE_FROM_SYSTEM | 
						FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL,
						GetLastError(),
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
						(LPTSTR) &lpMsgBuf,
						0,
						NULL );
		AfxMessageBox( (LPCTSTR)lpMsgBuf);
		LocalFree( lpMsgBuf );
	}
}

void CWPR_UTILITIESDlg::OnSm() 
{
	// TODO: Add your command handler code here
	//CStatusMonitorDlg dlg;
	//dlg.DoModal();

	//CALL BITEX
	 PROCESS_INFORMATION pi;
	STARTUPINFO si;

	//Initialization
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwFlags=STARTF_USESHOWWINDOW;

	//Open
	BOOL fRet=CreateProcess(NULL,
							"BITEX.exe",
							NULL,
							NULL,
							FALSE,
							NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE,
							NULL,
							NULL,
							&si,
							&pi);

	if(!fRet)
	{//Report the fail information
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
						FORMAT_MESSAGE_FROM_SYSTEM | 
						FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL,
						GetLastError(),
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
						(LPTSTR) &lpMsgBuf,
						0,
						NULL );
		AfxMessageBox( (LPCTSTR)lpMsgBuf);
		LocalFree( lpMsgBuf );
	}

}

void CWPR_UTILITIESDlg::RecordDataFromSM(){
	FILE* fp = fopen("SM_log_Binary.dat","a+");
	FILE* fp1 = fopen("SM_log.txt","a+");

	if(!fp)
		return;
	fwrite(&g_sm_status,sizeof(sm_status),1,fp);
	fclose(fp);

	if(!fp1)
		return;
	unsigned char byte[45];
	memcpy(byte,&g_sm_status,sizeof(sm_status));
	for(int i=0; i<45; i++){
		fprintf(fp1,"Byte %d = %0x\n",i,byte[i]);
	}
	fprintf(fp1,"============================\n");
	fclose(fp1);
	return;
}

void CWPR_UTILITIESDlg::OnBasicSetting() 
{
	// TODO: Add your command handler code here
	CBasicSettingDlg dlg;
	if(dlg.DoModal() == IDOK){

		global.basic.basicinfo.oblique_struct.prt_high = dlg.m_nPRT_ObliqueHigh;
		global.basic.basicinfo.oblique_struct.pulse_width_high = dlg.m_nPW_ObliqueHigh;
		global.basic.basicinfo.oblique_struct.spec_domain_avg_high = dlg.m_nSAvg_ObliqueHigh;
		global.basic.basicinfo.oblique_struct.time_domain_avg_high = dlg.m_nTAvg_ObliqueHigh;
		
		global.basic.basicinfo.oblique_struct.prt_low = dlg.m_nPRT_ObliqueLow;
		global.basic.basicinfo.oblique_struct.pulse_width_low = dlg.m_nPW_ObliqueLow;
		global.basic.basicinfo.oblique_struct.spec_domain_avg_low = dlg.m_nSAvg_ObliqueLow;
		global.basic.basicinfo.oblique_struct.time_domain_avg_low = dlg.m_nTAvg_ObliqueLow;
		
		global.basic.basicinfo.vertical_struct.prt_high = dlg.m_nPRT_VerticalHigh;
		global.basic.basicinfo.vertical_struct.pulse_width_high = dlg.m_nPW_VerticalHigh;
		global.basic.basicinfo.vertical_struct.spec_domain_avg_high = dlg.m_nSAvg_VerticalHigh;
		global.basic.basicinfo.vertical_struct.time_domain_avg_high = dlg.m_nTAvg_VerticalHigh;
		
		global.basic.basicinfo.vertical_struct.prt_low = dlg.m_nPRT_VerticalLow;
		global.basic.basicinfo.vertical_struct.pulse_width_low = dlg.m_nPW_VerticalLow;
		global.basic.basicinfo.vertical_struct.spec_domain_avg_low = dlg.m_nSAvg_VerticalLow;
		global.basic.basicinfo.vertical_struct.time_domain_avg_low = dlg.m_nTAvg_VerticalLow;
		
		global.basic.Save();//save basic setting changed by user
	}
}

void CWPR_UTILITIESDlg::OnPha0() 
{
	// TODO: Add your control notification handler code here

	HICON hIcon_shut = AfxGetApp()->LoadIcon(IDI_ICON14) ;
	HICON hIcon_start = AfxGetApp()->LoadIcon(IDI_ICON15);
	//FIRST WE NEED TO CHECK IF THE STATUS MONITOR IS RUNNING. 
	//IF NOT WE NEED TO ASK THE USER TO START THE SM 
	
	if(!global.cs_sm.IsOn()){
		m_HPA0.SetCheck(FALSE);
		m_HPA0.SetWindowText("HIGH POWER AMPLIFIER OFF");
		AfxMessageBox("STATUS MONITOR IS NOT AVAILABLE. START IT PLEASE.");
		return;
	}

	UINT ret = 0;
	m_HPA0_ON = !m_HPA0_ON;
	if(m_HPA0_ON){
	    cmparam.cparam[0] = HPA_START_MASK;
	}
	else{
		cmparam.cparam[0] = HPA_SHUT_MASK;
	}
	a442_sm_command("HPA0",cmparam.param,ret);
	if(m_HPA0_ON){
		m_hpa0_status.SetIcon(hIcon_start);
		m_HPA0.SetWindowText("HIGH POWER AMPLIFIER ON");
	}
	else{
		m_hpa0_status.SetIcon(hIcon_shut);
		m_HPA0.SetWindowText("HIGH POWER AMPLIFIER OFF");
	}
}

//////////////////////////////////////////////////
//LOG THE CONTROL WORDS OF SM
void LogsmCtrlWords(char* str){
	time_t ltime;
	time(&ltime);

	FILE* fp;
	fp = fopen("CTRLWORDS.txt","a+");
	if(!fp)
		return;
	fprintf(fp,"%s: Byte1--%x Byte2--%x\t%s",
				str,cmparam.cparam[0],cmparam.cparam[1],ctime(&ltime));
	fclose(fp);
	
	return;
}

void CWPR_UTILITIESDlg::OnTestStop() 
{
	// TODO: Add your command handler code here
	testtask.Stop(NULL);
}

	
void CWPR_UTILITIESDlg::SetCtrlWordsForEveryBeam(){

	float factor = 1;
	int num = 0;
	int i=0;
	int j=0;

	//set fft points
	if(global.basic.basicinfo.nfft == 1){
		g_scalednumfftpts = 1;
	}
	else if(global.basic.basicinfo.nfft == 128){
		g_scalednumfftpts = 2;
	}
	else if(global.basic.basicinfo.nfft == 256){
		g_scalednumfftpts = 3;
	}
	else if(global.basic.basicinfo.nfft  == 512){
		g_scalednumfftpts = 4;
	}
	else if(global.basic.basicinfo.nfft  == 1024){
		g_scalednumfftpts = 5;
	}
	else if(global.basic.basicinfo.nfft  == 2048){
		g_scalednumfftpts = 6;
	}

	//set mode and beam direct.
	g_submode_ctrlwrds[EH].cw0_flds.bmdirchange = 0; 
	g_submode_ctrlwrds[EH].cw0_flds.bmdirection = //NORTH_DIREC;  
			global_advance.beamctrlsetting.nBeamDirection[0];
	g_submode_ctrlwrds[EH].cw0_flds.mode = 1; 

	g_submode_ctrlwrds[EL].cw0_flds.bmdirchange = 1; 
	g_submode_ctrlwrds[EL].cw0_flds.bmdirection = //NORTH_DIREC; 
			global_advance.beamctrlsetting.nBeamDirection[0];
	g_submode_ctrlwrds[EL].cw0_flds.mode = 0; 

	g_submode_ctrlwrds[NH].cw0_flds.bmdirchange = 0; 
	g_submode_ctrlwrds[NH].cw0_flds.bmdirection = //EAST_DIREC; 
			global_advance.beamctrlsetting.nBeamDirection[1];
	g_submode_ctrlwrds[NH].cw0_flds.mode = 1; 

	g_submode_ctrlwrds[NL].cw0_flds.bmdirchange = 1; 
	g_submode_ctrlwrds[NL].cw0_flds.bmdirection = //EAST_DIREC;  
			global_advance.beamctrlsetting.nBeamDirection[1];
	g_submode_ctrlwrds[NL].cw0_flds.mode = 0; 

	g_submode_ctrlwrds[VH].cw0_flds.bmdirchange = 0; 
	g_submode_ctrlwrds[VH].cw0_flds.bmdirection = //VERTICAL_DIREC;  
			global_advance.beamctrlsetting.nBeamDirection[2];
	g_submode_ctrlwrds[VH].cw0_flds.mode = 1; 

	g_submode_ctrlwrds[VL].cw0_flds.bmdirchange = 1; 
	g_submode_ctrlwrds[VL].cw0_flds.bmdirection = //VERTICAL_DIREC;
			global_advance.beamctrlsetting.nBeamDirection[2];
	g_submode_ctrlwrds[VL].cw0_flds.mode = 0; 

	////////////////////////////////////////////////////////////
	g_submode_ctrlwrds[WH].cw0_flds.bmdirchange = 0; 
	g_submode_ctrlwrds[WH].cw0_flds.bmdirection = //SOUTH_DIREC;  
			global_advance.beamctrlsetting.nBeamDirection[3];
	g_submode_ctrlwrds[WH].cw0_flds.mode = 1; 

	g_submode_ctrlwrds[WL].cw0_flds.bmdirchange = 1; 
	g_submode_ctrlwrds[WL].cw0_flds.bmdirection = //SOUTH_DIREC; 
			global_advance.beamctrlsetting.nBeamDirection[3];
	g_submode_ctrlwrds[WL].cw0_flds.mode = 0; 

	g_submode_ctrlwrds[SH].cw0_flds.bmdirchange = 0; 
	g_submode_ctrlwrds[SH].cw0_flds.bmdirection = //WEST_DIREC; 
			global_advance.beamctrlsetting.nBeamDirection[4];
	g_submode_ctrlwrds[SH].cw0_flds.mode = 1; 

	g_submode_ctrlwrds[SL].cw0_flds.bmdirchange = 1; 
	g_submode_ctrlwrds[SL].cw0_flds.bmdirection = //WEST_DIREC; 
			global_advance.beamctrlsetting.nBeamDirection[4];
	g_submode_ctrlwrds[SL].cw0_flds.mode = 0; 
	////////////////////////////////////////////////////////////

	//set prt and pulse width
	for(i=0; i<G_KMAXBEAMS; i++)
	{
		g_submode_ctrlwrds[i].cw0_flds.fftpts = g_scalednumfftpts;//3
		g_submode_ctrlwrds[i].cw0_flds.spectra_samples = 128 - g_knumber_of_spectra[i]; //128-n//8
		g_submode_ctrlwrds[i].cw0_flds.tda_samples = g_ktda_samples[i];//9

		//liuchen modify this 2006/8/24
		g_submode_ctrlwrds[i].cw2_flds.rfgatemoving = 0;//10 range bin = 16*10
		g_PC_code_moving = global_advance.dspsetting.nPCCodeMove;

		double factor = global_advance.dspsetting.nSampleRate;
		if(i%2)
		{  //low mode 
			if(i==4 || i==5)  
			{  //vertical beam
				g_submode_ctrlwrds[i].cw2_flds.txpulse = int (global.basic.basicinfo.vertical_struct.pulse_width_low *factor/1000.0);  
				g_submode_ctrlwrds[i].cw2_flds.prt = int(global.basic.basicinfo.vertical_struct.prt_low * factor/1000.0);  
			}
			else
			{   //oblique	    
				g_submode_ctrlwrds[i].cw2_flds.txpulse = int (global.basic.basicinfo.oblique_struct.pulse_width_low *factor/1000.0);
				g_submode_ctrlwrds[i].cw2_flds.prt = int(global.basic.basicinfo.oblique_struct.prt_low * factor/1000.0);  
			} 
			
			g_submode_ctrlwrds[i].cw2_flds.rfgatemoving =  global_advance.dspsetting.nRFGateMoveL;
		}
		else
		{//high mode
			if(i==4 || i== 5)  
			{  //vertical beam
				g_submode_ctrlwrds[i].cw2_flds.txpulse = int (global.basic.basicinfo.vertical_struct.pulse_width_high *factor/1000.0);  
				g_submode_ctrlwrds[i].cw2_flds.prt = int(global.basic.basicinfo.vertical_struct.prt_high * factor/1000.0);
			}
			else
			{   //oblique
				g_submode_ctrlwrds[i].cw2_flds.txpulse =int (global.basic.basicinfo.oblique_struct.pulse_width_high *factor/1000.0);    
				g_submode_ctrlwrds[i].cw2_flds.prt = int(global.basic.basicinfo.oblique_struct.prt_high * factor/1000.0);
			}
			//g_submode_ctrlwrds[i].cw0_flds.rev240m = global.basic.basicinfo.bHighModeRange240m?1:0;
			
			g_submode_ctrlwrds[i].cw2_flds.rfgatemoving =  global_advance.dspsetting.nRFGateMoveH;
		
		}

		//set time domain averaging enable 2011/11/3
		g_submode_ctrlwrds[i].cw0_flds.pcs =global.basic.basicinfo.bHighModeRange240m?1:0;
		
		//set others
		g_submode_ctrlwrds[i].cw0_flds.dptestctrl			= 0;  //1
		g_submode_ctrlwrds[i].cw0_flds.dptestphaseshift		= 0; //3
		g_submode_ctrlwrds[i].cw1_flds.workmode				= 7;
		g_submode_ctrlwrds[i].cw1_flds.coaxialdriver		= 1;
		g_submode_ctrlwrds[i].cw1_flds.testsrcsel			= 8;
		g_submode_ctrlwrds[i].cw1_flds.rfattenuation		= 0x7f;
		g_submode_ctrlwrds[i].cw1_flds.noisesrcctrl			= 0;
		g_submode_ctrlwrds[i].cw1_flds.rxtestoutsel			= 1;
		g_submode_ctrlwrds[i].cw1_flds.smrst				= 1;
		g_submode_ctrlwrds[i].cw1_flds.rxtestsignalampctrl	= 0x0f;
		g_submode_ctrlwrds[i].cw1_flds.rxtestfresel			= 0;
		g_submode_ctrlwrds[i].cw1_flds.lophctrl				= 1;
		g_submode_ctrlwrds[i].cw1_flds.txctrl				= 1;
	}
	
	//Set stc
	for(i=0; i<5; i++){
	   for(j=0; j<4; j++)
	   {
		   //for low mode
		   g_submode_ctrlwrds[i*2+1].cw3_6[j].cw3_6_flds.stc1 =  global.basic.basicinfo.stc_struct.ch_stc[j*6+0][i];
		   g_submode_ctrlwrds[i*2+1].cw3_6[j].cw3_6_flds.stc2 =  global.basic.basicinfo.stc_struct.ch_stc[j*6+1][i];
		   g_submode_ctrlwrds[i*2+1].cw3_6[j].cw3_6_flds.stc3 =  global.basic.basicinfo.stc_struct.ch_stc[j*6+2][i];
		   g_submode_ctrlwrds[i*2+1].cw3_6[j].cw3_6_flds.stc4 =  global.basic.basicinfo.stc_struct.ch_stc[j*6+3][i];
		   g_submode_ctrlwrds[i*2+1].cw3_6[j].cw3_6_flds.stc5 =  global.basic.basicinfo.stc_struct.ch_stc[j*6+4][i];  
		   g_submode_ctrlwrds[i*2+1].cw3_6[j].cw3_6_flds.stc6 =  global.basic.basicinfo.stc_struct.ch_stc[j*6+5][i];
	   
		   //for high mode
		   g_submode_ctrlwrds[i*2].cw3_6[j].cw3_6_flds.stc1 =  global.basic.basicinfo.stc_sturct_high.ch_stc[j*6+0][i];
		   g_submode_ctrlwrds[i*2].cw3_6[j].cw3_6_flds.stc2 =  global.basic.basicinfo.stc_sturct_high.ch_stc[j*6+1][i];
		   g_submode_ctrlwrds[i*2].cw3_6[j].cw3_6_flds.stc3 =  global.basic.basicinfo.stc_sturct_high.ch_stc[j*6+2][i];
		   g_submode_ctrlwrds[i*2].cw3_6[j].cw3_6_flds.stc4 =  global.basic.basicinfo.stc_sturct_high.ch_stc[j*6+3][i];
		   g_submode_ctrlwrds[i*2].cw3_6[j].cw3_6_flds.stc5 =  global.basic.basicinfo.stc_sturct_high.ch_stc[j*6+4][i];  
		   g_submode_ctrlwrds[i*2].cw3_6[j].cw3_6_flds.stc6 =  global.basic.basicinfo.stc_sturct_high.ch_stc[j*6+5][i];
          
	   }
	}
     g_bCycleCtrol = g_ctrl_config.b_CycleTest;
	 g_CommunicationSel = g_communication_config.selection;
}

void CWPR_UTILITIESDlg::OnTestandgetdata() 
{
	// TODO: Add your command handler code here
	CDoptestParamDlg DoptestParamdlg;
	if(DoptestParamdlg.DoModal() == IDOK)
	{
	    SetCtrlWordsForTest(DoptestParamdlg);
		m_RFAttenSlider.SetPos(103-DoptestParamdlg.m_TST_RF_ATTEN);
		m_RTACSlider.SetPos((60-4*DoptestParamdlg.m_TST_SIGNAL_AMP)/4);

		cur_value = m_RFAttenSlider.GetPos()-103;
		CString str;
		str.Format("%d",cur_value);
		GetDlgItem(IDC_RFATTEN_VALUE)->SetWindowText(str);
		UpdateData(FALSE);
	
		if(testtask.IsStarted())
			testtask.Stop(NULL);
		b_nochanged = TRUE; //For 8km wpr, there is a bug in the hardware.
		global.cs_test.TurnOn();
		testtask.Start();

		/*ENABLE THE BEAM CTRL BUTTON*/
		m_button_west.EnableWindow(TRUE);
		m_button_east.EnableWindow(TRUE);
		m_button_north.EnableWindow(TRUE);
		m_button_south.EnableWindow(TRUE);
		m_button_virtical.EnableWindow(TRUE);

	}
    	
	return;
}

void CWPR_UTILITIESDlg::SetCtrlWordsForTest(CDoptestParamDlg& DoptestParamdlg){

	int Param[17];          
	HANDLE hFile;            
	CFile outFile;       
	char* pFileName = "TestParam.dat";
	
	g_test_strt         = DoptestParamdlg.m_TST_BEAM_NUM;
	g_test_end          = g_test_strt;
	g_dop_freq_selected = DoptestParamdlg.m_TST_DOP_PHASE;
	g_rf_freq_selected  = DoptestParamdlg.m_TST_RF_FREQ;
	g_rf_lev_atten_sel  = 6 * DoptestParamdlg.m_TST_SIGNAL_AMP;
	g_lo_phase_ctrl     = DoptestParamdlg.m_TST_LO_PHASE; 
	g_bm_dir_change     = DoptestParamdlg.m_TST_BM_DIRCHANGE;
	g_coax_switch       = DoptestParamdlg.m_TST_COAX_SWITCH;
	g_dop_test_ctrl     = DoptestParamdlg.m_TST_DOP_TST_CTRL;  
	g_noise_source      = DoptestParamdlg.m_TST_NOISE_SOURCE;
	g_sm_reset          = DoptestParamdlg.m_TST_SM_RESET;
	g_trans_ctrl        = DoptestParamdlg.m_TST_TRANSMITTER;
	g_signal_source	    = (int)pow(2,DoptestParamdlg.m_TST_SIGNAL_SOURCE);
	g_signal_output     = DoptestParamdlg.m_TST_SIGNAL_OUTPUT;
	g_RF_attenuation    = 103 - DoptestParamdlg.m_TST_RF_ATTEN;
	g_RF_gate_moving    = DoptestParamdlg.m_TST_RF_GATEMOVING;
	g_DIF_gate_moving   = DoptestParamdlg.m_TST_DIF_GATEMOVING;
	g_PC_code_moving    = DoptestParamdlg.m_TST_PCCODE_MOVING;

	g_curbeamnum = g_test_strt;

 	g_timedomainavg = g_ktda_samples[g_test_strt];	
	memcpy(&g_nomal_ctrlwrds, &g_submode_ctrlwrds[g_test_strt],sizeof(control_word_0_6));
	
	Param[0]  = DoptestParamdlg.m_TST_BEAM_NUM;
	Param[1]  = DoptestParamdlg.m_TST_DOP_PHASE;
	Param[2]  = DoptestParamdlg.m_TST_RF_ATTEN;
	Param[3]  = DoptestParamdlg.m_TST_RF_FREQ;
	Param[4]  = DoptestParamdlg.m_TST_COAX_SWITCH;
	Param[5]  = DoptestParamdlg.m_TST_DOP_TST_CTRL;
	Param[6]  = DoptestParamdlg.m_TST_BM_DIRCHANGE;
	Param[7]  = DoptestParamdlg.m_TST_LO_PHASE;
	Param[8]  = DoptestParamdlg.m_TST_NOISE_SOURCE;
	Param[9]  = DoptestParamdlg.m_TST_SIGNAL_AMP;
	Param[10] = DoptestParamdlg.m_TST_SIGNAL_OUTPUT;
	Param[11] = DoptestParamdlg.m_TST_SIGNAL_SOURCE;
	Param[12] = DoptestParamdlg.m_TST_SM_RESET;
	Param[13] = DoptestParamdlg.m_TST_TRANSMITTER;
	Param[14] = DoptestParamdlg.m_TST_RF_GATEMOVING;
	Param[15] = DoptestParamdlg.m_TST_DIF_GATEMOVING;
    Param[16] = g_PC_code_moving;

	//save param to the control words
	g_nomal_ctrlwrds.cw0_flds.bmdirchange = g_bm_dir_change; // CHANGE BEAM DIRECTION (BDC = 0)  ON STARTING BEAM 
	g_dop_freq_selected = (8-g_dop_freq_selected) & 0x7;
	g_nomal_ctrlwrds.cw0_flds.dptestphaseshift = g_dop_freq_selected; //3
	g_nomal_ctrlwrds.cw0_flds.dptestctrl = g_dop_test_ctrl;//0;  //1 //DOPPLER TEST COMMAND,doppler test = 1,
	g_nomal_ctrlwrds.cw0_flds.fftpts = g_scalednumfftpts;//3
	g_nomal_ctrlwrds.cw0_flds.spectra_samples = 128 - g_knumber_of_spectra[g_test_strt]; //128-n//8
	g_nomal_ctrlwrds.cw0_flds.tda_samples = g_ktda_samples[g_test_strt];//9
	//{phase shift control , bit0 =0, every time domain number shift phase. bit0=1, every sweep shift phase
	//g_nomal_ctrlwrds.cw0_flds.spare = 0;
	//}
	g_nomal_ctrlwrds.cw1_flds.txctrl	     = g_trans_ctrl;
	g_nomal_ctrlwrds.cw1_flds.lophctrl    = g_lo_phase_ctrl;  //RECEIVER TEST LOCAL OSCILLATOR CONTROL
	g_nomal_ctrlwrds.cw1_flds.rxtestfresel = g_rf_freq_selected;  //RECEIVER TEST FREQUENCY CONTROL
	g_nomal_ctrlwrds.cw1_flds.rxtestsignalampctrl = g_tac_values[g_rf_lev_atten_sel / 6 ];
	g_nomal_ctrlwrds.cw1_flds.smrst         = g_sm_reset;
	g_nomal_ctrlwrds.cw1_flds.rxtestoutsel	 = g_signal_output;
	g_nomal_ctrlwrds.cw1_flds.noisesrcctrl  = g_noise_source;
	if(g_RF_attenuation > 63)   
		g_RF_attenuation += 24;
	g_nomal_ctrlwrds.cw1_flds.rfattenuation = g_RF_attenuation;
	g_nomal_ctrlwrds.cw1_flds.testsrcsel	 = g_signal_source;
	g_nomal_ctrlwrds.cw1_flds.coaxialdriver = 0;
	g_nomal_ctrlwrds.cw1_flds.two_switcher = g_coax_switch;
	g_nomal_ctrlwrds.cw1_flds.workmode = 7;//2008/7/22 was 2;    // test mode
	g_nomal_ctrlwrds.cw2_flds.rfgatemoving = g_RF_gate_moving;
	g_nomal_ctrlwrds.cw1_flds.dif_gate_moving = g_DIF_gate_moving;

	//new control words setting
	g_nomal_ctrlwrds.cw0_flds.pcs = global.basic.basicinfo.bHighModeRange240m?1:0;
	g_nomal_ctrlwrds.cw0_flds.phc = global.basic.basicinfo.nPSCModeSel;
	g_nomal_ctrlwrds.cw3_6[0].cw3_6_flds.stc_cw = global.basic.basicinfo.bWholeRangeAddSTC?1:0;
	g_nomal_ctrlwrds.cw0_flds.rev240m = 0;//global.basic.basicinfo.bHighModeRange240m?1:0;
	if(DoptestParamdlg.m_TST_BEAM_NUM %2 == 1)
		g_nomal_ctrlwrds.cw0_flds.rev240m = 0;

	
	if(outFile.Open(pFileName,CFile::modeWrite)!=0)
	{
		outFile.Write( (void*)Param, 17*4);
		outFile.Close();
	}
	else
	{
		//If no file 
		hFile = CreateFile( pFileName, GENERIC_WRITE,
			FILE_SHARE_WRITE,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if( hFile!=INVALID_HANDLE_VALUE )
		{
			CloseHandle( hFile );
		}
		if(outFile.Open(pFileName,CFile::modeWrite)!=0)
		{
			outFile.Write( (void*)Param, 17*4); 
			outFile.Close();
		}
	}
    return;
}

void CWPR_UTILITIESDlg::Scale()
{
	return;
}

BOOL CWPR_UTILITIESDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(testtask.IsStarted())
		testtask.Stop(NULL);
	if(smtask.IsStarted())
		smtask.Stop(NULL);

	exit(EXIT_SUCCESS);
	return CDialog::DestroyWindow();
}

/*
***********************************************************
* SHOW SOME INFORMATION OF THE TX
***********************************************************
*/
void CWPR_UTILITIESDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	if(nIDEvent == IDEventTxInfo)
	{
	int integer = _f_tx_pwr_input.integer;
	int decimal = _f_tx_pwr_input.decimal;
    m_static_input_pwr.SetData(integer,decimal);

	integer = _f_tx_pwr_output.integer;
	decimal = _f_tx_pwr_output.decimal;
    m_static_output_pwr.SetData(integer,decimal);

	integer = _f_tx_pwr_reflect.integer;
	decimal = _f_tx_pwr_reflect.decimal;
	m_static_duty.SetData(integer, decimal);
/*
	unsigned  short pos = g_sm_status.sm_pos_pulse_width_h;
	pos = (pos<<8) + g_sm_status.sm_pos_pulse_width_l;
	unsigned  short neg = g_sm_status.sm_neg_pulse_width_h;
	neg = (neg<<8) + g_sm_status.sm_neg_pulse_width_l;

	double fDuty;
	if(pos+neg==0)
		fDuty = 0;
	else if(pos == 0xfe && neg== 0xfe)
		fDuty = 0;
	else
	    fDuty = (double)pos/(double)(pos+neg);

    fDuty  *= 100;
	m_static_duty.SetData((int)fDuty,(fDuty-((int)fDuty))*100);
  */  
	}


	if(nIDEvent==IDEventStatusBarTime)	
	{
		CTime t;
		t=CTime::GetCurrentTime();
		m_StatusBar.SetPaneText(1,t.Format("TIME %H:%M:%S"));
	}


	CDialog::OnTimer(nIDEvent);

}

/*
***********************************************************
* START THE COMMUNICATION WITH STATUS MONITOR
***********************************************************
*/
void CWPR_UTILITIESDlg::OnStartSm() 
{
	// TODO: Add your command handler code here
	if(smtask.IsStarted())
		smtask.Stop(NULL);
	
   	global.cs_sm.TurnOn();
    smtask.Start();
	//bSMOn = FALSE;
}

/*
***********************************************************
* STOP THE COMMUNICATION WITH STATUS MONITOR
***********************************************************
*/
void CWPR_UTILITIESDlg::OnStopSm() 
{
	// TODO: Add your command handler code here
	global.cs_sm.TurnOff();
	smtask.Stop(NULL);
	//bSMOn = TRUE;
}

/*
***********************************************************
* SHOW THE ADVANCED SETTING
***********************************************************
*/
void CWPR_UTILITIESDlg::OnAdvancedSetting() 
{
	// TODO: Add your command handler code here
	CAdvancedSettingDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		global_advance.Save();
	}
}

/*
***********************************************************
* CHANGE THE RF ATTENUATOR SLIDE CONTROL
***********************************************************
*/
void CWPR_UTILITIESDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if(GetDlgItem(IDC_SLIDER) == pScrollBar)
	{
		cur_value = m_RFAttenSlider.GetPos() -103;
		CString str;
		str.Format("%d",cur_value);
		GetDlgItem(IDC_RFATTEN_VALUE)->SetWindowText(str);
		//UpdateData(FALSE);
		if(old_value != cur_value){
			RFAttenuationChanged = 1;
			old_value = cur_value;	
		}
	}

	if(GetDlgItem(IDC_RTACSLIDER) == pScrollBar)
	{
		cur_rtac_value = m_RTACSlider.GetPos()*4 -60;
		CString str;
		str.Format("%d",cur_rtac_value);
		GetDlgItem(IDC_RTAC_VALUE)->SetWindowText(str);
		//UpdateData(FALSE);
		if(old_rtac_value != cur_rtac_value){
			RTACChanged = 1;
			old_rtac_value = cur_rtac_value;
		}
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

/*
***********************************************************
* CHANGE THE RF ATTENUATOR BY THE SPIN 
***********************************************************
*/
void CWPR_UTILITIESDlg::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	if(pNMUpDown->iDelta == -1)              
	{ 
		m_RFAttenSlider.SetPos(m_RFAttenSlider.GetPos()+1);
		cur_value = m_RFAttenSlider.GetPos()-103;
		CString str;
		str.Format("%d",cur_value);
		GetDlgItem(IDC_RFATTEN_VALUE)->SetWindowText(str);
		//UpdateData(FALSE);

		if(old_value != cur_value){
			RFAttenuationChanged = 1;
			old_value = cur_value;	
		}
    }
    else if(pNMUpDown->iDelta == 1)
	{
		m_RFAttenSlider.SetPos(m_RFAttenSlider.GetPos()-1);
		cur_value = m_RFAttenSlider.GetPos()-103;
		CString str;
		str.Format("%d",cur_value);
		GetDlgItem(IDC_RFATTEN_VALUE)->SetWindowText(str);
		//UpdateData(FALSE);

		if(old_value != cur_value){
			RFAttenuationChanged = 1;
			old_value = cur_value;	
		}
	}
	*pResult = 0;
}

/*
***********************************************************
* START THE COMMUNICATION WITH UPS
***********************************************************
*/
void CWPR_UTILITIESDlg::OnStartUps() 
{
	// TODO: Add your command handler code here
	if(upstask.IsStarted())
		upstask.Stop(NULL);
	
   	global.cs_ups.TurnOn();
    upstask.Start();
}

/*
***********************************************************
* STOP THE COMMUNICTION WITH UPS
***********************************************************
*/
void CWPR_UTILITIESDlg::OnStopUps() 
{
	// TODO: Add your command handler code here
	global.cs_ups.TurnOff();
	upstask.Stop(NULL);
}

/*
***********************************************************
* SHUT DOWN THE UPS
***********************************************************
*/
void CWPR_UTILITIESDlg::OnButtonUps() 
{
	// TODO: Add your control notification handler code here
	dhv_ups_shutdown(); 
}

/*
***********************************************************
* SHOW THE UPS STATUS
***********************************************************
*/
void CWPR_UTILITIESDlg::OnButtonStatus() 
{
	// TODO: Add your control notification handler code here
	CUPSDlg upsdlg;
	upsdlg.DoModal();	
}

/*
***********************************************************
* CHANGE THE BEAM DIRECTION TO THE EAST
***********************************************************
*/
void CWPR_UTILITIESDlg::OnCheckEast() 
{
	// TODO: Add your control notification handler code here
	if(m_b_east){
		m_button_east.SetIcon(m_hBeam[EAST]);
	}
	else{	
		m_button_east.SetIcon(m_hBeamSelected[EAST]);
		m_button_north.SetIcon(m_hBeam[NORTH]);
		m_button_virtical.SetIcon(m_hBeam[VIRTICAL]);
		m_button_south.SetIcon(m_hBeam[SOUTH]);
		m_button_west.SetIcon(m_hBeam[WEST]);
	}

	m_b_north = m_b_south = m_b_virtical = m_b_west = false;
	m_b_east = !m_b_east;
	
	//CHECK THE MODE AND SET THE INFORMATIN ON THE SCREEN
    if(g_nomal_ctrlwrds.cw0_flds.mode){
		//HIGH MDE
	    g_curbeamnum = 0;
	}else
	{
		g_curbeamnum = 1;
	}

	SetBeam(EAST);
	UpdateData(FALSE);
}

/*
***********************************************************
* CHANGE THE BEAM DIRECTION TO THE NORTH
***********************************************************
*/
void CWPR_UTILITIESDlg::OnCheckNorth() 
{
	// TODO: Add your control notification handler code here
	if(m_b_north){
		m_button_north.SetIcon(m_hBeam[NORTH]);
	}
	else{	
		m_button_north.SetIcon(m_hBeamSelected[NORTH]);
		m_button_east.SetIcon(m_hBeam[EAST]);
		m_button_virtical.SetIcon(m_hBeam[VIRTICAL]);
		m_button_south.SetIcon(m_hBeam[SOUTH]);
		m_button_west.SetIcon(m_hBeam[WEST]);
	}

	m_b_east = m_b_south = m_b_virtical = m_b_west = false;
	m_b_north = !m_b_north;

	//CHECK THE MODE AND SET THE INFORMATIN ON THE SCREEN
    if(g_nomal_ctrlwrds.cw0_flds.mode){
		//HIGH MDE
		g_curbeamnum = 2;

	}else
	{
		g_curbeamnum = 3;
	}

	SetBeam(NORTH);
	UpdateData(FALSE);
}

/*
***********************************************************
* CHANGE THE BEAM DIRECTION TO THE SOUTH
***********************************************************
*/
void CWPR_UTILITIESDlg::OnCheckSouth() 
{
	// TODO: Add your control notification handler code here
	if(m_b_south){
		m_button_south.SetIcon(m_hBeam[SOUTH]);
	}
	else{	
		m_button_south.SetIcon(m_hBeamSelected[SOUTH]);
		m_button_east.SetIcon(m_hBeam[EAST]);
		m_button_virtical.SetIcon(m_hBeam[VIRTICAL]);
		m_button_north.SetIcon(m_hBeam[NORTH]);
		m_button_west.SetIcon(m_hBeam[WEST]);
	}

	m_b_north = m_b_east = m_b_virtical = m_b_west = false;
	m_b_south = !m_b_south;

	//CHECK THE MODE AND SET THE INFORMATIN ON THE SCREEN
    if(g_nomal_ctrlwrds.cw0_flds.mode){
		//HIGH MDE
		g_curbeamnum = 8;

	}else
	{
		g_curbeamnum = 9;
	}

	SetBeam(SOUTH);
	UpdateData(FALSE);
}

/*
***********************************************************
* CHANGE THE BEAM DIRECTION TO THE VIRTICAL
***********************************************************
*/
void CWPR_UTILITIESDlg::OnCheckVirtical() 
{
	// TODO: Add your control notification handler code here
	if(m_b_virtical){
		m_button_virtical.SetIcon(m_hBeam[VIRTICAL]);
	}
	else{	
		m_button_virtical.SetIcon(m_hBeamSelected[VIRTICAL]);
		m_button_east.SetIcon(m_hBeam[EAST]);
		m_button_south.SetIcon(m_hBeam[SOUTH]);
		m_button_north.SetIcon(m_hBeam[NORTH]);
		m_button_west.SetIcon(m_hBeam[WEST]);
	}

	m_b_north = m_b_south = m_b_east = m_b_west = false;
	m_b_virtical = !m_b_virtical;

	if(g_nomal_ctrlwrds.cw0_flds.mode){
		//HIGH MDE
		g_curbeamnum = 4;
		
	}else
	{
		g_curbeamnum = 5;
	}

	SetBeam(VIRTICAL);
	UpdateData(FALSE);
}

/*
***********************************************************
* CHANGE THE BEAM DIRECTION TO THE WEST
***********************************************************
*/
void CWPR_UTILITIESDlg::OnCheckWest() 
{
	// TODO: Add your control notification handler code here
	if(m_b_west){
		m_button_west.SetIcon(m_hBeam[WEST]);
	}
	else{	
		m_button_west.SetIcon(m_hBeamSelected[WEST]);
		m_button_east.SetIcon(m_hBeam[EAST]);
		m_button_virtical.SetIcon(m_hBeam[VIRTICAL]);
		m_button_north.SetIcon(m_hBeam[NORTH]);
		m_button_south.SetIcon(m_hBeam[SOUTH]);
	}

	m_b_north = m_b_south = m_b_virtical = m_b_east = false;
	m_b_west = !m_b_west;

	if(g_nomal_ctrlwrds.cw0_flds.mode){
		//HIGH MDE
		g_curbeamnum = 6;
		
	}else
	{
		g_curbeamnum = 7;
	}

	SetBeam(WEST);
	UpdateData(FALSE);
}

/*
***********************************************************
* CHANGE THE BEAM DIRECTION BY HIT THE BUTTON
***********************************************************
*/
void CWPR_UTILITIESDlg::SetBeam(int id)
{
	if(global.cs_dataprocess.IsOn())
	{
		control_word_0_6 cw={0};

		memcpy(&cw,&g_nomal_ctrlwrds,sizeof(control_word_0_6));
		if(id<0 || id>5)
			id = EAST;
		
		cw.cw0_flds.bmdirection = global_advance.beamctrlsetting.nBeamDirection[id];
		testtask.dp_task.DownLoadCtrlWords(cw);
	}
	return;
}

void CWPR_UTILITIESDlg::OnDataview() 
{
	// TODO: Add your command handler code here
	if(!bDataViewEnable){
		dataview = new CDataView;
		dataview->Create(IDD_DIALOG_DATAVIEW,this);
		dataview->setParent(this);
		dataview->ShowWindow(SW_SHOW);
		bDataViewEnable = TRUE;
	}
}

void CWPR_UTILITIESDlg::OnUpdateStartSm(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//pCmdUI->Enable(bSMOn);

}

void CWPR_UTILITIESDlg::OnUpdateStopSm(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//pCmdUI->Enable(!bSMOn);
}



BOOL CWPR_UTILITIESDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg-> message == WM_KEYDOWN  &&  pMsg-> wParam == VK_RETURN) 
		return FALSE;

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CWPR_UTILITIESDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	// TODO: Add your message handler code here and/or call default
	int id, alarm_count;
    P_STATUS_ITEM_INFO_BIN pInfo = (P_STATUS_ITEM_INFO_BIN)pCopyDataStruct->lpData;
	CString str = CString(pInfo->m_strName);
	STATUS_EVL level = (STATUS_EVL)pInfo->m_nAlarm_Level;
	if(level == EVL_WARNNING)
	{ 
		if(!reportTable.Lookup(str, id)){
			alarm_count = m_alarmdisplist.GetItemCount();
			m_alarmdisplist.InsertItem(alarm_count, "WARNNING",0);
			m_alarmdisplist.SetItemText(alarm_count,1,str);
			reportTable.SetAt(str,alarm_count);
		}
	}else if(level == EVL_FALSE)
	{
		if(!reportTable.Lookup(str, id)){
			alarm_count = m_alarmdisplist.GetItemCount();
			m_alarmdisplist.InsertItem(alarm_count, "ERROR",1);
			m_alarmdisplist.SetItemText(alarm_count,1,str);
			reportTable.SetAt(str,alarm_count);
		}
	}

	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}

void CWPR_UTILITIESDlg::ShowSysInfo()
{
	CString str;
	//m_strSysInfo += "------DSP INFO------\r\n";
	str.Format("SAMPLE RATE:        %dMHz",global_advance.dspsetting.nSampleRate);
	m_strSysInfo += str+"\r\n";

	str.Format("PRT(H):             %dns",global.basic.basicinfo.oblique_struct.prt_high);
	m_strSysInfo += str+"\r\n";
	
	str.Format("PRT(L):             %dns",global.basic.basicinfo.oblique_struct.prt_low);
	m_strSysInfo += str+"\r\n";

	str.Format("PULSE WIDTH(H):     %dns", global.basic.basicinfo.oblique_struct.pulse_width_high);
	m_strSysInfo += str+"\r\n";
	
	str.Format("PULSE WIDTH(L):     %dns", global.basic.basicinfo.oblique_struct.pulse_width_low);
	m_strSysInfo += str+"\r\n";

	str.Format("FFT NUM:            %d", global.basic.basicinfo.nfft);
	m_strSysInfo += str+"\r\n";

	str.Format("TIME DOMAIN AVG(H): %d", global.basic.basicinfo.oblique_struct.time_domain_avg_high);
	m_strSysInfo += str+"\r\n";

	str.Format("TIME DOMAIN AVG(L): %d", global.basic.basicinfo.oblique_struct.time_domain_avg_low);
	m_strSysInfo += str+"\r\n";

	str.Format("FREQ DOMAIN AVG(H): %d", global.basic.basicinfo.oblique_struct.spec_domain_avg_high);
	m_strSysInfo += str+"\r\n";

	str.Format("FREQ DOMAIN AVG(L): %d", global.basic.basicinfo.oblique_struct.spec_domain_avg_low);
	m_strSysInfo += str+"\r\n";

	str.Format("RANGEBIN(H):        %d", global_advance.dmasetting.nDMA_High/2-global_advance.dspsetting.nBeginGateMoveH);
	m_strSysInfo += str+"\r\n";

	str.Format("RANGEBIN(L):        %d",global_advance.dmasetting.nDMA_Low/2-global_advance.dspsetting.nBeginGateMoveL);
	m_strSysInfo += str+"\r\n";


	m_strSysInfo += "\r\n";
	str.Format("CENTER FREQUENCY:   %dMHz",global_advance.dspsetting.nCenterFreq);
	m_strSysInfo += str+"\r\n";


	UpdateData(FALSE);

	return;
}


void CWPR_UTILITIESDlg::OnButtonDyntest() 
{
	// TODO: Add your control notification handler code here
	return;
}

#include "WPR_UTILITY_SPECView.h"
void CWPR_UTILITIESDlg::OnTotalspecView() 
{
	// TODO: Add your command handler code here
	if(g_bCycleCtrol)
	{
		AfxMessageBox("DON'T SUPPORT CYCLE TEST.");
		return;
	}
	/*
	CTotalSpecDlg dlg;
	specsview = &dlg;
	dlg.setParent(this);
	dlg.DoModal();
	*/
	if(!bSpectrasViewEnable){
		specsview = new CTotalSpecDlg;
		specsview->Create(IDD_DIALOG_SPEC_VIEW,this);
		specsview->setParent(this);
		specsview->ShowWindow(SW_SHOW);
		bSpectrasViewEnable = TRUE;

	}
	
}

void CWPR_UTILITIESDlg::ShowSpecTotal(UINT wParam, UINT lParam)
{
    if(bSpectrasViewEnable){
		if(specsview->p)
			specsview->p->Invalidate(FALSE);
	}
}

void CWPR_UTILITIESDlg::OnButtonInclinometer() 
{
	// TODO: Add your control notification handler code here
	//HERE I WANT TO RUN SM SIMULATOR THERE ARE
	//2 SOLUTION: ONE IS TO RUN IT BY SHELL THE OTHER IS TO CREATE
	//A PROCESS. THE FIRST WAY IS TOO EASY SO I WANT TO
	//TRY ANOTHER.
    PROCESS_INFORMATION pi;
	STARTUPINFO si;

	//Initialization
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwFlags=STARTF_USESHOWWINDOW;

	//Open
	BOOL fRet=CreateProcess(NULL,
							"inclinometer.exe",
							NULL,
							NULL,
							FALSE,
							NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE,
							NULL,
							NULL,
							&si,
							&pi);

	if(!fRet)
	{//Report the fail information
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
						FORMAT_MESSAGE_FROM_SYSTEM | 
						FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL,
						GetLastError(),
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
						(LPTSTR) &lpMsgBuf,
						0,
						NULL );
		AfxMessageBox( (LPCTSTR)lpMsgBuf);
		LocalFree( lpMsgBuf );
	}
}
