//#include <opencv2/opencv.hpp>
//using namespace cv;  // cv 안써도 됨
//using namespace std; //std 안써도 됨
//
//int main() {
//	int n;	double max, min;
//	//각 출력
//	Point pt8, pt7; Size sz; Rect rect; Vec<double, 3> v1, v2;
//	Scalar_<uchar> scal; Matx<int, 3, 3> mx; Mat m;
//	vector<Point> vc;
//
//	cout << "Point" << pt8.x << pt7.dot(pt8) << endl;
//	cout << "Size" << sz.width << sz.area() << endl;
//	cout << "Rect" << rect << rect.x << rect.width << rect.br() << endl;
//	cout << "Vec" << v1 << v1.mul(v2) << v1[0] << endl;
//	cout << "Scalar" << scal << scal[0] << endl;
//	cout << "Matx" << mx << mx(0, 0) << endl;
//	cout << "Mat" << m << m.dims << "속성이 많다" << endl;
//	cout << "Vector" << (Mat)vc << ((Mat)vc).reshape(1, 1) << endl;
//	cout << "Vector_2" << vc.capacity() << vc.size() << endl; //벡터 용량, 벡터 원소 개수
//
//
//	//객체
//	{
//		//RotationRect
//		Point2d center; Size size; double angle;
//		RotatedRect rot_rect(center, size, angle); Point2f pt_r[4];
//		rot_rect.points(pt_r); //꼭짓점 반환
//		cout << rot_rect.center << endl;
//
//		//Mat 연산
//		Mat m1, m2; Mat image0;
//		m1 = m1 + m2; m1 = m2;//위치 포인터 저장
//		m1 = 100; //원소를 값 100 전부 지정
//		m1.resize(5, Scalar(50)); //m1의 가로, 새로생긴 부분은 50으로(생략시 랜덤)
//		m1.reshape(3, 2); //3채널 2행
//		m1.create(3, 5, CV_16S);
//		m1.copyTo(m2); m1 = m2.clone(); // 복사
//		m1.convertTo(m2, CV_8U); //변형
//		m1.push_back(m2); //아래에 추가 (Scalar 가능)
//		m1.pop_back(3); //뒤에 3만큼 제거
//		m1.release(); //m1 해제
//		m1.t(); //전치
//		m1.inv(DECOMP_LU); //역행렬
//		invert(m1, m2, DECOMP_LU); //역행렬 계산
//		add(image0, 10, image0); //+10
//		subtract(image0, 10, image0); // -10
//		divide(m1, m2, m1); //나누기
//		Rect roi(100, 100, 1, 1);  //영역지정
//		cout << "Mat" << m(roi) << endl; // 영역출력
//		flip(image0, image0, 0); // 0 : x축 기준 상하 뒤집기, 1: y축 기준 좌우 뒤집기, -1 : 상하좌우 뒤집기
//		repeat(image0, 1, 2, image0);  //반복 복사
//		transpose(image0, image0);  //행렬 전치 (반시계방향으로 90도 회전)
//		Mat ch0, ch1, ch2; Mat bgr_arr[] = { ch0, ch1, ch2 }; vector<Mat> bgr_vec;
//		merge(bgr_arr, 3, image0); //채널 합성 [1,2,3,1,2,3,1,2,3; 1,2,3,1,2,3,1,2,3]
//		split(image0, bgr_vec);	//채널 분리 bgr_vec[0], bgr_vec[1], bgr_vec[2]
//		int from_to[] = { 0,0,2,1,1,2 }; // 입력 출력 채널의 순서쌍 {0번채널 0번에, 2번채널 1번에, ,,}
//		mixChannels(&image0, 1, bgr_arr, 2, from_to, 3);  //채널 합성, 원본  분해요소 분해수 분해순서쌍 
//		exp(m1, m2);
//		log(m1, m2);
//		sqrt(m1, m2);
//		pow(m1, 2, m2);
//		abs(m1);
//		absdiff(m1, m2, m1); //영상차이
//		bitwise_or(m1, m2, m1); //원소 간 논리 합
//		bitwise_and(m1, m2, m1); //원소간 논리 곱
//		bitwise_xor(m1, m2, m1); // 원소간 배타적 논리 합
//		bitwise_not(m1, m2); //행렬 반전;
//		int minIdx[2], maxIdx[2]; Point minLoc, maxLoc;
//		minMaxIdx(m1, &min, &max); //최댓값, 최솟값 가져오기 (double)
//		minMaxIdx(m1, &min, &max, minIdx, maxIdx); //최소최대값(double), 최소최대좌표(int[2])
//		minMaxLoc(m1, 0, 0, &minLoc, &maxLoc); //최소 최고 위치 (Point)
//		normalize(m1, m2, min, max, NORM_MINMAX); //m1의 최소 > min, m1의 최대 > max
//		Scalar mean1, stddev; Mat mask;
//		mean1 = sum(m1); // [60000, 700000, 80000, 0]
//		mean1 = mean(m1); // [126,157,138,0]
//		meanStdDev(m1, mean1, stddev, mask); //행렬, 평균행렬, 표준편차, 마스크 1인 영역만 계산 (생략가능)
//		sort(m1, m2, SORT_EVERY_ROW); //행렬 원소 정렬  행렬, 저장행렬, 행 단위 오름차순
//		sort(m1, m2, SORT_EVERY_ROW + SORT_DESCENDING); // 행단위 내림차순
//		sort(m1, m2, SORT_EVERY_COLUMN); // 열단위 오름차순
//		sortIdx(m1, m2, SORT_EVERY_ROW); //정렬 원소의 원본좌표 [0,1,2; 1,2,0; 0,1,2]
//		sortIdx(m1, m2, SORT_EVERY_COLUMN); //[ 0,1,1; 2,1,0; 1,2,2]
//		reduce(m1, m2, 0, REDUCE_SUM); //0 - 열방향 감축 (위에서 아래로 합 결과) [24,24,26]
//		reduce(m1, m2, 1, REDUCE_AVG); //1 - 행방향 감축 (왼쪽>오른쪽 평균) [4.2;8.0;2.0]
//		reduce(m1, m2, 0, REDUCE_MAX); // 열방향 최대값 도출 [11,12,15]
//		reduce(m1, m2, 1, REDUCE_MIN); // 행방향 최솟값 도출 [2;6;7]
//		//행렬곱
//		double alpha = 1.0, beta = 1.0; // 스케일을 곱하는 인수로 사용될 변수
//		gemm(m1, m2, alpha, noArray(), beta, m2, GEMM_1_T); // [2x3]x[3x2] = [2x2], GEMM_n_T(생략시 적용x) n번 전치후 곱
//		solve(m1, m2, m1, DECOMP_LU); //연립방정식 풀이
//		int i, j, k;
//		m1.at<int>(i, j) = k; //행렬 원소 접근
//		m1.at<Vec3i>(i, j)[2] = 2; // 2채널
//		addWeighted(m1, alpha, m2, beta, 0, m1); //원소 비율곱
//		int bins, range_max;
//		int histSize[] = { bins }; // 히스토그램 계급 개수 
//		float range[] = { 0, (float)range_max }; // 0번 채널 화소값 범위
//		int channels[] = { 0 }; // 채널 목록 - 단일채널
//		const float* ranges[] = { range }; //모든 채널 화소 범위 예) [0,256] 의 주소값
//		calcHist(&m1, 1, channels, Mat(), m2, 1, histSize, ranges); // 원소개수계산
//		//      이미지,         마스크, 저장, 차원수, 각차원의 bins 수, 각 차원의 히스토그램 범위
//
//		//Vector 연산
//		vector<Point> vc1; vector<int> vc2;
//		vc1.push_back(Point(10, 20));
//		int arr_int[] = { 10,20,30,40,50 }; //배열 Vector 변환
//		vector<int> v4(arr_int + 2, arr_int + sizeof(arr_int) / sizeof(int));
//		vc2.insert(vc2.begin() + 2, 100);  //3번째 위치에 100 삽입 [10,20,100,30,40,50]
//		vc1.erase(vc1.begin() + 3); //4번째 위치 제거 [10,20,100,40,50]
//		vc1.reserve(10000000);    // 용량
//		vc1.clear();  // 초기화
//		exp(vc1, vc2);
//		log(vc1, vc2);
//		exp(vc1, vc2);
//		log(vc1, vc2);
//		sqrt(vc1, vc2);
//		pow(vc1, 2, vc2);
//		magnitude(vc1, vc2, vc1);//벡터 > 크기
//		phase(vc1, vc2, vc1); //벡터 > 각도
//		cartToPolar(vc1, vc2, m1, m2);//벡터(vc1,vc2) > 크기(m1), 각도(m2)
//		polarToCart(m1, m2, vc1, vc2); //행렬 입력 > 벡터 반환 //크기와 각도로 각 원소의 x,y좌표 계산
//
//
//		//Range
//		Range r1(0, 1), r2(2, 3);
//		m2 = m1(r1, r2);
//		m2.setTo(50); // (m1의 r1-r2까지의 영역이 50으로 변경)
//		m2.locateROI(size, pt8); //size와 pt에 정보 저장
//		m2.adjustROI(-1, 1, 2, -1); //(위쪽, 아래, 왼쪽, 오른쪽) 영역 변화
//
//		//그리기
//		Mat image; Scalar color; int 두께; double start_angle, end_angle;
//		line(image, pt7, pt8, color, 두께, LINE_AA, 1);
//		rectangle(image, rect, color, 두께);  //두께 -1 : 꽉 채우기
//		circle(image, rot_rect.center, 1, Scalar(0), 2);
//		putText(image, "TEXT", pt7, FONT_HERSHEY_SIMPLEX, 두께, color);
//		ellipse(image, pt7, Size(100, 60), angle, start_angle, end_angle, color, 두께);
//
//		//이미지
//		Mat img0, img1;
//		threshold(img0, img1, 70, 255, THRESH_BINARY); // 영상 이진화
//	}
//
//	//예외처리
//	{
//		string msg1 = "a is one.";
//		string msg2 = "a is two.";
//		string msg3 = "a is three.";
//		int a;
//		while (true) {
//			cout << "input a : ";
//			cin >> a;
//
//			try {
//				if (a == 0) CV_Error(Error::StsDivByZero, "a is zero.");
//				if (a == 1) CV_Error(Error::StsBadSize, msg1);
//				if (a == 2) CV_Error_(Error::StsOutOfRange, ("%s : %d", msg2.c_str(), a));
//				if (a == 3) CV_Error_(Error::StsDivByZero, ("%s : %d", msg3.c_str(), a));
//
//				CV_Assert(a != 4);
//			}
//			catch (cv::Exception& e) {
//				cout << "Exception code (" << e.code << "):" << e.what();
//				cout << endl;
//				if (e.code == Error::StsAssert)
//					break;
//			}
//		}
//
//		string filename = "../image/read_gray.jpg"; //영상파일 위치
//		Mat gray2gray = imread(filename, IMREAD_GRAYSCALE); //영상파일 로드
//		Mat gray2color = imread(filename, IMREAD_COLOR);
//		CV_Assert(gray2gray.data&& gray2color.data);
//	}
//
//	//기타
//	{
//		//시간
//		double start_time = clock();
//
//		//포화 산술 연산
//		uchar uch = saturate_cast<uchar>(-50); // -50 > 0, 300 > 255
//
//		int ms;
//		waitKey(ms);
//	}
//
//
//
//	//vector to Mat
//	((Mat)v1).reshape(1, 1);
//	//int 배열 출력 (vector > Mat)
//	int bins;
//	int histSize[] = { bins }; // 히스토그램 계급 개수
//	vector<int> v1(histSize, histSize + sizeof(histSize) / sizeof(int));
//	cout << "histSize[]" << ((Mat)v1).reshape(1, 1) << endl;
//
//	//원본좌표를 이용하면, 크기를 정렬할 때 쉽게 할 수 있다
//	//rects->다양한 사각형 크기들
//	//	sortIdx(sizes, sort_idx, SORT_EVERY_COLUMN);
//	//->크기별로 원본좌표 저장
//	//	for (i++) : rects[sort_idx(i)];->크기별로 출력
//
//	//회전변환행렬     
//	Mat m1, m2;
//	float theta = 20 * CV_PI / 180; //라디안 각도
//	Matx22f m(cos(theta), -sin(theta), sin(theta), cos(theta)); //회전 변환 행렬
//	transform(m1, m2, m); // 회전 변환 (rect_pt1 = [200,50; 400,50; 400,250; 200,250]
//
//	//반복자 행렬 원소 접근 (포인터 접근방식)
//	Mat m3;
//	MatConstIterator_<uchar> it_m1 = m1.begin<uchar>(); //반복자 선언 it_m1은 포인터
//	MatIterator_<uchar> it_m2 = m2.begin<uchar>();
//	Mat_<Vec3f>::iterator it_m3 = m3.begin<Vec3f>(); //3채널의 m3
//	for (; it_m1 != m1.end<uchar>(); ++it_m1, ++it_m2, ++it_m3) {//행렬 전체 조회 (원소수만큼) 
//		*it_m2 = *it_m1; //1대1 대응     //주솟값 ++
//		(*it_m3)[0] = *it_m1 * 0.5f; //3채널에 각 부여
//		(*it_m3)[1] = *it_m1 * 0.3f;
//		(*it_m3)[2] = *it_m1 * 0.2f;
//	}
//
//	Mat hist, hist_img; Point2i pt1, pt2;
//	//hist 활용
//	normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);  //256가지 밝기를 나타내는 hist_img
//	rectangle(hist_img, pt1, pt2, Scalar(0), -1); //시작점 끝점 꽉차게 그리기
//	flip(hist_img, hist_img, 0); //x 축 기준 영상 뒤집기
//
//}
//
////HSV to GBR 바 만들기
//Mat make_palatte(int rows) {
//	Mat hsv(rows, 1, CV_8UC3);
//	for (int i = 0; i < rows; i++) {
//
//		[HVS 컬러]
//		uchar hue = saturate_cast<uchar>((float)i / rows * 180); //색상 계산
//		hsv.at<Vec3b>(i) = Vec3b(hue, 255, 255); //HVS 컬러 지정
//	}
//	cvtColor(hsv, hsv, COLOR_HSV2BGR); // HVS -> BGR 컬러
//	return hsv;
//}