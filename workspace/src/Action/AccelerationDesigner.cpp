///
/// @file 曲線設計クラス
/// @note 拘束条件もった曲線式を設計する
/// @date 2022/06/29 谷口拓海
///
#include "../../include/Action/AccelerationDesigner.h"

/**
	* @brief コンストラクタ
*/
AccelDesigner::AccelDesigner ()
{
	t0 = t1 = t2 = t3 = x0 = x3 = 0;
}

/**
	* @brief デストラクタ
*/
AccelDesigner::~AccelDesigner()
{
}

/**
	* @brief 距離拘束曲線式を初期化する
	* @param j_max		最大躍度の大きさ [m/s/s/s], 正であること
	* @param a_max		最大加速度の大きさ [m/s/s], 正であること
	* @param v_start	始点速度 [m/s]
	* @param v_target	目標速度 [m/s]
	* @param dist		走行距離 [m]
	* @param x_start	開始距離 [m]
	* @param t_start	開始時間 [m]
	* @return なし
*/
void AccelDesigner::reset(const double j_max, const double a_max, const double v_sat,
	const double v_start, const double v_target, const double dist,
	const double x_start, const double t_start)
{
	double v_max = 0.0f;						/* 最大速度					 */
	double v_end = v_target;					/* 終点速度					 */
	double dist_min = 0.0f;						/* 最短走行距離				 */
	double d_sum = 0.0f;						/* 必要最低距離				 */

	/* 最大速度の仮置き */
	v_max = dist > 0 ? std::max({ v_start, v_sat, v_target }) : std::min({ v_start, -v_sat, v_target });

	/* 走行距離から終点速度$v_e$を算出 */
	dist_min = AccelCurve::calcMinDistance(j_max, a_max, v_start, v_end);

	if (std::abs(dist) < std::abs(dist_min)) {
		/* 目標速度$v_t$に向かい，走行距離$d$で到達し得る終点速度$v_e$を算出 */
		v_end = AccelCurve::calcVelocityEnd(j_max, a_max, v_start, v_target, dist);
		v_max = v_end; //< 走行距離の拘束を満たすため，飽和速度まで加速できない
	}

	/* 曲線を生成 */
	ac.reset(j_max, a_max, v_start, v_max); //< 加速
	dc.reset(j_max, a_max, v_max, v_end);   //< 減速

	/* 飽和速度まで加速すると走行距離の拘束を満たさない場合の処理 */
	d_sum = ac.x_end() + dc.x_end();
	if (std::abs(dist) < std::abs(d_sum)) {

		/* 走行距離から最大速度$v_m$を算出; 下記v_maxは上記v_max以下になる */
		v_max = AccelCurve::calcVelocityMax(j_max, a_max, v_start, v_end, dist);

		/* 無駄な減速を回避 */
		v_max = dist > 0 ? std::max({ v_start, v_max, v_end }) : std::min({ v_start, v_max, v_end });
		
		// 加速
		ac.reset(j_max, a_max, v_start, v_max);

		// 減速
		dc.reset(j_max, a_max, v_max, v_end);
	}

	/* 各定数の算出 */
	x0 = x_start;
	x3 = x_start + dist;
	t0 = t_start;

	// 曲線加速終了の時刻
	t1 = t0 + ac.t_end(); 

	//< 等速走行終了の時刻
	t2 = t0 + ac.t_end() + (dist - ac.x_end() - dc.x_end()) / v_max; 

	//< 曲線減速終了の時刻
	t3 = t0 + ac.t_end() + (dist - ac.x_end() - dc.x_end()) / v_max + dc.t_end(); 
}