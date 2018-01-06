#ifndef GRAPHICS_VERTEX_H
#define GRAPHICS_VERTEX_H
#include <QGraphicsEllipseItem>
#include <QtDebug>
#include <QDrag>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QMimeData>
#include <QWidget>
#include <QPointF>
#include <QObject>
#include <QPainter>
#include "graphics_edge.h"
class GVertex:  public QObject, public QGraphicsEllipseItem{
    Q_OBJECT
protected:
    QColor color_;
    bool is_drag_over_;
    QString name_;
    QVector<GEdge*> edges_;
    int vertex_position_;
    bool is_cut_;
    int radius_;

    void mousePressEvent(QGraphicsSceneMouseEvent *event){
        setSelected(true);//qDebug() << name_ << " pressed";
        event->accept();
        emit fuck(vertex_position_);

    }
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event){
        //qDebug() << name_<< " moved" << pos().x() << "." << pos().y() << "  " << rect().x() << "." << rect().y();
        QPointF position = event->scenePos();
        setPos(position.x(),position.y());
        for(int i = 0; i < edges_.size(); i++){
            edges_[i]->ChangePos(this, position.x(), position.y());
        }
        event->accept();
    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
        setSelected(false);//qDebug() << name_<< " released";
        event->accept();

    }

public:
    GVertex(int r, int pos):QGraphicsEllipseItem(-r,-r,2*r,2*r),QObject(), vertex_position_(pos){
        //setToolTip("Fuck You!!!!");
        //setCursor(Qt::OpenHandCursor);
        radius_ = r/2;
        color_ = Qt::lightGray;
        is_drag_over_ = false;
        setAcceptDrops(true);
        is_cut_ = false;

        setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    }
    ~GVertex(){}
    void SetName(QString s){
        name_ = s;
        setToolTip(s);
    }
    void SetCut(bool is){
        if(is_cut_ != is){
            is_cut_ = is;
            update(-radius_,-radius_,2*radius_,2*radius_);
        }
    }


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
            /*painter->setPen(QPen(QColor(0, 160, 230), 2));
            painter->drawEllipse(QPointF(120, 60), 50, 20);*/

            // 设置画刷颜色
            if(!is_cut_)
            painter->setBrush(QColor(0, 160, 90));
            else
                painter->setBrush(QColor(255,0,0));

            // 绘制圆
            painter->drawEllipse(QPointF(0, 0), radius_, radius_);

            QRectF rect(-radius_*2,-radius_*2,radius_*4,radius_*2);
            painter->drawText(rect,Qt::AlignHCenter,name_);
    }

    void AddEdge(GEdge *e){
        edges_.push_back(e);
    }

    void Destroy(QGraphicsScene *scene){
        for(int i = 0; i < edges_.size(); i++){
            GVertex *v1 = edges_[i]->vex1(), *v2 = edges_[i]->vex2();
            if(v1 == v2){

            }else{
                v2 = (this == v1)?v2:v1;
                v2->RemoveEdge(edges_[i]);

            }
            scene->removeItem(edges_[i]);
            delete edges_[i];
        }
    }
    void RemoveEdge(GEdge *e){
        for(int i = 0; i < edges_.size(); i++){
            if(edges_[i] == e){
                edges_.erase(edges_.begin() + i);
                //qDebug() << i;
                break;
            }
        }
    }
    void DeleteEdge(GVertex *v2, QGraphicsScene *scene){
        for(int i = 0; i < edges_.size(); i++){
            if(edges_[i]->vex1() == v2 || edges_[i]->vex2() == v2){
                v2->RemoveEdge(edges_[i]);
                scene->removeItem(edges_[i]);
                delete edges_[i];
                edges_.erase(edges_.begin() + i);
                break;
            }
        }
    }
    GEdge *GetEdge(GVertex *v2){
        for(int i = 0; i < edges_.size(); i++){
            if(edges_[i]->vex2() == v2 || edges_[i]->vex1() == v2){
                return edges_[i];
            }
        }
    }
    void SetEdgeCut(bool is){
        for(int i = 0; i < edges_.size(); i++){
            edges_[i]->SetCut(is);
        }
    }

    int VertexPos(){
        return vertex_position_;
    }

signals:
    void fuck(int);
};

#endif // GRAPHICS_VERTEX_H
