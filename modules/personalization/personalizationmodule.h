#ifndef PERSONALIZATIONMODULE_H
#define PERSONALIZATIONMODULE_H

#include "moduleinterface.h"
#include "personalizationwidget.h"
#include "personalizationmodel.h"
#include "personalizationwork.h"

#include "module/themewidget/themewidget.h"
#include "module/fontswidget/fontswidget.h"
#include "module/fontswidget/fontlistwidget.h"

namespace dcc
{
namespace personalization
{
class PersonalizationModule : public QObject, public ModuleInterface
{
    Q_OBJECT

public:
    explicit PersonalizationModule(FrameProxyInterface *frame, QObject *parent = 0);

    void initialize();
    void moduleActive();
    void moduleDeactive();
    void reset();

    ModuleWidget *moduleWidget();

    const QString name() const;

private:
    void showThemeWidget();
    void showFontsWidget();
    void showStanardFontsListWidget();
    void showMonoFontsListWidget();

private:
    ~PersonalizationModule();

    void contentPopped(ContentWidget *const w);

private:

    PersonalizationWidget *m_personalizationWidget;
    PersonalizationModel  *m_model;
    PersonalizationWork   *m_work;
};
}
}


#endif // PERSONALIZATIONMODULE_H