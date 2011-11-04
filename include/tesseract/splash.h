#pragma once
#ifndef TESSERACT_TESSERACT_SPLASH_H
#define TESSERACT_TESSERACT_SPLASH_H

#include <QFrame>
#include <QColor>
#include <QString>
#include <QPicture>


class CSplashScreen : public QFrame
{
public:
	CSplashScreen(const QPixmap& pixmap);

	void clearMessage();
	void showMessage(const QString& theMessage, int theAlignment = Qt::AlignLeft, const QColor& theColor = Qt::black);

private:
	virtual void paintEvent(QPaintEvent* pe);

	QPixmap itsPixmap;
	QString itsMessage;
	int itsAlignment;
	QColor itsColor;
};

#endif