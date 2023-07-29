// file included directly

// File contains conversion procedure from VALID UTF-8 strings.

/*
    valid_utf8_to_fixed_length converts a valid UTF-8 string into UTF-32.

    The `OUTPUT` template type decides what to do with UTF-32: store
    it directly or convert into UTF-16 (with AVX512).

    Input:
    - str           - valid UTF-8 string
    - len           - string length
    - out_buffer    - output buffer

    Result:
    - pair.first    - the first unprocessed input byte
    - pair.second   - the first unprocessed output word
*/
template <endianness big_endian>
std::pair<const char*, char*> valid_utf16_to_latin1(const char* str, size_t len, char* output) {

    __m512i byteflip = _mm512_setr_epi64(
            0x0607040502030001,
            0x0e0f0c0d0a0b0809,
            0x0607040502030001,
            0x0e0f0c0d0a0b0809,
            0x0607040502030001,
            0x0e0f0c0d0a0b0809,
            0x0607040502030001,
            0x0e0f0c0d0a0b0809
        );
    const char* ptr = str;
    const char* end = ptr + len;

    const __m512i v_80 = _mm512_set1_epi8(char(0x80));


    // OUTPUT* output = dwords;
    /**
     * In the main loop, we consume 64 bytes per iteration,
     * but we access 64 + 4 bytes.
     * We check for ptr + 64 + 64 <= end because
     * we want to be do maskless writes without overruns.
     */
    while (ptr + 64 + 64 <= end) {
        const __m512i utf16 = _mm512_loadu_si512((const __m512i*)ptr);
        const __mmask64 ascii = _mm512_test_epi8_mask(utf16, v_80);
        if(ascii == 0) {
            _mm512_storeu_epi8((__m512i*)(output),utf16);
            output += 64;
            ptr += 64;
            continue;
        }

        // this is to store # of leading bits.
        int leading_count0;
        int leading_count1;
        int leading_count2;

        // the 
        const __m512i lane0 = broadcast_epi128<0>(utf16); // the first 128 bits are repeated (or broadcasted) 4 times.
        const __m512i lane1 = broadcast_epi128<1>(utf16); // the second 128 bits are repeated 4 times.
        const __m512i lane2 = broadcast_epi128<2>(utf16); // the third 128 bits are repeated 4 times.
        const __m512i lane3 = broadcast_epi128<3>(utf16); // the fourth 128 bits are repeated 4 times.

        __m512i vec0 = expand_and_identify(lane0, lane1, leading_count0); //get the leading bits in the first lane merged /w the second
        __m512i vec1 = expand_and_identify(lane1, lane2, leading_count1); //get the leading bits in the second lane merged /w the third
        

        if(leading_count0 + leading_count1 <= 16) {
            //add the two vectors together
            vec0 = _mm512_mask_expand_epi32(vec0, 
                                            // this mask is to signal which is vec1 or vec2
                                            __mmask16((
                                                        (1<<leading_count1) // e.g. if leading_count1 is 4, (1<<4) = 16 in binary is 10000
                                                        -1) // ... and subtracting 1 gives 01111.
                                                        <<leading_count0), //adds leading_count0 number of zeroes to the end of the mask
                                            vec1);
            leading_count0 += leading_count1;
            vec0 = expand_utf8_to_utf32(vec0);
            SIMDUTF_ICELAKE_WRITE_UTF16_OR_UTF32(vec0, leading_count0, false)
        } else {
            vec0 = expand_utf8_to_utf32(vec0);
            vec1 = expand_utf8_to_utf32(vec1);
            SIMDUTF_ICELAKE_WRITE_UTF16_OR_UTF32(vec0, leading_count0, false)
            SIMDUTF_ICELAKE_WRITE_UTF16_OR_UTF32(vec1, leading_count1, false)
        }
        __m512i vec2 = expand_and_identify(lane2, lane3, leading_count2);
        uint32_t tmp1;
        ::memcpy(&tmp1, ptr + 64, sizeof(tmp1));
        const __m512i lane4 = _mm512_set1_epi32(tmp1);
        int leading_count3;
        __m512i vec3 = expand_and_identify(lane3, lane4, leading_count3);
        if(leading_count2 + leading_count3 <= 16) {
            vec2 = _mm512_mask_expand_epi32(vec2, __mmask16(((1<<leading_count3)-1)<<leading_count2), vec3);
            leading_count2 += leading_count3;
            vec2 = expand_utf8_to_utf32(vec2);
            SIMDUTF_ICELAKE_WRITE_UTF16_OR_UTF32(vec2, leading_count2, false)
        } else {
            vec2 = expand_utf8_to_utf32(vec2);
            vec3 = expand_utf8_to_utf32(vec3);
            SIMDUTF_ICELAKE_WRITE_UTF16_OR_UTF32(vec2, leading_count2, false)
            SIMDUTF_ICELAKE_WRITE_UTF16_OR_UTF32(vec3, leading_count3, false)
        }
        ptr += 4*16;
    }

    if (ptr + 64 <= end) {
        const __m512i utf16 = _mm512_loadu_si512((const __m512i*)ptr);
        const __m512i v_80 = _mm512_set1_epi8(char(0x80));
        const __mmask64 ascii = _mm512_test_epi8_mask(utf16, v_80);
        if(ascii == 0) {
            SIMDUTF_ICELAKE_STORE_ASCII(UTF32, utf16, output)
            output += 64;
            ptr += 64;
        } else {
            const __m512i lane0 = broadcast_epi128<0>(utf16);
            const __m512i lane1 = broadcast_epi128<1>(utf16);
            int leading_count0;
            __m512i vec0 = expand_and_identify(lane0, lane1, leading_count0);
            const __m512i lane2 = broadcast_epi128<2>(utf16);
            int leading_count1;
            __m512i vec1 = expand_and_identify(lane1, lane2, leading_count1);
            if(leading_count0 + leading_count1 <= 16) {
                vec0 = _mm512_mask_expand_epi32(vec0, __mmask16(((1<<leading_count1)-1)<<leading_count0), vec1);
                leading_count0 += leading_count1;
                vec0 = expand_utf8_to_utf32(vec0);
                SIMDUTF_ICELAKE_WRITE_UTF16_OR_UTF32(vec0, leading_count0, true)
            } else {
                vec0 = expand_utf8_to_utf32(vec0);
                vec1 = expand_utf8_to_utf32(vec1);
                SIMDUTF_ICELAKE_WRITE_UTF16_OR_UTF32(vec0, leading_count0, true)
                SIMDUTF_ICELAKE_WRITE_UTF16_OR_UTF32(vec1, leading_count1, true)
            }

            const __m512i lane3 = broadcast_epi128<3>(utf16);
            SIMDUTF_ICELAKE_TRANSCODE16(lane2, lane3, true)

            ptr += 3*16;
        }
    }
    return {ptr, output};
}


using utf8_to_utf16_result = std::pair<const char*, char16_t*>;
