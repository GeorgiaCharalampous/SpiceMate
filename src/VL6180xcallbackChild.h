#ifndef stdint
#include <stdint.h>
#endif
#ifndef  VL6180xcallbackInterface
#include <VL6180xcallbackInterface.h>
#endif

class VL6180xcallbackChild : public VL6180xcallback {
	virtual void hasSample(uint8_t sample);

	private:
	uint8_t counter = 0;
	uint8_t upperLimit = 180;
	uint8_t lowerLimit = 20;

	//std::thread processThread;
};