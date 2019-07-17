#ifndef MIREJTIMER_H
#define MIREJTIMER_H
#pragma once

#include <Windows.h>

//-----------------------------------------------------------------------------
// ����: MirEjTimer
// ����: �߾��ȼ�ʱ����
//       ����Ϊ�߾��ȼ�ʱ��, ��ҪӲ��֧��, ��ĳЩ���ù��͵Ļ����Ͽ����޷�����.
//       �����ʹ�÷�ʽ��ȫ����һ����׼���, ֧�ֿ�ʼ/ֹͣ/��ͣ/�����Ȳ���.
//-----------------------------------------------------------------------------
class MirEjTimer
{

private:
	enum TimerStatus { tsRun, tsStop, tsPause };

	static __int64		m_n64Freq;		// ��ʱ��Ƶ��
	__int64				m_n64TimeBegin;			// ��ʼʱ��
	__int64				m_n64TimeEnd;			// ֹͣʱ��
	int					m_nPrecision;				// ��ʱ������
	TimerStatus			m_TimerStatus;		// ��ʱ��״̬

	__int64 GetCurrentCount();

	// ����/������������
public:
	MirEjTimer(int nPrecision = 10000, bool bPlay = true);
	~MirEjTimer();

	//���ü�ʱ������
	inline void SetPrecision(int nPrecision = 10000) { m_nPrecision = nPrecision;}

	// ȡ��ʱ������
	inline int GetPrecision() const { return m_nPrecision; }

	// ȡ��ǰ��ʱ������
	DWORD GetTime();

	// ��ʼ��ʱ
	void Play();

	// ֹͣ��ʱ
	void Stop();

	// ��ͣ��ʱ
	void Pause();
};
#endif // !MIREJTIMER_H