module LedStateMachine {
    state machine SM {
        action enterOff
        action exitOff
        action enterOn
        action exitOn
        action enterBlink
        action exitBlink

        signal redButton
        signal greenButton
        signal yellowButton

        initial enter OFF

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
            exit do { exitBlink }
        }
    }
}
