#pragma once

#include "Variable.h"

//�L�[����
bool isLeftKey(AppEnv&);
bool isRightKey(AppEnv&);

//���ړ�����
int PlayerMove(AppEnv&);

//�W�����v����
void Jump(AppEnv&);

//�v���C���[�ړ��܂Ƃ�
void MoveUpdate(AppEnv&);