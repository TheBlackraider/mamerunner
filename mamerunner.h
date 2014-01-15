
#ifndef MAMERUNNER_H
#define MAMERUNNER_H

#include <plasma/abstractrunner.h>
#include <KIcon>
#include <QFile>
#include <QXmlStreamReader>
#include <QString>

// Define our plasma Runner
class mamerunner : public Plasma::AbstractRunner {
    Q_OBJECT

private:
  QFile* mameListFile;
  QFile* configfile;

  
public:
    // Basic Create/Destroy
    mamerunner( QObject *parent, const QVariantList& args );
    ~mamerunner();

    void match(Plasma::RunnerContext &context);
    void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match);
};
// This is the command that links your applet to the .desktop file
K_EXPORT_PLASMA_RUNNER(mamerunner, mamerunner)

#endif
