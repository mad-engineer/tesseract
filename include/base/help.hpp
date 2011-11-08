/* Copyright (C) 2006,2007,2008 P.L. Lucas
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, 
 * Boston, MA 02111-1307, USA. 
 */

#pragma once
#ifndef TESSERACT_BASE_HELP_HPP
#define TESSERACT_BASE_HELP_HPP

#include <QToolbar>
#include <QLineEdit>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextBrowser>

#ifdef TESSERACT_USE_VLD
#	include <vld.h>
#endif

#include "basewidget.hpp"

/**Shows help in simple html. Users can do searches.
*/
class Help:public BaseWidget
{
	Q_OBJECT
	public:
	Help(QWidget * parent = 0);
	void setSource(const QString source, QString anchor="");
	BaseWidget *copyBaseWidget( QWidget * parent = 0 );
	~Help();
	private:
	QVBoxLayout *vlayout;
	QToolBar *toolbar;
	QTextBrowser *browser;
	QLineEdit *lineedit;
	QCheckBox *check_box;
	QPushButton *search_button;
	QString source;
	void create_buttons();
	public slots:
	void back();
	void forward();
	void find();
	void go_home();
	void textChanged ( const QString & text );
};
	
#endif
