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

    //! Handler implementation for tick
    //!
    //! Rate group; button polling + blink clock
    void tick_handler(FwIndexType portNum,  //!< The port number
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

    //! Implementation for action enterBlinkOn of state machine LedStateMachine_SM
    void LedStateMachine_SM_action_enterBlinkOn(SmId smId,                         //!< The state machine id
                                                LedStateMachine_SM::Signal signal  //!< The signal
                                                ) override;

    //! Implementation for action exitBlinkOn of state machine LedStateMachine_SM
    void LedStateMachine_SM_action_exitBlinkOn(SmId smId,                         //!< The state machine id
                                               LedStateMachine_SM::Signal signal  //!< The signal
                                               ) override;

    //! Implementation for action enterBlinkOff of state machine LedStateMachine_SM
    void LedStateMachine_SM_action_enterBlinkOff(SmId smId,                         //!< The state machine id
                                                 LedStateMachine_SM::Signal signal  //!< The signal
                                                 ) override;

    //! Implementation for action exitBlinkOff of state machine LedStateMachine_SM
    void LedStateMachine_SM_action_exitBlinkOff(SmId smId,                         //!< The state machine id
                                                LedStateMachine_SM::Signal signal  //!< The signal
                                                ) override;

  private:
    // ----------------------------------------------------------------------
    // Implementations for internal state machine guards
    // ----------------------------------------------------------------------

    //! Implementation for guard blinkPeriodElapsed of state machine LedStateMachine_SM
    bool LedStateMachine_SM_guard_blinkPeriodElapsed(SmId smId,                         //!< The state machine id
                                                     LedStateMachine_SM::Signal signal  //!< The signal
    ) const override;

  private:
    // ----------------------------------------------------------------------
    // Helper functions
    // ----------------------------------------------------------------------

    //! Set the LED GPIO level; return true if the write succeeds
    bool setLedLevel(Fw::Logic level);

    //! Read button GPIOs and send SM signals on active-low press edges
    void pollButtons();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! Previous button levels for rising/falling edge detection (active-low press)
    Fw::Logic m_lastRed = Fw::Logic::HIGH;
    Fw::Logic m_lastYellow = Fw::Logic::HIGH;
    Fw::Logic m_lastGreen = Fw::Logic::HIGH;

    U32 m_ticks = 0;
};

}  // namespace LedStateMachine

#endif
