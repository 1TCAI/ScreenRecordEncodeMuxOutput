#ifndef AVRECORD_H
#define AVRECORD_H

#include <QObject>
#include <QString>
#include <condition_variable>
#include <atomic>
#include <QMutex>


#include <QDebug>
#include <QAudioDeviceInfo>
#include <thread>
#include <fstream>
#include <QThread>
#include <dshow.h>

extern "C"
{
#endif
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
#include "libavutil/audio_fifo.h"
#include "libavutil/imgutils.h"
#include "libswresample/swresample.h"
#include <libavutil\avassert.h>
#ifdef __cplusplus
};


using namespace std;

class AVRecord : public QObject
{
    Q_OBJECT

private:
    enum RecordState {
        NotStarted,
        Started,
        Paused,
        Stopped,
        Unknown,
    };
public:
    explicit AVRecord(QObject *parent = nullptr);
    void Init(const QVariantMap& map);

signals:

public slots:
    void Start();
    void Pause();
    void Stop();

private:
    //从fifobuf读取音视频帧，写入输出流，复用，生成文件
    void MuxThreadProc();

    int OpenVideo();
    int OpenAudio();
    int OpenOutput();

    void InitVideoBuffer();
    void InitAudioBuffer();

    void ScreenRecordThreadProc();
    void SoundRecordThreadProc();
    void FlushEncoders();
    void Release();

    QString GetSpeakerDeviceName();
//    QString GetMicrophoneDeviceName();

    AVFrame* AllocAudioFrame(AVCodecContext* c, int nbSamples);
    void FlushAudioDecoder();
    void FlushVideoDecoder();

private:
    QString				m_filePath;
    int					m_width;
    int					m_height;
    int					m_fps;
    int					m_audioBitrate;
    int					m_offsetx;
    int					m_offsety;
    int m_vIndex;		//输入视频流索引
    int m_aIndex;		//输入音频流索引
    int m_vOutIndex;	//输出视频流索引
    int m_aOutIndex;	//输出音频流索引
    AVFormatContext		*m_vFmtCtx;
    AVFormatContext		*m_aFmtCtx;
    AVFormatContext		*m_oFmtCtx;
    AVCodecContext		*m_vDecodeCtx;  ///解码器上下文参数
    AVCodecContext		*m_aDecodeCtx;
    AVCodecContext		*m_vEncodeCtx;
    AVCodecContext		*m_aEncodeCtx;
    SwsContext			*m_swsCtx;  ///// 视频颜色空间转换、缩放操作
    SwrContext			*m_swrCtx;  ///// 音频重采样
    AVFifoBuffer		*m_vFifoBuf;    /// 视频共享队列
    AVAudioFifo			*m_aFifoBuf;    /// 音频共享队列

    AVFrame				*m_vOutFrame;
    uint8_t				*m_vOutFrameBuf;
    int					m_vOutFrameSize;

    int					m_nbSamples;
    RecordState			m_state;
    std::condition_variable m_cvNotPause;	//当点击暂停的时候，两个采集线程挂起
    std::mutex				m_mtxPause;


    std::condition_variable m_cvVBufNotFull;
    std::condition_variable m_cvVBufNotEmpty;
    std::mutex				m_mtxVBuf;


    std::condition_variable m_cvABufNotFull;
    std::condition_variable m_cvABufNotEmpty;
    std::mutex				m_mtxABuf;
    int64_t					m_vCurPts;
    int64_t					m_aCurPts;
};

#endif // AVRECORD_H
