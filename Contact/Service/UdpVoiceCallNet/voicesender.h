#ifndef VOICESENDER_H
#define VOICESENDER_H
// 这是发送线程

#include <QObject>
#include <QThread>
#include <QDebug>

#include <QAudio>
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioOutput>
#include <QIODevice>

// #include <QtNetwork/QUdpSocket>
#include <QtNetwork>
#include <QUdpSocket>
#include <QHostAddress>

class VoiceSender : public QThread {
  Q_OBJECT

 public:

  explicit VoiceSender(QObject *parent = nullptr);
  ~VoiceSender();
  // udp 套接字
  QUdpSocket *m_pUdpSocket = Q_NULLPTR;
  quint16 m_destPort = 10004;

  // 目的地址
  QHostAddress m_destAddress;
  void setDestPort(quint16 port);
  void setDestAddress(const QString &address);

  QAudioInput *m_pAudioInput = Q_NULLPTR;
  QIODevice *m_pInputDevice  = Q_NULLPTR;
  QAudioFormat m_format;

  // 自定义存放数据的结构体
  struct video {
    int  lens;
    char data[960];
  };

  /*
   * @brief 设置发送端audio格式
   * @param sampleRate, int
   * @note 采样频率，一般实际应用中保证采样频率为信号最高频率的2.56～4倍
   * @param channelCount, int
   * @note 指声音在录制或播放时，在不同空间位置采集或回放的相互独立的音频信号，
   *       常见的有单声道，双声道，四声道，这个倒是声道越多效果越好。
   * @param sampleSize, int
   * @note 每个样本的大小，也就是振幅，
   *       假如样本大小为16 Bit = 2 ^ 16 = 65536，
   *       即能够记录 65535 个数，
   *       常见的有 8Bit、16Bit( CD级 )，而到了 32Bit 意义就不大了
   */
  void setAudioFormat(int sampleRate,
                      int channelCount,
                      int sampleSize);
  void myStart();
  void myStop();

 public slots:

  void onReadyRead();
};

#endif // VOICESENDER_H
