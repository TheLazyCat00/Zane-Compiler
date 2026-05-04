#include "globals/targets.hpp"

#include <llvm/TargetParser/Host.h>
#include <string>

namespace constants::targets {

Target getHostTarget() {
	const auto triple = llvm::sys::getDefaultTargetTriple();
	for (const auto& target : ALL_TARGETS) {
		if (triple.find(target.triple) != std::string::npos
			|| std::string(target.triple).find(triple) != std::string::npos) {
			return target;
		}
	}

	return LINUX_X64;
}

}
