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

#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>

// TODO: Remove this if old config is finally replaced
#include "projects.hpp"

using std::vector;
using std::ifstream;
using std::unique_ptr;

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
void config::receiveConfiguration( string node , string prop , string datatype , string defval , string minval , string maxval )
{
	QDomDocument & defdoc = data[settings::defVal()];
	QDomDocument & mindoc = data[settings::limMin()];
	QDomDocument & maxdoc = data[settings::limMax()];

	QDomNodeList defnodelist = defdoc.elementsByTagName( node.c_str() );
	QDomNodeList minnodelist = defdoc.elementsByTagName( node.c_str() );
	QDomNodeList maxnodelist = defdoc.elementsByTagName( node.c_str() );

	for( map< settings , QDomDocument >::iterator doc = data.begin() ; doc != data.end() ; doc++ )
	{
		QDomNodeList &noderef  = doc->second.elementsByTagName( node.c_str() );

		if( noderef.isEmpty() )
		{
			doc->second.appendChild( doc->second.createElement( node.c_str() ) );
		}
	}

	QDomElement elem = defdoc.firstChildElement( node.c_str() );
	QDomElement attr = mindoc.createElement( prop.c_str() );

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

#	ifdef _DEBUG

	QFile deffile( string( filename + ".def" ).c_str() );
	QFile minfile( string( filename + ".min" ).c_str() );
	QFile maxfile( string( filename + ".max" ).c_str() );

	if( ! deffile.open( QFile::WriteOnly ) )
	{
		BOOST_ASSERT_MSG( false , "Caught unknown exception." );
	}

	if( ! minfile.open( QFile::WriteOnly ) )
	{
		BOOST_ASSERT_MSG( false , "Caught unknown exception." );
	}

	if( ! maxfile.open( QFile::WriteOnly ) )
	{
		BOOST_ASSERT_MSG( false , "Caught unknown exception." );
	}

	QTextStream defts( &deffile );
	defts << defdoc.toString();

	QTextStream maxts( &maxfile );
	maxts << maxdoc.toString();

	QTextStream mints( &minfile );
	mints << mindoc.toString();

	deffile.close();
	minfile.close();
	maxfile.close();

#	endif
}

/*
*	This internal (private) method will be called if any errors
*	happened during the xml-parse process or the limit values (min, max) are
*	needed to verify the correctness of the parsed value.
*
*/
void config::getValue( const settings &conf, const string &node, string &propType, string &propVal )
{
	// Get the right container
	QDomNamedNodeMap DomMap = data[conf]

	//// get the node (example: <terminal> )
	.firstChildElement( node.c_str() )

	// Get the attribute node (example: <maxlines> )
	.firstChildElement( propType.c_str() )

	// Get the Attributes for this node (example:  type="color" value="Red" )
	.attributes();

	// get the first map element for the type
	propType = DomMap.item( 0 ).nodeValue().toStdString();
	
	BOOST_ASSERT_MSG( propType.size() , "The requested property type is empty" );

	// get the second map element for the value
	propVal = DomMap.item( 1 ).nodeValue().toStdString();

	BOOST_ASSERT_MSG( propVal.size() , "The requested property value is empty" );
}

