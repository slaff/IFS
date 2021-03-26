// List of test modules to register

#ifdef ARCH_HOST
#define HOST_TEST_MAP(XX) XX(Hybrid)
#else
#define HOST_TEST_MAP(XX)
#endif

#define TEST_MAP(XX)                                                                                                   \
	XX(Errors)                                                                                                         \
	XX(Attributes)                                                                                                     \
	HOST_TEST_MAP(XX)
