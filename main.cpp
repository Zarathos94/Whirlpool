#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <algorithm>
#include <stdio.h>
#include <fstream>
#include "Headers/Defines.h"
#include "Headers/Tables.h"

using namespace std;

static void Buffer_Proces(struct TheWStruct * const pointer) {
	int i, r;
	u64 K[8];
	u64 _wblock[8];
	u64 _wstate[8];
	u64 _L[8];
	u8 *_buffer = pointer->_buffer;
	for (i = 0; i < 8; i++, _buffer += 8) {
		_wblock[i] =
			(((u64)_buffer[0]        ) << 56) ^
			(((u64)_buffer[1] & 0xffL) << 48) ^
			(((u64)_buffer[2] & 0xffL) << 40) ^
			(((u64)_buffer[3] & 0xffL) << 32) ^
			(((u64)_buffer[4] & 0xffL) << 24) ^
			(((u64)_buffer[5] & 0xffL) << 16) ^
			(((u64)_buffer[6] & 0xffL) <<  8) ^
			(((u64)_buffer[7] & 0xffL)      );
	}
	_wstate[0] = _wblock[0] ^ (K[0] = pointer->_hash[0]);
	_wstate[1] = _wblock[1] ^ (K[1] = pointer->_hash[1]);
	_wstate[2] = _wblock[2] ^ (K[2] = pointer->_hash[2]);
	_wstate[3] = _wblock[3] ^ (K[3] = pointer->_hash[3]);
	_wstate[4] = _wblock[4] ^ (K[4] = pointer->_hash[4]);
	_wstate[5] = _wblock[5] ^ (K[5] = pointer->_hash[5]);
	_wstate[6] = _wblock[6] ^ (K[6] = pointer->_hash[6]);
	_wstate[7] = _wblock[7] ^ (K[7] = pointer->_hash[7]);

	for (r = 1; r <= R; r++) {
   		_L[0] =
   			C0[(int)(K[0] >> 56)       ] ^
   			C1[(int)(K[7] >> 48) & 0xff] ^
   			C2[(int)(K[6] >> 40) & 0xff] ^
   			C3[(int)(K[5] >> 32) & 0xff] ^
   			C4[(int)(K[4] >> 24) & 0xff] ^
   			C5[(int)(K[3] >> 16) & 0xff] ^
   			C6[(int)(K[2] >>  8) & 0xff] ^
   			C7[(int)(K[1]      ) & 0xff] ^
			rc[r];
   		_L[1] =
   			C0[(int)(K[1] >> 56)       ] ^
   			C1[(int)(K[0] >> 48) & 0xff] ^
   			C2[(int)(K[7] >> 40) & 0xff] ^
   			C3[(int)(K[6] >> 32) & 0xff] ^
   			C4[(int)(K[5] >> 24) & 0xff] ^
   			C5[(int)(K[4] >> 16) & 0xff] ^
   			C6[(int)(K[3] >>  8) & 0xff] ^
   			C7[(int)(K[2]      ) & 0xff];
   		_L[2] =
   			C0[(int)(K[2] >> 56)       ] ^
   			C1[(int)(K[1] >> 48) & 0xff] ^
   			C2[(int)(K[0] >> 40) & 0xff] ^
   			C3[(int)(K[7] >> 32) & 0xff] ^
   			C4[(int)(K[6] >> 24) & 0xff] ^
   			C5[(int)(K[5] >> 16) & 0xff] ^
   			C6[(int)(K[4] >>  8) & 0xff] ^
   			C7[(int)(K[3]      ) & 0xff];
   		_L[3] =
   			C0[(int)(K[3] >> 56)       ] ^
   			C1[(int)(K[2] >> 48) & 0xff] ^
   			C2[(int)(K[1] >> 40) & 0xff] ^
   			C3[(int)(K[0] >> 32) & 0xff] ^
   			C4[(int)(K[7] >> 24) & 0xff] ^
   			C5[(int)(K[6] >> 16) & 0xff] ^
   			C6[(int)(K[5] >>  8) & 0xff] ^
   			C7[(int)(K[4]      ) & 0xff];
   		_L[4] =
   			C0[(int)(K[4] >> 56)       ] ^
   			C1[(int)(K[3] >> 48) & 0xff] ^
   			C2[(int)(K[2] >> 40) & 0xff] ^
   			C3[(int)(K[1] >> 32) & 0xff] ^
   			C4[(int)(K[0] >> 24) & 0xff] ^
   			C5[(int)(K[7] >> 16) & 0xff] ^
   			C6[(int)(K[6] >>  8) & 0xff] ^
   			C7[(int)(K[5]      ) & 0xff];
   		_L[5] =
   			C0[(int)(K[5] >> 56)       ] ^
   			C1[(int)(K[4] >> 48) & 0xff] ^
   			C2[(int)(K[3] >> 40) & 0xff] ^
   			C3[(int)(K[2] >> 32) & 0xff] ^
   			C4[(int)(K[1] >> 24) & 0xff] ^
   			C5[(int)(K[0] >> 16) & 0xff] ^
   			C6[(int)(K[7] >>  8) & 0xff] ^
   			C7[(int)(K[6]      ) & 0xff];
   		_L[6] =
   			C0[(int)(K[6] >> 56)       ] ^
   			C1[(int)(K[5] >> 48) & 0xff] ^
   			C2[(int)(K[4] >> 40) & 0xff] ^
   			C3[(int)(K[3] >> 32) & 0xff] ^
   			C4[(int)(K[2] >> 24) & 0xff] ^
   			C5[(int)(K[1] >> 16) & 0xff] ^
   			C6[(int)(K[0] >>  8) & 0xff] ^
   			C7[(int)(K[7]      ) & 0xff];
   		_L[7] =
   			C0[(int)(K[7] >> 56)       ] ^
   			C1[(int)(K[6] >> 48) & 0xff] ^
   			C2[(int)(K[5] >> 40) & 0xff] ^
   			C3[(int)(K[4] >> 32) & 0xff] ^
   			C4[(int)(K[3] >> 24) & 0xff] ^
   			C5[(int)(K[2] >> 16) & 0xff] ^
   			C6[(int)(K[1] >>  8) & 0xff] ^
   			C7[(int)(K[0]      ) & 0xff];
   		K[0] = _L[0];
   		K[1] = _L[1];
   		K[2] = _L[2];
   		K[3] = _L[3];
   		K[4] = _L[4];
   		K[5] = _L[5];
   		K[6] = _L[6];
   		K[7] = _L[7];
   		_L[0] =
   			C0[(int)(_wstate[0] >> 56)       ] ^
   			C1[(int)(_wstate[7] >> 48) & 0xff] ^
   			C2[(int)(_wstate[6] >> 40) & 0xff] ^
   			C3[(int)(_wstate[5] >> 32) & 0xff] ^
   			C4[(int)(_wstate[4] >> 24) & 0xff] ^
   			C5[(int)(_wstate[3] >> 16) & 0xff] ^
   			C6[(int)(_wstate[2] >>  8) & 0xff] ^
   			C7[(int)(_wstate[1]      ) & 0xff] ^
			K[0];
   		_L[1] =
   			C0[(int)(_wstate[1] >> 56)       ] ^
   			C1[(int)(_wstate[0] >> 48) & 0xff] ^
   			C2[(int)(_wstate[7] >> 40) & 0xff] ^
   			C3[(int)(_wstate[6] >> 32) & 0xff] ^
   			C4[(int)(_wstate[5] >> 24) & 0xff] ^
   			C5[(int)(_wstate[4] >> 16) & 0xff] ^
   			C6[(int)(_wstate[3] >>  8) & 0xff] ^
   			C7[(int)(_wstate[2]      ) & 0xff] ^
			K[1];
   		_L[2] =
   			C0[(int)(_wstate[2] >> 56)       ] ^
   			C1[(int)(_wstate[1] >> 48) & 0xff] ^
   			C2[(int)(_wstate[0] >> 40) & 0xff] ^
   			C3[(int)(_wstate[7] >> 32) & 0xff] ^
   			C4[(int)(_wstate[6] >> 24) & 0xff] ^
   			C5[(int)(_wstate[5] >> 16) & 0xff] ^
   			C6[(int)(_wstate[4] >>  8) & 0xff] ^
   			C7[(int)(_wstate[3]      ) & 0xff] ^
			K[2];
   		_L[3] =
   			C0[(int)(_wstate[3] >> 56)       ] ^
   			C1[(int)(_wstate[2] >> 48) & 0xff] ^
   			C2[(int)(_wstate[1] >> 40) & 0xff] ^
   			C3[(int)(_wstate[0] >> 32) & 0xff] ^
   			C4[(int)(_wstate[7] >> 24) & 0xff] ^
   			C5[(int)(_wstate[6] >> 16) & 0xff] ^
   			C6[(int)(_wstate[5] >>  8) & 0xff] ^
   			C7[(int)(_wstate[4]      ) & 0xff] ^
			K[3];
   		_L[4] =
   			C0[(int)(_wstate[4] >> 56)       ] ^
   			C1[(int)(_wstate[3] >> 48) & 0xff] ^
   			C2[(int)(_wstate[2] >> 40) & 0xff] ^
   			C3[(int)(_wstate[1] >> 32) & 0xff] ^
   			C4[(int)(_wstate[0] >> 24) & 0xff] ^
   			C5[(int)(_wstate[7] >> 16) & 0xff] ^
   			C6[(int)(_wstate[6] >>  8) & 0xff] ^
   			C7[(int)(_wstate[5]      ) & 0xff] ^
			K[4];
   		_L[5] =
   			C0[(int)(_wstate[5] >> 56)       ] ^
   			C1[(int)(_wstate[4] >> 48) & 0xff] ^
   			C2[(int)(_wstate[3] >> 40) & 0xff] ^
   			C3[(int)(_wstate[2] >> 32) & 0xff] ^
   			C4[(int)(_wstate[1] >> 24) & 0xff] ^
   			C5[(int)(_wstate[0] >> 16) & 0xff] ^
   			C6[(int)(_wstate[7] >>  8) & 0xff] ^
   			C7[(int)(_wstate[6]      ) & 0xff] ^
			K[5];
   		_L[6] =
   			C0[(int)(_wstate[6] >> 56)       ] ^
   			C1[(int)(_wstate[5] >> 48) & 0xff] ^
   			C2[(int)(_wstate[4] >> 40) & 0xff] ^
   			C3[(int)(_wstate[3] >> 32) & 0xff] ^
   			C4[(int)(_wstate[2] >> 24) & 0xff] ^
   			C5[(int)(_wstate[1] >> 16) & 0xff] ^
   			C6[(int)(_wstate[0] >>  8) & 0xff] ^
   			C7[(int)(_wstate[7]      ) & 0xff] ^
			K[6];
   		_L[7] =
   			C0[(int)(_wstate[7] >> 56)       ] ^ C1[(int)(_wstate[6] >> 48) & 0xff] ^ C2[(int)(_wstate[5] >> 40) & 0xff] ^
   			C3[(int)(_wstate[4] >> 32) & 0xff] ^ C4[(int)(_wstate[3] >> 24) & 0xff] ^
   			C5[(int)(_wstate[2] >> 16) & 0xff] ^
   			C6[(int)(_wstate[1] >>  8) & 0xff] ^
   			C7[(int)(_wstate[0]      ) & 0xff] ^
			K[7];
   		_wstate[0] = _L[0];
   		_wstate[1] = _L[1];
   		_wstate[2] = _L[2];
   		_wstate[3] = _L[3];
   		_wstate[4] = _L[4];
   		_wstate[5] = _L[5];
   		_wstate[6] = _L[6];
   		_wstate[7] = _L[7];
	}
	pointer->_hash[0] ^= _wstate[0] ^ _wblock[0];
	pointer->_hash[1] ^= _wstate[1] ^ _wblock[1];
	pointer->_hash[2] ^= _wstate[2] ^ _wblock[2];
	pointer->_hash[3] ^= _wstate[3] ^ _wblock[3];
	pointer->_hash[4] ^= _wstate[4] ^ _wblock[4];
	pointer->_hash[5] ^= _wstate[5] ^ _wblock[5];
	pointer->_hash[6] ^= _wstate[6] ^ _wblock[6];
	pointer->_hash[7] ^= _wstate[7] ^ _wblock[7];
}
void WhirlInitiate(struct TheWStruct * const pointer) {
	int i;

	memset(pointer->_bitLength, 0, 32);
	pointer->_bufferBits = pointer->_bufferPos = 0;
	pointer->_buffer[0] = 0; /* it's only necessary to cleanup buffer[bufferPos] */
	for (i = 0; i < 8; i++) {
		pointer->_hash[i] = 0L; /* initial value */
	}
}
void WAdd(const unsigned char * const _source,
			   unsigned long _sourceBits,
			   struct TheWStruct * const pointer) {

	int _sourcePos	= 0;
	int _sourceGap	= (8 - ((int)_sourceBits & 7)) & 7;
	int _bufferRem	= pointer->_bufferBits & 7;
	int i;
	u32 b, _carry;
	u8 *_buffer		= pointer->_buffer;
	u8 *_bitLength	= pointer->_bitLength;
	int _bufferBits	= pointer->_bufferBits;
	int _bufferPos	= pointer->_bufferPos;

	u64 value = _sourceBits;
	for (i = 31, _carry = 0; i >= 0 && value != 0LL; i--) {
		_carry += _bitLength[i] + ((u32)value & 0xff);
		_bitLength[i] = (u8)_carry;
		_carry >>= 8;
		value >>= 8;
	}

	while (_sourceBits > 8) {

		b = ((_source[_sourcePos] << _sourceGap) & 0xff) |
			((_source[_sourcePos + 1] & 0xff) >> (8 - _sourceGap));

		_buffer[_bufferPos++] |= (u8)(b >> _bufferRem);
		_bufferBits += 8 - _bufferRem;
		if (_bufferBits == 512) {

			Buffer_Proces(pointer);
			_bufferBits = _bufferPos = 0;
		}
		_buffer[_bufferPos] = b << (8 - _bufferRem);
		_bufferBits += _bufferRem;

		_sourceBits -= 8;
		_sourcePos++;
	}

	b = (_source[_sourcePos] << _sourceGap) & 0xff;

	_buffer[_bufferPos] |= b >> _bufferRem;
	if (_bufferRem + _sourceBits < 8) {

		_bufferBits += _sourceBits;
	} else {

		_bufferPos++;
		_bufferBits += 8 - _bufferRem;
		_sourceBits -= 8 - _bufferRem;

		if (_bufferBits == 512) {

			Buffer_Proces(pointer);
			_bufferBits = _bufferPos = 0;
		}
		_buffer[_bufferPos] = b << (8 - _bufferRem);
		_bufferBits += (int)_sourceBits;
	}
	pointer->_bufferBits	= _bufferBits;
	pointer->_bufferPos	= _bufferPos;
}
const char
	str[17] = "0123456789ABCDEF";
