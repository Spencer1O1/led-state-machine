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
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command TODO_1
    //!
    //! TODO
    void TODO_1_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                           U32 cmdSeq            //!< The command sequence number
                           ) override;

    //! Handler implementation for command TODO_2
    //!
    //! TODO
    void TODO_2_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                           U32 cmdSeq            //!< The command sequence number
                           ) override;
};

}  // namespace LedStateMachine

#endif
