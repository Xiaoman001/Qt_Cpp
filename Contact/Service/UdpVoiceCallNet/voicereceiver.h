#ifndef VOICERECEIVER_H
#define VOICERECEIVER_H

// 这是接收线程
#include <QThread>
#include <QObject>
#include <QAudioFormat>
#include <QAudioOutput>
#include <QMutex>
#include <QMutexLocker>
#include <QByteArray>

#include <QtNetwork/QUdpSocket>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QDebug>

#define MAX_AUDIO_LEN 960000 // 如果接收缓冲区大于这个数值就剪掉
#define FRAME_LEN_60ms 960   // 每一个语音帧长度是960字节

class VoiceReceiver : public QThread
{
  Q_OBJECT

 public:
  explicit VoiceReceiver(QObject *parent = nullptr);
  ~VoiceReceiver();

  // ----------- 添加数据相关 ----------------------------------------
  // 设置当前的PCM Buffer
  void setCurrentBuffer(QByteArray buffer);

  // 添加数据
  void addAudioBuffer(char *pData,
                      int   len);

  // 清空当前的数据
  void cleanAllAudioBuffer(void);

  // ------------- End ----------------------------------------------

  // 设置当前的采样率、采样位数、通道数目
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
  void setCurrentSampleInfo(int sampleRate,
                            int channelCount,
                            int sampleSize);

  virtual void run(void) override;

  // 设置音量
  void         setCurrentVolumn(qreal volumn);

  void         stop(); // 停止
  void exitRun();

 private:

  QAudioOutput *m_pVoiceOutput = nullptr;
  QIODevice *m_pAudioIo   = nullptr;

  QByteArray m_PcmDataBuffer;
  int m_currentPlayIndex = 0;

  QMutex m_mutex;

  // 播放状态
  volatile bool m_isPlaying = true;

  // for Audio

  struct video {
    int  lens;
    char data[960];
  };

  // udp
  QUdpSocket *m_pUdpsocket;
  quint16 m_receivePort = 10004;
  void setReceivePort(quint16 port);
 private slots:

  void readyReadSlot();
 signals:
  void talkingSignal(bool isTalking);
};

#endif // VOICERECEIVER_H
