#include "harriscore.h"
#include <ctime>
#include <QtCore>
#include <opencv2/opencv.hpp>
#include "harris.h"

class HarrisCorePrivate
{
    friend class HarrisCore;

    HarrisCorePrivate(int wSize=3, double sig=0.5)
        :windowSize(wSize),sigma(sig)
    {}

    HarrisCorePrivate(QString filePath, int wSize=3, double sig=0.5)
        :HarrisCorePrivate(wSize,sig)
    {
        image = cv::imread(std::string(filePath.toLocal8Bit()));
        cv::cvtColor (image,image,CV_BGR2GRAY);
    }

    cv::Mat image;
    cv::Mat image_gx;
    cv::Mat image_gy;

    int windowSize;
    double sigma;
    QList<QPoint> points;
};

HarrisCore::HarrisCore()
    :p_harris(new HarrisCorePrivate())
{    
}

HarrisCore::HarrisCore(QString filePath)
    :p_harris(new HarrisCorePrivate(filePath))
{
}

bool HarrisCore::isValid() const
{
    if (p_harris==NULL)
        return false;
    return !(p_harris->image.empty());
}

int HarrisCore::windowsSize() const
{
    return p_harris->windowSize;
}

double HarrisCore::sigma() const
{
    return p_harris->sigma;
}

void HarrisCore::setWindowSize(int size)
{
    p_harris->windowSize = size;
}

void HarrisCore::setSigma(double sigma)
{
    p_harris->sigma = sigma;
}

bool HarrisCore::generatePoints(QList<QPointF> &points)
{
    if (isValid()==false)
        return false;

    points.clear();

    std::clock_t t1 = std::clock();
    Harris harris;
    harris.neighbourhood = p_harris->windowSize;
    harris.detect(p_harris->image);
    harris.getCorners(points,0.01);

    std::clock_t t2 = std::clock();
    qDebug()<<"cost time: "<<(t2-t1)/double(CLOCKS_PER_SEC)<<"s";

    return true;
}