void WPEnd(struct TheWStruct * const pointer,
					unsigned char * const result) {
	int i;
	u8 *_buffer		= pointer->_buffer;
	u8 *_bitLength	= pointer->_bitLength;
	int _bufferBits	= pointer->_bufferBits;
	int _bufferPos	= pointer->_bufferPos;
	u8 *_digest      = result;

	_buffer[_bufferPos] |= 0x80U >> (_bufferBits & 7);
	_bufferPos++; /* all remaining bits on the current u8 are set to zero. */

	if (_bufferPos > 32) {
		if (_bufferPos < 64) {
		    memset(&_buffer[_bufferPos], 0, 64 - _bufferPos);
		}

		Buffer_Proces(pointer);

		_bufferPos = 0;
	}
   	if (_bufferPos < 32) {
   	    memset(&_buffer[_bufferPos], 0, 32 - _bufferPos);
   	}
   	_bufferPos = 32;

	memcpy(&_buffer[32], _bitLength, 32);

	Buffer_Proces(pointer);

	for (i = 0; i < 8; i++) {
		_digest[0] = (u8)(pointer->_hash[i] >> 56);
		_digest[1] = (u8)(pointer->_hash[i] >> 48);
		_digest[2] = (u8)(pointer->_hash[i] >> 40);
		_digest[3] = (u8)(pointer->_hash[i] >> 32);
		_digest[4] = (u8)(pointer->_hash[i] >> 24);
		_digest[5] = (u8)(pointer->_hash[i] >> 16);
		_digest[6] = (u8)(pointer->_hash[i] >>  8);
		_digest[7] = (u8)(pointer->_hash[i]      );
		_digest += 8;
	}
	pointer->_bufferBits	= _bufferBits;
	pointer->_bufferPos	= _bufferPos;
}
int main() {
    char WP[16];
    ofstream fileout("WPHash.txt");

    cout << "Enter text that you want to hash with Whirlpool hash:\n";
    scanf("%s", WP);
    struct TheWStruct
		whirl;

    int len;

	char
		digest[64],
		buffer[4100];
	unsigned char
		*tmp = (unsigned char *)digest;

    WhirlInitiate(&whirl);

	char *p = WP;
	len = strlen(WP);
	while (len > 4096) {

	    sprintf(buffer, "%s", p);
		p += 4096;
		len -= 4096;
		WAdd((unsigned char *)buffer, 4096 * 8, &whirl);
	}
	sprintf(buffer, "%s", p);

	WAdd((unsigned char *)buffer, len * 8, &whirl);

	WPEnd(&whirl, tmp);

	len = 0;
	while (len < 128) {

		buffer[len++] = str[*tmp >> 4];
		buffer[len++] = str[*tmp & 0x0F];
		tmp++;
	}
	buffer[128] = 0;
	cout << "The output hash is in the file called WPHash.txt in the executable directory\n";
	fileout << buffer;
    cout << "The hash output:\n";
    cout << buffer;
    return 0;
}
