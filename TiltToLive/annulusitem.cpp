#include "annulusitem.h"
#include "constants.h"
#include <QDebug>
#include <QPainter>

AnnulusItem::AnnulusItem(const QRectF &rect, qreal thk, QGraphicsItem *parent):
    QGraphicsEllipseItem (rect, parent), thck(thk)   {this->rect = rect;updatepaintshape();}

AnnulusItem::AnnulusItem(qreal x, qreal y, qreal w, qreal h, qreal thk, QGraphicsItem *parent):
    QGraphicsEllipseItem (x,y,w,h,parent), thck(thk)   {this->rect = QRectF(x,y,w,h);updatepaintshape();}
AnnulusItem::~AnnulusItem() {}

QRectF AnnulusItem::boundingRect() const    {return rect;}

void AnnulusItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
        painter->save();
        painter->setBrush(QBrush(WAVE_COLOR));
        painter->drawPath(paintshape);

        painter->restore();
}

QPainterPath AnnulusItem::shape() const{
    return paintshape;
}

void AnnulusItem::updatepaintshape(){
    double a = this->rect.width() / 2,b = this->rect.height() / 2;
    QPainterPath bigCircle;
    bigCircle.addEllipse(rect.x(), rect.y(), a * 2, b * 2);

    a -= thck;
    b -= thck;
    QPainterPath smallCircle;
    smallCircle.addEllipse(rect.x() + thck, rect.y() + thck, a * 2, b * 2);

    paintshape = bigCircle - smallCircle;
}

void AnnulusItem::setRect(qreal x, qreal y, qreal w, qreal h){
    QRectF rec(x,y,w,h);
    if(rec == rect) return ;
    prepareGeometryChange();
    rect = rec;
    updatepaintshape();
    update();
}
