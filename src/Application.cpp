#include "Application.h"
Application::Application(BlindsControlViewController *controller)
    : controller_(controller) {}

void Application::setup() { controller_->loadView(); }

void Application::loop() { controller_->loop(); }
