#include "simdutf.h"

#include <array>
#include <iostream>

#include <tests/helpers/transcode_test_base.h>
#include <tests/helpers/random_int.h>
#include <tests/helpers/test.h>


namespace {
  std::array<size_t, 7> input_size{7, 16, 12, 64, 67, 128, 256};

  using simdutf::tests::helpers::transcode_utf8_to_latin1_test_base;

  constexpr size_t trials = 10000;
}

void printByteInBinary(const char& byte) {
    for (int i = 7; i >= 0; --i) {
        std::cout << ((byte >> i) & 1);
    }
    std::cout << std::endl;
}


TEST(convert_pure_ASCII) {
  for(size_t trial = 0; trial < trials; trial ++) {
    if((trial % 100) == 0) { std::cout << "."; std::cout.flush(); }
    size_t counter = 0;
    auto generator = [&counter]() -> uint8_t {
      return counter++ & 0x7f;
    };

    auto procedure = [&implementation](const char* utf8, size_t size, char* latin1) -> size_t {
      return implementation.convert_utf8_to_latin1(utf8, size, latin1);
    };
    auto size_procedure = [&implementation](const char* utf8, size_t size) -> size_t {
      return implementation.latin1_length_from_utf8(utf8, size);
    };

    for (size_t size: input_size) {
      transcode_utf8_to_latin1_test_base test(generator, size);
      ASSERT_TRUE(test(procedure));
      ASSERT_TRUE(test.check_size(size_procedure));
    }
  }
} 

TEST(convert_1_or_2_valid_UTF8_bytes_to_latin1) {
  for(size_t trial = 0; trial < trials; trial ++) {
    // printf("%i \n",trial);
    uint32_t seed{1234+uint32_t(trial)};
    if((trial % 100) == 0) { std::cout << "."; std::cout.flush(); }
    simdutf::tests::helpers::RandomInt random(0x0000, 0x0ff, seed); // range for 1 or 2 UTF-8 bytes

    auto procedure = [&implementation](const char* utf8, size_t size, char* latin1) -> size_t {
      return implementation.convert_utf8_to_latin1(utf8, size, latin1);
    };
    auto size_procedure = [&implementation](const char* utf8, size_t size) -> size_t {
      return implementation.latin1_length_from_utf8(utf8, size);
    };
    for (size_t size: input_size) {
      //printf("input size:%i \n",input_size);
      transcode_utf8_to_latin1_test_base test(random, size);
      ASSERT_TRUE(test(procedure));
      ASSERT_TRUE(test.check_size(size_procedure));
    }
  }
}

TEST(too_large_input) {
  uint32_t seed{1234};
  int fix_size = 512;
  simdutf::tests::helpers::RandomIntRanges random({//{0x0000, 0xff},
                                                {0x010000, 0x10FFFF}
                                                }, seed);

auto getUtf8SequenceLength = [](char byte) {
    if ((byte & 0b11100000) == 0b11000000) { // 2 byte UTF-8 header
        return 2;
    }
    else if ((byte & 0b11110000) == 0b11100000) { // 3 byte UTF-8 header
        return 3;
    }
    else if ((byte & 0b11111000) == 0b11110000) { // 4 byte UTF-8 header
        return 4;
    }
    else {
        return 0; // 1 byte UTF-8 sequence (ASCII)
    }
};


  for(size_t trial = 0; trial < trials; trial++) {
    transcode_utf8_to_latin1_test_base test(random, fix_size);
    for (int i = 0; i < fix_size; i++) {

/*       printByteInBinary(test.input_utf8[i]);
      std::cout << i << "\n"; */

      auto header_type = getUtf8SequenceLength(test.input_utf8[i]);

      //if((test.input_utf8[i] & 0b11111000) == 0b11110000) { 
      if(header_type != 0) { 


        auto procedure = [&implementation, &i](const char* utf8, size_t size, char* latin1) -> size_t {
          simdutf::result res = implementation.convert_utf8_to_latin1_with_errors(utf8, size, latin1);
          ASSERT_EQUAL(res.error,simdutf::error_code::TOO_LARGE);
          ASSERT_EQUAL(res.count,i); 
          return 0;
        };


        //test.input_utf8[i] += ((test.input_utf8[i] & 0b100) == 0b100) ? 0b10 : 0b100;   // Make sure we get too large error and not header bits error
        ASSERT_TRUE(test(procedure)); //no conversion should take place
        //test.input_utf8[i] -= 0b100;
/*           if (i + 3 < test.input_utf8.size()) {
            test.input_utf8[i] = 0x2a;
            test.input_utf8[i+1] = 0x2a;
            test.input_utf8[i+2] = 0x2a;
            test.input_utf8[i+3] = 0x2a;
          } */

          //does the same as the conditional above: e.g. replace a 4 byte by a '*' ASCII character once its done.
          for(auto it = test.input_utf8.begin(); it != test.input_utf8.end(); ++it) {
              if(std::distance(it, test.input_utf8.end()) >= header_type) { 
                  std::fill_n(it, header_type, 0x2a);
              }
          }

        }
    }
  }
}


