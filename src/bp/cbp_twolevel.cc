#include "cbp_twolevel.h"

TWOLEVEL::TWOLEVEL() : GHR(0), PHT(PHT_SIZE, 2) {}

void TWOLEVEL::init(){
    GHR = 0;
    std::fill(PHT.begin(), PHT.end(), 2);
};

uint8_t TWOLEVEL::GetPrediction(uint64_t PC, int* confidence){
    uint32_t index = GHR & (PHT_SIZE - 1);
    return PHT[index] >= 2;
}

void TWOLEVEL::UpdatePredictor(uint64_t PC, OpType optype, bool taken, bool pred, uint64_t target){
    uint32_t index = GHR & (PHT_SIZE - 1);

    PHT[index] += taken ? 1 : -1;
    PHT[index] = sat_count(PHT[index]);

    GHR = ((GHR << 1) | taken) & (PHT_SIZE - 1);
};

void TWOLEVEL::TrackOtherInst(uint64_t PC, OpType optype, bool taken, uint64_t target){};

uint8_t TWOLEVEL::IsFull() const {
    return 0;
}

uint32_t TWOLEVEL::sat_count(uint32_t val){
    if(val > 3){
        val = 3;
    } else if(val < 0){
        val = 0;
    }
    return val;
}