/*
*	This slot method is called from all other modules.
*	When the program starts every module sends its default
*	settings and the limit values to this config module.
*	At runtime runtime other modules will request the configuration
*	values which are stored in "filename". Several errors
*	can happen during the "reading values from file" process.
*	If any error will happen then the default value will be sent
*	to the enquirer.
*
*	Note: 
*	I know this is crap design but as long Qt's moccing
*	mechanism does not support templates i do not have a better
*	idea to solve this. If you have a better way feel free and
*	commit or send me a message through github.
*/
void config::requestAttribute( string node , string propVal )
{
	QFile file( filename.c_str() );

	string dummy;

	// Try to open the xml configuration file
	if( ! file.open( QFile::ReadOnly ) )
	{
		string error = "Could not open the xml configuration file: " + filename;
		getValue( settings::defVal() , node , dummy , propVal );
		return;
	}

	QDomDocument actdoc;

	{
		QString errmsg;

		if( ! actdoc.setContent( & file , &errmsg ) )
		{
			string error = "Could not parse the xml document. Error Message (" + errmsg.toStdString() + ").";
			getValue( settings::defVal() , node , dummy , propVal );
			return;
		}
	}

	QDomNodeList nodelist = actdoc.elementsByTagName( node.c_str() );

	if( nodelist.isEmpty() )
	{
		string error = "Could not find the requested node (" + node + ") in the xml configuration file.";
		getValue( settings::defVal() , node , dummy , propVal );
		return;
	}

	QDomNode elem = nodelist.at( 0 );

	if( ! elem.hasAttributes() )
	{
		string error = "The requested property (" + propVal + ") has no attributes.";
		getValue( settings::defVal() , node , dummy , propVal );
		return;
	}

	QDomNamedNodeMap attrmap = elem.attributes();

	if( ! attrmap.contains( propVal.c_str() ) )
	{
		string error = "The requested property (" + propVal + ") does not contain a value attribute.";
		getValue( settings::defVal() , node , dummy , propVal );
		return;
	}

	string defVal = "";
	string propType = propVal;
	string requestedProperty = propVal;
	string configVal = attrmap.namedItem( requestedProperty.c_str() ).nodeValue().toStdString();

	getValue( settings::defVal() , node , propType , defVal );

	if( propType == "size" )
	{
		bool ok;
		int actVal = QString( configVal.c_str() ).toInt( &ok );

		if( ok )
		{
			string minVal , maxVal;

			dummy = requestedProperty;
			getValue( settings::limMin() , node , dummy , minVal );

			dummy = requestedProperty;
			getValue( settings::limMax() , node , dummy , maxVal );

			if( actVal < QString( minVal.c_str() ).toInt() )
			{
				string error = "The parsed value (" + configVal + ")" 
							   "in the node (" + node + ")"
							   "for the property (" + requestedProperty + ")"
							   "is smaller then the allowed minimum bound for"
							   "this value (" + minVal + ").";

				propVal = defVal;
				return;
			}
			else if( actVal > QString( maxVal.c_str() ).toInt() )
			{
				string error = "The parsed value (" + configVal + ")" 
							   "in the node (" + node + ")"
							   "for the property (" + requestedProperty + ")"
							   "is bigger then the allowed maximum bound for"
							   "this value (" + maxVal + ").";

				propVal = defVal;
				return;
			}
			else
			{
				propVal = configVal;
			}
		}
		else
		{
			string error = "Could not parse the value (" + configVal + ")" 							  
						   "in the node (" + node + ")"
						   "for the property (" + requestedProperty + ").";

			propVal = defVal;
			return;
		}
	}
	else
	{
		propVal = configVal;
	}

	emit sendAttribute( node , requestedProperty , propVal );
}

int settings::get() const
{
	return id;
}

void basewidgetconfig::receiveAttribute( string node , string prop , string propVal )
{
	if( node == "terminal" )
	{
		emit sendTerminalAttribute( prop , propVal );
	}
	else
	{
		BOOST_ASSERT_MSG( false , "Unknown node name. No back signal will be send" );
	}
}

void basewidgetconfig::requestTerminalAttribute( string node , string propVal )
{
	requestAttribute( node , propVal );
}

basewidgetconfig::basewidgetconfig( const string &rootname , const string &filename ) : 
config( rootname , filename )
{
	// Connect attribute request
	bool terminalConfigurationRequest = QObject::connect
	( 
		this , SIGNAL( sendAttribute( string , string , string ) ) , 
		this , SLOT( receiveAttribute( string , string , string ) )
	);

	BOOST_ASSERT_MSG
	( 
		terminalConfigurationRequest , 
		"Something went wrong while connection terminal with attribute requester." 
	);
}

basewidgetconfig::~basewidgetconfig()
{
	// Connect configuration
	bool terminalConfigurationConnection = QObject::disconnect
	( 
		this , SIGNAL( sendAttribute( string , string , string ) ) , 
		this , SLOT( receiveAttribute( string , string , string ) )
	);

	BOOST_ASSERT_MSG
	( 
		terminalConfigurationConnection , 
		"Something went wrong while disconnection Terminal with configuration" 
	);
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

