#include "ObjectDetection.h"
#include "math.h"
#include <algorithm>

/**
* Helper function to find a cosine of angle between vectors
* from pt0->pt1 and pt0->pt2
*/
static double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0)
{
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

/**
* Helper function to display text in the center of a contour
*/
void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour)
{
	int fontface = cv::FONT_HERSHEY_SIMPLEX;
	double scale = 0.4;
	int thickness = 1;
	int baseline = 0;

	cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
	cv::Rect r = cv::boundingRect(contour);

	cv::Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
	cv::rectangle(im, pt + cv::Point(0, baseline), pt + cv::Point(text.width, -text.height), CV_RGB(255, 255, 255), CV_FILLED);
	cv::putText(im, label, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
}

void objectDetectTest()
{
	cv::Mat src;
	cv::Mat gray;
	cv::Mat bw;
	cv::Mat dst;
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Point> approx;

	VideoCapture capture(0);
	int q;

	while (cvWaitKey(30) != 'q')
	{
		capture >> src;
		if (true)
		{
			// Convert to grayscale
			cv::cvtColor(src, gray, CV_BGR2GRAY);

			// Use Canny instead of threshold to catch squares with gradient shading
			blur(gray, bw, Size(3, 3));
			cv::Canny(gray, bw, 80, 240, 3);
			cv::imshow("bw", bw);

			// Find contours
			cv::findContours(bw.clone(), contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

			src.copyTo(dst);

			for (int i = 0; i < contours.size() - 1; i++)
			{
				// Approximate contour with accuracy proportional
				// to the contour perimeter
				cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);

				//skip small objects
				if (std::fabs(cv::contourArea(contours[i])) < 2500)
					continue;

				if (approx.size() == 7)
				{

					std::vector<Point> contour = contours[i];
					// Number of vertices of polygonal curve
					int vtc = approx.size();

					//get the middel point of the bounding rectangle
					//cv::Rect r = cv::boundingRect(contours[i]);
					//cv::Point middelPoint(r.x + ((r.width) / 2), r.y + ((r.height) / 2));

					int xmid = 0;
					int ymid = 0;
					for (int i = 0; i < approx.size() ; i++)
					{
						xmid += approx[i].x;
						ymid += approx[i].y;
					}
					cv::Point middelPoint(xmid / approx.size(), ymid / approx.size());

					std::vector<double> distancesToCenter;
					std::vector<double> sortedDistances;

					for (int x = 0; x < approx.size(); x++) {
						distancesToCenter.push_back(sqrt((double)((middelPoint.x - approx[x].x)*(middelPoint.x - approx[x].x) + (middelPoint.y - approx[x].y)*(middelPoint.y - approx[x].y))));
						sortedDistances.push_back(sqrt((double)((middelPoint.x - approx[x].x)*(middelPoint.x - approx[x].x) + (middelPoint.y - approx[x].y)*(middelPoint.y - approx[x].y))));
					}

					Point pointOfArrow;
					std::sort(sortedDistances.begin(), sortedDistances.end());

					for (int y = 0; y < distancesToCenter.size(); y++) {
						if (distancesToCenter[y] == sortedDistances[6]) {
							pointOfArrow = approx[y];
							break;
						}
					}
					
					//cv::line(dst, pointOfArrow, middelPoint, COLORMAP_BONE, 4);
					
					/*
					for (int x = 0; x < approx.size() - 1; x++) {

					cv::line(dst, approx[x], approx[x + 1], COLORMAP_BONE, 20);
					}
					*/




					string arrowstring;
					double arrowAngle = 0;
					arrowAngle = acos((double)((pointOfArrow.x - middelPoint.x) /sortedDistances[6]));

					if (arrowAngle < 0.25*CV_PI && arrowAngle > -0.25*CV_PI)
						arrowstring = "left";
					else if (arrowAngle < 1.25*CV_PI && arrowAngle > 0.75*CV_PI)
						arrowstring = "right";
					else if (pointOfArrow.y < middelPoint.y)
						arrowstring = "up";
					else if (pointOfArrow.y > middelPoint.y)
						arrowstring = "down";

					if (!isContourConvex(approx)) {
						setLabel(dst, arrowstring, contours[i]);
					}

				}

				// Skip non-convex objects 
				if (!isContourConvex(approx))
					continue;

				if (approx.size() == 3)
				{
					setLabel(dst, "TRIANGLE", contours[i]);    // Triangles
				}
				else if (approx.size() >= 4 && approx.size() <= 6)
				{
					// Number of vertices of polygonal curve
					int vtc = approx.size();

					// Get the cosines of all corners
					std::vector<double> cos;
					for (int j = 2; j < vtc + 1; j++)
						cos.push_back(angle(approx[j%vtc], approx[j - 2], approx[j - 1]));

					// Sort ascending the cosine values
					std::sort(cos.begin(), cos.end());

					// Get the lowest and the highest cosine
					double mincos = cos.front();
					double maxcos = cos.back();

					// Use the degrees obtained above and the number of vertices
					// to determine the shape of the contour
					if (vtc == 4)
						setLabel(dst, "RECTANGLE", contours[i]);
					else if (vtc == 5)
						setLabel(dst, "PENTAGON", contours[i]);
					else if (vtc == 6)
						setLabel(dst, "HEXAGON", contours[i]);
				}

				else {

					// Detect and label circles
					double area = cv::contourArea(contours[i]);
					cv::Rect r = cv::boundingRect(contours[i]);
					int radius = r.width / 2;

					if (std::abs(1 - ((double)r.width / r.height)) <= 0.2 &&
						std::abs(1 - (area / (CV_PI * (radius*radius)))) <= 0.2)
						setLabel(dst, "CIRCLE", contours[i]);
				}
			}
			
			cv::imshow("src", src);
			cv::imshow("dst", dst);

		}
		else
		{
			break;
		}
	}
}