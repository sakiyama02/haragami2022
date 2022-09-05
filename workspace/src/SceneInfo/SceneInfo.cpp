#include "../../include/SceneInfo/SceneInfo.hpp"

char SceneInfo::init(){
	// timeAttack.csv
	// slalom.csv
	// slalom1.csv  パターン１
	// slalom2.csv　パターン２
	// garage.csv
	// garage1.csv　パターン１
	// garage2.csv　パターン２
	// リサイズ使うとコンパイルできやんねんけど
	// ここで考えるのをやめた
	//  実機用（EV3）  /ev3rt/res/timeAttack.csv
	FileIO &file = FileIO::getInstance();
	#ifdef EV3
	printf("EV3 in\n");
	vector<char> tabuf(file.getSize("/ev3rt/res/timeAttack.csv"));
	file.read(tabuf,"/ev3rt/res/timeAttack.csv");
	decode(tabuf,timeAttackData);
	tabuf.shrink_to_fit();

	vector<char> s0buf(file.getSize("/ev3rt/res/slalom.csv"));
	file.read(s0buf,"/ev3rt/res/slalom.csv");
	decode(s0buf,slalomData[common]);
	s0buf.shrink_to_fit();

	vector<char> s1buf(file.getSize("/ev3rt/res/slalom1.csv"));
	file.read(s1buf,"/ev3rt/res/slalom1.csv");
	decode(s1buf,slalomData[pattern1]);
	s1buf.shrink_to_fit();

	vector<char> s2buf(file.getSize("/ev3rt/res/slalom2.csv"));
	file.read(s2buf,"/ev3rt/res/slalom2.csv");
	decode(s2buf,slalomData[pattern2]);
	s2buf.shrink_to_fit();

	vector<char> g0buf(file.getSize("/ev3rt/res/garage.csv"));
	file.read(g0buf,"/ev3rt/res/garage.csv");
	decode(g0buf,garageData[common]);
	g0buf.shrink_to_fit();

	vector<char> g1buf(file.getSize("/ev3rt/res/garage1.csv"));
	file.read(g1buf,"/ev3rt/res/garage1.csv");
	decode(g1buf,garageData[pattern1]);
	g1buf.shrink_to_fit();

	vector<char> g2buf(file.getSize("/ev3rt/res/garage2.csv"));
	file.read(g2buf,"/ev3rt/res/garage2.csv");
	decode(g2buf,garageData[pattern2]);
	g2buf.shrink_to_fit();
	#else

	
	vector<char> tabuf(file.getSize("timeAttack.csv"));
	file.read(tabuf,"timeAttack.csv");
	decode(tabuf,timeAttackData);
	tabuf.shrink_to_fit();

	vector<char> s0buf(file.getSize("slalom.csv"));
	file.read(s0buf,"slalom.csv");
	decode(s0buf,slalomData[common]);
	s0buf.shrink_to_fit();

	vector<char> s1buf(file.getSize("slalom1.csv"));
	file.read(s1buf,"slalom1.csv");
	decode(s1buf,slalomData[pattern1]);
	s1buf.shrink_to_fit();

	vector<char> s2buf(file.getSize("slalom2.csv"));
	file.read(s2buf,"slalom2.csv");
	decode(s2buf,slalomData[pattern2]);
	s2buf.shrink_to_fit();

	vector<char> g0buf(file.getSize("garage.csv"));
	file.read(g0buf,"garage.csv");
	decode(g0buf,garageData[common]);
	g0buf.shrink_to_fit();

	vector<char> g1buf(file.getSize("garage1.csv"));
	file.read(g1buf,"garage1.csv");
	decode(g1buf,garageData[pattern1]);
	g1buf.shrink_to_fit();

	vector<char> g2buf(file.getSize("garage2.csv"));
	file.read(g2buf,"garage2.csv");
	decode(g2buf,garageData[pattern2]);
	g2buf.shrink_to_fit();
	#endif
	return 0;
}

