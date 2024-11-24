#include "cbp_take.h"

TAKE::TAKE(void){};

void TAKE::init(){};

uint8_t TAKE::GetPrediction(uint64_t addr, int* confidence){
    return 1;
}

void TAKE::UpdatePredictor(uint64_t PC, OpType OPTYPE, bool resolveDir, bool predDir, uint64_t branchTarget){};

void TAKE::TrackOtherInst(uint64_t PC, OpType opType, bool taken, uint64_t branchTarget){};

uint8_t TAKE::IsFull() const {
    return 0; // Placeholder: Return 0 to indicate "not full" by default
}