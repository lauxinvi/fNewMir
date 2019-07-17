#include "..\MirEjTimer.h"

// �ྲ̬��������
_int64 MirEjTimer::m_n64Freq = 0;

//-----------------------------------------------------------------------------
// ������: MirEjTimer::MirEjTimer()
// ��  ��: ���캯��
// ��  ��: [void] - ��
// ����ֵ: [void] - ��
//         ʧ�����׳�EJMSimpleException�쳣
//-----------------------------------------------------------------------------
MirEjTimer::MirEjTimer(int nPrecision, bool bPlay)
	: m_n64TimeBegin(0)
	, m_n64TimeEnd(0)
	, m_TimerStatus(tsStop)
{
	if (m_n64Freq == 0)
	{
		LARGE_INTEGER tmp;
		QueryPerformanceFrequency(&tmp);
		m_n64Freq = tmp.QuadPart;
	}

	m_nPrecision = nPrecision;

	if (bPlay)
	{
		Play();
	}
}

//-----------------------------------------------------------------------------
// ������: MirEjTimer::~MirEjTimer()
// ��  ��: ��������
// ��  ��: [void] - ��
// ����ֵ: [void] - ��
//-----------------------------------------------------------------------------
MirEjTimer::~MirEjTimer()
{
}

//-----------------------------------------------------------------------------
// ������: MirEjTimer::GetTime()
// ��  ��: ȡ��ǰ��ʱ������, ��ֵ���Ծ�����Ϊ����
// ��  ��: [void] - ��
// ����ֵ: [DWORD] - ����ʱ����������״̬, �򷵻ؿ�ʼ����ǰʱ�̵ļ���ֵ
//                   ����ʱ����ֹͣ, �򷵻شӿ�ʼ��ֹͣʱ�̵ļ���ֵ
//-----------------------------------------------------------------------------
DWORD MirEjTimer::GetTime()
{
	if (m_TimerStatus != tsRun)
	{
		return DWORD((m_n64TimeEnd - m_n64TimeBegin) * m_nPrecision / m_n64Freq);
	}
	else
	{
		return DWORD((GetCurrentCount() - m_n64TimeBegin) * m_nPrecision / m_n64Freq);
	}
}

//-----------------------------------------------------------------------------
// ������: MirEjTimer::Play()
// ��  ��: ��ʼ��ʱ
// ��  ��: [void] - ��
// ����ֵ: [void] - ��
//-----------------------------------------------------------------------------
void MirEjTimer::Play()
{
	if (m_TimerStatus == tsStop)
	{
		m_n64TimeBegin = GetCurrentCount();
	}
	m_TimerStatus = tsRun;
}

//-----------------------------------------------------------------------------
// ������: MirEjTimer::Stop()
// ��  ��: ֹͣ��ʱ
// ��  ��: [void] - ��
// ����ֵ: [void] - ��
//-----------------------------------------------------------------------------
void MirEjTimer::Stop()
{
	m_n64TimeEnd = GetCurrentCount();
	m_TimerStatus = tsStop;
}

//-----------------------------------------------------------------------------
// ������: MirEjTimer::Pause()
// ��  ��: ��ͣ��ʱ
// ��  ��: [void] - ��
// ����ֵ: [void] - ��
//-----------------------------------------------------------------------------
void MirEjTimer::Pause()
{
	m_n64TimeEnd = GetCurrentCount();
	m_TimerStatus = tsPause;
}

//-----------------------------------------------------------------------------
// ������: MirEjTimer::GetCurrentCount()
// ��  ��: ȡϵͳ��ʱ���ļ���ֵ
// ��  ��: [void] - ��
// ����ֵ: [__int64] - ϵͳ��ʱ���ļ���ֵ
//-----------------------------------------------------------------------------
__int64 MirEjTimer::GetCurrentCount()
{
	LARGE_INTEGER tmp;
	QueryPerformanceCounter(&tmp);
	return tmp.QuadPart;
}