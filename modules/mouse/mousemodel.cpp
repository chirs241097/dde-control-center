#include "mousemodel.h"

MouseModel::MouseModel(QObject *parent)
    :QObject(parent)
{
    m_baseSettings  = new MouseModelBaseSettings(this);
    m_mouseSettings = new MouseModelMouseSettings(this);
    m_touchSettings = new MouseModelMouseSettings(this);
    m_trackSettings = new MouseModelThinkpadSettings(this);
}

MouseModel::~MouseModel()
{

}

MouseModelBaseSettings *MouseModel::getBaseSettings() const
{
    return m_baseSettings;
}

MouseModelMouseSettings *MouseModel::getMouseSettings() const
{
    return m_mouseSettings;
}

MouseModelMouseSettings *MouseModel::getTouchSettings() const
{
    return m_touchSettings;
}

MouseModelThinkpadSettings *MouseModel::getTrackSettings() const
{
    return m_trackSettings;
}
