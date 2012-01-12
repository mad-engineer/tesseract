/* Copyright (C) 2011 Tesseract Project
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

/** @file config.h
 * This file contains application's config parameters. Configuration is automatically load and save from CONFIG_PATH/config.rc and from user home/.qtoctave.rc
 */
#pragma once

#define PKG_ENABLED

#ifndef TESSERACT_BASE_CONFIG_HPP
#define TESSERACT_BASE_CONFIG_HPP

#include <cstdio>

#include <QMap>
#include <QString>
#include <QDomDocument>

#include <map>
#include <string>

#include <boost/lexical_cast.hpp>

using std::map;
using std::string;

#ifdef TESSERACT_USE_VLD
#	include <vld.h>
#endif

#include "session.hpp"

namespace tesseract
{

class settings
{
	int id;

	/*	Do not change this order. 
	*	It is importing
	*	To parse xml document.
	*/
	enum
	{
		ID_SETTINGS_ACTIVE,
		ID_SETTINGS_DEFAULT,
		ID_SETTINGS_LIMITS_MIN,
		ID_SETTINGS_LIMITS_MAX
	};

	explicit settings( int newId ) :
	id(newId) 
	{

	}


	public:

		int get() const;

		static settings actVal()
		{
			return settings( ID_SETTINGS_ACTIVE );
		}

		static settings defVal()
		{
			return settings( ID_SETTINGS_DEFAULT );
		}

		static settings limMin()
		{
			return settings( ID_SETTINGS_LIMITS_MIN );
		}

		static settings limMax()
		{
			return settings( ID_SETTINGS_LIMITS_MAX );
		}
};

class config : public QObject
{
	Q_OBJECT

	// how the xml document root node called
	const string rootname;

	// where is the configuration file located
	const string filename;

	typedef map< settings , QDomDocument > configmap;
	typedef std::pair< settings , QDomDocument > settingspair;

	configmap data;
	
	void getValue
	( 
		const settings &conf, 
		const string &node, 
		string &propType,
		string &propVal 
	);


	signals:

		void sendAttribute( string node , string prop , string propVal );


	public:

		config( const string &rootname , const string &filename );
		virtual ~config() { };


	public slots:

		// this slot receives new configurations
		void receiveConfiguration
		( 
			string node, 
			string prop,
			string datatype,
			string defval,
			string minval = "", 
			string maxval = "" 
		);

		void requestAttribute( string node , string propVal );
};

class basewidgetconfig : public config
{
	Q_OBJECT


	signals:

		void sendTerminalAttribute( string node , string propVal );


	public:

		basewidgetconfig( const string &rootname , const string &filename );
		~basewidgetconfig();


	public slots:

		void receiveAttribute( string node , string prop , string propVal );
		void requestTerminalAttribute( string node , string propVal );
};

}

/**
 * Gets config of parameter.
 * @param parameter Parameter name.
 * @return A QString with parameter value.
 */
const QString getConfig( const QString &parameter );

/**
 * Sets config of parameter.
 * @param configuration Add a parameter with value. QMap key is parameter name. QMap value is parameter value.
 */
void setConfig( const QMap< QString , QString > &configuration );

#endif
