#include "updatemodule.h"
#include "updateview.h"

UpdateModule::UpdateModule(FrameProxyInterface *frame, QObject *parent)
    : QObject(parent),
      ModuleInterface(frame),
      m_updateView(nullptr),
      m_updatePage(nullptr),
      m_updateMirrors(nullptr),
      m_mirrorsWidget(nullptr)
{

}

UpdateModule::~UpdateModule()
{
    m_work->deleteLater();
    m_model->deleteLater();

    if (m_updateView)
        m_updateView->deleteLater();
}

void UpdateModule::initialize()
{
    m_model = new UpdateModel();
    m_work = new UpdateWork(m_model);

    m_work->moveToThread(qApp->thread());
    m_model->moveToThread(qApp->thread());
}

void UpdateModule::moduleActive()
{
//    qDebug() << "update active";
}

void UpdateModule::moduleDeactive()
{
    //    qDebug() << "update deactive";
}

void UpdateModule::reset()
{

}

void UpdateModule::contentPopped(ContentWidget * const w)
{
    Q_UNUSED(w);
    if(w == m_updatePage)
        m_updatePage = nullptr;
    else if(w == m_updateMirrors)
        m_updateMirrors = nullptr;
    else if(w == m_mirrorsWidget)
        m_mirrorsWidget = nullptr;

    w->deleteLater();
}

ModuleWidget *UpdateModule::moduleWidget()
{
    if (!m_updateView)
    {
        m_updateView = new UpdateView;

        connect(m_updateView, SIGNAL(pushUpdate()), this, SLOT(onPushUpdate()));
        connect(m_updateView, SIGNAL(pushMirrors()), this, SLOT(onPushSettings()));
    }

    return m_updateView;
}

const QString UpdateModule::name() const
{
    return QStringLiteral("update");
}

void UpdateModule::onPushUpdate()
{
    m_work->checkUpdate();

    if (!m_updatePage)
    {
        m_updatePage = new UpdateCtrlWidget;
        connect(m_model, &UpdateModel::appInfos, m_updatePage, &UpdateCtrlWidget::loadAppList);
        connect(m_model, &UpdateModel::packageDownloadSize, m_updatePage, &UpdateCtrlWidget::onPackagesDownloadSize);
        connect(m_model, &UpdateModel::progressChanged, m_updatePage, &UpdateCtrlWidget::updateDownloadProgress);
        connect(m_updatePage, &UpdateCtrlWidget::actionType, this, &UpdateModule::onActionType);
        connect(m_model, &UpdateModel::statusChanged, m_updatePage, &UpdateCtrlWidget::onStatus);
    }

    m_frameProxy->pushWidget(this, m_updatePage);
}

void UpdateModule::onPushMirror()
{
    if(!m_mirrorsWidget)
    {
        m_mirrorsWidget = new MirrorsWidget();
        m_mirrorsWidget->setDefaultMirror(m_work->defaultMirror());
        m_mirrorsWidget->setMirrorInfoList(m_work->mirrorInfos());
        connect(m_mirrorsWidget, SIGNAL(mirrorName(QString, QString)), this, SLOT(setCurMirrorName(QString, QString)));
    }

    m_frameProxy->pushWidget(this, m_mirrorsWidget);
}

void UpdateModule::onPushSettings()
{
    if(!m_updateMirrors)
    {
        m_updateMirrors = new UpdateSettings(m_model);
        m_updateMirrors->setDefaultMirror(m_model->mirror());
        m_updateMirrors->setAutoUpdate(m_work->autoUpdate());
        connect(m_updateMirrors, SIGNAL(mirrors()), this, SLOT(onPushMirror()));
        connect(m_updateMirrors, SIGNAL(autoUpdate(bool)), this, SLOT(setAutoUpdate(bool)));
    }

    m_frameProxy->pushWidget(this, m_updateMirrors);
}

void UpdateModule::setCurMirrorName(const QString &name, const QString& src)
{
    if(m_updateMirrors)
    {
        m_updateMirrors->setDefaultMirror(name);
        m_work->setMirrorSource(src);
    }
}

void UpdateModule::setAutoUpdate(bool autoUpdate)
{
    m_work->setAutoUpdate(autoUpdate);
}

void UpdateModule::onActionType(UpdateType type)
{
    if(type == UpdateType::CheckUpdate)
    {
        m_work->prepareDistUpgrade();
        if(m_updatePage)
        {
            m_updatePage->setCurState(UpdateType::StartDownload);
        }
    }
    else if(type == UpdateType::StartDownload)
    {
        if(m_work->pauseJob())
        {
            if(m_updatePage)
            {
                m_updatePage->setCurState(UpdateType::StopDownload);
            }
        }
    }
    else if(type == UpdateType::StopDownload)
    {

        if(m_work->startJob())
        {
            if(m_updatePage)
            {
                m_updatePage->setCurState(UpdateType::StartDownload);
            }
        }
    }
    else
    {
        QProcess::startDetached("/usr/lib/deepin-daemon/dde-offline-upgrader");
    }
}