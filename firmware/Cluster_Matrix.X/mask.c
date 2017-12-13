#include "matrix.h"

const u32 mask_exist[3][13] =
{
	{
		0b11111110000000000011111110000000,//14
		0b11111110111111111011111110000000,//23
		0b11111110011111110011111110000000,//21
		0b11111110111111111011111110000000,//23
		0b11111110111111111011111110000000,//23
		0b11111110011111110011111110000000,//21
		0b11111100111111111011111110000000,//22
		0b11111100011111111011111110000000,//21
		0b11111100011111110011111110000000,//20
		0b11111110111111111011111110000000,//23
		0b11111110111111111011111110000000,//23
		0b11111110111111111011111110000000,//23
		0b11111110000000000011111110000000// 14
	},
	{
		0b11111110000000000011111110000000,//14
		0b11111110111111111011111110000000,//23
		0b11111110011111110011111110000000,//21
		0b11111110111111111011111110000000,//23
		0b11111110111111111001111110000000,//22
		0b11111110011111110001111110000000,//20
		0b11111110111111111011111110000000,//23
		0b11111100011111111011111110000000,//21
		0b11111100011111110011111110000000,//20
		0b11111110111111111011111110000000,//23
		0b11111110111111111011111110000000,//23
		0b11111110111111111011111110000000,//23
		0b11111110000000000011111110000000// 14
	},
	{
		0b11111110000000000011111110000000,//14
		0b11111110111111111011111110000000,//23
		0b11111110011111110011111110000000,//21
		0b11111110111111111011111110000000,//23
		0b11111110111111111001111110000000,//22
		0b11111110011111110001111110000000,//20
		0b11111110111111111011111110000000,//23
		0b11111100011111111011111110000000,//21
		0b11111100011111110011111110000000,//20
		0b11111110111111111011111110000000,//23
		0b11111110111111111011111110000000,//23
		0b11111110111111111011111110000000,//23
		0b11111110000000000011111110000000// 14
	}
};

u32 cluster_data[3][13] = {

	{
		0,0,0,0,0,0,
		0b00000001111111111000000000000000,
		0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,
		0b00000001111111111000000000000000,
		0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,
		0b00000001111111111000000000000000,
		0,0,0,0,0,0
	}
};

u32 side_by_side[13] =
{
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111
};

u32 conseil[13] =
{
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111,
	0b11111111111111111111111111111111
};

u32 gameoflife[2][13] =
{
	{
		0b0,
		0b0,
		0b0,
		0b0,
		0b0,
		0b0,
		0b0,
		0b0,
		0b0,
		0b0,
		0b0,
		0b0,
		0b0
	},
	{
		0b0,
		0b0,
		0b0,
		0b0,
		0b0,
		0b0,
		0b0,
		0b0,
		0b0,
		0b0,
		0b0,
		0b0,
		0b0
	}
};
