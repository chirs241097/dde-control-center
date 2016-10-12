#include "mainwidget.h"

#include <dimagebutton.h>

DWIDGET_USE_NAMESPACE

MainWidget::MainWidget(Frame *parent)
    : FrameWidget(parent),

      m_pluginsController(new PluginsController(this)),

      m_lastPluginWidget(nullptr),

      m_userAvatarBtn(new DImageButton),
      m_currentTimeLbl(new QLabel),
      m_currentDateLbl(new QLabel),
      m_pluginsLayout(new QHBoxLayout),
      m_pluginsIndicator(new DPageIndicator),
      m_nextPluginBtn(new QPushButton),
      m_allSettingsBtn(new QPushButton)
{
    m_nextPluginBtn->setText("Next");
    m_allSettingsBtn->setText("All settings");

    m_userAvatarBtn->setPixmap(QPixmap());
    m_currentTimeLbl->setText("time");
    m_currentDateLbl->setText("date");

    m_pluginsIndicator->setFixedHeight(20);
    m_pluginsIndicator->setPageCount(4);
    m_pluginsIndicator->setCurrentPage(0);

    QVBoxLayout *timedateLayout = new QVBoxLayout;
    timedateLayout->addWidget(m_currentTimeLbl);
    timedateLayout->addWidget(m_currentDateLbl);
    timedateLayout->setSpacing(0);
    timedateLayout->setMargin(0);

    QHBoxLayout *headerLayout = new QHBoxLayout;
    headerLayout->addWidget(m_userAvatarBtn);
    headerLayout->addLayout(timedateLayout);
    headerLayout->setSpacing(0);
    headerLayout->setMargin(0);

    QVBoxLayout *centeralLayout = static_cast<QVBoxLayout *>(layout());
    centeralLayout->addLayout(headerLayout);
    centeralLayout->addLayout(m_pluginsLayout);
    centeralLayout->addWidget(m_pluginsIndicator);
    centeralLayout->addWidget(m_nextPluginBtn);
    centeralLayout->addWidget(m_allSettingsBtn);
    centeralLayout->setSpacing(0);
    centeralLayout->setMargin(0);

    connect(m_pluginsController, &PluginsController::pluginAdded, this, &MainWidget::pluginAdded);
    connect(m_nextPluginBtn, &QPushButton::clicked, this, &MainWidget::showNextPlugin);
    connect(m_allSettingsBtn, &QPushButton::clicked, this, &MainWidget::showAllSettings);

    m_pluginsController->loadPlugins();
}

void MainWidget::showPlugin(QWidget * const w)
{
    if (m_lastPluginWidget)
        m_lastPluginWidget->setVisible(false);
    m_lastPluginWidget = w;
    m_lastPluginWidget->setVisible(true);
}

void MainWidget::pluginAdded(QWidget * const w)
{
    // TODO: fixed height
    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pluginsLayout->addWidget(w);
    showPlugin(w);
}

void MainWidget::showNextPlugin()
{
    m_pluginsIndicator->nextPage();

    const int index = m_pluginsLayout->indexOf(m_lastPluginWidget);
    QLayoutItem *item = m_pluginsLayout->itemAt(index + 1);
    if (item && item->widget())
        showPlugin(item->widget());
    else
        showPlugin(m_pluginsLayout->itemAt(0)->widget());
}
