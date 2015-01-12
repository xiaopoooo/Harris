#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class QGraphicsScene;
class QGraphicsPixmapItem;
class QGraphicsItemGroup;
class QSlider;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionGenerate_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *imageLayer;
    QGraphicsItemGroup *pointsLayer;
    QSlider *sliderWindowSize;
    QString imagePath;

};

#endif // MAINWINDOW_H
