#ifndef TELLOSTATE_H
#define TELLOSTATE_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <Tello/TelloEnumTypes.h>

class TelloState : public QObject
{
    Q_OBJECT
public:
    TelloState(QHostAddress a, quint16 p);
    ~TelloState();

    // Getter functions for int variables
    int getMid() { return mid; }
    int getX() { return x; }
    int getY() { return y; }
    int getZ() { return z; }
    int getPitch() { return pitch; }
    int getRoll() { return roll; }
    int getYaw() { return yaw; }
    int getTempLowest() { return templ; }
    int getTempHighest() { return temph; }
    int getDistanceTof() { return tof; }
    int getHeight() { return h; }
    int getBattery() { return bat; }

    // Getter functions for double variables
    double *getMpry() { return mpry; }
    double getVgx() { return vgx; }
    double getVgy() { return vgy; }
    double getVgz() { return vgz; }
    double getBaro() { return baro; }
    double getTime() { return time; }
    double getAgx() { return agx; }
    double getAgy() { return agy; }
    double getAgz() { return agz; }

    void resetVariables();
private:
    QUdpSocket *socket;
    QHostAddress ip;
    quint16 port;

    bool isRunning, sdk_mode_enabled, wifi_snr_requested;
    int mid, x, y, z, pitch, roll, yaw, templ, temph, tof, h, bat, snrValue;
    double mpry[3], vgx, vgy, vgz, baro, time, agx, agy, agz;

    QTimer *timer;
    qint64 lastTimeResponseReceived;
    void timeoutCheck();

    void readResponse();
    void parseStatus(QString str);

signals:
    void dataAvailable();
    void status(TelloStatus);

};

#endif // TELLOSTATE_H
