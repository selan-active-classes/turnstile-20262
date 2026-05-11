/**
 * This program simulates the operation of a Turnstile.
 * The goal is to model the Turnstile's operation as a Finit State Machine.
 * The program also relies on the Game Loop design pattern
 * to control the simulation.
 *
 * @author Selan
 * @date September 25th, 2025
 */
#include <cassert>
#include <iostream>

#include "turnstile.hpp"

int main() {
  Turnstile ts;
  while (not ts.ended()) {  // Keep going until the simulation ends.
    ts.process_events();
    ts.update();
    ts.render();
  }
  std::cout << "\n>>> Coins collected: " << ts.get_coins() << '\n';
  std::cout << "\n>>> # times out of service: " << ts.how_many_times_out_of_service() << '\n';
  return 0;
}
