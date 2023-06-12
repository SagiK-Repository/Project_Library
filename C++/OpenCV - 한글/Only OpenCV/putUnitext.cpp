#include "putUnitext.h"

HBITMAP stringToBitmap(char* text, cv::Scalar color)
{
	int textLength = (int)strlen(text);
	HDC hTextDC = CreateCompatibleDC(NULL);

	HFONT mFont = CreateFont(
		20,                            // 글자높이
		10,                            // 글자너비
		0,                            // 출력각도
		0,                            // 기준 선에서의각도
		FW_HEAVY,                    // 글자굵기
		FALSE,                        // Italic 적용여부
		FALSE,                        // 밑줄적용여부
		FALSE,                        // 취소선적용여부
		DEFAULT_CHARSET,            // 문자셋종류
		OUT_DEFAULT_PRECIS,            // 출력정밀도
		CLIP_CHARACTER_PRECIS,        // 클리핑정밀도
		PROOF_QUALITY,                // 출력문자품질
		DEFAULT_PITCH,                // 글꼴Pitch
		_T("궁서체")                // 글꼴
	);

	HFONT hOldFont = (HFONT)SelectObject(hTextDC, mFont);
	
	HBITMAP hDstBMP = NULL;

	RECT textArea = { 0, 0, 0, 0 };
	DrawText(hTextDC, (LPCTSTR)text, textLength, &textArea, DT_CALCRECT);

	if ((textArea.right > textArea.left) && (textArea.bottom > textArea.top))
	{
		BITMAPINFOHEADER  bitmapInfoHeader;
		memset(&bitmapInfoHeader, 0x0, sizeof(BITMAPINFOHEADER));

		void *lpvBits = NULL;

		bitmapInfoHeader.biSize = sizeof(bitmapInfoHeader);
		bitmapInfoHeader.biWidth = textArea.right - textArea.left;
		bitmapInfoHeader.biHeight = textArea.bottom - textArea.top;
		bitmapInfoHeader.biPlanes = 1;
		bitmapInfoHeader.biBitCount = 32;
		bitmapInfoHeader.biCompression = BI_RGB;

		hDstBMP = CreateDIBSection(hTextDC, (LPBITMAPINFO)&bitmapInfoHeader, 0, (LPVOID*)&lpvBits, NULL, 0);

		HBITMAP hOldBMP = (HBITMAP)SelectObject(hTextDC, hDstBMP); //Take BMP from DC

		if (hOldBMP != NULL)
		{
			int TEXT_RED = (int)color.val[2];
			int TEXT_GREEN = (int)color.val[1];
			int TEXT_BLUE = (int)color.val[0];

			SetTextColor(hTextDC, RGB(TEXT_RED, TEXT_GREEN, TEXT_BLUE));
			SetBkColor(hTextDC, 0x00EFFEFF);
			SetBkMode(hTextDC, OPAQUE);

			DrawText(hTextDC, (LPCTSTR)text, textLength, &textArea, DT_NOCLIP);
		}
		::SelectObject(hTextDC, hOldBMP);

	}
	::SelectObject(hTextDC, hOldFont);
	if (hTextDC) { ::DeleteDC(hTextDC); }
	if (hOldFont) { ::DeleteObject(hOldFont); }

	return hDstBMP;
}

cv::Mat bitmapToMat(HBITMAP hBitmap)
{
	BITMAP bitmap;
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bitmap);

	int nChannels = bitmap.bmBitsPixel == 1 ? 1 : bitmap.bmBitsPixel / 8;
	int depth = bitmap.bmBitsPixel == 1 ? 1 : 8;// IPL_DEPTH_1U : IPL_DEPTH_8U;

	BYTE *pBuffer = new BYTE[bitmap.bmHeight*bitmap.bmWidth*nChannels];
	GetBitmapBits(hBitmap, bitmap.bmHeight*bitmap.bmWidth*nChannels, pBuffer);

	cv::Mat Channel4Mat(bitmap.bmHeight, bitmap.bmWidth, CV_MAKETYPE(depth, nChannels));
	memcpy(Channel4Mat.data, pBuffer, bitmap.bmHeight*bitmap.bmWidth*nChannels);
	cv::Mat ret(bitmap.bmHeight, bitmap.bmWidth*nChannels, CV_8UC3);
	cv::cvtColor(Channel4Mat, ret, cv::COLOR_BGRA2BGR);

	delete[] pBuffer;

	return ret;
}

void putUniText(cv::Mat src, cv::Mat& dst, char* text, cv::Point point, cv::Scalar color)
{
	int width = src.cols;
	int height = src.rows;

	cv::Scalar var = { 0,0,0 };
	HBITMAP hBitmap = stringToBitmap(text, color);		// Text to Bimap
	cv::Mat text_image = bitmapToMat(hBitmap);				// Bitmap to Mat
	cv::Vec3b elem;

	if (src.channels() == 1)		merge(src, dst);
	else if (src.channels() != 1)	src.copyTo(dst);

	if ((point.y > height) || (point.x > width)) src.copyTo(dst);

	for (int y = point.y; y < (point.y + text_image.rows); y++)
	{
		for (int x = point.x; x < (point.x + text_image.cols); x++)
		{
			if (y >= height || x >= width) continue;

			elem = text_image.at<cv::Vec3b>(y - point.y, x - point.x);

			if ((int)(elem[0]) == color.val[0] && (int)(elem[1]) == color.val[1] && (int)(elem[2]) == color.val[2])
				dst.at<cv::Vec3b>(y, x) = text_image.at<cv::Vec3b>(y - point.y, x - point.x);
		}
	}

	DeleteObject(hBitmap);
}