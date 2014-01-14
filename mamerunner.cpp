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


void mamerunner::match(Plasma::RunnerContext &context)
{

    const QString term = context.query();
    if (term.length() < 3) {
        return;
    }
    //TODO
}

void mamerunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context)
}

#include "mamerunner.moc"
