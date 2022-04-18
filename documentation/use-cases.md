# Use Cases

## Startup device

1. User pushes power button
2. Device gets battery level
3. If battery level < 10%
   1. Device displays "Low battery!" error
4. Device connects to wireless network
5. If connection unsuccessful
   1. Device retries to connect until successful
6. Device loads enabling state of blinds
7. Device displays blind control buttons, battery level, wireless connection state and status message.

## Enable and disable individual blinds

1. User enables/disables a blind to control
2. System stores selection

## Enable and disable all blinds

1. User enables/disables all blinds
2. System stores selection

## Move blinds

1. User selects move command (open, close, tilt, stop)
2. System sends move command to enabled blinds

## Display battery level

1. Device gets battery level
2. Device displays battery level
   * Colors indicate level (e.g. red < 10%, 11% < orange < 20%, 20% &le; green)

## Display WiFi connection status

1. Device gets WiFi connection status
2. Device displays connection status
3. If connection status is offline
   1. Device retries to connect until successful

## Power down by button

1. User presses power off button
2. Device saves unsaved data
3. Device turns off

## Power down after timeout

1. Device is idle for 1 minute (no buttons pressed)
2. Device saves unsaved data
3. Device turns off
