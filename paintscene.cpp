#include "paintscene.h"
#include <QDebug>
 
PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
 
}
 
PaintScene::~PaintScene()
{
 
}
 
void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    color = event->button() == Qt::MouseButton::LeftButton ? Qt::red : Qt::blue;
    // При нажатии кнопки мыши отрисовываем эллипс
    addEllipse(event->scenePos().x() - 5,
               event->scenePos().y() - 5,
               10,
               10,
               QPen(Qt::NoPen),
               QBrush(color));
    // Сохраняем координаты точки нажатия
    previousPoint = event->scenePos();
}
 
void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Отрисовываем линии с использованием предыдущей координаты
    addLine(previousPoint.x(),
            previousPoint.y(),
            event->scenePos().x(),
            event->scenePos().y(),
            QPen(color,10,Qt::SolidLine,Qt::RoundCap));
    // Обновляем данные о предыдущей координате
    previousPoint = event->scenePos();
    qDebug() << "Mouse position:" << previousPoint;
}