/*
TEST(convert_1_or_2_or_3_UTF8_bytes) {
  for(size_t trial = 0; trial < trials; trial ++) {
    uint32_t seed{1234+uint32_t(trial)};
    if((trial % 100) == 0) { std::cout << "."; std::cout.flush(); }
    // range for 1, 2 or 3 UTF-8 bytes
    simdutf::tests::helpers::RandomIntRanges random({{0x0000, 0xd7ff},
                                                     {0xe000, 0xffff}}, seed);

    auto procedure = [&implementation](const char* utf8, size_t size, char32_t* utf32) -> size_t {
      return implementation.convert_utf8_to_utf32(utf8, size, utf32);
    };
    auto size_procedure = [&implementation](const char* utf8, size_t size) -> size_t {
      return implementation.utf32_length_from_utf8(utf8, size);
    };
    for (size_t size: input_size) {
      transcode_utf8_to_utf32_test_base test(random, size);
      ASSERT_TRUE(test(procedure));
      ASSERT_TRUE(test.check_size(size_procedure));
    }
  }
}

TEST(convert_3_or_4_UTF8_bytes) {
  for(size_t trial = 0; trial < trials; trial ++) {
    uint32_t seed{1234+uint32_t(trial)};
    if((trial % 100) == 0) { std::cout << "."; std::cout.flush(); }
    simdutf::tests::helpers::RandomIntRanges random({{0x0800, 0xd800-1},
                                                     {0xe000, 0x10ffff}}, seed); // range for 3 or 4 UTF-8 bytes

    auto procedure = [&implementation](const char* utf8, size_t size, char32_t* utf32) -> size_t {
      return implementation.convert_utf8_to_utf32(utf8, size, utf32);
    };
    auto size_procedure = [&implementation](const char* utf8, size_t size) -> size_t {
      return implementation.utf32_length_from_utf8(utf8, size);
    };
    for (size_t size: input_size) {
      transcode_utf8_to_utf32_test_base test(random, size);
      ASSERT_TRUE(test(procedure));
      ASSERT_TRUE(test.check_size(size_procedure));
    }
  }
}


TEST(convert_null_4_UTF8_bytes) {
  for(size_t trial = 0; trial < trials; trial ++) {
    uint32_t seed{1234+uint32_t(trial)};
    if((trial % 100) == 0) { std::cout << "."; std::cout.flush(); }
    simdutf::tests::helpers::RandomIntRanges random({{0x0000, 0x00000},
                                                     {0x10000, 0x10ffff}}, seed); // range for 3 or 4 UTF-8 bytes

    auto procedure = [&implementation](const char* utf8, size_t size, char32_t* utf32) -> size_t {
      return implementation.convert_utf8_to_utf32(utf8, size, utf32);
    };

    for (size_t size: input_size) {
      transcode_utf8_to_utf32_test_base test(random, size);
      ASSERT_TRUE(test(procedure));
    }
  }
} */

int main(int argc, char* argv[]) {
  return simdutf::test::main(argc, argv);
}
