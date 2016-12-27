
// PharmexCodeTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PharmexCodeTest.h"
#include "PharmexCodeTestDlg.h"
#include <winspool.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPharmexCodeTestDlg dialog




CPharmexCodeTestDlg::CPharmexCodeTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPharmexCodeTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPharmexCodeTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPharmexCodeTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CPharmexCodeTestDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPharmexCodeTestDlg message handlers

BOOL CPharmexCodeTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPharmexCodeTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPharmexCodeTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPharmexCodeTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPharmexCodeTestDlg::OnBnClickedOk()
{
	
	// TODO: Add your control notification handler code here
	int i;
	int rtnflg;
	char prt_type[50];
	char	rpt_buf[350];
	char	printjob_descr[50];
	char pharmex_font[30]= {0x1b,0x28,0x31,0x51,0x1b,0x28,0x73,0x31,0x70,0x32,
						    0x31,0x76,0x30,0x73,0x30,0x62,0x31,0x30,0x31,0x54,
							0x1b,0x26,0x61,0x30,0x30,0x30,0x30,0x48,0,0};

	char prtc_cpi12[12] = {0x1B,0x28,0x73,0x31,0x32,0x48,0,0,0,0,0,0};
	char prtc_lpi8[12] = {0x1B,0x26,0x6C,0x38,0x44,0,0,0,0,0,0,0};
	char prtc_font1[25] = {0x1B,0x28,0x38,0x55,0x1B,0x28,0x73,0x30,0x70,0x31,0x31,0x68,0x30,0x73,0x30,0x62,0x34,0x30,0x39,0x39,0x54,0,0,0,0};

	char    szDevice[100];
	char    szDriver[100];
	char	szNewPrint[100];
	CString str;
	HANDLE		hPrinter;						// 11/24/01
	DOC_INFO_1	DocInfo;						// 11/24/01
	DWORD		dwJob;							// 11/24/01
	DWORD		dwBytesWritten;					// 11/24/01



	memcpy(printjob_descr, "Printing Laser Label                              ", 50);	// 11/28/07 defect #1775 DAC


	CPrintDialog dlgPrint(FALSE);
	if (dlgPrint.DoModal() != IDOK)
		return;
//	str = dlgPrint.GetPortName();
//	str = dlgPrint.GetDriverName();
	str = dlgPrint.GetDeviceName();
	int len = str.GetLength();
	memset(szDevice,0,100);
	memcpy(szDevice,str,str.GetLength());
	delete dlgPrint;

	GetProfileString("devices", szDevice,"",szDriver, 64);			// 07/17/06 get the default printer before anything is done
	strcpy(szNewPrint, szDevice);				// copy printer name to szNewPrint
	strcat(szNewPrint, ",");					// put ',' after it
	strcat(szNewPrint, szDriver);				// now copy driver & port
	WriteProfileString("windows", "device", szNewPrint);// make default
	if (!OpenPrinter(szDevice, &hPrinter, NULL))// 11/24/01 get a handle to the printer
		{
		i = GetLastError();					// 07/02/02
		return;
		}									// 07/02/02
	DocInfo.pDocName = "RX Label";			// 11/24/01
	DocInfo.pOutputFile = NULL;				// 11/24/01
	DocInfo.pDatatype = "RAW";				// 11/24/01
	if ( (dwJob = StartDocPrinter(hPrinter, 1, (LPBYTE)&DocInfo)) == 0)	// 11/24/01
		{
		rtnflg = GetLastError();			// 11/24/01
		goto prt_exit;						// 11/24/01
		}

	if (!StartPagePrinter(hPrinter))		// 11/24/01
		goto prt_exit;						// 11/24/01
	  i = 33;
	  rtnflg = 0;
	  while (i < 256)
		{
		  memset(rpt_buf,' ',350);
		  memcpy(rpt_buf,prtc_cpi12,12);
		  memcpy(rpt_buf+12,prtc_lpi8,12);
		  sprintf(rpt_buf+24, "%-4d thru %-4d",i,i+3);
		  rpt_buf[39] = 0x0a;
		  rpt_buf[40] = 0x0a;
		  WritePrinter(hPrinter, rpt_buf, 41, &dwBytesWritten);
	//    10/13/16 print all pharmex codes
		  memset(rpt_buf,' ',300);                                          // build line 1
		  memcpy(rpt_buf,prtc_cpi12,12);
		  memcpy(rpt_buf+12,prtc_lpi8,12);
		  memcpy(rpt_buf+24, pharmex_font, 28);                       // put out pharmex font codes
		  rpt_buf[48] = 0x39;
		  if ( i < 256)
			{
			rpt_buf[52] = i;//0x21;
			i++;
			}
		  if ( i < 256)
			{
			rpt_buf[53] = i;//0x21;
			i++;
			}
		  if ( i < 256)
			{
			rpt_buf[54] = i;//0x21;
			i++;
			}
		  if ( i < 256)
			{
			rpt_buf[55] = i;//0x21;
			i++;
			}
		  memcpy(rpt_buf+56,prtc_font1,25);                          // get font other line feeds in
		  if ( rtnflg == 23)
			{
			rtnflg = 0;
			rpt_buf[81] = 0x0a;
			rpt_buf[82] = 0x0c;
			WritePrinter(hPrinter, rpt_buf, 83, &dwBytesWritten);
			}
		  else
			{
			rpt_buf[81] = 0x0a;
			WritePrinter(hPrinter, rpt_buf, 82, &dwBytesWritten);
			rtnflg++;
			}
		}
		rpt_buf[0] = 0x0c;
		WritePrinter(hPrinter, rpt_buf, 1, &dwBytesWritten);




prt_exit:
//	spclos();										// 07/23/12 defect #7181:  be sure default printer is restored
	ClosePrinter(hPrinter);							// 11/24/01
	//OnOK();
}
