#include "cbp_notake.h"

NOTAKE::NOTAKE(void){};

void NOTAKE::init(){};

uint8_t NOTAKE::GetPrediction(uint64_t addr, int* confidence){
    return 0;
}

void NOTAKE::UpdatePredictor(uint64_t PC, OpType OPTYPE, bool resolveDir, bool predDir, uint64_t branchTarget){};

void NOTAKE::TrackOtherInst(uint64_t PC, OpType opType, bool taken, uint64_t branchTarget){};

uint8_t NOTAKE::IsFull() const {
    return 0; // Placeholder: Return 0 to indicate "not full" by default
}