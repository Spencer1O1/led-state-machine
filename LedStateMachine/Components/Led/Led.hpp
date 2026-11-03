// ======================================================================
// \title  Led.hpp
// \author spencerls
// \brief  hpp file for Led component implementation class
// ======================================================================

#ifndef LedStateMachine_Led_HPP
#define LedStateMachine_Led_HPP

#include "LedStateMachine/Components/Led/LedComponentAc.hpp"

namespace LedStateMachine {

class Led final : public LedComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct Led object
    Led(const char* const compName  //!< The component name
    );

    //! Destroy Led object
    ~Led();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for run
    //!
    //! Rate group; drives blinking + optional button polling
    void run_handler(FwIndexType portNum,  //!< The port number
                     U32 context           //!< The call order
                     ) override;

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command RED
    //!
    //! Press the red button (OFF)
    void RED_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                        U32 cmdSeq            //!< The command sequence number
                        ) override;

    //! Handler implementation for command GREEN
    //!
    //! Press the green button (ON)
    void GREEN_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                          U32 cmdSeq            //!< The command sequence number
                          ) override;

    //! Handler implementation for command YELLOW
    //!
    //! Press the yellow button (BLINK)
    void YELLOW_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                           U32 cmdSeq            //!< The command sequence number
                           ) override;

  private:
    // ----------------------------------------------------------------------
    // Implementations for internal state machine actions
    // ----------------------------------------------------------------------

    //! Implementation for action enterOff of state machine LedStateMachine_SM
    void LedStateMachine_SM_action_enterOff(SmId smId,                         //!< The state machine id
                                            LedStateMachine_SM::Signal signal  //!< The signal
                                            ) override;

    //! Implementation for action exitOff of state machine LedStateMachine_SM
    void LedStateMachine_SM_action_exitOff(SmId smId,                         //!< The state machine id
                                           LedStateMachine_SM::Signal signal  //!< The signal
                                           ) override;

    //! Implementation for action enterOn of state machine LedStateMachine_SM
    void LedStateMachine_SM_action_enterOn(SmId smId,                         //!< The state machine id
                                           LedStateMachine_SM::Signal signal  //!< The signal
                                           ) override;

    //! Implementation for action exitOn of state machine LedStateMachine_SM
    void LedStateMachine_SM_action_exitOn(SmId smId,                         //!< The state machine id
                                          LedStateMachine_SM::Signal signal  //!< The signal
                                          ) override;

    //! Implementation for action enterBlink of state machine LedStateMachine_SM
    void LedStateMachine_SM_action_enterBlink(SmId smId,                         //!< The state machine id
                                              LedStateMachine_SM::Signal signal  //!< The signal
                                              ) override;

    //! Implementation for action exitBlink of state machine LedStateMachine_SM
    void LedStateMachine_SM_action_exitBlink(SmId smId,                         //!< The state machine id
                                             LedStateMachine_SM::Signal signal  //!< The signal
                                             ) override;

  private:
    // ----------------------------------------------------------------------
    // Helper functions
    // ----------------------------------------------------------------------

    //! Read button GPIOs and send SM signals on active-low press edges
    void pollButtons();

    //! Toggle the LED while the state machine is in BLINK
    void updateBlink();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! Current blink level (HIGH = on, LOW = off)
    Fw::Logic m_blinkLevel = Fw::Logic::LOW;

    //! Previous button levels for rising/falling edge detection (active-low press)
    Fw::Logic m_lastRed = Fw::Logic::HIGH;
    Fw::Logic m_lastYellow = Fw::Logic::HIGH;
    Fw::Logic m_lastGreen = Fw::Logic::HIGH;
};

}  // namespace LedStateMachine

#endif
