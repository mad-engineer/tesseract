#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <iostream>

#include <QMap>
#include <QDir>
#include <QString>
#include <QTranslator>

#include "config.hpp"
#include "projects.hpp"

namespace tesseract
{

bool operator < ( settings const& lhs, settings const& rhs )
{
	return lhs.get() < rhs.get();
}

config::config()
{
	data.insert( configpair( settings::active()  , map< string , string >() ) );
	data.insert( configpair( settings::default() , map< string , string >() ) );
}

int settings::get() const
{
	return id;
}

}

static QMap<QString, QString> config;

static QMap<QString, QString> load_config( const QString &file )
{
	QMap<QString, QString> config;
	
	FILE *in = fopen( file.toLocal8Bit().data() , "r" );
	
	if( in == NULL ) 
	{
		// TODO: Add translation possibility
		std::cout << "The config file :" << file.toStdString() << "does not exists" << std::endl; 

		return config;
	}
	
	char buf[1024];
	char *p, *parameter;
	char *value;
		
	while( ! feof( in ) )
	{
		if( fgets( buf , 1024 , in ) == NULL ) 
		{
			break;
		}

		if( feof( in ) )
		{
			break;
		}

		if( buf[0] == '#' ) 
		{
			continue;
		}

		p = strchr( buf , '=' );

		if( p != NULL )
		{
			*p = '\0';

			parameter=buf;
			value = p + 1;

			QString qparameter( QString( parameter ).trimmed() );
			QString qvalue( QString( value ).trimmed() );
			
			if( config.value( parameter ).isEmpty() )
			{
				config[qparameter] = qvalue;
			}
			else
			{
				config[qparameter] = config[qparameter] + '\n' + qvalue;
			}
		}
	}
	
	fclose( in );
	
	return config;
}

const QString getConfig( const QString &parameter )
{
	if ( config.isEmpty() )
	{	
		config = load_config( configPath() + "config.rc" );
	}
	
	return config.value( parameter );
}


void setConfig( const QMap<QString,QString> &configuration )
{
	QMapIterator<QString, QString> k( configuration );
	
	while ( k.hasNext() )
	{
		k.next();
		
		if( ! k.key().isEmpty() )
		{
			config[k.key().trimmed()] = k.value().trimmed();
		}
	}
	
	QString home_config = configPath() + "config.rc";
	
	FILE *out = fopen( home_config.toLocal8Bit().data() , "w" );

	if( ! out )
	{
		exit(-1234567890);
	}
	
	fprintf( out , "#QtOctave local configuration.\n" );
	
	QMapIterator<QString, QString> i( config );

	while ( i.hasNext() )
	{
		i.next();

		if( i.key().size() && i.value().size() )
		{
			QStringList values = i.value().split( '\n' );
			QString item;

			foreach( item , values )
			{
				fprintf( out , "%s=%s\n" , i.key().toLocal8Bit().data() , item.toLocal8Bit().data() );
			}
		}
	}
	
	fclose( out );
}

