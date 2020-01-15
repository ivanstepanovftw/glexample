//
// Created by ivan on 12.01.2020.
//

#pragma once

#include <exception>
#include <string>
#include <stdexcept>

class WindowException : public std::logic_error {
    using std::logic_error::logic_error;
};
