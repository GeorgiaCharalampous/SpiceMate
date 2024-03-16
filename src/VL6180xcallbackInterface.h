class VL6180xcallback {
/** Called after a sample has arrived. \param sample contains sensor readings **/
	public:
        virtual void hasSample(uint8_t sample) = 0;
};
