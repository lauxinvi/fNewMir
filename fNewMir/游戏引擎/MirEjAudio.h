#ifndef MIREJAUDIO_H
#define MIREJAUDIO_H
#pragma once

#include "MirEjHead.h"
#include "�����ļ�\WavFile.h"

class MirEjAudio
{
public:
	MirEjAudio();
	~MirEjAudio();

	void		Init();//��ʼ����Ƶ
	void		Update();//�ŵ�msgѭ�����棬һ�����fpsѭ������
	void		SendWav(LPWSTR, bool t = false, bool b = false);//�������� t=true������ t=falseЧ���� b�Ƿ�ѭ��
	void		Release();
	void		SetMaster(bool b) { _masterenabled = b; SubmitVolume(); }
	bool		SetMaster() { return _masterenabled; }
	void		SetEffect(bool b) { _effectenabled = b; SubmitVolume(); }
	bool		SetEffect() { return _effectenabled; }
private:
	void		SubmitMaster();
	void		SubmitEffect();
	void		SubmitVolume();

	IXAudio2*					_AudioEJ;		//��������
	IXAudio2MasteringVoice*		_pmastervoice;	//������ͨ��
	bool						_AudioRead;		//������Ƶ
	IXAudio2SourceVoice*		_pmastersource;	//��������Դ
	IXAudio2SourceVoice*		_peffectsource;	//Ч������Դ
	bool						_masterread;	//������׼��
	bool						_effectread;	//Ч����׼��
	bool						_masterenabled;	//��������
	bool						_effectenabled;	//����Ч����
	bool						_masterloop;	//������ѭ��
	bool						_effectloop;	//Ч����ѭ��

	LPWSTR						_mastermusic;	//������
	WAVEFORMATEX*				_masterpwfx;	//�������ļ���ʽ
	XAUDIO2_BUFFER				_masterbuffer;	//����������
	XAUDIO2_VOICE_STATE			_masterstate;	//������״̬

	LPWSTR						_effectmusic;	//Ч����
	WAVEFORMATEX*				_effectpwfx;	//Ч�����ļ���ʽ
	XAUDIO2_BUFFER				_effectbuffer;	//Ч��������
	XAUDIO2_VOICE_STATE			_effectstate;	//Ч����״̬
};
#endif // !MIREJAUDIO_H