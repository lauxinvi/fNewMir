#ifndef MIREJTIMER_H
#define MIREJTIMER_H
#pragma once

#include <Windows.h>

//-----------------------------------------------------------------------------
// 类名: MirEjTimer
// 功能: 高精度计时器类
//       本类为高精度计时器, 需要硬件支持, 在某些配置过低的机器上可能无法运行.
//       本类的使用方式完全类似一个标准秒表, 支持开始/停止/暂停/读数等操作.
//-----------------------------------------------------------------------------
class MirEjTimer
{

private:
	enum TimerStatus { tsRun, tsStop, tsPause };

	static __int64		m_n64Freq;		// 计时器频率
	__int64				m_n64TimeBegin;			// 开始时刻
	__int64				m_n64TimeEnd;			// 停止时刻
	int					m_nPrecision;				// 计时器精度
	TimerStatus			m_TimerStatus;		// 计时器状态

	__int64 GetCurrentCount();

	// 构造/析构函数定义
public:
	MirEjTimer(int nPrecision = 10000, bool bPlay = true);
	~MirEjTimer();

	//设置计时器精度
	inline void SetPrecision(int nPrecision = 10000) { m_nPrecision = nPrecision;}

	// 取计时器精度
	inline int GetPrecision() const { return m_nPrecision; }

	// 取当前计时器读数
	DWORD GetTime();

	// 开始计时
	void Play();

	// 停止计时
	void Stop();

	// 暂停计时
	void Pause();
};
#endif // !MIREJTIMER_H