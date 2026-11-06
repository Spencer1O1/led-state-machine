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

void Led ::tick_handler(FwIndexType portNum, U32 context) {
    if (this->m_ticks < 10) {
        ++this->m_ticks;
    }

    this->sm_sendSignal_tick();
    this->pollButtons();
    this->dispatchCurrentMessages();
}

// ----------------------------------------------------------------------
// Handler helpers
// ----------------------------------------------------------------------

void Led ::pollButtons() {
    Fw::Logic red = Fw::Logic::HIGH;
    Fw::Logic yellow = Fw::Logic::HIGH;
    Fw::Logic green = Fw::Logic::HIGH;

    // Active-low buttons: fire once on HIGH -> LOW edge
    if (this->isConnected_gpioRead_OutputPort(0) && this->gpioRead_out(0, red) == Drv::GpioStatus::OP_OK) {
        if (red == Fw::Logic::LOW && this->m_lastRed == Fw::Logic::HIGH) {
            this->sm_sendSignal_redButton();
        }
        this->m_lastRed = red;
    }
    if (this->isConnected_gpioRead_OutputPort(1) && this->gpioRead_out(1, yellow) == Drv::GpioStatus::OP_OK) {
        if (yellow == Fw::Logic::LOW && this->m_lastYellow == Fw::Logic::HIGH) {
            this->sm_sendSignal_yellowButton();
        }
        this->m_lastYellow = yellow;
    }
    if (this->isConnected_gpioRead_OutputPort(2) && this->gpioRead_out(2, green) == Drv::GpioStatus::OP_OK) {
        if (green == Fw::Logic::LOW && this->m_lastGreen == Fw::Logic::HIGH) {
            this->sm_sendSignal_greenButton();
        }
        this->m_lastGreen = green;
    }
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void Led ::RED_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    this->sm_sendSignal_redButton();
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void Led ::GREEN_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    this->sm_sendSignal_greenButton();
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void Led ::YELLOW_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    this->sm_sendSignal_yellowButton();
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void Led ::LedStateMachine_SM_action_enterOff(SmId smId, LedStateMachine_SM::Signal signal) {
    this->setLedLevel(Fw::Logic::LOW);
    this->log_ACTIVITY_HI_ModeChanged(LedMode::OFF);
    this->tlmWrite_LedState(LedState::OFF);
}

void Led ::LedStateMachine_SM_action_exitOff(SmId smId, LedStateMachine_SM::Signal signal) {}

void Led ::LedStateMachine_SM_action_enterOn(SmId smId, LedStateMachine_SM::Signal signal) {
    this->setLedLevel(Fw::Logic::HIGH);
    this->log_ACTIVITY_HI_ModeChanged(LedMode::ON);
    this->tlmWrite_LedState(LedState::ON);
}

void Led ::LedStateMachine_SM_action_exitOn(SmId smId, LedStateMachine_SM::Signal signal) {}

void Led ::LedStateMachine_SM_action_enterBlink(SmId smId, LedStateMachine_SM::Signal signal) {
    this->log_ACTIVITY_HI_ModeChanged(LedMode::BLINK);
}

void Led ::LedStateMachine_SM_action_exitBlink(SmId smId, LedStateMachine_SM::Signal signal) {}

void Led::LedStateMachine_SM_action_enterBlinkOn(SmId smId, LedStateMachine_SM::Signal signal) {
    this->m_ticks = 0;
    this->setLedLevel(Fw::Logic::HIGH);
    this->tlmWrite_LedState(LedState::BLINK_ON);
}

void Led::LedStateMachine_SM_action_exitBlinkOn(SmId smId, LedStateMachine_SM::Signal signal) {}

void Led::LedStateMachine_SM_action_enterBlinkOff(SmId smId, LedStateMachine_SM::Signal signal) {
    this->m_ticks = 0;
    this->setLedLevel(Fw::Logic::LOW);
    this->tlmWrite_LedState(LedState::BLINK_OFF);
}

void Led::LedStateMachine_SM_action_exitBlinkOff(SmId smId, LedStateMachine_SM::Signal signal) {}

// ----------------------------------------------------------------------
// Implementations for internal state machine guards
// ----------------------------------------------------------------------

bool Led::LedStateMachine_SM_guard_blinkPeriodElapsed(SmId smId, LedStateMachine_SM::Signal signal) const {
    return this->m_ticks >= 10;
}

// ---------------------------------------------------------------------
// Helper functions
// ---------------------------------------------------------------------

bool Led ::setLedLevel(Fw::Logic level) {
    if (!this->isConnected_gpioWrite_OutputPort(0)) {
        return false;
    }

    if (this->gpioWrite_out(0, level) != Drv::GpioStatus::OP_OK) {
        return false;
    }

    return true;
}

}  // namespace LedStateMachine
