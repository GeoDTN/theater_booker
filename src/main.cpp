#include <iostream>

#include "theater_booker.hpp"

int main(int argc, const char **argv)
{
  unordered_map<string,string> playing_movies{
  {"theater_1","movie_1"}, \
  {"theater_2","movie_2"}, \
  {"theater_3","movie_3"}, \
  {"theater_4","movie_4"}, \
  {"theater_5","movie_5"}, \
  {"theater_6","movie_6"}, \ 
  {"theater_7","movie_7"}, \
  {"theater_8","movie_8"}};

  theater_booker theater_booker(playing_movies);
  auto movies = theater_booker.see_playing_movies();
  std::cout << "movies \n";
  for (auto movie : movies) std::cout << movie << ' ' << "\t";
  std::cout << "\n";
  auto theaters = theater_booker.see_theaters_showing_movies();
  std::cout << "theaters \n";
  for (auto theater : theaters) std::cout << theater << ' ' << "\t";
  std::cout << "\n";

  auto seats = theater_booker.see_available_seats("theater_6", "movie_6");
  std::cout << "seats in theater 6 \n";
  for (auto seat : seats) std::cout << seat << ' ' << "\t";
  std::cout << "\n\n";

  std::cout << "seats in theater 6 after booking\n";
  theater_booker.book_seats("theater_6", { 1, 2 });
  seats = theater_booker.see_available_seats("theater_6", "movie_6");
  for (auto seat : seats) std::cout << seat << ' ' << "\t";
  std::cout << "\n\n";

  std::cout << "seats in theater 6 after booking with -ve number\n";
  theater_booker.book_seats("theater_6", { -1, 1, 2 });
  seats = theater_booker.see_available_seats("theater_6", "movie_6");
  for (auto seat : seats) std::cout << seat << ' ' << "\t";
  std::cout << "\n\n";

  std::cout << "seats in theater 6 after booking with -ve number\n";
  auto booked_seats = theater_booker.book_seats("theater_6", { -1, 1, 2 });
  for (auto seat : booked_seats) std::cout << seat << ' ' << "\t";// none
  std::cout << "\n\n";

  std::cout << "seats booked in theater 6 \n";
  booked_seats = theater_booker.book_seats("theater_6", { 3, 4 });// expected only 3,4
  for (auto seat : booked_seats) std::cout << seat << ' ' << "\t";
  std::cout << "\n\n";

  std::cout << "seats booked in theater 6 with request including unavailable seats \n";
  booked_seats = theater_booker.book_seats("theater_6", { 3, 4 });// expected only 0
  for (auto seat : booked_seats) std::cout << seat << ' ' << "\t";
  std::cout << "\n\n";

  std::cout << "seats booked in theater 6 with request of unavailable seats \n";
  booked_seats = theater_booker.book_seats("theater_6", { 3, 4, 5 });// expected only 5
  for (auto seat : booked_seats) std::cout << seat << ' ' << "\t";
  std::cout << "\n\n";
}
