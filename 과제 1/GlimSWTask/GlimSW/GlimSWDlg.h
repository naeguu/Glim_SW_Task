
// GlimSWDlg.h: 헤더 파일
//

#pragma once


// CGlimSWDlg 대화 상자
class CGlimSWDlg : public CDialogEx
{
// 생성입니다.
public:
	CGlimSWDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CImage m_image;
	CString m_stCenter;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIMSW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int m_nStartX;
	int m_nStartY;
	int m_nEndX;
	int m_nEndY;
	void drawRandCir();
	afx_msg void OnBnClickedBtnDraw();
	void actionCir(float& fSttX, float& fSttY, float fOneactionX, float fOneactionY);
	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnOpen();

private:
	int m_nCnt = 0;
};
