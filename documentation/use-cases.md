# Use Cases

## Startup device

1. User pushes power button
2. Device displays startup
3. Device gets battery level
4. If battery level < 3%
   1. Device displays error
   2. Device waits for 5 seconds
   3. Device turns off
5. Device connects to wireless network
6. If connection unsuccessful
   1. Device retries to connect until successful
7. Device loads enabling state of blinds
8. Device displays blind controls, battery level and menu

## Enable and disable blinds

1. User enables/disables a blind to control
2. System stores selection

## Move blinds

1. User selects move command (up, down, stop)
2. System sends move command to enabled blinds
3. If sending a move command is unsuccessful
   1. Device displays error message for 5 seconds

## Display battery level

1. Device gets battery level
2. Device displays battery level
   * Colors indicate level (e.g. red < 10%, 11% < yellow < 49%, green > 50%)
   * Blinking or tone indicates need to charge if level is e.g. < 5%

## Power down by button

1. User pushes power button
2. Device saves unsaved data
3. Device turns off

## Power down after timeout

1. Device is idle for 2 (tbc - the time the longest blind takes to open/close + margin) minutes
2. Device turns off

## Power down because of low battery

1. Device determines battery level
2. If battery level < 3%
3. Device displays error
4. Device waits for 5 seconds
5. Device turns off
