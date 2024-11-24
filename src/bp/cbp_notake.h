#ifndef _CBP_NOTAKE_H_
#define _CBP_NOTAKE_H_

#include "cbp_to_scarab.h"

class NOTAKE
{
public:

    NOTAKE(void);
    void init();
    uint8_t GetPrediction(uint64_t addr, int* confidence);
    void UpdatePredictor(uint64_t PC, OpType OPTYPE, bool resolveDir, bool predDir, uint64_t branchTarget);
    void TrackOtherInst(uint64_t PC, OpType opType, bool taken, uint64_t branchTarget);
    uint8_t IsFull() const;

};

#endif