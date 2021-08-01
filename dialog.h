#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QLabel>
#include <QList>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPushButton>
#include <QSlider>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

    QTextEdit* myText;
    //QLabel* myLabel;
    QList<QString> list;
    QTimer* timer;
    QMediaPlayer* player;  //创建一个音乐播放器
    QMediaPlaylist* playlist;
    QPushButton* pauseBtn;
    QPushButton* startBtn;
    QPushButton* stopBtn;
    QPushButton* volumeBtn;
    QSlider* volumeSlide;


    void creatControls();
    void playMusic();
    void readText();
    void showText();

public slots:
    void on_pauseBtn_clicked();
    void on_startBtn_clicked();
    void on_stopBtn_clicked();
    void on_volumeBtn_clicked();
    void on_volumeSlide_valueChanged(int value);
};

#endif // DIALOG_H
