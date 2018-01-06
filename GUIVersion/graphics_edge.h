#ifndef GRAPHICS_EDGE_H
#define GRAPHICS_EDGE_H
#include <QGraphicsLineItem>
#include "graphics_vertex.h"
class GVertex;
class GEdge:public QGraphicsLineItem{
public:
    GEdge(int x1, int y1, int x2, int y2, GVertex *v1, GVertex *v2):QGraphicsLineItem(x1, y1, x2, y2){
        setToolTip("Fuck You!!!!");
        num_edge_ = 1;
        vertex_1_ = v1;
        vertex_2_ = v2;
    }
    GVertex* vex1(){
        return vertex_1_;
    }
    GVertex* vex2(){
        return vertex_2_;
    }
    int AddRepeat(){
        num_edge_++;
    }
    void DesRepeat(){
        num_edge_--;
    }
    void ChangePos(GVertex* v, int x, int y){
            if(v == vertex_1_){
                setLine(x, y, line().x2(), line().y2());
            }
            else if(v == vertex_2_){
                setLine(line().x1(), line().y1(), x, y);
            }
        }
    int Repeat(){
        return num_edge_;
    }
    void SetCut(bool is){
        if(is_cut_ != is){
            is_cut_ = is;
            setLine(line().x1()+1, line().y1(), line().x2(), line().y2());
            setLine(line().x1()-1, line().y1(), line().x2(), line().y2());
        }
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
        QPen pen;
        if(!is_cut_)
            pen.setColor(QColor(0,0,0));
        else
            pen.setColor(QColor(255,0,0));
        painter->setPen(pen);
        painter->drawLine(QPointF(line().x1(),line().y1()), QPointF(line().x2(),line().y2()));
    }

private:
    int num_edge_;
    GVertex *vertex_1_, *vertex_2_;
    bool is_cut_;

};

#endif // GRAPHICS_EDGE_H
