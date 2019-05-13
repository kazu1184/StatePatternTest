/*
@brief		�X�e�[�g�C���^�[�t�F�C�X
@file		IState.h
@date		2018/11/25
@author		Shozo Tanaka
*/

#pragma once
#ifndef ISTATE_DEFINED
#define ISTATE_DEFINED

#include "..\\Game\\Player.h"

class Player;

// IState�C���^�[�t�F�C�X��錾����
class IState 
{
public:
	// ��Ԃ�����������
	virtual void Initialize(Player* player) = 0;
	// ��Ԃ����������s����
	virtual void Execute(const DX::StepTimer& timer) = 0;
	// ��Ԃ�`�悷��
	virtual void Render(DirectX::SpriteBatch* spriteBatch) = 0;
};

#endif // ISTATE_DEFINED