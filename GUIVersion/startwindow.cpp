#include "startwindow.h"

#include <QString>
#include <QObject>
#include <QFileDialog>
StartWindow::StartWindow(QWidget *parent, int width, int height)
    : QDialog(parent)
{

    setWindowTitle(tr("Welcome to start window"));
    setWindowFlags(windowFlags() &~ Qt::WindowMinMaxButtonsHint);
    window_width_ = width*0.5;
    window_height_ = height*0.5;
    //resize(window_width_, window_height_);
    setFixedSize(window_width_, window_height_);


    label_ = new QLabel(this);
    QString s = QString("<html>"
                        "<body>"
                        ""
                        "<span style='color:rgba(0,0,0,0.6);font-size:40px;'>Hello</span>"
                        ""
                        "</body>"
                        "</html>");
    label_->setText(s);
    label_->move(0,0);
    label_->adjustSize();



    read_file_label_ = new QLabel(this);
    read_file_label_->move(window_width_/4,window_height_*0.25);
    read_file_label_->setText(tr("<span style='color:rgba(0,0,0,0.6)'>请从电脑中选择一个.AKuYa文件打开</span>"));
    read_file_label_->adjustSize();//<font color='rgba(0,0,0,0.2)' face='微软雅黑' size='3'>请从电脑中选择一个.AKuYa文件打开</font>

    read_file_edit_ = new QLineEdit(this);
    read_file_edit_->move(window_width_/4, window_height_*0.31);
    read_file_edit_->resize(window_width_/3,window_height_/15);

    read_file_button_ = new QPushButton(this);
    read_file_button_->move(window_width_/4 + window_width_/3 + window_width_*0.05, window_height_*0.31);
    read_file_button_->resize(window_width_*0.13, window_height_/15);

    connect(read_file_button_, &QPushButton::clicked, this, &ClickScanFile);

    or_label_ = new QLabel(this);
    or_label_->move(window_width_/4,window_height_*0.52);
    or_label_->setText(tr("<span style='color:rgba(0,0,0,0.6)'>或者</span>"));
    or_label_->adjustSize();

    new_file_label_ = new QLabel(this);
    new_file_label_->move(window_width_/4,window_height_*0.56);
    new_file_label_->setText(tr("<span style='color:rgba(0,0,0,0.6)'>创建一个新的AKuYa文件</span>"));
    new_file_label_->adjustSize();

    new_file_edit_ = new QLineEdit(this);
    new_file_edit_->move(window_width_/4, window_height_*0.62);
    new_file_edit_->resize(window_width_/3,window_height_/15);

    new_file_button_ = new QPushButton(this);
    new_file_button_->move(window_width_/4 + window_width_/3 + window_width_*0.05, window_height_*0.62);
    new_file_button_->resize(window_width_*0.13, window_height_/15);

    connect(new_file_button_, &QPushButton::clicked, this, &ClickNewFile);
}
void StartWindow::ClickScanFile(){
    QString path = QFileDialog::getOpenFileName(this, tr("fuck you"), ".", tr("Image Files(*.jpg *.png)"));
    if(path.length() != 0){
        read_file_edit_->setText(path);
    }
}
void StartWindow::ClickNewFile(){

    MainWindow *a = new MainWindow(0, window_width_*1.6, window_height_*2*0.8, "new");
    a->show();close();
}

StartWindow::~StartWindow()
{
    delete new_file_label_;
    delete read_file_label_;
    delete label_;
    delete or_label_;
    delete new_file_edit_;
    delete read_file_label_;
    delete new_file_button_;
    delete read_file_button_;
}
