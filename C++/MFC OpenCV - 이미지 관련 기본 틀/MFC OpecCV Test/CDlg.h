
#include <opencv2/opencv.hpp>
#include <time.h>
#include <opencv2/core/utils/logger.hpp>
using namespace cv;  // cv 안써도 됨
using namespace std; //std 안써도 됨

#pragma warning (disable:4819) //경고 메시지 숨기기
#pragma warning (disable:4996) //경고 메시지 숨기기

//

#pragma once


// CDlg 대화 상자
class CDlg : public CDialogEx
{
// 생성입니다.
public:
	CDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	Mat Image01, Image02, Image03;//원본이미지
	Mat PicImg1, PicImg2, PicImg3; //이미지 띄우기용 (원본이미지 간섭을 줄이기 위해
	CString load_name; // 로딩 이미지 이름

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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	CEdit m_edit6;
	CEdit m_edit5;
	CEdit m_edit4;
	CEdit m_edit3;
	CEdit m_edit2;
	CEdit m_edit1;
	CStatic m_pic1;
	CStatic m_pic2;
	CStatic m_pic3;


	void FillBitmapInfo(BITMAPINFO* bmi, int width, int height, int bpp, int origin);
	void DisplayImage(CDC* pDC, CRect rect, Mat& srcimg);

};
