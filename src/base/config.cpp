#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <vector>
#include <fstream>
#include <iostream>

using std::vector;
using std::ifstream;

#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using boost::property_tree::ptree;
using boost::property_tree::ptree_bad_path;
using boost::property_tree::xml_parser_error;

#include <QMap>
#include <QDir>
#include <QString>
#include <QTranslator>

#include "config.hpp"
#include "projects.hpp"

namespace tesseract
{

bool operator < ( settings const & lhs , settings const & rhs )
{
	return lhs.get() < rhs.get();
}

config::config( string const &newRootName , string const &newConfigPath ) : 
rootname( newRootName ),
filename( newConfigPath )
{

}

// this slot receives new configurations
void config::receiveConfiguration( string const &node, settingsmap const &defaults, settingsmap const &limitmin, settingsmap const &limitmax )
{
	configmap defmap;
	configmap limminmap;
	configmap limmaxmap;
	settingsmap activemap = shared_ptr<map<string,string>>( new map<string,string>() );

	defmap.insert( settingspair( settings::default() , defaults		 ) );
	limminmap.insert( settingspair( settings::limitsMin() , limitmin ) );
	limmaxmap.insert( settingspair( settings::limitsMax() , limitmax ) );

	data.insert( configpair( node , defmap ) );
	data.insert( configpair( node , limminmap ) );
	data.insert( configpair( node , limmaxmap ) );

	try
	{
		ptree pt;

		read_xml( filename , pt );

		vector<string> defaultKeys;
		vector<string> defaultValues;
		vector<string> limitMaxValues;
		vector<string> limitMinValues;

		for( map<string,string>::const_iterator i = defaults->begin() ; i != defaults->end() ; i++ )
		{
			const string key = i->first;
			const string val = i->second;

			try
			{
				const string activeValue = pt.get<string>( rootname + "." + node + "." + key );

				map<string,string>::const_iterator foundMin = limitmin->find( key );
				map<string,string>::const_iterator foundMax = limitmax->find( key );

				int limitMinVal = -1;
				int limitMaxVal = -1;

				if( foundMin != limitmin->end() )
				{
					limitMinVal = boost::lexical_cast<int,string>( foundMin->second );
				}

				if( foundMax != limitmax->end() )
				{
					limitMaxVal = boost::lexical_cast<int,string>( foundMax->second );
				}

				if( limitMinVal != -1 )
				{
					try
					{
						const int testValue = boost::lexical_cast<int,string>( activeValue );

						if( ( testValue <= limitMaxVal ) && ( testValue >= limitMinVal ) )
						{
							activemap->insert( std::pair<string,string>( key , activeValue ) );
						}
						else
						{
							activemap->insert( std::pair<string,string>( key , val ) );
						}

					}
					catch ( boost::bad_lexical_cast )
					{
						BOOST_ASSERT_MSG
						( 
							false , 
							string
							(
								string( "Could not cast numeric key: \"" ) 
								+ key + string( "\"" ) + string( " with value: \"" ) 
								+ val + string( "\"" )
							).c_str()
						);
					}
					catch( ... )
					{
						BOOST_ASSERT_MSG( false , "Caught unknown exception." );
					}
				}
				
				// if the value is not numeric 
				// or an exception was thrown before
				if( activemap->find( key ) == activemap->end() )
				{
					activemap->insert( std::pair<string,string>( key , val ) );
				}
			}
			catch( ... )
			{
				BOOST_ASSERT_MSG( false , "Caught unknown exception." );
			}
		}
	}
	catch( ptree_bad_path * e )
	{
		BOOST_ASSERT_MSG( false , e->what() );
	}
	catch (	xml_parser_error * e )
	{
		string errormsg( "Error while parsing xml file (" + e->filename() + " )" );
		//		errormsg.append( "in line ( " + e->line() + ")." );
		errormsg.append( "Message: ( " + e->message() );
		errormsg.append( boost::lexical_cast<string,int>( e->line() ) );
		errormsg.append( ". ( " + e->message() + ")." );

		BOOST_ASSERT_MSG( false , errormsg.c_str() );
	}
	catch( ... )
	{
		BOOST_ASSERT_MSG( false , "Caught unknown exception." );
	}

	configmap actmap;
	actmap.insert( settingspair( settings::active()  , activemap ) );
	data.insert( configpair( node , actmap ) );
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
		std::cout << "The config file :" << file.toStdString() 
				  << "does not exists" << std::endl; 

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

