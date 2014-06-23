#include "mainWindow.h"
#include "ui_mainWindow.h"

#include "coolGraphicsView.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	mUi(new Ui::MainWindow)
{
	mUi->setupUi(this);
	connect(mUi->graphicsView, &CoolGraphicsView::newMessage, mUi->plainTextEdit, &QPlainTextEdit::appendPlainText);
}

MainWindow::~MainWindow()
{
	delete mUi;
}
