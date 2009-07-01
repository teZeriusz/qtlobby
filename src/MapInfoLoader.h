#ifndef MAPINFOLOADER_H
#define MAPINFOLOADER_H

#include <QThread>
#include "UnitSyncLib.h"
#include "RawHeightMap.h"

class MapInfoLoader : public QThread {
    Q_OBJECT
public:
    MapInfoLoader(QObject* parent = 0);
    void setMap(QString mapName);
    void cleanup();
    bool mapPresent;
    QImage minimap;
    QImage heightmap;
    RawHeightMap rawHeightmap;
    QImage metalmap;
    MapInfo mapinfo;
    void run();
signals:
    void loadCompleted(QString mapName);
private slots:
    void clearData();
private:
    bool m_autoclean;
    QString m_mapName;
    char m_description[255];
    char m_author[200];
};

#endif // MAPINFOLOADER_H