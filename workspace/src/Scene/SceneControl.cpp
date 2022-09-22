
#include "../../include/Scene/SceneControl.h"
#include "../../include/Judge/PaternJudge.h"
#include "../../include/Task/Task.h"
#include "../../include/SceneInfo/SceneInfo.hpp"
#include "../../include/Judge/Judgement.h"
#include "../../include/Correction/Correction.h"
#include "../../include/Steering/TailMotor.h"
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
    scene_num = 0;
    now_scene = 1;
    correction_flag = 0;
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
			garage_card=paternjudge.getGarage();
            if(garage_card >= 4){
                garage_card = 1;
            }
            if(garage_card == 1 || garage_card == 2){
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
            
            if(garage_card== 1 || garage_card == 2){
                sceneData = sceneInfo.get(GARAGE,now_scene,pattern1);
            }else{
                sceneData = sceneInfo.get(GARAGE,now_scene,pattern2);
            }
            break;
    }
    //実行
    Task *task = new Task(sceneData.moveData,sceneData.correctionData);
    error = task->run();

    if(tail_flg==0){
        TailMotor &tailMotor = TailMotor::getInstance();
    	int8 chk = tailMotor.setCounts(sceneData.moveData.tail_angle,10);
        if(chk == SYS_OK){
            tail_flg = 1;
        }
    }
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
    if(correction_flag==0){
        for(int8 i = 0; i < sizeof(sceneData.correctionData.correction); ++i){
		    if ( sceneData.correctionData.correction[i] >= 1 ) {
		    	//printf("coorection_start\n");
			    Correction correction;
			    error = correction.run(sceneData.correctionData);
                if(error == RESULT_TRUE){
                    correction_flag = 1;
                }
			    break;
		    }
	    } 
    }
    if(sceneData.paterndecisiondata.garage_point){
        paternjudge.Judge(1);
        if(paternjudge.getGarage()==garage_card){
            now_scene++;
            correction_flag = 0;
        }
    }else{
        judge_bool=judgement.judge(sceneData.decisionData);
    }
    if(judge_bool == 1){
        now_scene++;
        correction_flag = 0;
        tail_flg = 0;
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
