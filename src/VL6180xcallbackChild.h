#include <stdint.h>
#include <VL6180xcallbackInterface.h>

class VL6180xcallbackChild : public VL6180xcallback {
	virtual void hasSample(uint8_t v);
};
