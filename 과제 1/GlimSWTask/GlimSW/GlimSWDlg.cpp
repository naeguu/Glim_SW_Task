
// GlimSWDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GlimSW.h"
#include "GlimSWDlg.h"
#include "afxdialogex.h"

#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGlimSWDlg 대화 상자



CGlimSWDlg::CGlimSWDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIMSW_DIALOG, pParent)
	, m_nStartX(0)
	, m_nStartY(0)
	, m_nEndX(0)
	, m_nEndY(0)
	, m_stCenter(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGlimSWDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_STARTX_NUM, m_nStartX);
	DDX_Text(pDX, IDC_EDIT_STARTY_NUM, m_nStartY);
	DDX_Text(pDX, IDC_EDIT_ENDX_NUM, m_nEndX);
	DDX_Text(pDX, IDC_EDIT_ENDY_NUM, m_nEndY);
	DDX_Text(pDX, IDC_EDIT_CENTER, m_stCenter);
}

BEGIN_MESSAGE_MAP(CGlimSWDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CGlimSWDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CGlimSWDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CGlimSWDlg::OnBnClickedBtnOpen)
END_MESSAGE_MAP()


// CGlimSWDlg 메시지 처리기

BOOL CGlimSWDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(0, 0, 890, 525);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGlimSWDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGlimSWDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGlimSWDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGlimSWDlg::drawRandCir()
{
	UpdateData(TRUE);

	if (m_image != NULL) {
		m_image.Destroy();
	}

	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	memset(fm, 0, nWidth * nHeight);

	int maxRadius = min(min(m_nStartX, nWidth - m_nStartX), min(m_nStartY, nHeight - m_nStartY));
	int radius = rand() % (maxRadius + 1);

	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);

	CBrush brush(RGB(100, 100, 100));
	CBrush* pOldBrush = dc.SelectObject(&brush);

	CRect rect;
	rect.SetRect(m_nStartX, m_nStartY, m_nStartX, m_nStartY);
	rect.InflateRect(radius, radius);
	dc.Ellipse(rect);

	dc.SelectObject(pOldBrush);
}

void CGlimSWDlg::OnBnClickedBtnDraw()
{
	drawRandCir();
}


CString g_strFileImage = _T("C:\\drawimage");

void CGlimSWDlg::actionCir(float& fSttX, float& fSttY, float fOneactionX, float fOneactionY)
{
	if (m_image != NULL) {
		m_image.Destroy();
	}
	
	int radius = 50;
	int nGray = 128;
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);

	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	memset(fm, 0xff, nWidth * nHeight);

	HDC hDC = m_image.GetDC();
	
	HBRUSH hBrush = CreateSolidBrush(RGB(nGray, nGray, nGray));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	CRect rect;
	rect.SetRect(fSttX, fSttY, fSttX, fSttY);
	rect.InflateRect(radius, radius);
	Ellipse(hDC, fSttX - radius, fSttY - radius, fSttX + radius, fSttY + radius);

	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);

	m_image.ReleaseDC();
	
	if (fSttX < (float)m_nEndX && fSttY < (float)m_nEndY) {
		fSttX += fOneactionX;
		fSttY += fOneactionY;

		if (fSttX > m_nEndX && fSttY > m_nEndY) {
			fSttX = (float)m_nEndX;
			fSttY = (float)m_nEndY;
		}
	}
	else if (fSttX < (float)m_nEndX && fSttY >(float)m_nEndY) {
		fSttX += fOneactionX;
		fSttY += fOneactionY;

		if (fSttX > m_nEndX && fSttY < m_nEndY) {
			fSttX = (float)m_nEndX;
			fSttY = (float)m_nEndY;
		}
	}
	else if (fSttX > (float)m_nEndX && fSttY < (float)m_nEndY) {
		fSttX += fOneactionX;
		fSttY += fOneactionY;

		if (fSttX < m_nEndX && fSttY > m_nEndY) {
			fSttX = (float)m_nEndX;
			fSttY = (float)m_nEndY;
		}
	}
	else if (fSttX > (float)m_nEndX && fSttY > (float)m_nEndY) {
		fSttX += fOneactionX;
		fSttY += fOneactionY;

		if (fSttX < m_nEndX && fSttY < m_nEndY) {
			fSttX = (float)m_nEndX;
			fSttY = (float)m_nEndY;
		}
	}

	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);

	g_strFileImage.Format(_T("C:\\drawimage\\ationimg_%d.bmp"), m_nCnt);
	m_image.Save(g_strFileImage);
	m_nCnt++;
}

void CGlimSWDlg::OnBnClickedBtnAction()
{
	UpdateData(TRUE);

	m_nCnt = 0;

	float fSttX = (float)m_nStartX;
	float fSttY = (float)m_nStartY;

	float fDX = m_nEndX - m_nStartX;
	float fDY = m_nEndY - m_nStartY;
	float fOneactionX = fDX / 100.0f;
	float fOneactionY = fDY / 100.0f;

	for (int i = 0; i < 101; i++) {
		actionCir(fSttX, fSttY, fOneactionX, fOneactionY);
	}
}


void CGlimSWDlg::OnBnClickedBtnOpen()
{
	CFileDialog file(TRUE, _T("bmp"), NULL, OFN_FILEMUSTEXIST, _T("Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), this);

	file.m_ofn.lpstrInitialDir = g_strFileImage;

	if (file.DoModal() == IDOK) {
		CString g_strFilePath = file.GetPathName();

		if (m_image != NULL) {
			m_image.Destroy();
		}

		m_image.Load(g_strFilePath);

		unsigned char* fm = (unsigned char*)m_image.GetBits();
		int nWidth = m_image.GetWidth();
		int nHeight = m_image.GetHeight();
		int nPitch = m_image.GetPitch();

		int nGray = 128;
		int nSumX = 0;
		int nSumY = 0;
		int nCount = 0;

		for (int j = 0; j < nHeight; j++) {
			for (int i = 0; i < nWidth; i++) {
				if (fm[j * nPitch + i] == 128) {
					nSumX += i;
					nSumY += j;
					nCount++;
				}
			}
		}

		double dCenterX = (double)nSumX / nCount;
		double dCenterY = (double)nSumY / nCount;

		int nCenterX = (int)(round(dCenterX));
		int nCenterY = (int)(round(dCenterY));

		for (int i = -3; i <= 3; i++) {
			if (nCenterY + i >= 0 && nCenterY + i < nHeight && nCenterX + i >= 0 && nCenterX + i < nWidth) {
				fm[(nCenterY + i) * nPitch + (nCenterX + i)] = 0xff;
			}
			if (nCenterY + i >= 0 && nCenterY + i < nHeight && nCenterX - i >= 0 && nCenterX - i < nWidth) {
				fm[(nCenterY + i) * nPitch + (nCenterX - i)] = 0xff;
			}
		}

		//cout << dCenterX << "," << dCenterY << endl;

		CString stCenter;
		stCenter.Format(_T("(%.2f, %.2f)"), dCenterX, dCenterY);
		m_stCenter = stCenter;
		UpdateData(FALSE);
		

		CClientDC dc(this);
		m_image.Draw(dc, 0, 0);
	}
}
