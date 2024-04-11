class DPcallbackInterface {
/** 
 * Abstract callback interface.
 * Called after sample processing is finalised.
 * \param status gives the outcome of the processing.
 **/
	public:
        virtual void dataProcessed(bool status) = 0;
};
