#ifndef stdint
#include <stdint.h>
#endif
#ifndef  VL6180xcallbackInterface
#include <VL6180xcallbackInterface.h>
#endif
#ifndef DataProcess
#include <DataProcess.h>
#endif

class VL6180xcallbackChild : public VL6180xcallback {
	virtual void hasSample(uint8_t sample);
	DataProcess* dp = NULL;
	
	public:
	void registerDP(DataProcess* object){
		dp = object;
	};
};