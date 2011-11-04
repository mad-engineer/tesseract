#pragma once
#ifndef TESSERACT_SVGCANVAS_SVGCANVAS_H
#define TESSERACT_SVGCANVAS_SVGCANVAS_H

#include <QRegExp>

#include "basewidget.h"

class QSvgWidget;
class OctaveConnection;

/*
	Creates a simple canvas to plot svg files.
*/
class SvgCanvas: public BaseWidget
{
	Q_OBJECT
	QSvgWidget *svg_plot;
	int canvas_number;
	QRegExp re, re_save, re_delete_on_load;
	OctaveConnection *oc;
	QString svg_file_name;
	
	QMenu *menuFile;
	QAction *actionExportTo;
	
	void export_to_png_jpg( int width , int height , const QString &filename );
	void export_to_pdf_ps( int width , int height , const QString &filename );
	
	public:
		SvgCanvas( QWidget *parent=0 );
		void setOctaveConnection( OctaveConnection *oc );
		void setCanvasNumber( int n );
		int getCanvasNumber();
		BaseWidget *copyBaseWidget( QWidget * parent = 0 );
		
		public slots:
		void line_ready( const QString &line );
		void actionExport_to_callback();
		void load_file( const QString &file );
};


#endif

