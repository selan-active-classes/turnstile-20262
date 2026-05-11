/**
 * This class implements a Turnstile as a Finit State Machine.
 */
#ifndef TURNSTILE_HPP
#define TURNSTILE_HPP

#include <cstddef>
#include <cstdint>

/// Possible state of the FSM.
enum state_e : std::uint8_t {
  START = 0,
  LOCKED,
  UNLOCKED,
  OUT_OF_SERVICE,
  STOP,
};

/// Possible user inputs.
enum input_e : std::uint8_t {
  PUSH = 0,   //!< push the turnstile.
  COIN,       //!< Insert coin to open turnstile.
  ON,         //!< Turn back on turnstile if it's out of service.
  OFF,        //!< Turn off the turnstile (out of service).
  END,        //!< Request the simulation to end.
  UNDEFINED,  //!< Undefined input.
};

class Turnstile {
  state_e m_state{ START };              //!< Current state.
  input_e m_input{ UNDEFINED };          //!< Current input.
  std::size_t m_coins{ 0 };              //!< Keeps track of coins collected.
  std::size_t m_n_out_of_services{ 0 };  //!< How many times out of service.

public:
  /// Default Ctro.
  Turnstile() = default;
  /// Returns true if turnstile is (temporarily) out of order.
  [[nodiscard]] bool out_of_order() const { return m_state == OUT_OF_SERVICE; }
  /// Returns true if user requested the simulation to end.
  [[nodiscard]] bool ended() const { return m_state == STOP; }
  /// Returns the total of coins collected during the simulation.
  [[nodiscard]] size_t get_coins() const { return m_coins; }
  /// Returns the total of coins collected during the simulation.
  [[nodiscard]] size_t how_many_times_out_of_service() const { return m_n_out_of_services; }

  //== Methods from the Game Loop Design pattern.
  void process_events();
  void update();
  void render() const;
};

#endif  // !TURNSTILE_HPP
