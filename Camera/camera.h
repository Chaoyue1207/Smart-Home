#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include <QTimer>
#include <QImage>
#include <QLabel>
#include <opencv2/opencv.hpp>

namespace Ui {
class Camera;
}

class Camera : public QWidget
{
    Q_OBJECT

public:
    explicit Camera(QWidget *parent = 0);
    ~Camera();
    void camera_open();
    QImage Mat2QImage(cv::Mat& cvImg);
    QImage ScaleImage2Label(QImage qImage, QLabel* qLabel);

private slots:
    void readFrame();

private:
    Ui::Camera *ui;
    QTimer *timer;
    QImage image;
    cv::VideoCapture cap;
    cv::Mat frame;
};

#endif // CAMERA_H
