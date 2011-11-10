#pragma once
#ifndef TESSERACT_SVGCANVAS_SVGCANVAS_HPP
#define TESSERACT_SVGCANVAS_SVGCANVAS_HPP

#include <QRegExp>

#ifdef TESSERACT_USE_VLD
#	include <vld.h>
#endif

#include "basewidget.hpp"

class QSvgWidget;
class OctaveConnection;

/*
	Creates a simple canvas to plot svg files.
*/
class SvgCanvas: public BaseWidget
{
	Q_OBJECT

	QMenu *menuFile;
	int canvas_number;
	QSvgWidget *svg_plot;
	OctaveConnection *oc;
	QString svg_file_name;
	QAction *actionExportTo;
	QRegExp re, re_save, re_delete_on_load;

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

