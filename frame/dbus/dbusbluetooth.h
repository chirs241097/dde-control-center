/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -c DBusBluetooth -p DBusBluetooth com.deepin.daemon.Bluetooth.xml
 *
 * qdbusxml2cpp is Copyright (C) 2015 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef DBUSBLUETOOTH_H_1447678191
#define DBUSBLUETOOTH_H_1447678191

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface com.deepin.daemon.Bluetooth
 */
class DBusBluetooth: public QDBusAbstractInterface
{
    Q_OBJECT

    Q_SLOT void __propertyChanged__(const QDBusMessage &msg)
    {
        QList<QVariant> arguments = msg.arguments();
        if (3 != arguments.count()) {
            return;
        }
        QString interfaceName = msg.arguments().at(0).toString();
        if (interfaceName != "com.deepin.daemon.Bluetooth") {
            return;
        }
        QVariantMap changedProps = qdbus_cast<QVariantMap>(arguments.at(1).value<QDBusArgument>());
        QStringList keys = changedProps.keys();
        foreach(const QString & prop, keys) {
            const QMetaObject *self = metaObject();
            for (int i = self->propertyOffset(); i < self->propertyCount(); ++i) {
                QMetaProperty p = self->property(i);
                if (p.name() == prop) {
                    Q_EMIT p.notifySignal().invoke(this);
                }
            }
        }
    }
public:
    static inline const char *staticInterfaceName()
    { return "com.deepin.daemon.Bluetooth"; }

public:
    DBusBluetooth(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~DBusBluetooth();

    Q_PROPERTY(uint State READ state NOTIFY StateChanged)
    inline uint state() const
    { return qvariant_cast< uint >(property("State")); }

public Q_SLOTS: // METHODS
Q_SIGNALS: // SIGNALS
// begin property changed signals
    void StateChanged();
};

namespace com
{
namespace deepin
{
namespace daemon
{
typedef ::DBusBluetooth Bluetooth;
}
}
}
#endif
