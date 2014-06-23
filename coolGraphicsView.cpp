#include "coolGraphicsView.h"

#include <QtGui/QTouchEvent>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtWidgets/QApplication>

CoolGraphicsView::CoolGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
	viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
	CoolGraphicsScene * const scene = new CoolGraphicsScene(this);
	setScene(scene);
	connect(scene, &CoolGraphicsScene::newMessage, this, &CoolGraphicsView::newMessage);
}

bool CoolGraphicsView::viewportEvent(QEvent *event)
{
	switch (event->type()) {
	case QEvent::TouchBegin:
		simulatePress(static_cast<QTouchEvent *>(event), Qt::RightButton);
		return true;
	case QEvent::TouchUpdate:
		simulateMove(static_cast<QTouchEvent *>(event));
		return true;
	case QEvent::TouchEnd:
		simulateRelease(static_cast<QTouchEvent *>(event));
		return true;
	default:
		break;
	}
	return QGraphicsView::viewportEvent(event);
}

void CoolGraphicsView::simulateMouse(QObject *reciever, QEvent::Type event, QPointF const &pos
		, Qt::MouseButtons buttons)
{
	QMouseEvent *mouseEvent = new QMouseEvent(event, pos, mButton, buttons, Qt::NoModifier);
	QApplication::postEvent(reciever, mouseEvent);
}

/// Simulating mouse press with the given button. Next simulateMove and simulateRelease calls will use the same mouse button.
void CoolGraphicsView::simulatePress(QTouchEvent *event, Qt::MouseButton button)
{
	mButton = button;
	simulateMouse(event->target(), QEvent::MouseButtonPress, event->touchPoints()[0].pos(), mButton);
}

void CoolGraphicsView::simulateMove(QTouchEvent *event)
{
	simulateMouse(event->target(), QEvent::MouseMove, event->touchPoints()[0].pos(), mButton);
}

void CoolGraphicsView::simulateRelease(QTouchEvent *event)
{
	simulateMouse(event->target(), QEvent::MouseButtonRelease, event->touchPoints()[0].pos(), Qt::NoButton);
}

// ---- scene -----

CoolGraphicsScene::CoolGraphicsScene(QObject *parent)
	: QGraphicsScene(parent)
{
}

void CoolGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	emit newMessage("Pressed with " + buttonToString(event->button()) + " button");
}

void CoolGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	Q_UNUSED(event)
}

void CoolGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	emit newMessage("Released " + buttonToString(event->button()) + " button");
}

QString CoolGraphicsScene::buttonToString(Qt::MouseButton button) const
{
	return button == Qt::LeftButton ? "left"
			: button == Qt::RightButton ? "right"
			: "other";
}
