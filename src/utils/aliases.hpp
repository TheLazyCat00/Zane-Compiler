#pragma once

#include "utils/zane_ptr.hpp"
#include <llvm-21/llvm/IR/Module.h>
#include <map>
#include <string>
#include <filesystem>

struct Package;

using Packages = std::map<std::string, Ptr<Package>>;
using Modules = std::map<std::string, std::unique_ptr<llvm::Module>>;

namespace fs = std::filesystem;
[[maybe_unused]] constexpr auto _clangd_fs_used = sizeof(fs::path);
