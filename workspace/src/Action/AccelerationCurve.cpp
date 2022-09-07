///
/// @file 加速度曲線クラス
/// @note 加速度曲線式を作成する
/// @date 2022/06/29 谷口拓海
///
#include "../../include/Action/AccelerationCurve.h"

/**
	* @brief コンストラクタ
*/
AccelCurve::AccelCurve()
{
	jm = am = t0 = t1 = t2 = t3 = v0 = v1 = v2 = v3 = x0 = x1 = x2 = x3 = 0;
}

/**
	* @brief デストラクタ
*/
AccelCurve::~AccelCurve()
{
}

/**
	 * @brief 曲線式を初期化する
	 * @param j_max		最大躍度の大きさ [m/s/s/s], 正であること
	 * @param a_max		最大加速度の大きさ [m/s/s], 正であること
	 * @param v_start	始点速度 [m/s]
	 * @param v_target	目標速度 [m/s]
	 * @return なし
 */
void AccelCurve::reset(const double j_max, const double a_max, const double v_start, const double v_end)
{
	double tc = 0.0f;							/* 加減速時間				 */
	double tm = 0.0f;							/* 等加速時間				 */

	/* 符号付きで代入 */
	am = (v_end > v_start) ? a_max : -a_max;
	jm = (v_end > v_start) ? j_max : -j_max;

	/* 初期値と最終値を代入 */
	v0 = v_start;
	v3 = v_end;
	t0 = 0;
	x0 = 0;

	/* 速度が曲線となる部分の時間を決定 */
	tc = a_max / j_max;

	/* 等加速度直線運動の時間を決定 */
	tm = (v3 - v0) / am - tc;

	/* 等加速度直線運動の有無で分岐 */
	if (tm > 0) {
		/* 速度: 曲線 -> 直線 -> 曲線 */
		t1 = t0 + tc;
		t2 = t1 + tm;
		t3 = t2 + tc;
		v1 = v0 + am * tc / 2;                //< v(t) を積分
		v2 = v1 + am * tm;                    //< v(t) を積分
		x1 = x0 + v0 * tc + am * tc * tc / 6; //< x(t) を積分
		x2 = x1 + v1 * tm;                    //< x(t) を積分
		x3 = x0 + (v0 + v3) / 2 * (t3 - t0); //< v(t) グラフの台形の面積より
	}
	else {
		/* 速度: 曲線 -> 曲線 */
		const double tcp = std::sqrt((v3 - v0) / jm); //< 変曲までの時間
		t1 = t2 = t0 + tcp;
		t3 = t2 + tcp;
		v1 = v2 = (v0 + v3) / 2; //< 対称性より中点となる
		x1 = x2 = x0 + v1 * tcp + jm * tcp * tcp * tcp / 6; //< x(t) を積分
		x3 = x0 + 2 * v1 * tcp; //< 速度 v(t) グラフの面積より
	}
}

/**
	* @brief 走行距離から達しうる終点速度を算出する関数
	* @param j_max	最大躍度の大きさ [m/s/s/s], 正であること
	* @param a_max	最大加速度の大きさ [m/s/s], 正であること
	* @param vs		始点速度 [m/s]
	* @param vt		目標速度 [m/s]
	* @param d		走行距離 [m]
	* @return 終点速度
 */
