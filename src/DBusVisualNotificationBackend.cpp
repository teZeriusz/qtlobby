#include "DBusVisualNotificationBackend.h"
#include <QVariantList>

void DBusVisualNotificationBackend::showMessage(QString& title, QString& message, int timeout_ms)
{
    QString icon_path = QString();
    showMessage(title, message, icon_path, timeout_ms);
}

void DBusVisualNotificationBackend::showMessage(QString& title, QString& message, QString& icon_path, int timeout_ms)
{
    // TODO: Check if DBus is available

    // Use session bus
    m_notify = new QDBusInterface("org.kde.VisualNotifications", "/VisualNotifications", "org.kde.VisualNotifications");

    unsigned int replaces_id = 0;

    QVariantList args;
    args.append("QtLobby");      //QString app_name
    args.append(replaces_id);   //uint replaces_id
    args.append("");      //QString event_id
    args.append(icon_path);      //QString app_icon
    args.append(title);       //QString summary
    args.append(message);          //QString body
    args.append(QStringList());       //QStringList actions
    args.append(QVariantMap());         //QVariantMap hints
    args.append(timeout_ms);       //int timeout

    QDBusMessage replay = m_notify->callWithArgumentList(QDBus::AutoDetect, "Notify", args);

    if(replay.errorMessage() != "")
    {
        // TODO: Handle error
        qDebug() << replay.errorName() << " from DBus: " << replay.errorMessage();
        // TODO: Report an fallback error to the notification clas
    }
}
