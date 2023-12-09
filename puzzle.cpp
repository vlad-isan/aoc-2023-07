//
// Created by Vlad Isan on 05/12/2023.
//

#include "puzzle.h"

int puzzle_sample_1(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-sample-1.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_1(file);
}

int puzzle_sample_2(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-sample-2.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_2(file);
}

int puzzle_1(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-1.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_1(file);
}

int puzzle_2(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-2.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_2(file);
}

int do_puzzle_1(std::ifstream &file) {
    std::string line;

    std::vector<Hand> hands;

    while (std::getline(file, line)) {
        std::istringstream iss(line);

        std::string hand_str;
        uint64_t bid;

        iss >> hand_str >> bid;

        hands.emplace_back(hand_str, bid);
    }

    // calculate ranks
    std::sort(hands.begin(), hands.end());

    uint64_t winnings = 0;

    auto indices = std::views::iota(0u, hands.size());
    for (const auto &[index, hand]: std::views::zip(indices, hands)) {
        winnings += (index + 1) * hand.bid;
    }

    return winnings;
}

int do_puzzle_2(std::ifstream &file) {
    std::string line;

    std::vector<Hand2> hands;

    while (std::getline(file, line)) {
        std::istringstream iss(line);

        std::string hand_str;
        uint64_t bid;

        iss >> hand_str >> bid;

        hands.emplace_back(hand_str, bid);
    }

    // calculate ranks
    std::sort(hands.begin(), hands.end());

    uint64_t winnings = 0;

    auto indices = std::views::iota(0u, hands.size());
    for (const auto &[index, hand]: std::views::zip(indices, hands)) {
        winnings += (index + 1) * hand.bid;
    }

    return winnings;
}

Hand::Hand(const std::string &hand_str, uint64_t bid) : bid(bid) {
    std::ranges::transform(hand_str, this->cards.begin(), [&](char c) {
        Card card = cards_map.at(c);

        this->cards_count[card]++;

        return card;
    });

    this->calculate_hand_type();
}

void Hand::calculate_hand_type() {
    if (this->cards_count.size() == 1) {
        this->type = HandType::FIVE_OF_A_KIND;
    } else if (this->cards_count.size() == 2) {
        if (std::ranges::any_of(this->cards_count, [](auto pair) { return pair.second == 4; })) {
            this->type = HandType::FOUR_OF_A_KIND;
        } else {
            this->type = HandType::FULL_HOUSE;
        }
    } else if (this->cards_count.size() == 3) {
        if (std::ranges::any_of(this->cards_count, [](auto pair) { return pair.second == 3; })) {
            this->type = HandType::THREE_OF_A_KIND;
        } else {
            this->type = HandType::TWO_PAIRS;
        }
    } else if (this->cards_count.size() == 4) {
        this->type = HandType::ONE_PAIR;
    } else {
        this->type = HandType::HIGH_CARD;
    }
}

bool Hand::operator<(const Hand &other) const {
    if (this->type != other.type) {
        return this->type < other.type;
    } else {
        return std::lexicographical_compare(this->cards.begin(), this->cards.end(), other.cards.begin(),
                                            other.cards.end());
    }
}

Hand2::Hand2(const std::string &hand_str, uint64_t bid) : bid(bid) {
    std::ranges::transform(hand_str, this->cards.begin(), [&](char c) {
        Card2 card = cards_map2.at(c);

        this->cards_count[card]++;

        return card;
    });

    this->calculate_hand_type();
}

void Hand2::calculate_hand_type() {
    if (this->cards_count.size() == 1) {
        this->type = HandType::FIVE_OF_A_KIND;
    } else if (this->cards_count.size() == 2) {
        if (std::ranges::any_of(this->cards_count, [](auto pair) { return pair.first == Card2::JOKER; })) {
            this->type = HandType::FIVE_OF_A_KIND;
        } else if (std::ranges::any_of(this->cards_count, [](auto pair) { return pair.second == 4; })) {
            this->type = HandType::FOUR_OF_A_KIND;
        } else {
            this->type = HandType::FULL_HOUSE;
        }
    } else if (this->cards_count.size() == 3) {
        if (std::ranges::any_of(this->cards_count, [](auto pair) { return pair.first == Card2::JOKER; })) {
            switch (this->cards_count[Card2::JOKER]) {
                case 1:
                    if (std::ranges::any_of(this->cards_count, [](auto pair) { return pair.second == 3; })) {
                        this->type = HandType::FOUR_OF_A_KIND;
                    } else {
                        this->type = HandType::FULL_HOUSE;
                    }
                    break;
                case 2:
                case 3:
                    this->type = HandType::FOUR_OF_A_KIND;
                    break;
            }
        } else if (std::ranges::any_of(this->cards_count, [](auto pair) { return pair.second == 3; })) {
            this->type = HandType::THREE_OF_A_KIND;
        } else {
            this->type = HandType::TWO_PAIRS;
        }
    } else if (this->cards_count.size() == 4) {
        if (std::ranges::any_of(this->cards_count, [](auto pair) { return pair.first == Card2::JOKER; })) {
            this->type = HandType::THREE_OF_A_KIND;
        } else {
            this->type = HandType::ONE_PAIR;
        }
    } else {
        if (std::ranges::any_of(this->cards_count, [](auto pair) { return pair.first == Card2::JOKER; })) {
            this->type = HandType::ONE_PAIR;
        } else {
            this->type = HandType::HIGH_CARD;
        }
    }
}

bool Hand2::operator<(const Hand2 &other) const {
    if (this->type != other.type) {
        return this->type < other.type;
    } else {
        return std::lexicographical_compare(this->cards.begin(), this->cards.end(), other.cards.begin(),
                                            other.cards.end());
    }
}
