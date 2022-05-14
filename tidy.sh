#!/bin/sh
clang-tidy *.cpp -checks=bugprone-*,misc-*,performance-*,portability-*,readability-*,-readability-braces-around-statements,-readability-magic-numbers -- -DCPORTA -DMAIN_ASSIGNMENT -DMAIN_GAME -DMEMTRACE
#,-cppcoreguidelines-init-variables,cppcoreguidelines-*,-cppcoreguidelines-avoid-magic-numbers
