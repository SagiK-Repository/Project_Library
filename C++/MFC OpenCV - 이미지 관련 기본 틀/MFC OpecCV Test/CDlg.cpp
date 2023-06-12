#include "pch.h"
#include "framework.h"
#include "MFC OpecCV Test.h"
#include "CDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

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
// CDlg 대화 상자
CDlg::CDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_OPECCV_TEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void CDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT6, m_edit6);
	DDX_Control(pDX, IDC_EDIT5, m_edit5);
	DDX_Control(pDX, IDC_EDIT4, m_edit4);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_PIC1, m_pic1);
	DDX_Control(pDX, IDC_PIC2, m_pic2);
	DDX_Control(pDX, IDC_PIC3, m_pic3);
}
BEGIN_MESSAGE_MAP(CDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &CDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlg::OnBnClickedButton4)
END_MESSAGE_MAP()
// CDlg 메시지 처리기
void CDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CDlg::FillBitmapInfo(BITMAPINFO* bmi, int width, int height, int bpp, int origin)
{
	assert(bmi && width >= 0 && height >= 0 && (bpp == 8 || bpp == 24 || bpp == 32));
	BITMAPINFOHEADER* bmih = &(bmi->bmiHeader);
	memset(bmih, 0, sizeof(*bmih));
	bmih->biSize = sizeof(BITMAPINFOHEADER);
	bmih->biWidth = width;
	bmih->biHeight = origin ? abs(height) : -abs(height);
	bmih->biPlanes = 1;
	bmih->biBitCount = (unsigned short)bpp;
	bmih->biCompression = BI_RGB;
	if (bpp == 8) {
		RGBQUAD* palette = bmi->bmiColors;
		for (int i = 0; i < 256; i++) {
			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
			palette[i].rgbReserved = 0;
		}
	}
}
void CDlg::DisplayImage(CDC* pDC, CRect rect, Mat& srcimg)
{
	Mat img;
	int step = ((int)(rect.Width() / 4)) * 4; // 4byte 단위조정해야 영상이 기울어지지 않는다.
	resize(srcimg, img, Size(step, rect.Height()));
	uchar buffer[sizeof(BITMAPINFOHEADER) * 1024];
	BITMAPINFO* bmi = (BITMAPINFO*)buffer;
	int bmp_w = img.cols;
	int bmp_h = img.rows;
	int depth = img.depth();
	int channels = img.channels();
	int bpp = 8 * channels;
	FillBitmapInfo(bmi, bmp_w, bmp_h, bpp, 0);
	int from_x = MIN(0, bmp_w - 1);
	int from_y = MIN(0, bmp_h - 1);
	int sw = MAX(MIN(bmp_w - from_x, rect.Width()), 0);
	int sh = MAX(MIN(bmp_h - from_y, rect.Height()), 0);

	SetDIBitsToDevice(pDC->m_hDC, rect.left, rect.top, sw, sh, from_x, from_y, 0, sh, img.data + from_y * img.step, bmi, 0);
	img.release();
}



BOOL CDlg::OnInitDialog()
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

	//이미지 초기화
	Image01 = Mat(Size(273, 236), CV_8UC3, 1);
	Image02 = Mat(Size(273, 236), CV_8UC3, 1);
	Image03 = Mat(Size(273, 236), CV_8UC3, 1);
	PicImg1 = Image01.clone();
	PicImg2 = Image02.clone();
	PicImg3 = Image03.clone();

	//editText 초기화
	CString strs;
	strs.Format(_T("%.1f"), 0.7);
	SetDlgItemText(IDC_EDIT1, strs);
	//m_edit1.SetWindowText(strs);
	strs.Format(_T("%.1f"), 0.3);
	SetDlgItemText(IDC_EDIT2, strs);
	strs.Format(_T("%.1f"), 0.1);
	SetDlgItemText(IDC_EDIT3, strs);

	utils::logging::setLogLevel(utils::logging::LogLevel::LOG_LEVEL_SILENT);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CDlg::OnPaint()
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

	if (Image01.data != NULL) {
		PicImg1 = Image01.clone();
		resize(PicImg1, PicImg1, Size(272, 236));

		CRect rect;
		CDC* pDC;
		pDC = m_pic1.GetDC();
		m_pic1.GetClientRect(rect);
		DisplayImage(pDC, rect, PicImg1);
		ReleaseDC(pDC);
	}
	if (Image02.data != NULL) {
		PicImg2 = Image02.clone();
		resize(PicImg2, PicImg2, Size(272, 236));

		CRect rect;
		CDC* pDC;
		pDC = m_pic2.GetDC();
		m_pic2.GetClientRect(rect);
		DisplayImage(pDC, rect, PicImg2);
		ReleaseDC(pDC);
	}
	if (Image03.data != NULL) {
		PicImg3 = Image03.clone();
		resize(PicImg3, PicImg3, Size(272, 236));

		CRect rect;
		CDC* pDC;
		pDC = m_pic3.GetDC();
		m_pic3.GetClientRect(rect);
		DisplayImage(pDC, rect, PicImg3);
		ReleaseDC(pDC);
	}
}

void CDlg::OnBnClickedButton1() // Load Image
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY,
		_T("이미지 파일(*.jpg, *.png, *.GIF) | *.png;*.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |모든파일(*.*)|*.*||"), this, 0, 1);
	if (dlg.DoModal() == IDOK) {
		if (dlg.GetFileExt() == "jpg" || dlg.GetFileExt() == "png" || dlg.GetFileExt() == "bmp" || dlg.GetFileExt() == "BMP" || dlg.GetFileExt() == "JPG" || dlg.GetFileExt() == "gif" || dlg.GetFileExt() == "GIF") {
			Image01 = imread(string(CT2CA(dlg.GetPathName())), 1);
			load_name = dlg.GetFileTitle();
			Invalidate(FALSE);
		}
		else {
			MessageBox(_T("지원하지 않는 파일입니다. (_ _)"));
		}

	}
}


void CDlg::OnBnClickedButton5() // Distortion
{
	Invalidate(FALSE);
}


void CDlg::OnBnClickedButton3() // Save Image2
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (Image02.data != NULL) {
		CTime cTime = CTime::GetCurrentTime();//현재시간 받아오기
		CString sdate;
		sdate.Format(_T("_2DHisto %04d-%02d-%02d %02d_%02d_%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());

		CFileDialog dlg(FALSE, _T("jpg"), load_name + sdate, 0,
			_T("All Files (*.*)| *.*; ||"), this, 0, 1);
		if (dlg.DoModal() == IDOK) {
			if (dlg.GetFileExt() == "jpg" || dlg.GetFileExt() == "png" || dlg.GetFileExt() == "bmp" || dlg.GetFileExt() == "BMP" || dlg.GetFileExt() == "JPG" || dlg.GetFileExt() == "gif" || dlg.GetFileExt() == "GIF") {
				imwrite(string(CT2CA(dlg.GetPathName())), Image02);
			}
			else {
				imwrite(string(CT2CA(dlg.GetPathName())) + ".jpg", Image02);
			}
		}
	}
	else {
		MessageBox(_T(" 이미지를 불러와주세요. (*^0^*)"));
	}

}

void CDlg::OnBnClickedButton2() //Undistortion
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Invalidate(FALSE);
}


void CDlg::OnBnClickedButton4() // Save Image3
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}