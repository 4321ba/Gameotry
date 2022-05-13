#!/bin/sh
clang-tidy *.cpp -checks=bugprone-*,cppcoreguidelines-*,misc-*,performance-*,portability-*,readability-* -- -DCPORTA -DMAIN_ASSIGNMENT -DMAIN_GAME -DMEMTRACE
#,-readability-braces-around-statements,-cppcoreguidelines-init-variables,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers
