/*
    m5_blinds_controller_with_one_blind

    This example turns your M5Stack Core2 device into a remote control for 
	blinds which are controlled by Shelly 2.5 relays in roller mode.
	See https://github.com/k-phi/M5Core2BlindsController for further 
	information.
	
    Created 2022
    By Philipp Kraft
*/

#include <M5Core2.h>
#include <ApplicationConfiguration.h>
#include <BlindConfiguration.h>
#include <Application.h>
#include <ApplicationFactory.h>

// Replace "your_ssid" with the SSID of our WiFi network.
// Replace "your_pass" with the passphrase of your WiFi network.
// Modify the 60000 milliseconds idle time to modify the time before the device
// is automatically shutting down.
// Modify the 1000 milliseconds timeout between HTTP requests if needed.
ApplicationConfiguration appConfig = {
	"your_ssid", 
	"your_passphrase", 
	60000, 
	1000};

// Add a blind configuration for each blind you want to control.
// Make sure that the IDs (first parameter) is unique and the button position
// (parameters 2 to 4) are sucht that the buttons do not overlap.
BlindConfiguration blindConfigs[1] = {
  {0, 20, 62, 100, 30, "192.168.86.24", true, 2.0f}
};

unsigned int numberOfBlindConfigs = sizeof(blindConfigs) / sizeof(blindConfigs[0]);

ApplicationFactory factory;
Application *application;

void setup() {
  application = factory.createApplication(&appConfig, blindConfigs, numberOfBlindConfigs);
  application->setup();
}

void loop() {
  M5.update();
  application->loop();
}
