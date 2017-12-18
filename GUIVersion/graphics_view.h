#ifndef GRAPHICS_VIEW_H
#define GRAPHICS_VIEW_H
#include <QGraphicsView>
class GView : public QGraphicsView{
public:
    GView (QWidget *parent = 0):QGraphicsView(parent){

    }
    qreal GetScaleVal() const{
        return scale_val_;
    }
    qreal GetTranslateSpeed() const{
        return translate_speed_;
    }
    void SetScaleVal(qreal scale){
        scale_val_ = scale;
    }
    void SetTranslateSpeed(qreal speed){
        translate_speed_ = speed;
    }

private:
    qreal scale_val_;
    qreal translate_speed_;

protected:
    /*void mousePressEvent(QMouseEvent *event){

    }
    void mouseReleaseEvent(QMouseEvent *event){

    }*/
};

#endif // GRAPHICS_VIEW_H
