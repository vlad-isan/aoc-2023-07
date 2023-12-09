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

struct Hand {
    std::array<Card, 5> cards;
    uint64_t bid;

    Hand(const std::string &hand_str, uint64_t bid);

private:
    std::unordered_map<Card, uint64_t> cards_count;
};

int puzzle_sample_1(const std::string &base_file_path);

int puzzle_sample_2(const std::string &base_file_path);

int puzzle_1(const std::string &base_file_path);

int puzzle_2(const std::string &base_file_path);

int do_puzzle_1(std::ifstream &file);

int do_puzzle_2(std::ifstream &file);

#endif //PUZZLE_H
