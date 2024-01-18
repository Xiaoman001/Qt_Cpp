#include "voicesender.h"

VoiceSender::VoiceSender(QObject *parent)
  : QThread(parent)
{
  // client
  // 创建套接字
  m_pUdpSocket = new QUdpSocket(this);

  // 绑定端口
  m_pUdpSocket->bind(QHostAddress::AnyIPv4, 10005);

  // 目的地址
  m_destAddress.setAddress("127.0.0.1");

  //  m_destAddress.setAddress("192.168.3.15");
}

VoiceSender::~VoiceSender() {
  disconnect(m_pInputDevice, &QIODevice::readyRead,
             this, &VoiceSender::onReadyRead);
}

void VoiceSender::setDestPort(quint16 port)
{
  m_destPort = port;
}

void VoiceSender::setDestAddress(const QString &address)
{
  m_destAddress.setAddress(address);
}

// 看不懂
void VoiceSender::setAudioFormat(int sampleRate, int channelCount, int sampleSize) {
  m_format.setSampleRate(sampleRate);
  m_format.setChannelCount(channelCount);
  m_format.setSampleSize(sampleSize);
  m_format.setCodec("audio/pcm");
  m_format.setSampleType(QAudioFormat::SignedInt);
  m_format.setByteOrder(QAudioFormat::LittleEndian);
  QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
  if (!info.isFormatSupported(m_format)) {
    m_format = info.nearestFormat(m_format);
  }

  // QAudioInput
  m_pAudioInput = new QAudioInput(m_format, this);
}

void VoiceSender::myStart() {
  m_pAudioInput->reset();
  qDebug() << "audio begins to send";
  m_pInputDevice = m_pAudioInput->start();
  connect(m_pInputDevice, &QIODevice::readyRead,
          this, &VoiceSender::onReadyRead);
}

void VoiceSender::myStop() {
  qDebug() << "audio ends!";
  connect(m_pAudioInput, &QAudioInput::stateChanged,
  m_pAudioInput, [this](QAudio::State state) {
    if (QAudio::StoppedState == state) {
      disconnect(m_pInputDevice, &QIODevice::readyRead,
                 this, &VoiceSender::onReadyRead);
      m_pAudioInput->deleteLater();
    }
  });
  m_pAudioInput->stop();
}

// 不明白
void VoiceSender::onReadyRead() {
  video vp;

  // unknown
  memset(&vp.data, 0, sizeof(vp));

  // read audio from input device
  vp.lens = m_pInputDevice->read(vp.data, 960);
  int num = m_pUdpSocket->writeDatagram((const char *)&vp, sizeof(vp), m_destAddress, m_destPort);

  qDebug() << "sender" << num;
}
