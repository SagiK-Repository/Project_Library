
#include <opencv2/opencv.hpp>
#include <time.h>
#include <opencv2/core/utils/logger.hpp>
using namespace cv;  // cv 안써도 됨
using namespace std; //std 안써도 됨

#pragma warning (disable:4819) //경고 메시지 숨기기
#pragma warning (disable:4996) //경고 메시지 숨기기

//

#pragma once

static UINT ThreadImageCaptureFunc(LPVOID pParam);


// CDlg 대화 상자
class CDlg : public CDialogEx
{
// 생성입니다.
public:
	CDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	Mat m_Image;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_OPECCV_TEST_DIALOG };
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
	CStatic m_pic1;
	afx_msg void OnBnClickedButton1();
	void FillBitmapInfo(BITMAPINFO* bmi, int width, int height, int bpp, int origin);
	void DisplayImage(CDC* pDC, CRect rect, Mat& srcimg);
};
