///
/// @file �����x�Ȑ��N���X
/// @note �����x�Ȑ������쐬����
/// @date 2022/06/29 �J����C
///
#ifndef ACELLCURVE_HEADER
#define ACELLCURVE_HEADER



#include "../system/system.h"


class AccelCurve
{
public:
	AccelCurve();
	~AccelCurve();

	void reset(const double j_max, const double a_max, const double v_start, const double v_end);

	static double calcVelocityEnd(const double j_max, const double a_max,
		const double vs, const double vt, const double d);

	static double calcVelocityMax(const double j_max, const double a_max,
		const double vs, const double ve, const double d);

	static double calcMinDistance(const double j_max, const double a_max,
		const double v_start, const double v_end);

	// �R���X�g�����o�ϐ�
	/**
	* @brief ���x
	*/
	double j(const double t)const {
		if (t <= t0)
			return 0;
		else if (t <= t1)
			return jm;
		else if (t <= t2)
			return 0;
		else if (t <= t3)
			return -jm;
		else
			return 0;
	}

	/**
	* @brief �����x
	*/
	double a(const double t) const {
		if (t <= t0)
			return 0;
		else if (t <= t1)
			return jm * (t - t0);
		else if (t <= t2)
			return am;
		else if (t <= t3)
			return -jm * (t - t3);
		else
			return 0;
	}

	/**
	* @brief ���x
	*/
	double v(const double t) const {
		if (t <= t0)
			return v0;
		else if (t <= t1)
			return v0 + jm / 2 * (t - t0) * (t - t0);
		else if (t <= t2)
			return v1 + am * (t - t1);
		else if (t <= t3)
			return v3 - jm / 2 * (t - t3) * (t - t3);
		else
			return v3;
	}

	/**
	* @brief �ʒu
	*/
	double x(const double t) const {
		if (t <= t0)
			return x0 + v0 * (t - t0);
		else if (t <= t1)
			return x0 + v0 * (t - t0) + jm / 6 * (t - t0) * (t - t0) * (t - t0);
		else if (t <= t2)
			return x1 + v1 * (t - t1) + am / 2 * (t - t1) * (t - t1);
		else if (t <= t3)
			return x3 + v3 * (t - t3) - jm / 6 * (t - t3) * (t - t3) * (t - t3);
		else
			return x3 + v3 * (t - t3);
	}

	/**
	* @brief �I�_���� [s]
	*/
	double t_end() const { return t3; }
	/**
	 * @brief �I�_���x [m/s]
	 */
	double v_end() const { return v3; }
	/**
	 * @brief �I�_�ʒu [m]
	 */
	double x_end() const { return x3; }
	/**
	 * @brief ���E�̎���
	 */
	double t_0() const { return t0; }
	double t_1() const { return t1; }
	double t_2() const { return t2; }
	double t_3() const { return t3; }

private:


protected:
	double jm;									/* ���x�萔 [m/s/s/s]		 */
	double am;									/* �����x�萔 [m/s/s]		 */
	double t0, t1, t2, t3;						/* �����萔 [s]				 */
	double v0, v1, v2, v3;						/* ���x�萔 [m/s]			 */
	double x0, x1, x2, x3;						/* �ʒu�萔 [m]				 */
};

#endif