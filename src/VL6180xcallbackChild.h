#ifndef stdint
#include <stdint.h>
#endif
#ifndef  VL6180xcallback
#include <VL6180xcallback.h>
#endif
#ifndef DataProcess
#include <DataProcess.h>
#endif

class VL6180xcallbackChild : public VL6180xcallback {

	/**
	 * Callback for when sensor reading is obtained
	**/
	virtual void hasSample(uint8_t sample);

	public:

	/**
	 * Registers the pointer to the data processing object 
	**/
	void registerDP(DataProcess* object){
		dp = object;
	};

	private:
	/**
	 * Pointer to data processing object.
	 * For passing to the next unit (class)
	 * in the process chain.
	**/
	DataProcess* dp = NULL;
};