/// いろいろ試したけどc++のライブラリ使うとエラーが出ることが多い
char SceneInfo::decode(vector<char>& fileData,vector<SceneData>& sceneData){
	int cnt=0;
	char* data_ptr = NULL;
	char *save_ptr1 ;
	char *start;
	SceneData tmpData;
	printf("strtok\n");
	data_ptr = strtok_r(fileData.data(),",",&save_ptr1);
	start = data_ptr;
	do{
		
		// シーン番号
		tmpData.num=atoi(data_ptr);
		/// 動作構造体代入-----------------------------------------------------
		// 使用動作
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.moveData.motion=atoi(data_ptr);
		
		// ライン位置
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.moveData.edge=atoi(data_ptr);
		
		
		// PIDゲイン
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.moveData.gain.p=atof(data_ptr);
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.moveData.gain.i=atof(data_ptr);
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.moveData.gain.d=atof(data_ptr);
		


		// 閾値
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.moveData.target_val=atof(data_ptr);
		

		// 目標速度
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.moveData.speed=atoi(data_ptr);
		

		// カーブ半径
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.moveData.radius=atof(data_ptr);
		

		// 目標座標
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.moveData.coordinate.x=atof(data_ptr);
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.moveData.coordinate.y=atof(data_ptr);
		

		// 旋回方向
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.moveData.direction=atoi(data_ptr);
		

		// アーム位置
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.moveData.arm_angle=atoi(data_ptr);
		

		// アーム速度
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.moveData.arm_pwm=atoi(data_ptr);
		
		/// ------------------------------------------------------------------

		/// 判定構造体代入-----------------------------------------------------
		// 使用判定1
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.decision[0]=atoi(data_ptr);
		

		// 使用判定2
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.decision[1]=atoi(data_ptr);
		

		// 座標範囲
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.coordinate_range[0]=atoi(data_ptr);
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.coordinate_range[1]=atoi(data_ptr);
		

		// 目標座標
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.coordinate.x=atoi(data_ptr);
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.coordinate.y=atoi(data_ptr);
		

		// 距離範囲
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.distance_range=atoi(data_ptr);
		

		// 目標距離
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.distance=atoi(data_ptr);
		

		// 目標色
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.color=atoi(data_ptr);
		

		// RGB範囲
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.rgb_range[0]=atoi(data_ptr);//R
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.rgb_range[1]=atoi(data_ptr);//G
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.rgb_range[2]=atoi(data_ptr);//B
		

		// 目標RGB
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.rgb.r=atoi(data_ptr);//R
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.rgb.g=atoi(data_ptr);//G
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.rgb.b=atoi(data_ptr);//B
		
		// HSV範囲
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.hsv_range[0]=atoi(data_ptr);//H
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.hsv_range[1]=atoi(data_ptr);//S
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.hsv_range[2]=atoi(data_ptr);//V
		

		// 目標HSV
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.hsv.h=atoi(data_ptr);//H
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.hsv.s=atoi(data_ptr);//S
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.hsv.v=atoi(data_ptr);//V
		

		// 角度範囲
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.angle_range=atoi(data_ptr);
		

		// 角度
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.angle=atof(data_ptr);
		

		// 論理演算方法
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.decisionData.logic=atoi(data_ptr);
		
		/// ------------------------------------------------------------------

		/// 判定構造体代入-----------------------------------------------------
		// 使用補正
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.correction[0]=atoi(data_ptr);
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.correction[1]=atoi(data_ptr);
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.correction[2]=atoi(data_ptr);
		

		// 補正座標
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.coordinate.x=atof(data_ptr);
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.coordinate.y=atof(data_ptr);
		

		// 補正角度
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.angle=atof(data_ptr);
		

		/// 補正用判定
		// 使用判定1
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.decision[0]=atoi(data_ptr);
		

		// 使用判定2
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.decision[1]=atoi(data_ptr);
		

		// 座標範囲
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.coordinate_range[0]=atoi(data_ptr);
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.coordinate_range[1]=atoi(data_ptr);
		

		// 目標座標
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.coordinate.x=atoi(data_ptr);
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.coordinate.y=atoi(data_ptr);
		

		// 距離範囲
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.distance_range=atoi(data_ptr);
		
		// 目標距離
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.distance=atoi(data_ptr);
		
		// 目標色
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.color=atoi(data_ptr);
		

		// RGB範囲
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.rgb_range[0]=atoi(data_ptr);//R
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.rgb_range[1]=atoi(data_ptr);//G
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.rgb_range[2]=atoi(data_ptr);//B
		

		// 目標RGB
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.rgb.r=atoi(data_ptr);//R
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.rgb.g=atoi(data_ptr);//G
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.rgb.b=atoi(data_ptr);//B
		
		// HSV範囲
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.hsv_range[0]=atoi(data_ptr);//H
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.hsv_range[1]=atoi(data_ptr);//S
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.hsv_range[2]=atoi(data_ptr);//V
		

		// 目標HSV
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.hsv.h=atoi(data_ptr);//H
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.hsv.s=atoi(data_ptr);//S
		
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.hsv.v=atoi(data_ptr);//V
		

		// 角度範囲
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.angle_range=atoi(data_ptr);
		

		// 角度範囲
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.angle=atof(data_ptr);
		
		// 論理演算方法
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.correctionData.decisionData.logic=atoi(data_ptr);
		
		// スラロームパターンフラグ
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.paterndecisiondata.slalom_decision=atoi(data_ptr);
		
		// ガレージパターンフラグ
		data_ptr = strtok_r(NULL,",",&save_ptr1);
		tmpData.paterndecisiondata.garage_decision=atoi(data_ptr);
		
		// ガレージ格納ポイント
		data_ptr = strtok_r(NULL,"\n",&save_ptr1);
		tmpData.paterndecisiondata.garage_point=atoi(data_ptr);
		
		/// ------------------------------------------------------------------
		sceneData.push_back(tmpData);
		try
		{
			data_ptr = strtok_r(NULL,",",&save_ptr1);
		}catch(...){
			printf("catch\n");
			break;
		}
	}while(fileData.size() > (int)(data_ptr - start));
	
	printf("loop end\n");


	return 0;
}

SceneData SceneInfo::get(ScenarioType scenario,int scene,Pattern pattern){
	--scene;

	switch (scenario)
	{
	case TIMEATTACK:
		return timeAttackData[scene];
		break;
	case SLALOM:
		return slalomData[pattern][scene];

		break;
	case GARAGE:
		return garageData[pattern][scene];
		break;
	default:
		break;
	}
	SceneData temp;
	return temp;
}

int SceneInfo::get(ScenarioType scenario,Pattern pattern){
	switch (scenario)
	{
	case TIMEATTACK:
		return timeAttackData.size();
		break;
	case SLALOM:
		return slalomData[pattern].size();
		break;
	case GARAGE:
		return garageData[pattern].size();
		break;
	default:
		break;
	}

	return 0;
}
