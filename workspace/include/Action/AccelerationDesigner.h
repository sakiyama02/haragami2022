///
/// @file 拘束加速度曲線式クラス
/// @note 拘束条件もった加速度曲線式を作成する
/// @date 2022/06/29 谷口拓海
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
   * @brief 時刻 $t$ における躍度 $j$
   * @param t 時刻[s]
   * @return j 躍度[m/s/s/s]
   */
	double j(const double t) const {
		if (t < t2)
			return ac.j(t - t0);
		else
			return dc.j(t - t2);
	}
	/**
	 * @brief 時刻 $t$ における加速度 $a$
	 * @param t 時刻 [s]
	 * @return a 加速度 [m/s/s]
	 */
	double a(const double t) const {
		if (t < t2)
			return ac.a(t - t0);
		else
			return dc.a(t - t2);
	}
	/**
	 * @brief 時刻 $t$ における速度 $v$
	 * @param t 時刻 [s]
	 * @return v 速度 [m/s]
	 */
	double v(const double t) const {
		if (t < t2)
			return ac.v(t - t0);
		else
			return dc.v(t - t2);
	}
	/**
	 * @brief 時刻 $t$ における位置 $x$
	 * @param t 時刻 [s]
	 * @return x 位置 [m]
	 */
	double x(const double t) const {
		if (t < t2)
			return x0 + ac.x(t - t0);
		else
			return x3 - dc.x_end() + dc.x(t - t2);
	}
	/**
	 * @brief 終点時刻 [s]
	 */
	double t_end() const { return t3; }
	/**
	 * @brief 終点速度 [m/s]
	 */
	double v_end() const { return dc.v_end(); }
	/**
	 * @brief 終点位置 [m]
	 */
	double x_end() const { return x3; }
	/**
	 * @brief 境界の時刻
	 */
	double t_0() const { return t0; }
	double t_1() const { return t1; }
	double t_2() const { return t2; }
	double t_3() const { return t3; }
	
	/**
	 * @brief 境界のタイムスタンプを取得
	 * @return std::array<float, 8> 境界のタイムスタンプの配列
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
	double t0, t1, t2, t3;	/**< @brief 境界点の時刻 [s] */
	double x0, x3;			/**< @brief 境界点の位置 [m] */
	AccelCurve ac, dc;		/**< @brief 曲線加速，曲線減速オブジェクト */
};

#endif