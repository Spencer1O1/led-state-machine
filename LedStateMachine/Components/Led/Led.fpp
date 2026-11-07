module LedStateMachine {
    enum LedMode {
        OFF
        ON
        BLINK
    }

    enum LedState {
        OFF
        ON
        BLINK_ON
        BLINK_OFF
    }

    @ Led with 3 states
    queued component Led {
        state machine instance sm: SM

        @ Press the red button (OFF)
        async command RED

        @ Press the green button (ON)
        async command GREEN

        @ Press the yellow button (BLINK)
        async command YELLOW

        @ LED operating mode changed
        event ModeChanged(mode: LedMode) \
            severity activity high \
            format "LED mode changed to {}"

        event DEBUG(button: Fw.Logic) severity activity high format "{}"

        @ Current leaf state of the LED state machine
        telemetry LedState: LedState update on change

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Enables command handling
        import Fw.Command

        @ Enables event handling
        import Fw.Event

        @ Enables telemetry channels handling
        import Fw.Channel

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

        ###############################################################################
        # App-defined ports                                                           #
        ###############################################################################

        @ Rate group; button polling + blink clock
        sync input port tick: Svc.Sched

        @ GPIO ports to read the button GPIOs
        output port gpioRead: [3] Drv.GpioRead

        @ GPIO port to write to LED
        output port gpioWrite: Drv.GpioWrite
    }
}
