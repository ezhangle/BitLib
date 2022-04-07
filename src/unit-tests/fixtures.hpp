// =============================== FIXTURES ================================= //
// Project:         The Experimental Bit Algorithms Library
// Description:     Fixtures for testing 
// Creator:         Bryce Kille [2019]
// License:         BSD 3-Clause License
// ========================================================================== //
#ifndef _FIXTURES_HPP_INCLUDED
#define _FIXTURES_HPP_INCLUDED
// ========================================================================== //


// ============================== PREAMBLE ================================== //
// C++ standard library
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <random>
#include <limits>
#include <cstring>
// Project sources
#include "bitlib/bit-iterator/bit_iterator.hpp"
#include "bitlib/bit-containers/bit-containers.hpp"
#include "test_utils.hpp"
// Third-party libraries
#include "gtest/gtest.h"
// Miscellaneous
// ========================================================================== //


//TODO tests need a lot of cleanup. We should only copy what we need from random_vec
//and also refactor the vec generation to reduce duplication

using BaseTypes = ::testing::Types<unsigned char, unsigned short, unsigned int, unsigned long long>;
//using BaseTypes = ::testing::Types<unsigned char>;


template<typename WordType>
class VectorTest : public testing::Test {
    protected:

    using base_type = WordType;
    bit::bit_vector<WordType> empty_vec;
    bit::bit_vector<WordType> v2_ {256};
    bit::bit_vector<WordType> v3_ {"010111111"};

    std::vector<bit::bit_vector<WordType>> random_bitvecs;
    std::vector<std::vector<bool>> random_boolvecs;
    std::vector<WordType> random_vec;
    size_t word_size = 4;
    size_t bit_size = word_size*bit::binary_digits<WordType>::value;

    void SetUp() override {
        empty_vec = bit::bit_vector<WordType>(); 
        random_vec = get_random_vec<WordType>(word_size);
        for (size_t cont_size = 1; cont_size < bit_size; ++cont_size) {
            auto bitvec = bit::bit_vector<WordType>(bit_size);
            std::memcpy(&(*bitvec.begin().base()), &(random_vec[0]), word_size);
            bitvec.resize(cont_size);

            auto boolvec = boolvec_from_bitvec(bitvec);
            random_bitvecs.push_back(bitvec);
            random_boolvecs.push_back(boolvec);
        }
        size_t big_size = 64*64*10;
        for (int i = -4; i < 4; ++i) {
            size_t cont_size = big_size + i;
            auto bitvec = bit::bit_vector<WordType>(bit_size);
            std::memcpy(&(*bitvec.begin().base()), &(random_vec[0]), word_size);
            bitvec.resize(cont_size);

            auto boolvec = boolvec_from_bitvec(bitvec);
            random_bitvecs.push_back(bitvec);
            random_boolvecs.push_back(boolvec);
        }
    }
};
TYPED_TEST_SUITE(VectorTest, BaseTypes);

template<typename WordType>
class SingleRangeTest : public testing::Test {
    protected:

    using base_type = WordType;

    std::vector<bit::bit_vector<WordType>> random_bitvecs;
    std::vector<std::vector<bool>> random_boolvecs;
    std::vector<WordType> random_vec;
    size_t word_size = 4;
    size_t bit_size = word_size*bit::binary_digits<WordType>::value;

    void SetUp() override {
        random_vec = get_random_vec<WordType>(word_size);
        for (size_t cont_size = 1; cont_size < bit_size; ++cont_size) {
            auto bitvec = bit::bit_vector<WordType>(bit_size);
            std::copy(random_vec.begin(), random_vec.end(), bitvec.begin().base());
            bitvec.resize(cont_size);

            auto boolvec = boolvec_from_bitvec(bitvec);
            random_bitvecs.push_back(bitvec);
            random_boolvecs.push_back(boolvec);
        }
        size_t big_size = 64*64*10;
        for (int i = -4; i < 4; ++i) {
            size_t cont_size = big_size + i;
            auto bitvec = bit::bit_vector<WordType>(bit_size);
            std::copy(random_vec.begin(), random_vec.end(), bitvec.begin().base());
            bitvec.resize(cont_size);

            auto boolvec = boolvec_from_bitvec(bitvec);
            random_bitvecs.push_back(bitvec);
            random_boolvecs.push_back(boolvec);
        }
    }
};
TYPED_TEST_SUITE(SingleRangeTest, BaseTypes);

template<typename WordType>
class DoubleRangeTest : public testing::Test {
    protected:

    using base_type = WordType;

    std::vector<bit::bit_vector<WordType>> random_bitvecs1;
    std::vector<bit::bit_vector<WordType>> random_bitvecs2;
    std::vector<std::vector<bool>> random_boolvecs1;
    std::vector<std::vector<bool>> random_boolvecs2;
    std::vector<WordType> random_vec;
    size_t word_size = 4;
    size_t bit_size = word_size*bit::binary_digits<WordType>::value;

    void SetUp() override {
        // TODO this is ugly, need to refactor
        random_vec = get_random_vec<WordType>(word_size);
        for (size_t cont_size = 1; cont_size < bit_size; ++cont_size) {
            auto bitvec = bit::bit_vector<WordType>(bit_size);
            std::copy(random_vec.begin(), random_vec.end(), bitvec.begin().base());
            bitvec.resize(cont_size);

            auto boolvec = boolvec_from_bitvec(bitvec);
            random_bitvecs1.push_back(bitvec);
            random_boolvecs1.push_back(boolvec);
        }
        size_t big_size = 64*64*10;
        for (int i = -4; i < 4; ++i) {
            size_t cont_size = big_size + i;
            auto bitvec = bit::bit_vector<WordType>(bit_size);
            std::copy(random_vec.begin(), random_vec.end(), bitvec.begin().base());
            bitvec.resize(cont_size);

            auto boolvec = boolvec_from_bitvec(bitvec);
            random_bitvecs1.push_back(bitvec);
            random_boolvecs1.push_back(boolvec);
        }
        random_vec = get_random_vec<WordType>(word_size);
        for (size_t cont_size = 1; cont_size < bit_size; ++cont_size) {
            auto bitvec = bit::bit_vector<WordType>(bit_size);
            std::copy(random_vec.begin(), random_vec.end(), bitvec.begin().base());
            bitvec.resize(cont_size);

            auto boolvec = boolvec_from_bitvec(bitvec);
            random_bitvecs2.push_back(bitvec);
            random_boolvecs2.push_back(boolvec);
        }
        for (int i = -4; i < 4; ++i) {
            size_t cont_size = big_size + i;
            auto bitvec = bit::bit_vector<WordType>(bit_size);
            std::copy(random_vec.begin(), random_vec.end(), bitvec.begin().base());
            bitvec.resize(cont_size);

            auto boolvec = boolvec_from_bitvec(bitvec);
            random_bitvecs2.push_back(bitvec);
            random_boolvecs2.push_back(boolvec);
        }
    }
};
TYPED_TEST_SUITE(DoubleRangeTest, BaseTypes);
// ========================================================================== //
#endif // _FIXTURES_HPP_INCLUDED
// ========================================================================== //