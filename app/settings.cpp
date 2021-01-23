#include "settings.h"

#include <QApplication>
#include <QStandardPaths>
#include <QDebug>
#include <QDir>

Settings *Settings::m_settings_instance = nullptr;

Settings *Settings::instance()
{
    if (!m_settings_instance) {
        m_settings_instance = new Settings;
    }

    return m_settings_instance;
}

bool Settings::stayOnTop()
{
    return m_qsettings->value("stay_on_top", true).toBool();
}

DoubleClickBehavior Settings::doubleClickBehavior()
{
    QString result = m_qsettings->value("double_click_behavior", "close").toString().toLower();

    return stringToDoubleClickBehavior(result);
}

MouseWheelBehavior Settings::mouseWheelBehavior()
{
    QString result = m_qsettings->value("mouse_wheel_behavior", "close").toString().toLower();

    return stringToMouseWheelBehavior(result);
}

void Settings::setStayOnTop(bool on)
{
    m_qsettings->setValue("stay_on_top", on);
    m_qsettings->sync();
}

void Settings::setDoubleClickBehavior(DoubleClickBehavior dcb)
{
    m_qsettings->setValue("double_click_behavior", doubleClickBehaviorToString(dcb));
    m_qsettings->sync();
}

void Settings::setMouseWheelBehavior(MouseWheelBehavior mwb)
{
    m_qsettings->setValue("mouse_wheel_behavior", mouseWheelBehaviorToString(mwb));
    m_qsettings->sync();
}

QString Settings::doubleClickBehaviorToString(DoubleClickBehavior dcb)
{
    static QMap<DoubleClickBehavior, QString> _map {
        {ActionCloseWindow, "close"},
        {ActionMaximizeWindow, "maximize"},
        {ActionDoNothing, "ignore"}
    };

    return _map.value(dcb, "close");
}

QString Settings::mouseWheelBehaviorToString(MouseWheelBehavior mwb)
{
    static QMap<MouseWheelBehavior, QString> _map {
        {ActionZoomImage, "zoom"},
        {ActionPrevNextImage, "switch"}
    };

    return _map.value(mwb, "zoom");
}

DoubleClickBehavior Settings::stringToDoubleClickBehavior(QString str)
{
    static QMap<QString, DoubleClickBehavior> _map {
        {"close", ActionCloseWindow},
        {"maximize", ActionMaximizeWindow},
        {"ignore", ActionDoNothing}
    };

    return _map.value(str, ActionCloseWindow);
}

MouseWheelBehavior Settings::stringToMouseWheelBehavior(QString str)
{
    static QMap<QString, MouseWheelBehavior> _map {
        {"zoom", ActionZoomImage},
        {"switch", ActionPrevNextImage}
    };

    return _map.value(str, ActionZoomImage);
}

Settings::Settings()
    : QObject(qApp)
{
    QString configPath;

#ifdef FLAG_PORTABLE_MODE_SUPPORT
    QString portableConfigDirPath = QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("data");
    QFileInfo portableConfigDirInfo(portableConfigDirPath);
    if (portableConfigDirInfo.exists() && portableConfigDirInfo.isDir() && portableConfigDirInfo.isWritable()) {
        // we can use it.
        configPath = portableConfigDirPath;
    }
#endif // FLAG_PORTABLE_MODE_SUPPORT

    // %LOCALAPPDATA% under Windows.
    if (configPath.isEmpty()) {
        configPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    }

    m_qsettings = new QSettings(QDir(configPath).absoluteFilePath("config.ini"), QSettings::IniFormat, this);
}

