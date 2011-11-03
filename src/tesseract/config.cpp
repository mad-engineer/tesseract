#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <QString>
#include <QMap>
#include <QDir>

#include "projects.h"

static QMap<QString, QString> config;

static QMap<QString, QString> load_config(const QString file)
{
	QMap<QString, QString> config;
	
	FILE *in=fopen(file.toLocal8Bit().data(),"r");
	
	if(in==NULL) {printf ("%s no encontrado\n", file.toLocal8Bit().data() ); return config;}
	
	char buf[1024];
	char *p, *parameter;
	char *value;
		
	while(!feof(in))
	{
		if( fgets(buf,1024,in)==NULL) break;
		if(feof(in)) break;
		if(buf[0]=='#') continue;
		p=strchr(buf, '=');
		if( p!=NULL )
		{
			*p='\0';
			parameter=buf;
			value=p+1;
			QString qparameter(QString(parameter).trimmed());
			QString qvalue(QString(value).trimmed());
			if(config.value(parameter).isEmpty())
				config[qparameter]=qvalue;
			else
				config[qparameter]=config[qparameter]+"\n"+qvalue;
		}
	}
	
	fclose(in);
	
	return config;
}

const QString get_config(QString parameter)
{
	if (config.isEmpty())
	{
		QMap<QString, QString> global_config = load_config( QString(CONFIG_PATH) + "/config.rc");
		
		QDir dir(configPath());

		if( !(dir.exists()) )
		{
			printf("Building .qtoctave user config\n");
			dir.mkdir(configPath());
		}

		QMap<QString, QString> local_config = load_config(configPath()+"config.rc");
		
		foreach( QString key, global_config.keys() )
		{
			if( local_config.value(key).isEmpty() )
				local_config[key]=global_config[key];
		}
		
		config=local_config;
	}
	
	return config.value(parameter);
}


void set_config(QMap<QString,QString> configuration)
{
	QMapIterator<QString, QString> k(configuration);
	while (k.hasNext())
	{
		k.next();
		if( !k.key().isEmpty() )
			config[k.key().trimmed()]=k.value().trimmed();
	}
	
	QString home_config=configPath()+"config.rc";
	
	QMap<QString, QString> global_config = load_config( QString(CONFIG_PATH) + "/config.rc");
	
	FILE *out=fopen(home_config.toLocal8Bit().data(),"w");

	if( ! out )
	{
		exit(-1234567890);
	}
	
	fprintf(out,"#QtOctave local configuration.\n");
	
	QMapIterator<QString, QString> i(config);
	while (i.hasNext())
	{
		i.next();
		if
		(
			!i.key().isEmpty() && !i.value().isEmpty()
			&& global_config[i.key()]!=i.value()
		)
		{
			QStringList values=i.value().split("\n");
			QString item;
			foreach(item, values)
			{
				fprintf(out,"%s=%s\n",i.key().toLocal8Bit().data(),item.toLocal8Bit().data());
			}
		}
	}
	
	fclose(out);
}

