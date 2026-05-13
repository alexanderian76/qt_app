#ifndef PAINTSCENE\_H
#define PAINTSCENE\_H
 
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QtWidgets>

 
class PaintScene : public QGraphicsScene
{
 
    Q_OBJECT
 
public:
    explicit PaintScene(QObject *parent = 0);
    ~PaintScene();

 
private:
    QPointF     previousPoint;      // Координаты предыдущей точки
    Qt::GlobalColor color;
 
private:
    // Для рисования используем события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
 
};
 
#endif // PAINTSCENE\_H