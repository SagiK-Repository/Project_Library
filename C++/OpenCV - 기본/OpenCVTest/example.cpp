//#include <opencv2/opencv.hpp>
//using namespace cv;  // cv �Ƚᵵ ��
//using namespace std; //std �Ƚᵵ ��
//
//int main() {
//	int n;	double max, min;
//	//�� ���
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
//	cout << "Mat" << m << m.dims << "�Ӽ��� ����" << endl;
//	cout << "Vector" << (Mat)vc << ((Mat)vc).reshape(1, 1) << endl;
//	cout << "Vector_2" << vc.capacity() << vc.size() << endl; //���� �뷮, ���� ���� ����
//
//
//	//��ü
//	{
//		//RotationRect
//		Point2d center; Size size; double angle;
//		RotatedRect rot_rect(center, size, angle); Point2f pt_r[4];
//		rot_rect.points(pt_r); //������ ��ȯ
//		cout << rot_rect.center << endl;
//
//		//Mat ����
//		Mat m1, m2; Mat image0;
//		m1 = m1 + m2; m1 = m2;//��ġ ������ ����
//		m1 = 100; //���Ҹ� �� 100 ���� ����
//		m1.resize(5, Scalar(50)); //m1�� ����, ���λ��� �κ��� 50����(������ ����)
//		m1.reshape(3, 2); //3ä�� 2��
//		m1.create(3, 5, CV_16S);
//		m1.copyTo(m2); m1 = m2.clone(); // ����
//		m1.convertTo(m2, CV_8U); //����
//		m1.push_back(m2); //�Ʒ��� �߰� (Scalar ����)
//		m1.pop_back(3); //�ڿ� 3��ŭ ����
//		m1.release(); //m1 ����
//		m1.t(); //��ġ
//		m1.inv(DECOMP_LU); //�����
//		invert(m1, m2, DECOMP_LU); //����� ���
//		add(image0, 10, image0); //+10
//		subtract(image0, 10, image0); // -10
//		divide(m1, m2, m1); //������
//		Rect roi(100, 100, 1, 1);  //��������
//		cout << "Mat" << m(roi) << endl; // �������
//		flip(image0, image0, 0); // 0 : x�� ���� ���� ������, 1: y�� ���� �¿� ������, -1 : �����¿� ������
//		repeat(image0, 1, 2, image0);  //�ݺ� ����
//		transpose(image0, image0);  //��� ��ġ (�ݽð�������� 90�� ȸ��)
//		Mat ch0, ch1, ch2; Mat bgr_arr[] = { ch0, ch1, ch2 }; vector<Mat> bgr_vec;
//		merge(bgr_arr, 3, image0); //ä�� �ռ� [1,2,3,1,2,3,1,2,3; 1,2,3,1,2,3,1,2,3]
//		split(image0, bgr_vec);	//ä�� �и� bgr_vec[0], bgr_vec[1], bgr_vec[2]
//		int from_to[] = { 0,0,2,1,1,2 }; // �Է� ��� ä���� ������ {0��ä�� 0����, 2��ä�� 1����, ,,}
//		mixChannels(&image0, 1, bgr_arr, 2, from_to, 3);  //ä�� �ռ�, ����  ���ؿ�� ���ؼ� ���ؼ����� 
//		exp(m1, m2);
//		log(m1, m2);
//		sqrt(m1, m2);
//		pow(m1, 2, m2);
//		abs(m1);
//		absdiff(m1, m2, m1); //��������
//		bitwise_or(m1, m2, m1); //���� �� �� ��
//		bitwise_and(m1, m2, m1); //���Ұ� �� ��
//		bitwise_xor(m1, m2, m1); // ���Ұ� ��Ÿ�� �� ��
//		bitwise_not(m1, m2); //��� ����;
//		int minIdx[2], maxIdx[2]; Point minLoc, maxLoc;
//		minMaxIdx(m1, &min, &max); //�ִ�, �ּڰ� �������� (double)
//		minMaxIdx(m1, &min, &max, minIdx, maxIdx); //�ּ��ִ밪(double), �ּ��ִ���ǥ(int[2])
//		minMaxLoc(m1, 0, 0, &minLoc, &maxLoc); //�ּ� �ְ� ��ġ (Point)
//		normalize(m1, m2, min, max, NORM_MINMAX); //m1�� �ּ� > min, m1�� �ִ� > max
//		Scalar mean1, stddev; Mat mask;
//		mean1 = sum(m1); // [60000, 700000, 80000, 0]
//		mean1 = mean(m1); // [126,157,138,0]
//		meanStdDev(m1, mean1, stddev, mask); //���, ������, ǥ������, ����ũ 1�� ������ ��� (��������)
//		sort(m1, m2, SORT_EVERY_ROW); //��� ���� ����  ���, �������, �� ���� ��������
//		sort(m1, m2, SORT_EVERY_ROW + SORT_DESCENDING); // ����� ��������
//		sort(m1, m2, SORT_EVERY_COLUMN); // ������ ��������
//		sortIdx(m1, m2, SORT_EVERY_ROW); //���� ������ ������ǥ [0,1,2; 1,2,0; 0,1,2]
//		sortIdx(m1, m2, SORT_EVERY_COLUMN); //[ 0,1,1; 2,1,0; 1,2,2]
//		reduce(m1, m2, 0, REDUCE_SUM); //0 - ������ ���� (������ �Ʒ��� �� ���) [24,24,26]
//		reduce(m1, m2, 1, REDUCE_AVG); //1 - ����� ���� (����>������ ���) [4.2;8.0;2.0]
//		reduce(m1, m2, 0, REDUCE_MAX); // ������ �ִ밪 ���� [11,12,15]
//		reduce(m1, m2, 1, REDUCE_MIN); // ����� �ּڰ� ���� [2;6;7]
//		//��İ�
//		double alpha = 1.0, beta = 1.0; // �������� ���ϴ� �μ��� ���� ����
//		gemm(m1, m2, alpha, noArray(), beta, m2, GEMM_1_T); // [2x3]x[3x2] = [2x2], GEMM_n_T(������ ����x) n�� ��ġ�� ��
//		solve(m1, m2, m1, DECOMP_LU); //���������� Ǯ��
//		int i, j, k;
//		m1.at<int>(i, j) = k; //��� ���� ����
//		m1.at<Vec3i>(i, j)[2] = 2; // 2ä��
//		addWeighted(m1, alpha, m2, beta, 0, m1); //���� ������
//		int bins, range_max;
//		int histSize[] = { bins }; // ������׷� ��� ���� 
//		float range[] = { 0, (float)range_max }; // 0�� ä�� ȭ�Ұ� ����
//		int channels[] = { 0 }; // ä�� ��� - ����ä��
//		const float* ranges[] = { range }; //��� ä�� ȭ�� ���� ��) [0,256] �� �ּҰ�
//		calcHist(&m1, 1, channels, Mat(), m2, 1, histSize, ranges); // ���Ұ������
//		//      �̹���,         ����ũ, ����, ������, �������� bins ��, �� ������ ������׷� ����
//
//		//Vector ����
//		vector<Point> vc1; vector<int> vc2;
//		vc1.push_back(Point(10, 20));
//		int arr_int[] = { 10,20,30,40,50 }; //�迭 Vector ��ȯ
//		vector<int> v4(arr_int + 2, arr_int + sizeof(arr_int) / sizeof(int));
//		vc2.insert(vc2.begin() + 2, 100);  //3��° ��ġ�� 100 ���� [10,20,100,30,40,50]
//		vc1.erase(vc1.begin() + 3); //4��° ��ġ ���� [10,20,100,40,50]
//		vc1.reserve(10000000);    // �뷮
//		vc1.clear();  // �ʱ�ȭ
//		exp(vc1, vc2);
//		log(vc1, vc2);
//		exp(vc1, vc2);
//		log(vc1, vc2);
//		sqrt(vc1, vc2);
//		pow(vc1, 2, vc2);
//		magnitude(vc1, vc2, vc1);//���� > ũ��
//		phase(vc1, vc2, vc1); //���� > ����
//		cartToPolar(vc1, vc2, m1, m2);//����(vc1,vc2) > ũ��(m1), ����(m2)
//		polarToCart(m1, m2, vc1, vc2); //��� �Է� > ���� ��ȯ //ũ��� ������ �� ������ x,y��ǥ ���
//
//
//		//Range
//		Range r1(0, 1), r2(2, 3);
//		m2 = m1(r1, r2);
//		m2.setTo(50); // (m1�� r1-r2������ ������ 50���� ����)
//		m2.locateROI(size, pt8); //size�� pt�� ���� ����
//		m2.adjustROI(-1, 1, 2, -1); //(����, �Ʒ�, ����, ������) ���� ��ȭ
//
//		//�׸���
//		Mat image; Scalar color; int �β�; double start_angle, end_angle;
//		line(image, pt7, pt8, color, �β�, LINE_AA, 1);
//		rectangle(image, rect, color, �β�);  //�β� -1 : �� ä���
//		circle(image, rot_rect.center, 1, Scalar(0), 2);
//		putText(image, "TEXT", pt7, FONT_HERSHEY_SIMPLEX, �β�, color);
//		ellipse(image, pt7, Size(100, 60), angle, start_angle, end_angle, color, �β�);
//
//		//�̹���
//		Mat img0, img1;
//		threshold(img0, img1, 70, 255, THRESH_BINARY); // ���� ����ȭ
//	}
//
//	//����ó��
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
//		string filename = "../image/read_gray.jpg"; //�������� ��ġ
//		Mat gray2gray = imread(filename, IMREAD_GRAYSCALE); //�������� �ε�
//		Mat gray2color = imread(filename, IMREAD_COLOR);
//		CV_Assert(gray2gray.data&& gray2color.data);
//	}
//
//	//��Ÿ
//	{
//		//�ð�
//		double start_time = clock();
//
//		//��ȭ ��� ����
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
//	//int �迭 ��� (vector > Mat)
//	int bins;
//	int histSize[] = { bins }; // ������׷� ��� ����
//	vector<int> v1(histSize, histSize + sizeof(histSize) / sizeof(int));
//	cout << "histSize[]" << ((Mat)v1).reshape(1, 1) << endl;
//
//	//������ǥ�� �̿��ϸ�, ũ�⸦ ������ �� ���� �� �� �ִ�
//	//rects->�پ��� �簢�� ũ���
//	//	sortIdx(sizes, sort_idx, SORT_EVERY_COLUMN);
//	//->ũ�⺰�� ������ǥ ����
//	//	for (i++) : rects[sort_idx(i)];->ũ�⺰�� ���
//
//	//ȸ����ȯ���     
//	Mat m1, m2;
//	float theta = 20 * CV_PI / 180; //���� ����
//	Matx22f m(cos(theta), -sin(theta), sin(theta), cos(theta)); //ȸ�� ��ȯ ���
//	transform(m1, m2, m); // ȸ�� ��ȯ (rect_pt1 = [200,50; 400,50; 400,250; 200,250]
//
//	//�ݺ��� ��� ���� ���� (������ ���ٹ��)
//	Mat m3;
//	MatConstIterator_<uchar> it_m1 = m1.begin<uchar>(); //�ݺ��� ���� it_m1�� ������
//	MatIterator_<uchar> it_m2 = m2.begin<uchar>();
//	Mat_<Vec3f>::iterator it_m3 = m3.begin<Vec3f>(); //3ä���� m3
//	for (; it_m1 != m1.end<uchar>(); ++it_m1, ++it_m2, ++it_m3) {//��� ��ü ��ȸ (���Ҽ���ŭ) 
//		*it_m2 = *it_m1; //1��1 ����     //�ּڰ� ++
//		(*it_m3)[0] = *it_m1 * 0.5f; //3ä�ο� �� �ο�
//		(*it_m3)[1] = *it_m1 * 0.3f;
//		(*it_m3)[2] = *it_m1 * 0.2f;
//	}
//
//	Mat hist, hist_img; Point2i pt1, pt2;
//	//hist Ȱ��
//	normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);  //256���� ��⸦ ��Ÿ���� hist_img
//	rectangle(hist_img, pt1, pt2, Scalar(0), -1); //������ ���� ������ �׸���
//	flip(hist_img, hist_img, 0); //x �� ���� ���� ������
//
//}
//
////HSV to GBR �� �����
//Mat make_palatte(int rows) {
//	Mat hsv(rows, 1, CV_8UC3);
//	for (int i = 0; i < rows; i++) {
//
//		[HVS �÷�]
//		uchar hue = saturate_cast<uchar>((float)i / rows * 180); //���� ���
//		hsv.at<Vec3b>(i) = Vec3b(hue, 255, 255); //HVS �÷� ����
//	}
//	cvtColor(hsv, hsv, COLOR_HSV2BGR); // HVS -> BGR �÷�
//	return hsv;
//}