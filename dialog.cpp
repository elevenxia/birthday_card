#include "dialog.h"
#include <QPixmap>
//#include <QMovie>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QTextCodec>
#include <QByteArray>
#include <QColor>
#include <QFont>
#include <QIcon>

// 若MSVC 编译版本错误，修改 msvc-version.conf 文件
// 解决MSVC编译时，界面汉字乱码的问题
#if _MSC_VER >= 1600     //MSVC2015>1899,    MSVC_VER= 14.0
#pragma execution_character_set("utf-8")
#endif

static int num = 0;


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
//    this->setWindowFlags(Qt::FramelessWindowHint); // 去除边框
//    this->setAttribute(Qt::WA_TranslucentBackground); // 透明设置
    playMusic();

    this->setFixedSize(474,640);
    this->setWindowIcon(QPixmap(":/resource/resource/background5.jpg"));
    this->setWindowTitle("toDQ");

//    player = new QMediaPlayer(this);//QMediaplayer用于解析音频文件和视频文件
//    player->setMedia(QUrl("qrc:/resource/resource/Happybirthday.mp3"));
//    player->setVolume(10);  //音量
//    player->play();
    this->setStyleSheet("background-color: rgba(190,190,255,150)");

    creatControls();

    myText = new QTextEdit(this);
    //设置背景图片，固定，上下左右居中
    myText->setStyleSheet("background-image:url(:/resource/resource/background4_65.png);"
                         "background-attachment:fixed;"
                         "background-repeat:none;"
                         "background-position:center;"
                         "background-color: rgb(230, 230, 250);"
                         "selection-color: rgb(255, 250, 205)");

    myText->setFixedSize(474,595);

//    myText->setTextColor(QColor(255, 0, 0, 127));
    myText->setTextColor(QColor(72,61,139,225));
//    QFont font = QFont("Microsoft YaHei",16,2);
    QFont font = QFont("STXinwei",16,2);
    myText->setFont(font);

    readText();
    timer = new QTimer(this);
    timer->start(2800);
    connect(timer, &QTimer::timeout, this, &Dialog::showText);
}

Dialog::~Dialog()
{

}

void Dialog::playMusic() {
    playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl("qrc:/resource/resource/Happybirthday.mp3"));

    playlist->setCurrentIndex(1);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);  // Loop mode

    player = new QMediaPlayer;
    player->setPlaylist(playlist);

    if (player->state() != QMediaPlayer::PlayingState)
        playlist->setCurrentIndex(0);
    player->setVolume(10);  //音量
    player->play();

}

void Dialog::creatControls() {
    pauseBtn = new QPushButton(this);
    pauseBtn->setGeometry(20, 610, 20, 20);
    pauseBtn->setToolTip("暂停");
    pauseBtn->setFixedSize(20, 20);
    QPixmap pixmap;
    pixmap.load(":/resource/resource/pause.bmp");
    pauseBtn->setIcon(pixmap);

    startBtn = new QPushButton(this);
    startBtn->setGeometry(60, 610, 20, 20);
    startBtn->setToolTip("播放");
    startBtn->setFixedSize(20, 20);
    pixmap.load(":/resource/resource/start.bmp");
    startBtn->setIcon(pixmap);

    stopBtn = new QPushButton(this);
    stopBtn->setGeometry(100, 610, 20, 20);
    stopBtn->setToolTip("结束");
    stopBtn->setFixedSize(20, 20);
    pixmap.load(":/resource/resource/stop.bmp");
    stopBtn->setIcon(pixmap);

    volumeBtn = new QPushButton(this);
    volumeBtn->setGeometry(210, 610, 20, 20);
    volumeBtn->setToolTip("静音");
    volumeBtn->setObjectName("volumeBtn");
    volumeBtn->setFixedSize(20, 20);
    pixmap.load(":/resource/resource/volume.bmp");
    volumeBtn->setIcon(pixmap);

    volumeSlide = new QSlider(Qt::Horizontal, this);
    volumeSlide->setGeometry(260, 610, 200, 20);
    volumeSlide->setRange(0, 100);
    volumeSlide->setValue(20);

    connect(pauseBtn, &QPushButton::clicked, this, &Dialog::on_pauseBtn_clicked);
    connect(startBtn, &QPushButton::clicked, this, &Dialog::on_startBtn_clicked);
    connect(stopBtn, &QPushButton::clicked, this, &Dialog::on_stopBtn_clicked);
    connect(volumeBtn, &QPushButton::clicked, this, &Dialog::on_volumeBtn_clicked);
    connect(volumeSlide, &QSlider::valueChanged, this, &Dialog::on_volumeSlide_valueChanged);
}

void Dialog::readText() {
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");

    QString textFilename = ":/resource/resource/toDQ.txt";
    QFile file(textFilename);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            QString str = codec->toUnicode(line);
            list << str;
        }
    }
}

void Dialog::showText() {
            myText->append(list.at(num++));
            //qDebug() << num;
            if (num == list.size()) timer->stop();
}

void Dialog::on_pauseBtn_clicked() {
    player->pause();
}

void Dialog::on_startBtn_clicked() {
    player->play();
}

void Dialog::on_stopBtn_clicked() {
    player->stop();
}

void Dialog::on_volumeBtn_clicked() {
    bool mute = player->isMuted();
    player->setMuted(!mute);
    if (mute) {
        volumeBtn->setIcon(QPixmap(":/resource/resource/volume.bmp"));
        int value = volumeSlide->value();
        player->setVolume(value);
    }
    else {
        volumeBtn->setIcon(QPixmap(":/resource/resource/mute.bmp"));
        player->setVolume(0);
    }

}

void Dialog::on_volumeSlide_valueChanged(int value) {
    player->setVolume(value);
    bool mute = player->isMuted();
    if (mute) {
        volumeBtn->setIcon(QPixmap(":/resource/resource/volume.bmp"));
    }
}
