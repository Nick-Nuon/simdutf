// file included directly

// Detect all invalid 2-byte sequences at once 
simdutf_really_inline __m512i check_special_cases(__m512i input, const __m512i prev1) {


  /* Possible values for high nibbles of first bytes: 
            ascii, # 0000
            ascii, # 0001
            ascii, # 0010
            ascii, # 0011
            ascii, # 0100
            ascii, # 0101
            ascii, # 0110
            ascii, # 0111
            continuation, # 1000
            continuation, # 1001
            continuation, # 1010
            continuation, # 1011
            _2_bytes, # 1100
            _2_bytes, # 1101
            _3_bytes, # 1110
            _4_bytes, # 1111 */

// The high and low nibbles of each byte, as well as the low nibble of the next byte, are looked
// up in their respective tables. 

  __m512i mask1 = _mm512_setr_epi64(
        0x0202020202020202, // ASCII =>            => 0000 0010
        0x4915012180808080, // continuation        => 1000 0000
        0x0202020202020202, // 2-bytes (# 1100)    => 0010 0001 Scenario a) code points starts by 0 XXXX XXXXXX
                            //         (# 1101)    => 0000 0001 Scenario b) code points starts by 1 XXXX XXXXXX
        0x4915012180808080, // 3-bytes             => 0001 0101
        0x0202020202020202, // 4-bytes             => 0100 1001
        0x4915012180808080,
        0x0202020202020202,
        0x4915012180808080);
    const __m512i v_0f = _mm512_set1_epi8(0x0f);
    __m512i index1 = _mm512_and_si512(_mm512_srli_epi16(prev1, 4), v_0f); // take the high nibble of last byte of previous input

    __m512i byte_1_high = _mm512_shuffle_epi8(mask1, index1); 

    __m512i mask2 = _mm512_setr_epi64(
        0xcbcbcb8b8383a3e7, // 203 203 203 (139 131 131 163 231) => first five low nibbles are assigned numbers different then the rest, all else are the same (203)
        0xcbcbdbcbcbcbcbcb, // 203 203 203 203 203 203 203 203 => e.g. everything that is not 
        0xcbcbcb8b8383a3e7, // e.g. 
/*                                0000 => 1110 0111 <- failure case for 2-byte #1100 ... 
                                  0001 => 1010 0011 <- failure case for 2-byte #1100 ... 
                                  0010 => 1000 0011
                                  0011 => 1000 0011 
                                  0100 => 1000 1011
                                  else => 1100 1011
                                  */
        0xcbcbdbcbcbcbcbcb,
        0xcbcbcb8b8383a3e7,
        0xcbcbdbcbcbcbcbcb,
        0xcbcbcb8b8383a3e7,
        0xcbcbdbcbcbcbcbcb);
     __m512i index2 = _mm512_and_si512(prev1, v_0f); // take the low nibble of last byte of previous input

    __m512i byte_1_low = _mm512_shuffle_epi8(mask2, index2);
    __m512i mask3 = _mm512_setr_epi64(
        0x101010101010101, // All non-continuations are 1, leading bits 0
        0x1010101babaaee6, // Continuations are  230, 174,186, 186 => e.g. have leading bits 1
                           // A continuation followed by another continuation constitutes a special case
        0x101010101010101, /* e.g.
                              1000 => 1110 0110 <- affects 2-byte #1100 a) 000 0000 XXXX (< 0x80)    b) 100 0000 XXXX ( )
                              1001 => 1010 1110 <- affects 2-byte #1100 a) 000 0001 XXXX (< 0x80)    b) 100 0001 XXXX ( )
                              1010 => 1011 1010 <- affects 2-byte #1100 a) 000 0010 XXXX (< 0x80)    b) 100 0010 XXXX ( )
                              1011 => 1011 1010 <- affects 2-byte #1100 a) 000 0011 XXXX (3F < 0x80) b) 100 0011 XXXX ( )
                              else => 0000 0001 <- two-byte will fail if not a continuation byte */
        0x1010101babaaee6,
        0x101010101010101,
        0x1010101babaaee6,
        0x101010101010101,
        0x1010101babaaee6
    );
    __m512i index3 = _mm512_and_si512(_mm512_srli_epi16(input, 4), v_0f);
    __m512i byte_2_high = _mm512_shuffle_epi8(mask3, index3);
    return _mm512_ternarylogic_epi64(byte_1_high, byte_1_low, byte_2_high, 128); // returns true only when byte_1_high, byte_1_low and byte_2_high's leading bits are zeroes.
  }

  // check for errors that involves 3 or 4 bytes units
  simdutf_really_inline __m512i check_multibyte_lengths(const __m512i input,
      const __m512i prev_input, const __m512i sc) {
    __m512i prev2 = prev<2>(input, prev_input);
    __m512i prev3 = prev<3>(input, prev_input);
    __m512i is_third_byte  = _mm512_subs_epu8(prev2, _mm512_set1_epi8(0b11100000u-1)); // Only 111_____ will be > 0, the rest is zero
    __m512i is_fourth_byte  = _mm512_subs_epu8(prev3, _mm512_set1_epi8(0b11110000u-1)); // Only 1111____ will be > 0, the rest is zero
    __m512i is_third_or_fourth_byte = _mm512_or_si512(is_third_byte, is_fourth_byte);
    const __m512i v_7f = _mm512_set1_epi8(char(0x7f)); 
    is_third_or_fourth_byte = _mm512_adds_epu8(v_7f, is_third_or_fourth_byte);  // Wnat to know whether or not the bit is < 128
    // We want to compute (is_third_or_fourth_byte AND v80) XOR sc.
    const __m512i v_80 = _mm512_set1_epi8(char(0x80));
    return _mm512_ternarylogic_epi32(is_third_or_fourth_byte, v_80, sc, 0b1101010);
    //__m512i is_third_or_fourth_byte_mask = _mm512_and_si512(is_third_or_fourth_byte, v_80);
    //return _mm512_xor_si512(is_third_or_fourth_byte_mask, sc);
  }
  //
  // Return nonzero if there are incomplete multibyte characters at the end of the block:
  // e.g. if there is a 4-byte character, but it's 3 bytes from the end.
  //
  simdutf_really_inline __m512i is_incomplete(const __m512i input) {
    // If the previous input's last 3 bytes match this, they're too short (they ended at EOF):
    // ... 1111____ 111_____ 11______
    __m512i max_value = _mm512_setr_epi64(
        0xffffffffffffffff,
        0xffffffffffffffff,
        0xffffffffffffffff,
        0xffffffffffffffff,
        0xffffffffffffffff,
        0xffffffffffffffff,
        0xffffffffffffffff,
        0xbfdfefffffffffff);
    return _mm512_subs_epu8(input, max_value);
  }

  struct avx512_utf8_checker {
    // If this is nonzero, there has been a UTF-8 error.
    __m512i error{};

    // The last input we received
    __m512i prev_input_block{};
    // Whether the last input we received was incomplete (used for ASCII fast path)
    __m512i prev_incomplete{};

    //
    // Check whether the current bytes are valid UTF-8.
    //
    simdutf_really_inline void check_utf8_bytes(const __m512i input, const __m512i prev_input) {
      // Flip prev1...prev3 so we can easily determine if they are 2+, 3+ or 4+ lead bytes
      // (2, 3, 4-byte leads become large positive numbers instead of small negative numbers)
      __m512i prev1 = prev<1>(input, prev_input); // There will always be a pair of bytes straddling the two SIMD registers, which need to be validated as well.
      // After loading v1 , we detect all invalid 2-byte sequences at once 
      __m512i sc = check_special_cases(input, prev1);
      // All remaining checks are invalid 3–4 byte sequences, which either have too many continuations, or not enough
      this->error = _mm512_or_si512(check_multibyte_lengths(input, prev_input, sc), this->error);
    }


    // The only problem that can happen at EOF is that a multibyte character is too short
    // or a byte value too large in the last bytes: check_special_cases only checks for bytes
    // too large in the first of two bytes.
    simdutf_really_inline void check_eof() {
      // If the previous block had incomplete UTF-8 characters at the end, an ASCII block can't
      // possibly finish them.
      this->error = _mm512_or_si512(this->error, this->prev_incomplete);
    }

    // returns true if ASCII.
    simdutf_really_inline bool check_next_input(const __m512i input) {
      const __m512i v_80 = _mm512_set1_epi8(char(0x80));
      const __mmask64 ascii = _mm512_test_epi8_mask(input, v_80);
      if(ascii == 0) {
        this->error = _mm512_or_si512(this->error, this->prev_incomplete);
        return true;
      } else {
        this->check_utf8_bytes(input, this->prev_input_block);
        this->prev_incomplete = is_incomplete(input);
        this->prev_input_block = input;
        return false;
      }
    }
    // do not forget to call check_eof!
    simdutf_really_inline bool errors() const {
        return _mm512_test_epi8_mask(this->error, this->error) != 0;
    }

  }; // struct avx512_utf8_checker
