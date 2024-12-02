#include "cbp_twolevel.h"

TWOLEVEL::TWOLEVEL() : HHRT(HHRT_SIZE), PHT(PHT_SIZE, 3) {}

void TWOLEVEL::init(){
    // Initialize HHRT entries to all 1s (maximum value based on GHR_BITS)
    std::fill(HHRT.begin(), HHRT.end(), (1 << GHR_BITS) - 1);
    // Initialize PHT entries to 3 (strongly taken)
    std::fill(PHT.begin(), PHT.end(), 3);
}

uint32_t TWOLEVEL::hash_PC(uint64_t PC){
    // Simple hash function: shift PC to remove alignment bits and modulo HHRT_SIZE
    return (PC >> 2) % HHRT_SIZE;
}

uint8_t TWOLEVEL::GetPrediction(uint64_t PC, int* confidence){
    uint32_t hhrt_index = hash_PC(PC);
    uint32_t history = HHRT[hhrt_index];
    uint32_t pht_index = history & (PHT_SIZE - 1);
    if(confidence) *confidence = PHT[pht_index];
    return PHT[pht_index] >= 2;  // Predict taken if counter is in upper half
}

void TWOLEVEL::UpdatePredictor(uint64_t PC, OpType optype, bool taken, bool pred, uint64_t target){
    uint32_t hhrt_index = hash_PC(PC);
    uint32_t history = HHRT[hhrt_index];
    uint32_t pht_index = history & (PHT_SIZE - 1);

    // Update the 2-bit saturating counter
    PHT[pht_index] += taken ? 1 : -1;
    PHT[pht_index] = sat_count(PHT[pht_index]);

    // Update the history register for this PC
    history = ((history << 1) | taken) & ((1 << GHR_BITS) - 1);
    HHRT[hhrt_index] = history;
}

void TWOLEVEL::TrackOtherInst(uint64_t PC, OpType optype, bool taken, uint64_t target){
    // No action needed for non-branch instructions in this predictor
}

uint8_t TWOLEVEL::IsFull() const {
    return 0;  // Predictor is never full in this implementation
}

int8_t TWOLEVEL::sat_count(int8_t val){
    if(val > 3){
        val = 3;
    } else if(val < 0){
        val = 0;
    }
    return val;
}
