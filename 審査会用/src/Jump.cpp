/*#include "Jump.h"
#include "OBJECT.h"
#include "lib\appEnv.hpp"
#include "Player.h"
#include "main.h"
#include "GameMain.h"



CJump::CJump()
{
	x = 0.0f;
	y = 10.0f;
	vy = 0.0f;

	jumping = false;
	ju1 = false;
	pressJ = false;
	dash_R = true;
	dash_L = false;
	pressR = false;
	pressL = false;
	dush_on = false;
	jump_dush = false;

	press = 0.0f;		//�W�����v�{�^���������Ă鎞�ԕϐ�
	press2 = 0.0f;		//�_�b�V���{�^���������Ă鎞�ԕϐ�
	count = 0;			//�A�j���[�V�����p
	action_x = 0.0;		//
	action_y = 0.0;		//
	Dpress = false;

	//�W�����v�l����ϐ���p��
	normal = 7.0f;
	//water = 1.0f;
	//half = 30.0f;

	//�d��
	gravity = -1.0f;
	//gravi1 = -0.05;
	//gravi2 = -2.0f;
}


void CJump::Move()
{
	int pressT = 0;
	pressT = 1;
	float a = action_x;
	float b = action_y;
	if (jumping){
		y += vy + 0.5 * gravity;
		vy += gravity;
		if (dash_R){
			a = 4;
			b = 2;
		}
		if (dash_L){
			a = 1;
			b = 5;
		}
		drawTextureBox(-200 + x, -Window::HEIGHT / 2 + y, 30 * 3, 30 * 3,
			30 * a - 30, 30 * b - 30, 30, 30,
			GM->Blues,
			Color(1, 1, 1));
	}
	if (y <= 10.0){
		y = 10.0f;
		if (!pressJ){			//�������ςȂ��ɂ��A���W�����v�P��
			press = 0;
		}
		if (!Dpress){
			press2 = 0;
		}
		pressT = 0;
		jumping = false;

		//�E�������Ă��āAS�������Ă��Ȃ��Ƃ�
		if (dash_R && !pressR&&!jump_dush){
			a = 5;
			if ((count / 5) % 3){			//�A�j���[�V��������
				a += 1;
			}
			b = 1;
		}
		//���������Ă��āAA�������Ă��Ȃ��Ƃ�
		if (dash_L && !pressL&&!jump_dush){
			a = 1;
			if ((count / 5) % 3){
				a += 1;
			}
			b = 4;
		}
		if (pressR&&!jump_dush){
			if ((count / 10) % 2){			//�E�i�s
				a -= 1;
			}
		}
		if (pressL&&!jump_dush){
			if ((count / 10) % 2){			//���i�s
				a += 1;
			}
		}
		//�L�����N�^�[�\��
		drawTextureBox(-200 + x, -Window::HEIGHT / 2 + y, 30 * 3, 30 * 3,
			30 * a - 30, 30 * b - 30 / 1, 30, 30,
			GM->Blues,
			Color(1, 1, 1));
		count += 1;
	}
}
void CJump::Draw()
{

}
void CJump::Update()
{
	Move();
}*/