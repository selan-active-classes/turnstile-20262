#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "turnstile.hpp"
#include <unordered_map>

/// Returns a lowercase version of the input string.
std::string to_lower(std::string_view s) {
  std::string str{ s };
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
};

void Turnstile::process_events() {
  // Mapeia comandos do usuário para seu respectivo código numérico que o representa internamente.
  std::unordered_map<std::string, input_e> user_command_to_code{ { "push", PUSH }, { "p", PUSH },
                                                                 { "coin", COIN }, { "c", COIN },
                                                                 { "end", END },   { "off", OFF } };
  if (m_state == START) {
    return;  // Não há entrada nesse estado, nada a fazer.
  }
  // Ler qual o comando o usuário quer executar.
  std::string user_command;
  std::getline(std::cin, user_command);
  // NOTE: Aqui é o uso interessante de um dicionário, no lugar de vários ifs ou mesmo o switch.
  m_input = user_command_to_code[to_lower(user_command)];
}

void Turnstile::update() {
  if (m_state == START) {
    m_state = LOCKED;
  } else if (m_state == UNLOCKED) {
    // NOTE: Ações que não mudam o estado são ignoradas.
    if (m_input == PUSH) {
      m_state = LOCKED;
    } else if (m_input == OFF) {
      m_state = OUT_OF_SERVICE;
      m_n_out_of_services++;
    }
  } else if (m_state == LOCKED) {
    // NOTE: Ações que não mudam o estado são ignoradas.
    if (m_input == COIN) {
      m_state = UNLOCKED;
      m_coins++;
    } else if (m_input == OFF) {
      m_state = OUT_OF_SERVICE;
      m_n_out_of_services++;
    }
  } else if (m_state == OUT_OF_SERVICE) {
    if (m_input == END) {
      m_state = STOP;
    }
    if (m_input == ON) {
      m_state = LOCKED;
    }
  }
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
