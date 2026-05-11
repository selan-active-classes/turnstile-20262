#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "turnstile.hpp"

/// Returns a lowercase version of the input string.
std::string to_lower(std::string_view s) {
  std::string str{ s };
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
};

void Turnstile::process_events() {
  // TODO:
}

void Turnstile::update() {
  // TODO:
}

// Show current state and corresponding input message.
void Turnstile::render() const {
  if (m_state == OUT_OF_SERVICE) {
    std::cout << "\nStatus: [OUT OF SERVICE] 🚧\n";
    std::cout << "Which action (on, end)? " << std::flush;
  } else if (m_state == LOCKED) {
    std::cout << "\nStatus: [LOCKED] 🔐\n";
    std::cout << "Which action (coin, push, off)? " << std::flush;
  } else if (m_state == UNLOCKED) {
    std::cout << "\nStatus: [UNLOCKED] 🔓\n";
    std::cout << "Which action (coin, push, off)? " << std::flush;
  } else if (m_state == STOP) {
    std::cout << "\nStatus: [ENDING SIMULATION] 🔚\n";
  } else if (m_input == UNDEFINED) {
    std::cout << "\nStatus: Unknown command ⁉️\n";
  }
}
