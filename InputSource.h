#pragma once
#include <array>
#include <GameKeyEnum.h>

class InputSource {
protected:
	std::array<bool, (size_t)(int(io::Key::Count))>* keys{nullptr};
	void clearKeys();
public:
	InputSource();

	InputSource(std::array<bool, (size_t)(int(io::Key::Count))>* keys_);
	
	virtual ~InputSource() = 0;

	virtual void update() = 0;
};