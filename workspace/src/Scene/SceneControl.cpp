
#include "../../include/Scene/SceneControl.h"
#include "../../include/Judge/PaternJudge.h"
#include "../../include/Task/Task.h"
#include "../../include/SceneInfo/SceneInfo.hpp"
#include "../../include/Judge/Judgement.h"
//コンストラクタ
SceneControl::SceneControl(){
    error     = SYS_NG;
    slalom_patern=0;
    garage_card=1;
    error = init();
    if(error != SYS_OK){
    }
}
//デストラクタ
SceneControl::~SceneControl(){}

int8_t SceneControl::init(){
    
    now_scenario = 0;
    scene_num = 10;
    now_scene = 1;
    SceneInfo& sceneInfo    = SceneInfo::getInstance();
    //タイムアタックのシーン数取得
    scene_num = sceneInfo.get(TIMEATTACK,common);
    printf("タイムアタックシーン数%d\n",scene_num);
    return SYS_OK;
}

int8_t SceneControl::run(){
    PaternJudge& paternjudge = PaternJudge::getInstance();
    SceneInfo& sceneInfo    = SceneInfo::getInstance();
    //シナリオ内全シーンが終了している場合
    if(now_scene > scene_num){
        now_scenario++;
        if(now_scenario == 1){
            //スラロームのシーン数取得
            scene_num = sceneInfo.get(SLALOM,common);
            now_scene = 1;
        }
        if(now_scenario == 2){
            slalom_patern=paternjudge.getSlalom();
            //スラロームのシーン数取得
            if(paternjudge.getSlalom() == 1){
                scene_num = sceneInfo.get(SLALOM,pattern1);
            }else{
                scene_num = sceneInfo.get(SLALOM,pattern2);
            }
            now_scene = 1;
        }
        if(now_scenario == 3){
            //スラロームのシーン数取得
            scene_num = sceneInfo.get(GARAGE,common);
            now_scene = 1;
        }
        if(now_scenario == 4){
            //ガレージのシーン数取得
            if(paternjudge.getGarage() == 1){
                scene_num = sceneInfo.get(GARAGE,pattern1);
            }else{
                scene_num = sceneInfo.get(GARAGE,pattern2);
            }
            now_scene = 1;
        }
        //全シナリオが終了している場合
        if(now_scenario > 4){
            printf("scene_all_finish\n");
            return ALL_SCENE_END;
        }
    }
    //シーン情報取得
    switch(now_scenario){
        case 0:
            //タイムアタック
            sceneData = sceneInfo.get(TIMEATTACK,now_scene,common);
            break;
        case 1:
            sceneData = sceneInfo.get(SLALOM,now_scene,common);
            break;
        case 2:
            //スラローム
            if(paternjudge.getSlalom() == 1){
                sceneData = sceneInfo.get(SLALOM,now_scene,pattern1);
            }else{
                sceneData = sceneInfo.get(SLALOM,now_scene,pattern2);
            }
            break;
        case 3:
            sceneData = sceneInfo.get(GARAGE,now_scene,common);
            break;
        case 4:
            //ガレージ
            garage_card=paternjudge.getGarage();
            if(garage_card== 1){
                sceneData = sceneInfo.get(GARAGE,now_scene,pattern1);
            }else{
                sceneData = sceneInfo.get(GARAGE,now_scene,pattern2);
            }
            break;
    }
    //実行
    Task *task = new Task(sceneData.moveData,sceneData.correctionData);
    error = task->run();
    if(error != SYS_OK){
        printf("task_run_error\n");
        ext_tsk();
    }

    delete task;

    return SYS_OK;
}

int8_t SceneControl::SceneSwitch(){
    int8_t judge_bool = 0;
    Judgement judgement;
    PaternJudge& paternjudge = PaternJudge::getInstance();
    //シーン切り替え判定
    //printf("scene_change_judge\n");
    if(sceneData.paterndecisiondata.garage_point){
        paternjudge.Judge(1);
        if(paternjudge.getGarage()==garage_card){
            now_scene++;
        }
    }else{
        judge_bool=judgement.judge(sceneData.decisionData);
    }
    if(judge_bool == 1){
        now_scene++;
        printf("scene_change\n");
    }
    //パターン判定
    if(sceneData.paterndecisiondata.slalom_decision){
        paternjudge.Judge(0);
    }
    if(sceneData.paterndecisiondata.garage_decision){
        paternjudge.Judge(1);
    }
    
    return SYS_OK;
}
