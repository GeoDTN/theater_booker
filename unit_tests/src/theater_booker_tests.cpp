#include "theater_booker_tests.hpp"


unordered_map<string,string> playing_movies{
  {"theater_2","movie_2"}, \
  {"theater_1","movie_1"}, \
  {"theater_3","movie_3"}, \
  {"theater_4","movie_4"}, \
  {"theater_5","movie_5"}, \
  {"theater_6","movie_6"}, \ 
  {"theater_7","movie_7"}, \
  {"theater_8","movie_8"}};

theater_booker thter_booker(playing_movies);

TEST(theater_booker_tests, see_playing_movies_test_positive)
{
  auto movies = thter_booker.see_playing_movies();
  std::unordered_set<string> test_movies{
    "movie_2", "movie_1", "movie_3", "movie_4", "movie_5", "movie_6", "movie_7", "movie_8"
  };

  EXPECT_EQ(movies, test_movies);
}

TEST(theater_booker_tests, see_playing_movies_test_negative) {}

TEST(theater_booker_tests, see_theaters_showing_movies_test_positive)
{
  auto theaters = thter_booker.see_theaters_showing_movies();
  unordered_set<string> test_theaters{
    "theater_2", "theater_1", "theater_3", "theater_4", "theater_5", "theater_6", "theater_7", "theater_8"
  };

  EXPECT_EQ(theaters, test_theaters);
}

TEST(theater_booker_Tests, see_theaters_showing_movies_test_negative) {}


TEST(theater_booker_tests, see_available_seats_test_positive)
{
  auto seats = thter_booker.see_available_seats("theater_6", "movie_6");
  unordered_set<int> seats_test{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
  EXPECT_EQ(seats, seats_test);
  thter_booker.book_seats("theater_6", { 1, 2 });
  seats = thter_booker.see_available_seats("theater_6", "movie_6");
  seats_test = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
  EXPECT_EQ(seats, seats_test);
}

TEST(theater_booker_Tests, see_available_seats_test_negative) {}

TEST(theater_booker_tests, book_seats_test_positive)
{
  auto booked_seats = thter_booker.book_seats("theater_6", { -1, 1, 2 });

  EXPECT_EQ(unordered_set<int>(0), booked_seats);

  booked_seats = thter_booker.book_seats("theater_6", { 3, 4 });
  unordered_set<int> seats_test{ 3, 4 };
  EXPECT_EQ(booked_seats, seats_test);

  booked_seats = thter_booker.book_seats("theater_6", { 3, 4 });// expected only 0
  EXPECT_EQ(unordered_set<int>(0), booked_seats);

  seats_test = { 5 };
  booked_seats = thter_booker.book_seats("theater_6", { 3, 4, 5 });// expected only 5
  EXPECT_EQ(booked_seats, seats_test);
}

TEST(theater_booker_Tests, book_seats_test_negative) {}
