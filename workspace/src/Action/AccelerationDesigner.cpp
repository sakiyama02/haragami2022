///
/// @file �Ȑ��݌v�N���X
/// @note �S�������������Ȑ�����݌v����
/// @date 2022/06/29 �J����C
///
#include "../../include/Action/AccelerationDesigner.h"

/**
	* @brief �R���X�g���N�^
*/
AccelDesigner::AccelDesigner ()
{
	t0 = t1 = t2 = t3 = x0 = x3 = 0;
}

/**
	* @brief �f�X�g���N�^
*/
AccelDesigner::~AccelDesigner()
{
}

/**
	* @brief �����S���Ȑ���������������
	* @param j_max		�ő���x�̑傫�� [m/s/s/s], ���ł��邱��
	* @param a_max		�ő�����x�̑傫�� [m/s/s], ���ł��邱��
	* @param v_start	�n�_���x [m/s]
	* @param v_target	�ڕW���x [m/s]
	* @param dist		���s���� [m]
	* @param x_start	�J�n���� [m]
	* @param t_start	�J�n���� [m]
	* @return �Ȃ�
*/
void AccelDesigner::reset(const double j_max, const double a_max, const double v_sat,
	const double v_start, const double v_target, const double dist,
	const double x_start, const double t_start)
{
	double v_max = 0.0f;							/* �ő呬�x					 */
	double v_end = v_target;						/* �I�_���x					 */
	double dist_min = 0.0f;						/* �ŒZ���s����				 */
	double d_sum = 0.0f;							/* �K�v�Œ዗��				 */

	/* �ő呬�x�̉��u�� */
	v_max = dist > 0 ? std::max({ v_start, v_sat, v_target }) : std::min({ v_start, -v_sat, v_target });

	/* ���s��������I�_���x$v_e$���Z�o */
	dist_min = AccelCurve::calcMinDistance(j_max, a_max, v_start, v_end);

	if (std::abs(dist) < std::abs(dist_min)) {
		/* �ڕW���x$v_t$�Ɍ������C���s����$d$�œ��B������I�_���x$v_e$���Z�o */
		v_end = AccelCurve::calcVelocityEnd(j_max, a_max, v_start, v_target, dist);
		v_max = v_end; //< ���s�����̍S���𖞂������߁C�O�a���x�܂ŉ����ł��Ȃ�
	}

	/* �Ȑ��𐶐� */
	ac.reset(j_max, a_max, v_start, v_max); //< ����
	dc.reset(j_max, a_max, v_max, v_end);   //< ����

	/* �O�a���x�܂ŉ�������Ƒ��s�����̍S���𖞂����Ȃ��ꍇ�̏��� */
	d_sum = ac.x_end() + dc.x_end();
	if (std::abs(dist) < std::abs(d_sum)) {

		/* ���s��������ő呬�x$v_m$���Z�o; ���Lv_max�͏�Lv_max�ȉ��ɂȂ� */
		v_max = AccelCurve::calcVelocityMax(j_max, a_max, v_start, v_end, dist);

		/* ���ʂȌ�������� */
		v_max = dist > 0 ? std::max({ v_start, v_max, v_end }) : std::min({ v_start, v_max, v_end });
		
		// ����
		ac.reset(j_max, a_max, v_start, v_max);

		// ����
		dc.reset(j_max, a_max, v_max, v_end);
	}

	/* �e�萔�̎Z�o */
	x0 = x_start;
	x3 = x_start + dist;
	t0 = t_start;

	// �Ȑ������I���̎���
	t1 = t0 + ac.t_end(); 

	//< �������s�I���̎���
	t2 = t0 + ac.t_end() + (dist - ac.x_end() - dc.x_end()) / v_max; 

	//< �Ȑ������I���̎���
	t3 = t0 + ac.t_end() + (dist - ac.x_end() - dc.x_end()) / v_max + dc.t_end(); 
}