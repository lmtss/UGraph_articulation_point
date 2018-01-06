#include "mainwindow.h"

#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QRect>
#include <iostream>


MainWindow::MainWindow(QWidget *parent, int width, int height, QString url)
    : QMainWindow(parent)
{
    setWindowTitle(tr("AKuYa"));
    setWindowFlags(windowFlags() &~ Qt::WindowMinMaxButtonsHint);
    window_width_ = width;
    window_height_ = height;
    setFixedSize(width, height);

    label_vertex_info_name_.setParent(this);
    label_vertex_info_num_edge_.setParent(this);
    label_vertex_num_adj_.setParent(this);

    edit_create_vertex_.setParent(this);
    edit_create_edge_1_.setParent(this);
    edit_create_edge_2_.setParent(this);

    button_create_edge_.setParent(this);
    button_create_vertex_.setParent(this);

    label_vertex_info_name_.resize(window_width_*0.09, window_height_*0.05);
    label_vertex_info_name_.move(window_width_*0.035, window_height_*0.449);
    label_vertex_info_name_.setText(tr("顶点名字"));
    label_vertex_info_name_.adjustSize();

    button_create_vertex_.resize(window_width_*0.026, window_height_*0.05);
    button_create_vertex_.move(window_width_*0.035, window_height_*0.19);
    button_create_vertex_.setText(tr("新建顶点"));
    button_create_vertex_.adjustSize();

    button_create_edge_.resize(window_width_*0.026, window_height_*0.05);
    button_create_edge_.move(window_width_*0.035, window_height_*0.252);
    button_create_edge_.setText(tr("新建边"));
    button_create_edge_.adjustSize();

    edit_create_vertex_.resize(window_width_*0.16, window_height_*0.05);
    edit_create_vertex_.move(window_width_*0.137, window_height_*0.19);

    edit_create_edge_1_.resize(window_width_*0.075, window_height_*0.05);
    edit_create_edge_1_.move(window_width_*0.137, window_height_*0.252);

    edit_create_edge_2_.resize(window_width_*0.075, window_height_*0.05);
    edit_create_edge_2_.move(window_width_*0.222, window_height_*0.252);


}

MainWindow::~MainWindow()
{

}
void MainWindow::Draw(){

}
void MainWindow::ReadFile(){

}
void MainWindow::ClickCreateVertex(){
    QString text = edit_create_vertex_.text();
    if(text.length() == 0){
        graph.InsertVertex("test");
    }else{
        try{
            graph.InsertVertex(text.toStdString());
        }catch(string error){
            std::cout << error;
        }
    }
}

