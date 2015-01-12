#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif // QT_VERSION >= 0x050000

#include "harriscore.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this)),
    imageLayer(new QGraphicsPixmapItem),
    sliderWindowSize(new QSlider(Qt::Horizontal,this)),
    pointsLayer(NULL)
{
    ui->setupUi(this);

    sliderWindowSize->setMinimum(1);
    sliderWindowSize->setMaximum(10);
    sliderWindowSize->setValue(3);
    QWidgetAction *actionWindowSize = new QWidgetAction(this);
    actionWindowSize->setDefaultWidget(sliderWindowSize);
    ui->toolBar->addActions(QList<QAction*>()<<actionWindowSize);

    connect(sliderWindowSize,SIGNAL(valueChanged(int)),SLOT(on_actionGenerate_triggered()));


    ui->actionOpen->setShortcut(QKeySequence::Open);
    ui->graphicsView->setScene(scene);
    scene->addItem(imageLayer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString path = QFileDialog::getOpenFileName(this,tr("Open image"),QString::null,"*.bmp;*.jpg;*.png;*.tif");
    if (path.isEmpty())
        return;

    if (!imageLayer->pixmap().isNull())
    {
        if (QMessageBox::question(this,tr("Warning"),tr("Open a new image would close the old one! Continue?"))!=QMessageBox::Yes)
            return;
    }    

    QPixmap img(path);
    if (img.isNull())
    {
        QMessageBox::critical(this,tr("Error"),tr("Open image failed!"));
        return;
    }

    imagePath = path;
    imageLayer->setPixmap(img);

    if (pointsLayer)
        scene->removeItem(pointsLayer);
    pointsLayer = NULL;
    ui->graphicsView->update();
}

void MainWindow::on_actionGenerate_triggered()
{
    if (imagePath.isEmpty())
        return;

    HarrisCore harris(imagePath);
    if (harris.isValid()==false)
    {
        QMessageBox::critical(this,tr("Error"),tr("Sopmething wrong!"));
        return;
    }

    harris.setWindowSize(sliderWindowSize->value());
    QList<QPointF> points;
    if (harris.generatePoints(points)==false)
    {
        QMessageBox::critical(this,tr("Error"),tr("Generating failed!"));
        return;
    }

    qDebug()<<points.count();
    if (pointsLayer) scene->removeItem(pointsLayer);
    pointsLayer = new QGraphicsItemGroup;
    foreach (QPointF pt, points) {
        QGraphicsEllipseItem *item = new QGraphicsEllipseItem(pt.x(),pt.y(),3,3);
        item->setPen(QPen(Qt::red));
        pointsLayer->addToGroup(item);
    }
    scene->addItem(pointsLayer);
}
