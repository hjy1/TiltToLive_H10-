#ifndef ANNULUSITEM_H
#define ANNULUSITEM_H

#include <QGraphicsItem>

class AnnulusItem : public QGraphicsEllipseItem
{
public:
    AnnulusItem(QGraphicsItem *parent): QGraphicsEllipseItem(parent)    {}
    AnnulusItem(const QRectF &rect, qreal thk, QGraphicsItem *parent = nullptr);
    AnnulusItem(qreal x, qreal y, qreal w, qreal h, qreal thk, QGraphicsItem *parent = nullptr);
    ~AnnulusItem();

    void SetThck(qreal &thk);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QPainterPath shape() const;

    void setRect(qreal x, qreal y, qreal w, qreal h);
private:

    QRectF rect;
    qreal thck;
    QPainterPath paintshape;

    void updatepaintshape();
};

#endif // ANNULUSITEM_H
