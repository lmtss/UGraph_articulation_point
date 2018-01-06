#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "DfsTarjan.h"
#include "graphics_view.h"
#include "graphics_vertex.h"
#include <QMainWindow>
#include <QString>
#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QRect>
#include <QWidget>
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>

//#include <iostream>
#include <fstream>
#include <string>
#include <QTextStream>
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    int window_width_, window_height_;
    QPushButton button_create_vertex_, button_create_edge_, button_delete_edge_, button_delete_vertex_, button_save_;
    QLabel label_vertex_info_name_, label_vertex_num_adj_, label_vertex_info_num_edge_;
    QLineEdit edit_create_vertex_, edit_create_edge_1_, edit_create_edge_2_, edit_delete_vertex_, edit_delete_edge_1_, edit_delete_edge_2_;
    UDGraph graph_;
    QGraphicsScene draw_scene_;
    QVector<GVertex*> vertex_list_;
    //QGraphicsView draw_view_;
    GView draw_view_;
    int cur_vertex_x_, cur_vertex_y_;
    int vertex_radius_;

    void Draw(int n){
        //for
        qDebug() << "draw!!!!!!!!!!" << n;
    }
    void ShowVertexInfo(VertexPosition pos){
        label_vertex_info_name_.setText(graph_[pos].c_str());
    }
    int InsertVertex(QString text){
        int ret = graph_.InsertVertex(text.toStdString());
        if(ret == 0){
            return 0;
        }

        else{
            GVertex *v = new GVertex(vertex_radius_*2,graph_.num_vex()-1);
            vertex_list_.push_back(v);

            draw_scene_.addItem(v);
            v->SetName(text);
            connect(v, &GVertex::fuck,this, &ShowVertexInfo);

            return 1;
        }
    }
    int InsertEdge(QString name1, QString name2){
        //Edge* ret = graph_.InsertEdge(name1.toStdString(),name2.toStdString());
        std::string s1 = name1.toStdString(), s2 = name2.toStdString();

        int n = graph_.IsExistEdge(s1,s2);qDebug() << "n1";
        if(n == 0){qDebug() << "n2";
            graph_.InsertEdge(s1,s2);
            /*GVertex *gvertex_1 = graph_.vertex_list_[graph_.map_name_position_[s1]].draw_item;
            GVertex *gvertex_2 = graph_.vertex_list_[graph_.map_name_position_[s2]].draw_item;*/
            GVertex *gvertex_1 = vertex_list_[graph_[s1]];
            GVertex *gvertex_2 = vertex_list_[graph_[s2]];
            if(n == 0){qDebug() << "n4";
                GEdge *e = new GEdge(gvertex_1->pos().x(),gvertex_1->pos().y(),gvertex_2->pos().x(),gvertex_2->pos().y(),gvertex_1, gvertex_2);
                draw_scene_.addItem(e);
                gvertex_1->AddEdge(e);
                gvertex_2->AddEdge(e);
                qDebug() << "n6";
                return 1;
            }else{qDebug() << "n5";
                /*GEdge *e = gvertex_1->GetEdge(gvertex_2);
                e->AddRepeat();*/
                return 2;
            }
        }else{qDebug() << "n3";
            return 0;
        }
    }

    int DeleteEdge(QString t1, QString t2){
        std::string name_1 = t1.toStdString(), name_2 = t2.toStdString();

        if(graph_.IsExistEdge(name_1, name_2) > 0){qDebug() << "d1";
            VertexPosition p1 = graph_[name_1], p2 = graph_[name_2];
            GVertex *gvertex_1 = vertex_list_[p1], *gvertex_2 = vertex_list_[p2];

            GEdge *e = gvertex_1->GetEdge(gvertex_2);
            int repeat = e->Repeat();
            if(repeat == 1){qDebug() << "d3";
                gvertex_1->RemoveEdge(e);
                gvertex_2->RemoveEdge(e);
                draw_scene_.removeItem(e);
                delete e;

            }else{qDebug() << "d4";
                e->DesRepeat();
            }//qDebug() << e->Repeat() <<  "e repeat";

            graph_.DeleteEdge(name_1, name_2, 1);
            return 1;

        }else{qDebug() << "d2";
            return 0;
        }

    }
    int DeleteVertex(QString text){
        std::string name = text.toStdString();

        if(graph_.is_exist_vertex(name)){

            VertexPosition pos = graph_[name];
            GVertex *gvertex = vertex_list_[pos];

            gvertex->Destroy(&draw_scene_);
            draw_scene_.removeItem(gvertex);

            graph_.DeleteVertex(pos);


            for(int i = 0; i < vertex_list_.size(); i++){
                if(vertex_list_[i] == gvertex){
                    vertex_list_.erase(vertex_list_.begin()+i);
                }
            }
            if(gvertex != NULL)
            delete gvertex;

            qDebug() << "DeleteVertex:  " << text << " exist";
            return 1;


        }else{
            qDebug() << "DeleteVertex:  " << text << " is not exist";
            return 0;
        }

    }
    void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
    {
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos!=pos2)
    {
    v.push_back(s.substr(pos1, pos2-pos1));
    pos1=pos2+c.size();
    pos2=s.find(c,pos1);
    }
    if(pos1 != s.length())
    v.push_back(s.substr(pos1));
    }