double AccelCurve::calcVelocityEnd(const double j_max, const double a_max,
	const double vs, const double vt, const double d)
{
	double tc			= 0.0f;					/* 加減速時間				 */
	double am			= 0.0f;					/* 最大加速度				 */
	double jm			= 0.0f;					/* 最大躍度					 */
	double d_triangle	= 0.0f;					/* 等減速値					 */
	double v_triangle	= 0.0f;					/* 等加速値					 */
	double amtc			= 0.0f;					/* 演算速度					 */
	double D			= 0.0f;					/* 2次方程式の途中演算行	 */
	double sqrtD		= 0.0f;					/* 2次方程式の2乗根			 */
	double a			= 0.0f;					/* 3次方程式パラメータ		 */
	double b			= 0.0f;					/* 3次方程式パラメータ		 */
	double aaa			= 0.0f;					/* 3次方程式パラメータ		 */
	double c0			= 0.0f;					/* 3次方程式パラメータ		 */
	double c1			= 0.0f;					/* 3次方程式パラメータ		 */
	double c2			= 0.0f;					/* 3次方程式パラメータ		 */

	/* 速度が曲線となる部分の時間を決定 */
	tc = a_max / j_max;

	/* 最大加速度の符号を決定 */
	am = (vt > vs) ? a_max : -a_max;
	jm = (vt > vs) ? j_max : -j_max;
	d_triangle = (vs + am * tc / 2) * tc;
	v_triangle = jm / am * d - vs;
	
	/* 等加速度直線運動の有無で分岐 */
	if (d * v_triangle > 0 && std::abs(d) > std::abs(d_triangle)) {
		/* 曲線・直線・曲線 */

		/* 2次方程式の解の公式を解く */
		amtc = am * tc;
		D = amtc * amtc - 4 * (amtc * vs - vs * vs - 2 * am * d);
		sqrtD = std::sqrt(D);
		return (-amtc + (d > 0 ? sqrtD : -sqrtD)) / 2;
	}

	/* 曲線・曲線 (走行距離が短すぎる) */
	/* 3次方程式を解いて，終点速度を算出;
	 * 簡単のため，値を一度すべて正に変換して，計算結果に符号を付与して返送 */
	a = std::abs(vs);
	b = (d > 0 ? 1 : -1) * jm * d * d;
	aaa = a * a * a;
	c0 = 27 * (32 * aaa * b + 27 * b * b);
	c1 = 16 * aaa + 27 * b;
	if (c0 >= 0) {
		/* ルートの中が非負のとき */
		c2 = cbrt((std::sqrt(c0) + c1) / 2);
		return (d > 0 ? 1 : -1) * (c2 + 4 * a * a / c2 - a) / 3;
	}
	else {
		/* ルートの中が負のとき */
		return (d > 0 ? 1 : -1) * (std::pow(std::complex<double>(c1 / 2, std::sqrt(-c0) / 2), double(1) / 3).real() * 2 - a) / 3;
	}
}

/**
 * @brief 走行距離から達しうる最大速度を算出する関数
 * @param j_max	最大躍度の大きさ [m/s/s/s], 正であること
 * @param a_max	最大加速度の大きさ [m/s/s], 正であること
 * @param vs	始点速度 [m/s]
 * @param ve	終点速度 [m/s]
 * @param d		走行距離 [m]
 * @return vm	最大速度 [m/s]
 */
double AccelCurve::calcVelocityMax(const double j_max, const double a_max,
	const double vs, const double ve, const double d)
{
	double tc = 0.0f;					/* 加減速時間				 */
	double am = 0.0f;					/* 最大加速度				 */
	double amtc = 0.0f;					/* 演算速度					 */
	double D = 0.0f;					/* 2次方程式の途中演算行	 */
	double sqrtD = 0.0f;				/* 2次方程式の2乗根			 */

	/* 速度が曲線となる部分の時間を決定 */
	tc = a_max / j_max;
	am = (d > 0) ? a_max : -a_max; 

	/* 2次方程式の解の公式を解く */
	amtc = am * tc;
	D = amtc * amtc - 2 * (vs + ve) * amtc + 4 * am * d + 2 * (vs * vs + ve * ve);

	if (D < 0) {
		/* 拘束条件がおかしい */
		/* 入力のチェック */
		if (vs * ve < 0) {
			return vs;
		}
	}
	sqrtD = std::sqrt(D);
	return (-amtc + (d > 0 ? sqrtD : -sqrtD)) / 2;
}

/**
 * @brief 速度差から変位を算出する関数
 * @param j_max		最大躍度の大きさ [m/s/s/s], 正であること
 * @param a_max		最大加速度の大きさ [m/s/s], 正であること
 * @param v_start	始点速度 [m/s]
 * @param v_end		終点速度 [m/s]
 * @return d		変位 [m]
 */
double AccelCurve::calcMinDistance(const double j_max, const double a_max,
	const double v_start, const double v_end)
{
	double tc	= 0.0f;							/* 加減速時間				 */
	double tm	= 0.0f;							/* 等加速時間				 */
	double t_all = 0.0f;						/* 総時間					 */
	double am	= 0.0f;							/* 最大加速度				 */
	double jm	= 0.0f;							/* 最大躍度					 */

	/* 符号付きで代入 */
	am = (v_end > v_start) ? a_max : -a_max;
	jm = (v_end > v_start) ? j_max : -j_max;
	/* 速度が曲線となる部分の時間を決定 */
	tc = a_max / j_max;
	/* 等加速度直線運動の時間を決定 */
	tm = (v_end - v_start) / am - tc;
	/* 始点から終点までの時間を決定 */
	t_all = (tm > 0) ? (tc + tm + tc) : (2 * std::sqrt((v_end - v_start) / jm));
	return (v_start + v_end) / 2 * t_all;
}