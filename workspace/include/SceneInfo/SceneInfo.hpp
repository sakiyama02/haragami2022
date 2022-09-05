#pragma once



#include "../system/system.h"
#include "../FileOp/FileIO.hpp"

using namespace std;

// ここの構造体はsystem.hに持っていく
// uintなどを使っていない理由はコンパイルが通らなかったため
// 結合時はそこでエラーがでるかも

enum ScenarioType{
	TIMEATTACK,
	SLALOM,
	GARAGE,
};

enum Pattern{
	common,
	pattern1,
	pattern2,
};


class SceneInfo{
	protected:


	private:
		SceneInfo( ){};
		~SceneInfo( ){};
		SceneInfo( const SceneInfo &x );
		SceneInfo&operator=( const SceneInfo & ) { return *this; };
		vector<SceneData> timeAttackData;
		vector<vector<SceneData> > slalomData{3};  // 0=共通,1=パターン1,2=パターン2
		vector<vector<SceneData> > garageData{3};  // 0=共通,1=パターン1,2=パターン2
		
	public:

		static SceneInfo &getInstance( )
		{
			static SceneInfo sceneInfo;
			return sceneInfo;
		}
		char init();
		char decode(vector<char>& fileData,vector<SceneData>& sceneData);
		SceneData get(ScenarioType scenario,int scene,Pattern pattern);
		int get(ScenarioType scenario,Pattern pattern);
};