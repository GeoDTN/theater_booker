#include <algorithm>
#include <iostream>
#include <numeric>

#include "theater_booker.hpp"

theater_booker::theater_booker(unordered_map<string, string> playing_movies) : playing_movies_(playing_movies)
{
  unordered_set<int> seats(max_number_of_seats_);
  for (uint8_t i = 1; i < max_number_of_seats_ + 1; ++i) { seats.insert(i); }
  for (const auto [theater, movie] : playing_movies_) { theaters_.insert({ theater, seats }); }
}

void theater_booker::update_theaters(const string &theater_name, const string &movie_name) noexcept
{
  std::lock_guard guard(mtx_1_);

  playing_movies_[theater_name] = movie_name;
  unordered_set<int> seats(max_number_of_seats_);// initially all seats are available
  for (uint8_t i = 1; i < max_number_of_seats_ + 1; ++i) { seats.insert(i); }
  theaters_[theater_name] = seats;
}

unordered_set<int> theater_booker::see_available_seats(const string &theater_name, const string &movie_name) noexcept
{
  // To Do : return seats with messages of reason ?
  auto is_theater_found = theaters_.find(theater_name);
  auto is_movie_found = playing_movies_.find(theater_name);

  if (is_theater_found == theaters_.end() || is_movie_found == playing_movies_.end()) {
    return unordered_set<int>(0);// return empty set
  }
  auto seats = theaters_[theater_name];
  return seats;
}

unordered_set<int> theater_booker::book_seats(const string &theater_name,
  const unordered_set<int> &requested_seats) noexcept
{
  std::lock_guard guard(mtx_1_);
  if (std::any_of(
        requested_seats.begin(), requested_seats.end(), [](auto requested_seat) { return requested_seat < 1; })) {
    std::cerr << "\033[31m" << "invalid seat number. Valid seat numbers are [1-20]" << std::endl;
    return unordered_set<int>(0);
  }
  // As multiple users  may try to book at the same time
  // and  there is writing, this section needs synchronization
  auto is_theater_showing_movie = theaters_.find(theater_name);
  if (is_theater_showing_movie == theaters_.end()) {
    // To Do : return with message to make clear if it is movie or seat unavailabilty
    // but the use case for now is movie is already available and playing
    // return empty set means no seat is available
    return unordered_set<int>(0);
  }
  auto booked_seats = requested_seats;

  auto available_seats = theaters_[theater_name];
  for (const auto &seat : requested_seats) {
    auto it = available_seats.find(seat);
    if (it != available_seats.end()) {
      available_seats.erase(it);// in next request it should be unavailable
    } else {
      // if the requested seat(s) not available, remove from returned seats
      booked_seats.erase(seat);
    }
  }

  theaters_[theater_name] = available_seats;// update available seats for the movie
  return booked_seats;
}
