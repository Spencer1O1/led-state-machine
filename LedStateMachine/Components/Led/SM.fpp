module LedStateMachine {
    state machine SM {
        action enterOff
        action exitOff
        action enterOn
        action exitOn
        action enterBlink
        action exitBlink

        action enterBlinkOn
        action exitBlinkOn
        action enterBlinkOff
        action exitBlinkOff

        signal redButton
        signal greenButton
        signal yellowButton
        signal tick

        guard blinkPeriodElapsed

        initial enter INIT

        state INIT {
            on tick enter OFF
        }

        state OFF {
            entry do { enterOff }
            on greenButton enter ON
            on yellowButton enter BLINK
            exit do { exitOff }
        }
        state ON {
            entry do { enterOn }
            on redButton enter OFF
            on yellowButton enter BLINK
            exit do { exitOn }
        }
        state BLINK {
            entry do { enterBlink }

            on redButton enter OFF
            on greenButton enter ON

            initial enter BLINK_ON

            state BLINK_ON {
                entry do { enterBlinkOn }
                on tick if blinkPeriodElapsed enter BLINK_OFF
                exit do { exitBlinkOn }
            }

            state BLINK_OFF {
                entry do { enterBlinkOff }
                on tick if blinkPeriodElapsed enter BLINK_ON
                exit do { exitBlinkOff }
            }

            exit do { exitBlink }
        }
    }
}
