#include "camera.h"
#include "ui_camera.h"

Camera::Camera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Camera)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    /*信号和槽*/
    connect(timer, SIGNAL(timeout()), this, SLOT(readFrame()));  // 时间到，读取当前摄像头信息
}

Camera::~Camera()
{
    delete ui;
}

void Camera::readFrame()
{
    cap >> frame;
    image = Mat2QImage(frame);
    QImage scaleImage = ScaleImage2Label( image, ui->lb_display );   // 显示到label上
    ui->lb_display->setPixmap(QPixmap::fromImage(scaleImage));
    ui->lb_display->setAlignment(Qt::AlignCenter);
    ui->lb_display->show();
}

void Camera::camera_open()
{
    cap.open(0);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    timer->start(33);              // 开始计时，超时则发出timeout()信号
}

QImage Camera::Mat2QImage(cv::Mat& cvImg)
{
    QImage qImg;
    if(cvImg.channels()==3)                             //3 channels color image
    {

        cv::cvtColor(cvImg,cvImg,CV_BGR2RGB);
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols, cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }
    else if(cvImg.channels()==1)                    //grayscale image
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_Indexed8);
    }
    else
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }

    return qImg;
}

QImage Camera::ScaleImage2Label(QImage qImage, QLabel* qLabel)
{
    QImage qScaledImage;
    QSize qImageSize = qImage.size();
    QSize qLabelSize = qLabel->size();
    double dWidthRatio = 1.0*qImageSize.width() / qLabelSize.width();
    double dHeightRatio = 1.0*qImageSize.height() / qLabelSize.height();
    if (dWidthRatio>dHeightRatio)
    {
        qScaledImage = qImage.scaledToWidth(qLabelSize.width());
    }
    else
    {
        qScaledImage = qImage.scaledToHeight(qLabelSize.height());
    }
    return qScaledImage;
}
