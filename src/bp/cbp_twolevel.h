#ifndef _CBP_TWOLEVEL_H_
#define _CBP_TWOLEVEL_H_

#include <vector>
#include <cstdint>
#include <algorithm>

#include "cbp_to_scarab.h"

class TWOLEVEL
{
private:
    static const int GHR_BITS = 8;  // Number of bits in the Global History Register
    static const int PHT_SIZE = 1 << GHR_BITS;  // Size of the Pattern History Table

    uint32_t GHR;  // Global History Register
    std::vector<int8_t> PHT;  // Pattern History Table with 2-bit saturating counters

public:
    // Constructor
    TWOLEVEL();

    // Initialize the predictor
    void init();

    // Get the branch prediction
    uint8_t GetPrediction(uint64_t PC, int* confidence);

    // Update the predictor after knowing the actual outcome
    void UpdatePredictor(uint64_t PC, OpType optype, bool taken, bool pred, uint64_t target);

    // Track non-branch instructions
    void TrackOtherInst(uint64_t PC, OpType optype, bool taken, uint64_t target);

    // Check if the predictor is full (not used for this implementation)
    uint8_t IsFull() const;

    uint32_t sat_count(uint32_t val);
};

#endif