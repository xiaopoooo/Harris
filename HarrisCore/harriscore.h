#ifndef HARRISCORE_H
#define HARRISCORE_H

#include "harriscore_global.h"
class HarrisCorePrivate;
class QPointF;

class HARRISCORESHARED_EXPORT HarrisCore
{

public:

    //Constructor
    HarrisCore();
    HarrisCore(QString filePath);


    //Properties
    bool isValid()const;
    int windowsSize() const;
    double sigma() const;

    void setWindowSize(int size);
    void setSigma(double sigma);

    //Process
    bool generatePoints(QList<QPointF> &points);

private:
    HarrisCorePrivate *p_harris;
};

#endif // HARRISCORE_H
