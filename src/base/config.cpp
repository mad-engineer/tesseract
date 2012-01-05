#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <memory>
#include <vector>
#include <fstream>
#include <iostream>

#include <QMap>
#include <QDir>
#include <QString>
#include <QTranslator>
#include <QTextStream>

#include "config.hpp"
#include "projects.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using std::vector;
using std::ifstream;
using std::unique_ptr;
using boost::property_tree::ptree;
using boost::property_tree::ptree_bad_path;
using boost::property_tree::xml_parser_error;



namespace tesseract
{

bool operator < ( const settings & lhs , const settings & rhs )
{
	return lhs.get() < rhs.get();
}

config::config( const string &newRootName , const string &newConfigPath ) : 
rootname( newRootName ),
filename( newConfigPath )
{
	data.insert( settingspair( settings::defVal() , QDomDocument() ) );
	data.insert( settingspair( settings::limMin() , QDomDocument() ) );
	data.insert( settingspair( settings::limMax() , QDomDocument() ) );
}

// this slot receives new configurations
void config::receiveConfiguration( const string &node , const string &prop , const string &datatype , const string &defval , const string &minval , const string &maxval )
{
	QDomDocument & defdoc = data[settings::defVal()];
	QDomDocument & mindoc = data[settings::limMin()];
	QDomDocument & maxdoc = data[settings::limMax()];

	QDomNodeList defnodelist = defdoc.elementsByTagName( node.c_str() );
	QDomNodeList minnodelist = defdoc.elementsByTagName( node.c_str() );
	QDomNodeList maxnodelist = defdoc.elementsByTagName( node.c_str() );

	QDomElement elem;
	
	if( defnodelist.isEmpty() )
	{
		elem = defdoc.createElement( node.c_str() );
	}
	else
	{
		elem = defdoc.firstChildElement( node.c_str() );
	}

	QDomElement attr = defdoc.createElement( prop.c_str() );

	attr.setAttribute( "type"  , datatype.c_str() );
	attr.setAttribute( "value" , defval.c_str()   );
	
	elem.appendChild( attr );
	defdoc.appendChild( elem );

	if( minval.size() )
	{
		if( minnodelist.isEmpty() )
		{
			elem = mindoc.createElement( node.c_str() );
		}
		else
		{
			elem = mindoc.firstChildElement( node.c_str() );
		}

		QDomElement attr = mindoc.createElement( prop.c_str() );

		attr.setAttribute( "type"  , datatype.c_str() );
		attr.setAttribute( "value" , minval.c_str()   );

		elem.appendChild( attr );
		mindoc.appendChild( elem );
	}

	if( maxval.size() )
	{
		if( maxnodelist.isEmpty() )
		{
			elem = maxdoc.createElement( node.c_str() );
		}
		else
		{
			elem = maxdoc.firstChildElement( node.c_str() );
		}

		QDomElement attr = maxdoc.createElement( prop.c_str() );

		attr.setAttribute( "type"  , datatype.c_str() );
		attr.setAttribute( "value" , maxval.c_str()   );

		elem.appendChild( attr );
		maxdoc.appendChild( elem );
	}

	QFile file( filename.c_str() );

	if( ! file.open( QFile::WriteOnly ) )
	{
		int test = 0;
	}

	QTextStream ts( &file );
	ts << defdoc.toString();

	file.close();
}

void config::requestAttribute( const string &node , string &propVal )
{
	QFile file( filename.c_str() );

	if( ! file.open( QFile::ReadOnly ) )
	{
		// TODO: Return the default value
		// TODO: Write error to terminal (via signal)
	}

	QDomDocument actdoc;

	if( ! actdoc.setContent( & file ) )
	{
		// TODO: Return default value
		// TODO: Write error to terminal (via signal)
	}

	QDomNodeList nodelist = actdoc.elementsByTagName( node.c_str() );

	if( nodelist.isEmpty() )
	{
		// TODO: Return default value
		// TODO: Write error to terminal (via signal)
	}

	QDomNode elem = nodelist.at( 0 );

	if( ! elem.hasChildNodes() )
	{
		// TODO: Return default value
		// TODO: Write error to terminal (via signal)
		// Could not find the requested property in the config file
	}

	elem = elem.firstChildElement( propVal.c_str() );

	if( ! elem.hasAttributes() )
	{
		// TODO: Return default value
		// TODO: Write error to terminal (via signal)
		// The node has no attributes
	}

	QDomNamedNodeMap attrmap = elem.attributes();

	if( ! attrmap.contains( "value" ) )
	{
		// TODO: Return default value
		// TODO: Write error to terminal (via signal)
		// The node does not contain value attribute
	}

	string valuetype = "size";

	if( valuetype == "size" )
	{
		QDomNode tmp = attrmap.namedItem( "value" );

		int test = tmp.nodeValue().toInt();
		propVal = tmp.nodeValue().toStdString();
	}
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

