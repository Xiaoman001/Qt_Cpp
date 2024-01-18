#include "voicereceiver.h"
#include <QTimer>

VoiceReceiver::VoiceReceiver(QObject *parent)
  : QThread(parent)
{
  m_PcmDataBuffer.clear();

  // 创建套接字
  m_pUdpsocket = new QUdpSocket(this);

  // 绑定端口
  m_pUdpsocket->bind(QHostAddress::AnyIPv4, m_receivePort);

  // 收到网络数据报就开始往outputDevice写入，进行播放
  connect(m_pUdpsocket, &QUdpSocket::readyRead,
          this, &VoiceReceiver::readyReadSlot);

  auto pTimer = new QTimer(this);
  connect(pTimer, &QTimer::timeout, this, []() {
    qDebug() << "-------------";
  });
  pTimer->start(1000);
}

VoiceReceiver::~VoiceReceiver()
{
  //  disconnect(m_pUdpsocket, &QUdpSocket::readyRead,
  //             this, &VoiceReceiver::readyReadSlot);

  //  delete m_pUdpsocket;
  //  delete m_pVoiceOutput;
  //  delete m_pAudioIo;
}

void VoiceReceiver::setCurrentVolumn(qreal volumn) {
  m_pVoiceOutput->setVolume(volumn);
}

void VoiceReceiver::setCurrentSampleInfo(int sampleRate, int channelCount, int sampleSize)
{
  QMutexLocker locker(&m_mutex);

  // Format
  QAudioFormat nFormat;
  nFormat.setSampleRate(sampleRate);
  nFormat.setChannelCount(channelCount);
  nFormat.setSampleSize(sampleSize);
  nFormat.setCodec("audio/pcm");
  nFormat.setSampleType(QAudioFormat::SignedInt);
  nFormat.setByteOrder(QAudioFormat::LittleEndian);

  if (m_pVoiceOutput != nullptr) delete m_pVoiceOutput;

  // QAudioOutput
  m_pVoiceOutput = new QAudioOutput(nFormat, this);
  m_pAudioIo     = m_pVoiceOutput->start();
}

void VoiceReceiver::run(void)
{
  qDebug() << "*************";
  if (m_isPlaying) {
    emit this->talkingSignal(m_isPlaying);
  }
  while (!this->isInterruptionRequested())
  {
    if (!m_isPlaying) {
      break;
    }
    QMutexLocker locker(&m_mutex);

    // 缓冲区不够播放60ms音频
    if (m_PcmDataBuffer.size() < m_currentPlayIndex + FRAME_LEN_60ms) {
      continue;
    } else {
      // 拷贝960字节的数据
      char *writeData = new char[FRAME_LEN_60ms];
      memcpy(writeData, &m_PcmDataBuffer.data()[m_currentPlayIndex], FRAME_LEN_60ms);

      // 写入音频数据
      m_pAudioIo->write(writeData, FRAME_LEN_60ms);
      m_currentPlayIndex += FRAME_LEN_60ms;

      qDebug() << m_currentPlayIndex;
      delete[]writeData;

      // 如果长度超过了MAX_AUDIO_LEN就从
      if (m_currentPlayIndex > MAX_AUDIO_LEN) {
        m_PcmDataBuffer     = m_PcmDataBuffer.right(m_PcmDataBuffer.size() - MAX_AUDIO_LEN);
        m_currentPlayIndex -= MAX_AUDIO_LEN;
      }
    }
  }
  m_PcmDataBuffer.clear();
  qDebug() << "receiver run over!";
}

// 添加数据
void VoiceReceiver::addAudioBuffer(char *pData, int len)
{
  QMutexLocker locker(&m_mutex);
  m_PcmDataBuffer.append(pData, len);

  // m_IsPlaying = true;
}

void VoiceReceiver::cleanAllAudioBuffer(void)
{
  QMutexLocker locker(&m_mutex);
  m_currentPlayIndex = 0;
  m_PcmDataBuffer.clear();
  m_isPlaying = false;
}

void VoiceReceiver::readyReadSlot() {
  while (m_pUdpsocket->hasPendingDatagrams()) {
    QHostAddress senderIp;
    quint16 senderPort;

    qDebug() << "audio is being received..." << endl;
    video vp;
    memset(&vp, 0, sizeof(vp));
    m_pUdpsocket->readDatagram((char *)&vp, sizeof(vp), &senderIp, &senderPort);

    // outputDevice->write(vp.data,vp.lens);
    this->addAudioBuffer(vp.data, vp.lens);
  }
}

void VoiceReceiver::stop() {
  // 关闭套接字
  m_pUdpsocket->close();
  m_pVoiceOutput->stop();
  this->cleanAllAudioBuffer();
}

void VoiceReceiver::exitRun()
{
  m_isPlaying = false;
  emit this->talkingSignal(m_isPlaying);
  this->quit();
  this->wait();
  qDebug() << "receive thread exit";
}

void VoiceReceiver::setReceivePort(quint16 port)
{
  m_receivePort = port;
}
