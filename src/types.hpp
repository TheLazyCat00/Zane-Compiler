#pragma once

#include "ir/nodes.hpp"
#include <llvm-18/llvm/IR/Module.h>
#include <map>
#include <string>
#include <filesystem>

using Packages = std::map<std::string, std::shared_ptr<ir::GlobalScope>>;
using Modules = std::map<std::string, std::unique_ptr<llvm::Module>>;

namespace fs = std::filesystem;
[[maybe_unused]] constexpr auto _clangd_fs_used = sizeof(fs::path);
