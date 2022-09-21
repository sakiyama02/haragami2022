#pragma once
#include "../system/system.h"

class SceneControl{
    private:
    int8_t  error;       //エラー値
    int16_t scene_num;   //シーン数
    int16_t now_scene;   //現シーン番号
    int8_t  now_scenario; //現在シナリオ
    int8_t slalom_patern;
    int8_t garage_card;
    int8_t correction_flag;
    SceneData sceneData;
    int8_t tail_flg=0;
    public:
    //コンストラクタ
    SceneControl();
    //デストラクタ
    ~SceneControl();
    //init      初期化
    //引数      -
    //戻り値    int8_t     エラー値
    int8_t  init();
    //run       動作
    //引数      -
    //戻り値    int8_t     エラー値
    int8_t  run();
    //switch    シーン切り替え
    //引数      -
    //戻り値    int8_t     エラー値
    int8_t  SceneSwitch();

    static SceneControl &getInstance()
    {
        static SceneControl sceneControl;
        return sceneControl;
    }
};