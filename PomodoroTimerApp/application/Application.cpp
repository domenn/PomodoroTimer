//
// Created by domen on 23. 11. 2018.
//

#include "Application.h"

Application::Application(ApplicationMode const &applicationMode)
    : session(Session::create(applicationMode))
{}

void Application::start()
{
	session->initialize();
}

long long Application::getMainTimerValue()
{
	return session->getMainTimerValue();
}
