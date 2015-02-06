#include "interf_dec.h"
#include "interf_enc.h"
#include "amr_interface.h"

/**********************************************************************/

int16_t WebRtcAmr_CreateEnc(AMREncInst** enc_inst)
{
	AMREncInst* context = (AMREncInst*)Encoder_Interface_init(1);
	if (context != NULL)
	{
		*enc_inst = context;
		return 0;
	}
	else
	{
		return -1;
	}
}

int16_t WebRtcAmr_CreateDecoder(AMRDecInst** dec_inst)
{
	AMRDecInst* context = (AMRDecInst*)Decoder_Interface_init();
	if (context != NULL)
	{
		*dec_inst = context;
		return 0;
	}
	else
	{
		return -1;
	}
}

int16_t WebRtcAmr_EncoderInit(AMREncInst* enc_inst,int16_t mode)
{
	return 0;
}

int16_t WebRtcAmr_DecoderInit(AMRDecInst* dec_inst)
{
	return 0;
}

int16_t WebRtcAmr_Encode(AMREncInst* enc_inst,int16_t* sample,int16_t sampleLen,int16_t* encoded,int16_t encodeMode)
{   
	unsigned char* charEncoded = (unsigned char*)encoded;
	int16_t iter               = sampleLen/(AMR_SAMPLE_SHORT_LEN);
	while(iter > 0)
	{
		Encoder_Interface_Encode((void*)enc_inst,(enum Mode)encodeMode,sample,charEncoded,1);
		sample      += AMR_SAMPLE_SHORT_LEN;
		charEncoded += AMR_FRAME_BYTE_LEN;
		iter--;
	}
	return AMR_FRAME_BYTE_LEN*iter;
}

int16_t WebRtcAmr_Decode(AMRDecInst* dec_inst,int16_t* encoded,int16_t len,int16_t* decoded,int16_t* speechType)
{
	unsigned char* charEncoded = (unsigned char*)encoded;
	int16_t iter               = len/AMR_FRAME_BYTE_LEN;
	*speechType                = 1;
	while(iter > 0)
	{
		Decoder_Interface_Decode((void*)dec_inst,charEncoded,decoded,1);
		charEncoded += AMR_FRAME_BYTE_LEN;
		decoded     += AMR_SAMPLE_SHORT_LEN;
		iter--;
	}
	return AMR_SAMPLE_SHORT_LEN*iter;
}

int16_t WebRtcAmr_FreeEnc(AMREncInst* enc_inst)
{
	Encoder_Interface_exit((void*)enc_inst);
	return 0;
}

int16_t WebRtcAmr_FreeDecoder(AMRDecInst* dec_inst)
{
	Decoder_Interface_exit((void*)dec_inst);
	return 0;
}


int16_t WebRtcAmr_EncodeBitmode(AMREncInst* enc_inst,int format)
{
	if (enc_inst == NULL)
	{
		return -1;
	}
	return 0;
}

int16_t WebRtcAmr_DecodeBitmode(AMRDecInst* dec_inst,int format)
{
	if (dec_inst == NULL)
	{
		return -1;
	}
	return 0;
}

int16_t WebRtcAmr_DecodePlc(AMRDecInst* dec_inst,int16_t* decoded,int16_t noOfLostFrames)
{
	if (dec_inst == NULL)
	{
		return -1;
	}
	return 0;
}