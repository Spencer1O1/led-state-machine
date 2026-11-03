// ======================================================================
// \title  Led.cpp
// \author spencerls
// \brief  cpp file for Led component implementation class
// ======================================================================

#include "LedStateMachine/Components/Led/Led.hpp"

namespace LedStateMachine {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

Led ::Led(const char* const compName) : LedComponentBase(compName) {}

Led ::~Led() {}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void Led ::RED_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void Led ::GREEN_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void Led ::YELLOW_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void Led ::LedStateMachine_SM_action_enterOff(SmId smId, LedStateMachine_SM::Signal signal) {
    // TODO
}

void Led ::LedStateMachine_SM_action_exitOff(SmId smId, LedStateMachine_SM::Signal signal) {
    // TODO
}

void Led ::LedStateMachine_SM_action_enterOn(SmId smId, LedStateMachine_SM::Signal signal) {
    // TODO
}

void Led ::LedStateMachine_SM_action_exitOn(SmId smId, LedStateMachine_SM::Signal signal) {
    // TODO
}

void Led ::LedStateMachine_SM_action_enterBlink(SmId smId, LedStateMachine_SM::Signal signal) {
    // TODO
}

void Led ::LedStateMachine_SM_action_exitBlink(SmId smId, LedStateMachine_SM::Signal signal) {
    // TODO
}

}  // namespace LedStateMachine
