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
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void Led ::run_handler(FwIndexType portNum, U32 context) {
    this->pollButtons();
    this->dispatchCurrentMessages();
    this->updateBlink();
}

void Led ::pollButtons() {
    Fw::Logic red = Fw::Logic::HIGH;
    Fw::Logic yellow = Fw::Logic::HIGH;
    Fw::Logic green = Fw::Logic::HIGH;

    if (this->isConnected_gpioRead_OutputPort(0)) {
        (void)this->gpioRead_out(0, red);
    }
    if (this->isConnected_gpioRead_OutputPort(1)) {
        (void)this->gpioRead_out(1, yellow);
    }
    if (this->isConnected_gpioRead_OutputPort(2)) {
        (void)this->gpioRead_out(2, green);
    }

    // Active-low buttons: fire once on HIGH -> LOW edge
    if ((red == Fw::Logic::LOW) && (this->m_lastRed == Fw::Logic::HIGH)) {
        this->sm_sendSignal_redButton();
    } else if ((green == Fw::Logic::LOW) && (this->m_lastGreen == Fw::Logic::HIGH)) {
        this->sm_sendSignal_greenButton();
    } else if ((yellow == Fw::Logic::LOW) && (this->m_lastYellow == Fw::Logic::HIGH)) {
        this->sm_sendSignal_yellowButton();
    }

    this->m_lastRed = red;
    this->m_lastYellow = yellow;
    this->m_lastGreen = green;
}

void Led ::updateBlink() {
    if (this->sm_getState() == LedStateMachine_SM::State::BLINK) {
        this->m_blinkLevel = (this->m_blinkLevel == Fw::Logic::HIGH) ? Fw::Logic::LOW : Fw::Logic::HIGH;
        if (this->isConnected_gpioWrite_OutputPort(0)) {
            (void)this->gpioWrite_out(0, this->m_blinkLevel);
        }
    }
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void Led ::RED_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    this->sm_sendSignal_redButton();
    this->dispatchCurrentMessages();
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void Led ::GREEN_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    this->sm_sendSignal_greenButton();
    this->dispatchCurrentMessages();
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void Led ::YELLOW_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    this->sm_sendSignal_yellowButton();
    this->dispatchCurrentMessages();
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void Led ::LedStateMachine_SM_action_enterOff(SmId smId, LedStateMachine_SM::Signal signal) {
    this->m_blinkLevel = Fw::Logic::LOW;
    if (this->isConnected_gpioWrite_OutputPort(0)) {
        (void)this->gpioWrite_out(0, Fw::Logic::LOW);
    }
    this->log_ACTIVITY_HI_StateChanged(LedMode::OFF);
    this->tlmWrite_LedState(LedMode::OFF);
}

void Led ::LedStateMachine_SM_action_exitOff(SmId smId, LedStateMachine_SM::Signal signal) {}

void Led ::LedStateMachine_SM_action_enterOn(SmId smId, LedStateMachine_SM::Signal signal) {
    this->m_blinkLevel = Fw::Logic::HIGH;
    if (this->isConnected_gpioWrite_OutputPort(0)) {
        (void)this->gpioWrite_out(0, Fw::Logic::HIGH);
    }
    this->log_ACTIVITY_HI_StateChanged(LedMode::ON);
    this->tlmWrite_LedState(LedMode::ON);
}

void Led ::LedStateMachine_SM_action_exitOn(SmId smId, LedStateMachine_SM::Signal signal) {}

void Led ::LedStateMachine_SM_action_enterBlink(SmId smId, LedStateMachine_SM::Signal signal) {
    this->m_blinkLevel = Fw::Logic::HIGH;
    if (this->isConnected_gpioWrite_OutputPort(0)) {
        (void)this->gpioWrite_out(0, this->m_blinkLevel);
    }
    this->log_ACTIVITY_HI_StateChanged(LedMode::BLINK);
    this->tlmWrite_LedState(LedMode::BLINK);
}

void Led ::LedStateMachine_SM_action_exitBlink(SmId smId, LedStateMachine_SM::Signal signal) {}

}  // namespace LedStateMachine
