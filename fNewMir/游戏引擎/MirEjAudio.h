#ifndef MIREJAUDIO_H
#define MIREJAUDIO_H
#pragma once

#include "MirEjHead.h"
#include "其它文件\WavFile.h"

class MirEjAudio
{
public:
	MirEjAudio();
	~MirEjAudio();

	void		Init();//初始化音频
	void		Update();//放到msg循环里面，一般放在fps循环那里
	void		SendWav(LPWSTR, bool t = false, bool b = false);//发送声音 t=true背景音 t=false效果音 b是否循环
	void		Release();
	void		SetMaster(bool b) { _masterenabled = b; SubmitVolume(); }
	bool		SetMaster() { return _masterenabled; }
	void		SetEffect(bool b) { _effectenabled = b; SubmitVolume(); }
	bool		SetEffect() { return _effectenabled; }
private:
	void		SubmitMaster();
	void		SubmitEffect();
	void		SubmitVolume();

	IXAudio2*					_AudioEJ;		//声音引擎
	IXAudio2MasteringVoice*		_pmastervoice;	//主声音通道
	bool						_AudioRead;		//启用音频
	IXAudio2SourceVoice*		_pmastersource;	//背景音音源
	IXAudio2SourceVoice*		_peffectsource;	//效果音音源
	bool						_masterread;	//背景音准备
	bool						_effectread;	//效果音准备
	bool						_masterenabled;	//允许背景音
	bool						_effectenabled;	//允许效果音
	bool						_masterloop;	//背景音循环
	bool						_effectloop;	//效果音循环

	LPWSTR						_mastermusic;	//背景音
	WAVEFORMATEX*				_masterpwfx;	//背景音文件格式
	XAUDIO2_BUFFER				_masterbuffer;	//背景音缓存
	XAUDIO2_VOICE_STATE			_masterstate;	//背景音状态

	LPWSTR						_effectmusic;	//效果音
	WAVEFORMATEX*				_effectpwfx;	//效果音文件格式
	XAUDIO2_BUFFER				_effectbuffer;	//效果音缓存
	XAUDIO2_VOICE_STATE			_effectstate;	//效果音状态
};
#endif // !MIREJAUDIO_H