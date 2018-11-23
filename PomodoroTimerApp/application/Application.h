//
// Created by domen on 23. 11. 2018.
//
#pragma once

#include "Session.h"
#include "ApplicationMode.h"

class Application {
    Session* const session;

public:
    Application(ApplicationMode const & applicationMode);

};