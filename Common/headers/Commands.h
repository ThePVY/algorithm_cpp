#pragma once

#pragma pack(push, 1)
struct _Command1x{
	uint16_t outs : 2;
	uint16_t time : 2;
	uint16_t code : 12;
};

enum class Commands4x{
	none, c41, c42, c43, c44
};

struct _Command4x{
	uint16_t out1 : 2;
	uint16_t out2 : 2;
	uint16_t out3 : 2;
	uint16_t delay12 : 4;
	uint16_t delay23 : 3;
	uint16_t delay34 : 3;
};
#pragma pack(pop)

union Command1x{
	uint16_t all;
	_Command1x bits;
	
	inline static Command1x Form(uint8_t outs, uint8_t time, uint16_t code){
		Command1x cmd;
		cmd.bits.outs = outs;
		cmd.bits.time = time;
		cmd.bits.code = code;
		return cmd;
	}
};

union Command4x{
	uint16_t all;
	_Command4x bits;
	
	inline static Command4x Form(uint8_t o1, uint8_t o2, uint8_t o3,
								 uint8_t d12, uint8_t d23, uint8_t d34){
		Command4x cmd;
		cmd.bits.out1 = o1;
		cmd.bits.out2 = o2;
		cmd.bits.out3 = o3;
		cmd.bits.delay12 = d12;
		cmd.bits.delay23 = d23;
		cmd.bits.delay34 = d34;
		return cmd;
	}
};




