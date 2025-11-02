#pragma once

enum class TileType : int
{
	Empty = 0,
	Solid = 1,
	Portal = 2,
	Spike = 3,
	Count,
	None
};

namespace tile {
	extern const int tw;
	extern const int th;
}