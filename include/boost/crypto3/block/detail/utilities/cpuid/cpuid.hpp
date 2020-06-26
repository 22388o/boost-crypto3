#ifndef CRYPTO3_CPUID_HPP#define CRYPTO3_CPUID_HPP#include <vector>#include <string>#include <iosfwd>#include <boost/crypto3/build.hpp>namespace boost {    namespace crypto3 {        /*!         * A class handling runtime CPU feature detection. It is limited to         * just the features necessary to implement CPU specific code in library,         * rather than being a general purpose utility.         *         * This class supports:         *         *  - x86 features using CPUID. x86 is also the only processor with         *    accurate cache line detection currently.         *         *  - PowerPC AltiVec detection on Linux, NetBSD, OpenBSD, and Darwin         *         *  - ARM NEON and crypto extensions detection. On Linux and Android         *    systems which support getauxval, that is used to access CPU         *    feature information. Otherwise a relatively portable but         *    thread-unsafe mechanism involving executing probe functions which         *    catching SIGILL signal is used.         */        class cpuid final {        public:            /**             * Probe the CPU and see what extensions are supported             */            static void initialize() {                g_processor_features = 0;#if defined(CRYPTO3_TARGET_CPU_IS_PPC_FAMILY) || defined(CRYPTO3_TARGET_CPU_IS_ARM_FAMILY) || \    defined(CRYPTO3_TARGET_CPU_IS_X86_FAMILY)                g_processor_features = cpuid::detect_cpu_features(&g_cache_line_size);#endif                g_endian_status = runtime_check_endian();                g_processor_features |= cpuid::CPUID_INITIALIZED_BIT;            }            static bool has_simd_32() {#if defined(CRYPTO3_TARGET_SUPPORTS_SSE2)                return cpuid::has_sse2();#elif defined(CRYPTO3_TARGET_SUPPORTS_ALTIVEC)                return cpuid::has_altivec();#elif defined(CRYPTO3_TARGET_SUPPORTS_NEON)                return cpuid::has_neon();#else                return true;#endif            }            /**             * Return a possibly empty string containing list of known CPU             * extensions. Each name will be seperated by a space, and the ordering             * will be arbitrary. This list only contains values that are useful for             * the library (for example FMA instructions are not checked).             *             * Example outputs "sse2 ssse3 rdtsc", "neon arm_aes", "altivec"             */            static std::string to_string() {                std::vector<std::string> flags;#define CPUID_PRINT(flag)           \    do {                            \        if (has_##flag()) {         \            flags.push_back(#flag); \        }                           \    } while (0)#if defined(CRYPTO3_TARGET_CPU_IS_X86_FAMILY)                CPUID_PRINT(sse2);                CPUID_PRINT(ssse3);                CPUID_PRINT(sse41);                CPUID_PRINT(sse42);                CPUID_PRINT(avx2);                CPUID_PRINT(avx512f);                CPUID_PRINT(rdtsc);                CPUID_PRINT(bmi2);                CPUID_PRINT(adx);                CPUID_PRINT(aes_ni);                CPUID_PRINT(clmul);                CPUID_PRINT(rdrand);                CPUID_PRINT(rdseed);                CPUID_PRINT(intel_sha);#endif#if defined(CRYPTO3_TARGET_CPU_IS_PPC_FAMILY)                CPUID_PRINT(altivec);                CPUID_PRINT(ppc_crypto);#endif#if defined(CRYPTO3_TARGET_CPU_IS_ARM_FAMILY)                CPUID_PRINT(neon);                CPUID_PRINT(arm_sha1);                CPUID_PRINT(arm_sha2);                CPUID_PRINT(arm_aes);                CPUID_PRINT(arm_pmull);#endif#undef CPUID_PRINT                std::string out;                for (const std::string &c : flags) {                    out.push_back(' ');                    out.insert(out.end(), c.begin(), c.end());                }                return out;            }            /**             * Return a best guess of the cache line size             */            static size_t cache_line_size() {                if (g_processor_features == 0) {                    initialize();                }                return g_cache_line_size;            }            static bool is_little_endian() {                return get_endian_status() == ENDIAN_LITTLE;            }            static bool is_big_endian() {                return get_endian_status() == ENDIAN_BIG;            }            enum CPUID_bits : uint64_t {#if defined(CRYPTO3_TARGET_CPU_IS_X86_FAMILY)                // These values have no relation to cpuid bitfields                // SIMD instruction sets                CPUID_SSE2_BIT = (1ULL << 0),                CPUID_SSSE3_BIT = (1ULL << 1),                CPUID_SSE41_BIT = (1ULL << 2),                CPUID_SSE42_BIT = (1ULL << 3),                CPUID_AVX2_BIT = (1ULL << 4),                CPUID_AVX512F_BIT = (1ULL << 5),                // Misc useful instructions                CPUID_RDTSC_BIT = (1ULL << 10),                CPUID_BMI2_BIT = (1ULL << 11),                CPUID_ADX_BIT = (1ULL << 12),                CPUID_BMI1_BIT = (1ULL << 13),                // Crypto-specific ISAs                CPUID_AESNI_BIT = (1ULL << 16),                CPUID_CLMUL_BIT = (1ULL << 17),                CPUID_RDRAND_BIT = (1ULL << 18),                CPUID_RDSEED_BIT = (1ULL << 19),                CPUID_SHA_BIT = (1ULL << 20),#endif#if defined(CRYPTO3_TARGET_CPU_IS_PPC_FAMILY)                CPUID_ALTIVEC_BIT = (1ULL << 0),                CPUID_PPC_CRYPTO3_BIT = (1ULL << 1),#endif#if defined(CRYPTO3_TARGET_CPU_IS_ARM_FAMILY)                CPUID_ARM_NEON_BIT = (1ULL << 0),                CPUID_ARM_RIJNDAEL_BIT = (1ULL << 16),                CPUID_ARM_PMULL_BIT = (1ULL << 17),                CPUID_ARM_SHA1_BIT = (1ULL << 18),                CPUID_ARM_SHA2_BIT = (1ULL << 19),#endif                CPUID_INITIALIZED_BIT = (1ULL << 63)            };#if defined(CRYPTO3_TARGET_CPU_IS_PPC_FAMILY)            /**             * Check if the processor supports AltiVec/VMX             */            static bool has_altivec() {                return has_cpuid_bit(CPUID_ALTIVEC_BIT);            }            /**             * Check if the processor supports POWER8 crypto3 extensions             */            static bool has_ppc_crypto() {                return has_cpuid_bit(CPUID_PPC_CRYPTO3_BIT);            }#endif#if defined(CRYPTO3_TARGET_CPU_IS_ARM_FAMILY)            /**             * Check if the processor supports NEON SIMD             */            static bool has_neon() {                return has_cpuid_bit(CPUID_ARM_NEON_BIT);            }            /**             * Check if the processor supports ARMv8 SHA1             */            static bool has_arm_sha1() {                return has_cpuid_bit(CPUID_ARM_SHA1_BIT);            }            /**             * Check if the processor supports ARMv8 SHA2             */            static bool has_arm_sha2() {                return has_cpuid_bit(CPUID_ARM_SHA2_BIT);            }            /**             * Check if the processor supports ARMv8 AES             */            static bool has_arm_aes() {                return has_cpuid_bit(CPUID_ARM_RIJNDAEL_BIT);            }            /**             * Check if the processor supports ARMv8 PMULL             */            static bool has_arm_pmull() {                return has_cpuid_bit(CPUID_ARM_PMULL_BIT);            }#endif#if defined(CRYPTO3_TARGET_CPU_IS_X86_FAMILY)            /**             * Check if the processor supports RDTSC             */            static bool has_rdtsc() {                return has_cpuid_bit(CPUID_RDTSC_BIT);            }            /**             * Check if the processor supports SSE2             */            static bool has_sse2() {                return has_cpuid_bit(CPUID_SSE2_BIT);            }            /**             * Check if the processor supports SSSE3             */            static bool has_ssse3() {                return has_cpuid_bit(CPUID_SSSE3_BIT);            }            /**             * Check if the processor supports SSE4.1             */            static bool has_sse41() {                return has_cpuid_bit(CPUID_SSE41_BIT);            }            /**             * Check if the processor supports SSE4.2             */            static bool has_sse42() {                return has_cpuid_bit(CPUID_SSE42_BIT);            }            /**             * Check if the processor supports AVX2             */            static bool has_avx2() {                return has_cpuid_bit(CPUID_AVX2_BIT);            }            /**             * Check if the processor supports AVX-512F             */            static bool has_avx512f() {                return has_cpuid_bit(CPUID_AVX512F_BIT);            }            /**             * Check if the processor supports BMI1             */            static bool has_bmi1() {                return has_cpuid_bit(CPUID_BMI1_BIT);            }            /**             * Check if the processor supports BMI2             */            static bool has_bmi2() {                return has_cpuid_bit(CPUID_BMI2_BIT);            }            /**             * Check if the processor supports AES-NI             */            static bool has_aes_ni() {                return has_cpuid_bit(CPUID_AESNI_BIT);            }            /**             * Check if the processor supports CLMUL             */            static bool has_clmul() {                return has_cpuid_bit(CPUID_CLMUL_BIT);            }            /**             * Check if the processor supports Intel SHA extension             */            static bool has_intel_sha() {                return has_cpuid_bit(CPUID_SHA_BIT);            }            /**             * Check if the processor supports ADX extension             */            static bool has_adx() {                return has_cpuid_bit(CPUID_ADX_BIT);            }            /**             * Check if the processor supports RDRAND             */            static bool has_rdrand() {                return has_cpuid_bit(CPUID_RDRAND_BIT);            }            /**             * Check if the processor supports RDSEED             */            static bool has_rdseed() {                return has_cpuid_bit(CPUID_RDSEED_BIT);            }#endif            /*             * Clear a cpuid bit             * Call cpuid::initialize to reset             *             * This is only exposed for testing, don't use unless you know             * what you are doing.             */            static void clear_cpuid_bit(CPUID_bits bit) {                const uint64_t mask = ~(static_cast<uint64_t>(bit));                g_processor_features &= mask;            }            /*             * Don't call this function, use cpuid::has_xxx above             * It is only exposed for the tests.             */            static bool has_cpuid_bit(CPUID_bits elem) {                if (g_processor_features == 0) {                    initialize();                }                const uint64_t elem64 = static_cast<uint64_t>(elem);                return ((g_processor_features & elem64) == elem64);            }            static std::vector<cpuid::CPUID_bits> bit_from_string(const std::string &tok) {#if defined(CRYPTO3_TARGET_CPU_IS_X86_FAMILY)                if (tok == "sse2" || tok == "simd") {                    return {boost::crypto3::cpuid::CPUID_SSE2_BIT};                }                if (tok == "ssse3") {                    return {boost::crypto3::cpuid::CPUID_SSSE3_BIT};                }                if (tok == "aesni") {                    return {boost::crypto3::cpuid::CPUID_AESNI_BIT};                }                if (tok == "clmul") {                    return {boost::crypto3::cpuid::CPUID_CLMUL_BIT};                }                if (tok == "avx2") {                    return {boost::crypto3::cpuid::CPUID_AVX2_BIT};                }                if (tok == "sha") {                    return {boost::crypto3::cpuid::CPUID_SHA_BIT};                }#elif defined(CRYPTO3_TARGET_CPU_IS_PPC_FAMILY)                if (tok == "altivec" || tok == "simd")                    return {boost::crypto3::cpuid::CPUID_ALTIVEC_BIT};#elif defined(CRYPTO3_TARGET_CPU_IS_ARM_FAMILY)                if (tok == "neon" || tok == "simd")                    return {boost::crypto3::cpuid::CPUID_ARM_NEON_BIT};                if (tok == "armv8sha1")                    return {boost::crypto3::cpuid::CPUID_ARM_SHA1_BIT};                if (tok == "armv8sha2")                    return {boost::crypto3::cpuid::CPUID_ARM_SHA2_BIT};                if (tok == "armv8aes")                    return {boost::crypto3::cpuid::CPUID_ARM_RIJNDAEL_BIT};                if (tok == "armv8pmull")                    return {boost::crypto3::cpuid::CPUID_ARM_PMULL_BIT};#else                CRYPTO3_UNUSED(tok);#endif                return {};            }        private:            enum endian_status : uint32_t {                ENDIAN_UNKNOWN = 0x00000000,                ENDIAN_BIG = 0x01234567,                ENDIAN_LITTLE = 0x67452301,            };#if defined(CRYPTO3_TARGET_CPU_IS_PPC_FAMILY) || defined(CRYPTO3_TARGET_CPU_IS_ARM_FAMILY) || \    defined(CRYPTO3_TARGET_CPU_IS_X86_FAMILY)            static uint64_t detect_cpu_features(size_t *cache_line_size);#endif            static endian_status runtime_check_endian() {                // Check runtime endian                const uint32_t endian32 = 0x01234567;                const uint8_t *e8 = reinterpret_cast<const uint8_t *>(&endian32);                endian_status endian = ENDIAN_UNKNOWN;                if (e8[0] == 0x01 && e8[1] == 0x23 && e8[2] == 0x45 && e8[3] == 0x67) {                    endian = ENDIAN_BIG;                } else if (e8[0] == 0x67 && e8[1] == 0x45 && e8[2] == 0x23 && e8[3] == 0x01) {                    endian = ENDIAN_LITTLE;                } else {                    throw std::exception();                }                // If we were compiled with a known endian, verify it matches at runtime#if defined(CRYPTO3_TARGET_CPU_IS_LITTLE_ENDIAN)                BOOST_ASSERT_MSG(endian == ENDIAN_LITTLE, "Build and runtime endian match");#elif defined(CRYPTO3_TARGET_CPU_IS_BIG_ENDIAN)                BOOST_ASSERT_MSG(endian == ENDIAN_BIG, "Build and runtime endian match");#endif                return endian;            }            static endian_status get_endian_status() {                if (g_endian_status == ENDIAN_UNKNOWN) {                    g_endian_status = runtime_check_endian();                }                return g_endian_status;            }            static uint64_t g_processor_features;            static size_t g_cache_line_size;            static enum endian_status g_endian_status;        };        uint64_t cpuid::g_processor_features = 0;        size_t cpuid::g_cache_line_size = CRYPTO3_TARGET_CPU_DEFAULT_CACHE_LINE_SIZE;        cpuid::endian_status cpuid::g_endian_status = ENDIAN_UNKNOWN;    }    // namespace crypto3}    // namespace nil#endif