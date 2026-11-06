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
    this->pollButtons();
    this->updateBlink();
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

void Led ::updateBlink() {
    if (this->sm_getState() != LedStateMachine_SM::State::BLINK) {
        return;
    }

    if (++this->m_blinkTicks < 10) {
        return;
    }

    Fw::Logic nextLevel = (this->m_blinkLevel == Fw::Logic::HIGH) ? Fw::Logic::LOW : Fw::Logic::HIGH;

    if (this->setLedLevel(nextLevel)) {
        this->m_blinkTicks = 0;
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
    this->log_ACTIVITY_HI_StateChanged(LedMode::OFF);
    this->tlmWrite_LedState(LedMode::OFF);
}

void Led ::LedStateMachine_SM_action_exitOff(SmId smId, LedStateMachine_SM::Signal signal) {}

void Led ::LedStateMachine_SM_action_enterOn(SmId smId, LedStateMachine_SM::Signal signal) {
    this->setLedLevel(Fw::Logic::HIGH);
    this->log_ACTIVITY_HI_StateChanged(LedMode::ON);
    this->tlmWrite_LedState(LedMode::ON);
}

void Led ::LedStateMachine_SM_action_exitOn(SmId smId, LedStateMachine_SM::Signal signal) {}

void Led ::LedStateMachine_SM_action_enterBlink(SmId smId, LedStateMachine_SM::Signal signal) {
    this->m_blinkTicks = 0;
    this->setLedLevel(Fw::Logic::HIGH);
    this->log_ACTIVITY_HI_StateChanged(LedMode::BLINK);
    this->tlmWrite_LedState(LedMode::BLINK);
}

void Led ::LedStateMachine_SM_action_exitBlink(SmId smId, LedStateMachine_SM::Signal signal) {}

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

    this->m_blinkLevel = level;
    return true;
}

}  // namespace LedStateMachine