public:
    MainWindow(QWidget *parent, int width, int height, QString url)
        : QMainWindow(parent)
    {

        int button_width = window_width_*0.026, button_height = window_height_*0.05;

        {
            //窗体
            setWindowTitle(tr("AKuYa"));
            setWindowFlags(windowFlags() &~ Qt::WindowMinMaxButtonsHint);
            window_width_ = width;
            window_height_ = height;
            setFixedSize(width, height);
        }

        {
            //顶点信息
            label_vertex_info_name_.setParent(this);
            //label_vertex_info_num_edge_.setParent(this);
            //label_vertex_num_adj_.setParent(this);

            label_vertex_info_name_.resize(window_width_*0.09, window_height_*0.05);
            label_vertex_info_name_.move(window_width_*0.035, window_height_*0.449);
            label_vertex_info_name_.setText(tr("顶点名字"));
            label_vertex_info_name_.adjustSize();

            label_vertex_info_name_.setText("<ul style='list-style-type:none'>"
                                            "<li>233</li>"
                                            "<li>233</li>"
                                            "</ul>");
            label_vertex_info_name_.adjustSize();
        }

        {

            edit_create_vertex_.setParent(this);
            edit_create_edge_1_.setParent(this);
            edit_create_edge_2_.setParent(this);
        }

        {
            button_create_edge_.setParent(this);
            button_create_vertex_.setParent(this);
        }

        {

        }

        {
            button_create_vertex_.resize(window_width_*0.026, window_height_*0.05);
            button_create_vertex_.move(window_width_*0.035, window_height_*0.19);
            button_create_vertex_.setText(tr("新建顶点"));
            button_create_vertex_.adjustSize();

            connect(&button_create_vertex_, &QPushButton::clicked, this, &ClickCreateVertex);
        }


        {
            button_create_edge_.resize(window_width_*0.026, window_height_*0.05);
            button_create_edge_.move(window_width_*0.035, window_height_*0.252);
            button_create_edge_.setText(tr("新建边"));
            button_create_edge_.adjustSize();

            connect(&button_create_edge_, &QPushButton::clicked, this, &ClickCreateEdge);
        }


        {
            edit_create_vertex_.resize(window_width_*0.16, window_height_*0.05);
            edit_create_vertex_.move(window_width_*0.137, window_height_*0.19);

            edit_create_edge_1_.resize(window_width_*0.075, window_height_*0.05);
            edit_create_edge_1_.move(window_width_*0.137, window_height_*0.252);

            edit_create_edge_2_.resize(window_width_*0.075, window_height_*0.05);
            edit_create_edge_2_.move(window_width_*0.222, window_height_*0.252);

        }

        {
            button_delete_edge_.setParent(this);
            button_delete_vertex_.setParent(this);

            button_delete_edge_.setText(tr("删除边"));
            button_delete_vertex_.setText(tr("删除顶点"));


            button_delete_edge_.resize(button_width, button_height);
            button_delete_edge_.move(window_width_*0.035, window_height_*0.383);

            button_delete_vertex_.resize(button_width, button_height);
            button_delete_vertex_.move(window_width_*0.035, window_height_*0.318);

            button_delete_edge_.adjustSize();
            button_delete_vertex_.adjustSize();

            connect(&button_delete_edge_, &QPushButton::clicked, this, &ClickDeleteEdge);
            connect(&button_delete_vertex_, &QPushButton::clicked, this, &ClickDeleteVertex);

        }

        {
            edit_delete_vertex_.setParent(this);
            edit_delete_vertex_.resize(window_width_*0.16, window_height_*0.05);
            edit_delete_vertex_.move(window_width_*0.137, window_height_*0.318);

            edit_delete_edge_1_.setParent(this);
            edit_delete_edge_1_.resize(window_width_*0.075, window_height_*0.05);
            edit_delete_edge_1_.move(window_width_*0.137, window_height_*0.383);

            edit_delete_edge_2_.setParent(this);
            edit_delete_edge_2_.resize(window_width_*0.075, window_height_*0.05);
            edit_delete_edge_2_.move(window_width_*0.222, window_height_*0.383);

        }


        {
            int t_w = window_width_*0.652;
            int t_h = window_height_*0.81;
            draw_view_.setParent(this);
            draw_view_.resize(window_width_*0.652, window_height_*0.81);
            draw_view_.move(window_width_*0.326, window_height_*0.158);
            draw_view_.setScene(&draw_scene_);
            draw_view_.show();

            draw_scene_.setSceneRect(-t_w/2,-t_h/2,t_w,t_h);
            draw_view_.setSceneRect(-t_w/2-5,-t_h/2-5,t_w+10,t_h+10);

            vertex_radius_ = 20;
            cur_vertex_x_ = 6;
            cur_vertex_y_ = 6;
        }

        {
            button_save_.setParent(this);
            button_save_.resize(window_width_*0.026, window_height_*0.05);
            button_save_.move(0,0);
            button_save_.setText(tr("Save as TXT"));
            button_save_.adjustSize();

            connect(&button_save_, &QPushButton::clicked, this, &ClickSave);
        }

        if(url != "new")
            ReadFile(url);



    }
    ~MainWindow(){}
    void ReadFile(QString file_name){
        ifstream file;
        file.open(file_name.toStdString());

        int n;
        std::string s1, s2;
        file >> n;
        for(int i = 0; i < n; i++){
            file >> s1;
            //graph_.InsertVertex(s1);

            InsertVertex(s1.c_str());
        }
        file >> n;
        for(int i = 0; i < n; i++){
            file >> s1 >> s2;
            //graph_.InsertEdge(s1,s2);
            InsertEdge(s1.c_str(),s2.c_str());
        }
        Tarjan();
    }
    void SaveAsFile(QString file_name){
        graph_.SaveAsFile(file_name.toStdString());
    }
    void ClickSave(){
        SaveAsFile("mdzz.txt");
    }



    void ClickCreateVertex(){
        QString text = edit_create_vertex_.text();
        //int ret = -1;
        if(text.length() == 0){

        }else{
            if(InsertVertex(text)){
                Tarjan();
            }

        }
    }
    void ClickCreateEdge(){
        QString t1 = edit_create_edge_1_.text(), t2 = edit_create_edge_2_.text();
        if(t1.length() == 0 || t2.length() == 0){

        }else{
            if(InsertEdge(t1,t2)){
                Tarjan();
            }
        }
    }
    void ClickDeleteVertex(){
        QString text = edit_delete_vertex_.text();
        if(text.length() == 0){

        }else{
            if(DeleteVertex(text)){
                Tarjan();
            }
        }

    }
    void ClickDeleteEdge(){
        QString t1 = edit_delete_edge_1_.text(), t2 = edit_delete_edge_2_.text();
        if(t1.length() == 0 || t2.length() == 0){

        }else{
            if(DeleteEdge(t1,t2)){
                Tarjan();
            }

        }
    }

    void Tarjan(){
        DfsTarjan dfs(graph_);
        for(int i = 0; i < graph_.num_vex(); i++){
            vertex_list_[i]->SetCut(false);
            vertex_list_[i]->SetEdgeCut(false);
        }
        dfs.Make();
        std::string cv = dfs.CutVertex();
        std::string ce = dfs.CutEdge();
        qDebug() << "com";
        std::vector<std::string> v1, v2;
        SplitString(cv, v1, ",");
        SplitString(ce, v2, ",");
        qDebug() << cv.c_str() << "FFFFFFFFFFFFFF";
        qDebug() << ce.c_str() << "FFFFFFFFFFFFFF";
        for(int i = 0; i < v1.size(); i++){
            vertex_list_[stoi(v1[i])]->SetCut(true);
            qDebug() << stoi(v1[i]);
        }

        for(int i = 0; i < v2.size(); i+=2){
            GEdge *e = vertex_list_[stoi(v2[i])]->GetEdge(vertex_list_[stoi(v2[i+1])]);
            e->SetCut(true);
        }

    }
};

#endif // MAINWINDOW_H
