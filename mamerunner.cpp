#include "mamerunner.h"

#include <KDebug>
#include <KIcon>

mamerunner::mamerunner(QObject *parent, const QVariantList& args)
    : Plasma::AbstractRunner(parent, args)
{
    Q_UNUSED(args);
    setObjectName("mamerunner");
}

mamerunner::~mamerunner()
{
}


/*
 * En este metodo es llamado por KRunner para realizar la busqueda que quiera hacer el runner en concreto
 * 
 * Nosotros miraremos en el fichero xml de la lista de juegos y mostraremos los juegos que vayan coincidiendo
 * con la entrada del usuario
 * 
 */
void mamerunner::match(Plasma::RunnerContext &context)
{

    // Comprobamos que la palabra tenga al menos tres digitos. Si no el runner pasara de hacer nada
    const QString term = context.query();
    if (term.length() < 3) {
        return;
    }
    

    // Nuestra cadena de activacion es 'mame' seguida <nombre del juego> o toda la lista
    if (!term.startsWith("mame"))
    {
      return;
    }
    
    /*
     * Realizamos la busqueda en el archivo XML
     * Por cada coincidencia creamos una instancia de la clase QueryMatch y la almacenamos
     * en la lista matches, que sera devuelta al final
     *
     */ 
    
    QList<Plasma::QueryMatch> matches;
    QStringList params = term.split(" ");

    configfile->setFileName("~/.mamerunner");
    
    if (!configfile->open(QIODevice::ReadOnly || QIODevice::Text))
      return;

    QString romdir;
    QString xmlgames;

    while (!configfile->atEnd())
    {
	QByteArray linea = configfile->readLine();
	
	if (!linea.startsWith('#'))
	{
	  QList<QByteArray> token = linea.split("=");
	   
	  if (token[0].toUpper() = "ROMDIR")
	    romdir = token[1];

	  if (token[0].toUpper() = "GAMELIST")
	    xmlgames = token[1];
	  
	  
	}
      
    }

    params.removeFirst();
    QString queryterm(params.join());

    mameListFile.setFileName(xmlgames);
    
    mameListFile.open(QIODevice::ReadOnly);

    QByteArray outArray;
    QBuffer buffer(&outArray);
    buffer.open(QIODevice::ReadWrite);

    QString xquery('declare variable $inputDocument external');
    xquery.append('declare variable $gamename external');
    xquery.append('doc($inputdocument)/game/name[$gamename]');
      
    QXmlQuery query;

    query.bindVariable("inputDocument", &mameListFile);
    query.bindVariable("gamename", &queryterm);
    
    query.setQuery('doc($inputDocument)/name["game=]');
    
    if (!query.isValid())
	return;

    QXmlFormatter formatter(query, &buffer);
    if (!query.evaluateTo(&formatter))
	return;

    buffer.close();

    
    // Sampler
    // Caso START
    if (params[1] == "start")
    {
	Plasma::QueryMatch ma(this);
	
	ma.setId("start");
	ma.setText("Start NZBGET");
	ma.setData("start");
	ma.setRelevance(1.0);
	matches.append(ma);
	m_arguments << "-D";
    }

}

/*
 * Este metodo es llamado cuando el usuario hace click en cualquier entrada, en el runner correspondiente
 */
void mamerunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context)
}

#include "mamerunner.moc"
