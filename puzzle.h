//
// Created by Vlad Isan on 05/12/2023.
//

#ifndef PUZZLE_H
#define PUZZLE_H

#include <algorithm>
#include <array>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <ranges>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "fmt/core.h"

enum class Card {
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
};

enum class Card2 {
    JOKER,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    QUEEN,
    KING,
    ACE
};

const std::unordered_map<char, Card> cards_map = {
        {'2', Card::TWO},
        {'3', Card::THREE},
        {'4', Card::FOUR},
        {'5', Card::FIVE},
        {'6', Card::SIX},
        {'7', Card::SEVEN},
        {'8', Card::EIGHT},
        {'9', Card::NINE},
        {'T', Card::TEN},
        {'J', Card::JACK},
        {'Q', Card::QUEEN},
        {'K', Card::KING},
        {'A', Card::ACE}
};

const std::unordered_map<char, Card2> cards_map2 = {
        {'J', Card2::JOKER},
        {'2', Card2::TWO},
        {'3', Card2::THREE},
        {'4', Card2::FOUR},
        {'5', Card2::FIVE},
        {'6', Card2::SIX},
        {'7', Card2::SEVEN},
        {'8', Card2::EIGHT},
        {'9', Card2::NINE},
        {'T', Card2::TEN},
        {'Q', Card2::QUEEN},
        {'K', Card2::KING},
        {'A', Card2::ACE}
};

enum class HandType {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIRS,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND
};

struct Hand {
    HandType type;
    std::array<Card, 5> cards{};
    uint64_t bid;

    Hand(const std::string &hand_str, uint64_t bid);

    bool operator<(const Hand &other) const;

private:
    std::unordered_map<Card, uint64_t> cards_count;

    void calculate_hand_type();
};

struct Hand2 {
    HandType type;
    std::array<Card2, 5> cards{};
    uint64_t bid;

    Hand2(const std::string &hand_str, uint64_t bid);

    bool operator<(const Hand2 &other) const;

private:
    std::unordered_map<Card2, uint64_t> cards_count;

    void calculate_hand_type();
};

int puzzle_sample_1(const std::string &base_file_path);

int puzzle_sample_2(const std::string &base_file_path);

int puzzle_1(const std::string &base_file_path);

int puzzle_2(const std::string &base_file_path);

int do_puzzle_1(std::ifstream &file);

int do_puzzle_2(std::ifstream &file);

#endif //PUZZLE_H
