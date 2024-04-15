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

	/**
	 * Assigns a reference to the fail descriptor pointer 
	**/
	void setFileDescriptor (int* a)
	{
		pfds_write = a;
	}

	private:
	/**
	 * Pointer to data processing object.
	 * For passing to the next unit (class)
	 * in the process chain.
	**/
	DataProcess* dp = nullptr;

	/**
	 * Pointer to a file descriptor to write to
	 * For blocking the processing thread 
	 * Initially a nullptr
	 * Needs to be set via setFileDescriptor
	**/

	int* pfds_write = nullptr;

};