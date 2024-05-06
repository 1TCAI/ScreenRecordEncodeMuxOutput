#ifndef AVFMPGSCREENRECORD_H
#define AVFMPGSCREENRECORD_H

#include <QObject>

class AVFmpgScreenRecord : public QObject
{
    Q_OBJECT
public:
    explicit AVFmpgScreenRecord(QObject *parent = nullptr);

signals:

public slots:
};

#endif // AVFMPGSCREENRECORD_H
