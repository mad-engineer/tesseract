#pragma once
#ifndef TESSERACT_BASE_SPLASH_HPP
#define TESSERACT_BASE_SPLASH_HPP

#include <QFrame>
#include <QColor>
#include <QString>
#include <QPicture>

#ifdef TESSERACT_USE_VLD
#	include <vld.h>
#endif


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