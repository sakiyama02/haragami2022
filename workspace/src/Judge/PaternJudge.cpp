#include "../../include/Judge/PaternJudge.h"

PaternJudge::PaternJudge(){
    
    judgement.push_back(new PaternSlalom());
    judgement.push_back(new PaternGarage());
}
PaternJudge::~PaternJudge(){
    for(it=judgement.begin();it != std::end(judgement); ++it){
        delete *it;
    }
}
int8 PaternJudge::Judge(int8 _patern){
    int8 paternChk=0;
    paternChk=judgement[_patern]->decide();
    patern[_patern]=paternChk;
    return SYS_OK;
}
int8 PaternJudge::getSlalom(){
    return patern[slalom];
}
int8 PaternJudge::getGarage(){
    return  patern[garage];
}