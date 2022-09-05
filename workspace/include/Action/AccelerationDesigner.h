///
/// @file �S�������x�Ȑ����N���X
/// @note �S�����������������x�Ȑ������쐬����
/// @date 2022/06/29 �J����C
///


#ifndef ACELLDESIGNER_HEADER
#define ACELLDESIGNER_HEADER
#include "./AccelerationCurve.h"
#include "../system/system.h"


class AccelDesigner {
public:

	AccelDesigner();
	~AccelDesigner();

	void reset(const double j_max, const double a_max, const double v_sat,
		const double v_start, const double v_target, const double dist,
		const double x_start, const double t_start);

	/**
   * @brief ���� $t$ �ɂ�������x $j$
   * @param t ����[s]
   * @return j ���x[m/s/s/s]
   */
	double j(const double t) const {
		if (t < t2)
			return ac.j(t - t0);
		else
			return dc.j(t - t2);
	}
	/**
	 * @brief ���� $t$ �ɂ���������x $a$
	 * @param t ���� [s]
	 * @return a �����x [m/s/s]
	 */
	double a(const double t) const {
		if (t < t2)
			return ac.a(t - t0);
		else
			return dc.a(t - t2);
	}
	/**
	 * @brief ���� $t$ �ɂ����鑬�x $v$
	 * @param t ���� [s]
	 * @return v ���x [m/s]
	 */
	double v(const double t) const {
		if (t < t2)
			return ac.v(t - t0);
		else
			return dc.v(t - t2);
	}
	/**
	 * @brief ���� $t$ �ɂ�����ʒu $x$
	 * @param t ���� [s]
	 * @return x �ʒu [m]
	 */
	double x(const double t) const {
		if (t < t2)
			return x0 + ac.x(t - t0);
		else
			return x3 - dc.x_end() + dc.x(t - t2);
	}
	/**
	 * @brief �I�_���� [s]
	 */
	double t_end() const { return t3; }
	/**
	 * @brief �I�_���x [m/s]
	 */
	double v_end() const { return dc.v_end(); }
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
	
	/**
	 * @brief ���E�̃^�C���X�^���v���擾
	 * @return std::array<double, 8> ���E�̃^�C���X�^���v�̔z��
	 */
	const std::array<double, 8> getTimeStamp() const {
		return { {
			t0 + ac.t_0(),
			t0 + ac.t_1(),
			t0 + ac.t_2(),
			t0 + ac.t_3(),
			t2 + dc.t_0(),
			t2 + dc.t_1(),
			t2 + dc.t_2(),
			t2 + dc.t_3(),
		} };
	}

	
protected:
	double t0, t1, t2, t3;	/**< @brief ���E�_�̎��� [s] */
	double x0, x3;			/**< @brief ���E�_�̈ʒu [m] */
	AccelCurve ac, dc;		/**< @brief �Ȑ������C�Ȑ������I�u�W�F�N�g */
};

#endif