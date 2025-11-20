/*
  ==============================================================================

    State.h
    Created: 20 Nov 2025 1:25:29pm
    Author:  Arjun Shenoy

  ==============================================================================
*/

#pragma once
#include <atomic>

struct MidiState
{
    std::atomic<int> lastNoteNumber { -1 };
};
