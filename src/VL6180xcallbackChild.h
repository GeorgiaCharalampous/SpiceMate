#ifndef stdint
#include <stdint.h>
#endif
#ifndef  VL6180xcallbackInterface
#include <VL6180xcallbackInterface.h>
#endif

class VL6180xcallbackChild : public VL6180xcallback {
	virtual void hasSample(int v);
};
