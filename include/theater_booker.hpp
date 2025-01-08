#ifndef THEATER_BOOKER_H_
#define THEATER_BOOKER_H_

#include <mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::unordered_set;
using std::string;
using std::unordered_map;

class theater_booker
{
public:
  explicit theater_booker(unordered_map<string, string> playing_movies);
  inline unordered_set<string> see_playing_movies() const noexcept
  {
    unordered_set<string> playing_movies{};
    for (const auto &[theater, movie] : playing_movies_) { playing_movies.insert(movie); }

    return playing_movies;
  }

  inline unordered_set<string> see_theaters_showing_movies() const noexcept
  {
    unordered_set<string> theaters_showing_movies{};
    for (const auto &[theater, movie] : playing_movies_) { theaters_showing_movies.insert(theater); }

    return theaters_showing_movies;
  }
  // Not to violate YAGNI :)
  // use case: may be theater is no more available for unexpected reasons like security issue ...
  inline void delete_theater(const string &theater_name)
  {
    std::lock_guard lock(mtx_1_);// C++17 CTAD
    theaters_.erase(theater_name);
    playing_movies_.erase(theater_name);
  }
  // Not to violate YAGNI :)
  // use case: may be when new movie starts
  void update_theaters(const string &theater_name, const string &movie_name) noexcept;
  unordered_set<int> see_available_seats(const string &theater_name, const string &movie_name) noexcept;
  // the client code collects all selected seats & communicates this function when user clicks ok
  // or submit
  // empty set means no requested seat(s) is available
  unordered_set<int> book_seats(const string &movie_name, const unordered_set<int> &seats_numbers) noexcept;

private:
  std::mutex mtx_1_;
  // <theater_name,available_seats>
  unordered_map<string, unordered_set<int>> theaters_{};
  // <theater_name, movie_name>
  unordered_map<string, string> playing_movies_{};
  size_t max_number_of_seats_{ 20 };
};

#endif