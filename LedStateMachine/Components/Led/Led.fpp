module LedStateMachine {
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
        event StateChanged(
            $state: string size 16  @< State name
        ) \
            severity activity high \
            format "LED entered {}"

        @ Current LED state name
        telemetry LedState: string size 16

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

    }
}
