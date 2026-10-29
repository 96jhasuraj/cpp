#include <iostream>
#include <iomanip>
#include <bitset>

void print_float_bits(const float f);
void fp32_to_bf16(const float f32_val);
void fast_negate(float& val);

int main() {
	float x = 0.1f;
	std::cout << x << " " << std::setprecision(20) << x << std::endl;
	print_float_bits(x);
	fp32_to_bf16(x);
	fast_negate(x);
	std::cout <<"x is " << x << std::endl;
}

void print_float_bits(const float f) {
	uint32_t bits_as_int = 0;
	std::memcpy(&bits_as_int, &f, sizeof(float));
	std::bitset<32> rawbits(bits_as_int);
	std::cout << "rawbits: " << rawbits << std::endl;
	float f2 = 0.0f;
	std::memcpy(&f2, &bits_as_int, sizeof(float));
	std::cout << "float from bits: " << std::setprecision(20) << f2 << std::endl;
}

void fp32_to_bf16(float f32_val) {
	uint32_t f32_bits;
	std::memcpy(&f32_bits, &f32_val, sizeof(float));
	uint32_t sign = (f32_bits >> 31);
	uint32_t exponent = (f32_bits >> 23);
	uint32_t mantissa = f32_bits & 0x7FFFFF;
	uint16_t bf16_bits = (sign << 15) | (exponent << 7) | (mantissa >> 16);
	std::bitset<16> bf16_bitset(bf16_bits);
	std::cout << "bfloat16 bits: " << bf16_bitset << std::endl;
}

void fast_negate(float& val) {
	uint32_t bit_as_int = 0;
	std::memcpy(&bit_as_int, &val, sizeof(float));
	uint32_t negative = bit_as_int ^ 0x80000000;
	std::memcpy(&val, &negative, sizeof(float));
}