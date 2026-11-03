module LedStateMachine {
    enum LedMode {
        OFF
        ON
        BLINK
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

        @ LED entered a new state
        event StateChanged(mode: LedMode) \
            severity activity high \
            format "LED entered {}"

        @ Current LED state name
        telemetry LedState: LedMode

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

        @ Rate group; drives blinking + optional button polling
        sync input port run: Svc.Sched

        @ GPIO ports to read the button GPIOs
        output port gpioRead: [3] Drv.GpioRead

        @ GPIO port to write to LED
        output port gpioWrite: Drv.GpioWrite
    }
}
