#ifndef COOLGRAPHCISVIEW_H
#define COOLGRAPHCISVIEW_H

#include <QtCore/QEvent>
#include <QtWidgets/QGraphicsView>

class QTouchEvent;

class CoolGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	explicit CoolGraphicsView(QWidget *parent = 0);

signals:
	void newMessage(QString const &message);

private:
	bool viewportEvent(QEvent *event) override;

	void simulateMouse(QObject *reciever, QEvent::Type event, QPointF const &pos, Qt::MouseButtons buttons);
	void simulatePress(QTouchEvent *event, Qt::MouseButton button);
	void simulateMove(QTouchEvent *event);
	void simulateRelease(QTouchEvent *event);

	Qt::MouseButton mButton;
};

class CoolGraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	explicit CoolGraphicsScene(QObject *parent = 0);

signals:
	void newMessage(QString const &message);

private:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

	QString buttonToString(Qt::MouseButton button) const;
};

#endif // COOLGRAPHCISVIEW_H
